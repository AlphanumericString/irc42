#!/usr/bin/env python3
"""
Basic IRC Server compatible with irssi
Supports: joining/leaving channels, nicknames, private messages, basic commands
"""

import socket
import threading
import time
import re
from datetime import datetime

class IRCClient:
    def __init__(self, socket, address, server):
        self.socket = socket
        self.address = address
        self.server = server
        self.nickname = None
        self.username = None
        self.realname = None
        self.hostname = address[0]
        self.channels = set()
        self.registered = False
        self.cap_negotiation = False
        self.cap_end_received = False

    def send(self, message):
        """Send a message to the client"""
        try:
            if not message.endswith('\r\n'):
                message += '\r\n'
            self.socket.send(message.encode('utf-8'))
        except:
            self.disconnect()

    def disconnect(self):
        """Disconnect the client"""
        self.server.remove_client(self)

class IRCChannel:
    def __init__(self, name):
        self.name = name
        self.clients = set()
        self.topic = ""
        self.created = datetime.now()

    def add_client(self, client):
        self.clients.add(client)
        client.channels.add(self.name)

    def remove_client(self, client):
        if client in self.clients:
            self.clients.remove(client)
        if self.name in client.channels:
            client.channels.remove(self.name)

    def broadcast(self, message, exclude=None):
        """Send message to all clients in channel except excluded one"""
        for client in self.clients:
            if client != exclude:
                client.send(message)

class IRCServer:
    def __init__(self, host='localhost', port=6667):
        self.host = host
        self.port = port
        self.clients = {}
        self.channels = {}
        self.server_name = "irc.example.com"
        self.running = False

    def start(self):
        """Start the IRC server"""
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind((self.host, self.port))
        self.socket.listen(5)
        self.running = True

        print(f"IRC Server started on {self.host}:{self.port}")

        while self.running:
            try:
                client_socket, address = self.socket.accept()
                client = IRCClient(client_socket, address, self)
                self.clients[client_socket] = client

                thread = threading.Thread(target=self.handle_client, args=(client,))
                thread.daemon = True
                thread.start()

                print(f"Client connected from {address}")
            except OSError:
                break

    def stop(self):
        """Stop the IRC server"""
        self.running = False
        self.socket.close()

    def remove_client(self, client):
        """Remove client from server"""
        # Remove from all channels
        for channel_name in list(client.channels):
            if channel_name in self.channels:
                channel = self.channels[channel_name]
                channel.remove_client(client)
                # Notify others in channel
                if client.nickname:
                    channel.broadcast(f":{client.nickname}!{client.username}@{client.hostname} QUIT :Client disconnected")
                # Remove empty channels
                if not channel.clients:
                    del self.channels[channel_name]

        # Remove from client list
        if client.socket in self.clients:
            del self.clients[client.socket]

        try:
            client.socket.close()
        except:
            pass

        if client.nickname:
            print(f"Client {client.nickname} disconnected")

    def find_client_by_nick(self, nickname):
        """Find client by nickname"""
        for client in self.clients.values():
            if client.nickname and client.nickname.lower() == nickname.lower():
                return client
        return None

    def handle_client(self, client):
        """Handle messages from a client"""
        buffer = ""

        while self.running:
            try:
                data = client.socket.recv(1024).decode('utf-8')
                if not data:
                    break

                buffer += data

                while '\n' in buffer:
                    line, buffer = buffer.split('\n', 1)
                    line = line.rstrip('\r')

                    if line:
                        self.process_message(client, line)

            except Exception as e:
                print(f"Error handling client: {e}")
                break

        self.remove_client(client)

    def process_message(self, client, message):
        """Process IRC message from client"""
        parts = message.split(' ')
        command = parts[0].upper()

        print(f"Received command: {command} from {client.address}")  # Debug

        if command == 'CAP':
            self.handle_cap(client, parts)
        elif command == 'NICK':
            self.handle_nick(client, parts)
        elif command == 'USER':
            self.handle_user(client, parts)
        elif command == 'JOIN':
            self.handle_join(client, parts)
        elif command == 'PART':
            self.handle_part(client, parts)
        elif command == 'PRIVMSG':
            self.handle_privmsg(client, parts, message)
        elif command == 'QUIT':
            self.handle_quit(client, parts)
        elif command == 'PING':
            self.handle_ping(client, parts)
        elif command == 'WHO':
            self.handle_who(client, parts)
        elif command == 'NAMES':
            self.handle_names(client, parts)
        elif command == 'LIST':
            self.handle_list(client, parts)
        else:
            # Unknown command
            client.send(f":{self.server_name} 421 {client.nickname or '*'} {command} :Unknown command")

    def handle_cap(self, client, parts):
        """Handle CAP (Client Capability) command"""
        if len(parts) < 2:
            return

        subcommand = parts[1].upper()

        if subcommand == 'LS':
            # Client requests capability list
            client.cap_negotiation = True
            # We don't support any capabilities, so send empty list
            client.send(f":{self.server_name} CAP * LS :")
        elif subcommand == 'REQ':
            # Client requests specific capabilities
            if len(parts) > 2:
                caps = ' '.join(parts[2:])
                # We don't support any capabilities, so NAK everything
                client.send(f":{self.server_name} CAP * NAK :{caps}")
            else:
                client.send(f":{self.server_name} CAP * NAK :")
        elif subcommand == 'END':
            # Client ends capability negotiation
            client.cap_negotiation = False
            client.cap_end_received = True
            self.check_registration(client)
        elif subcommand == 'LIST':
            # Client requests active capabilities
            client.send(f":{self.server_name} CAP * LIST :")

    def handle_nick(self, client, parts):
        """Handle NICK command"""
        if len(parts) < 2:
            client.send(f":{self.server_name} 431 :No nickname given")
            return

        new_nick = parts[1]

        # Check if nickname is already in use
        if self.find_client_by_nick(new_nick) and self.find_client_by_nick(new_nick) != client:
            client.send(f":{self.server_name} 433 * {new_nick} :Nickname is already in use")
            return

        old_nick = client.nickname
        client.nickname = new_nick

        if old_nick:
            # Notify all channels about nick change
            for channel_name in client.channels:
                if channel_name in self.channels:
                    channel = self.channels[channel_name]
                    channel.broadcast(f":{old_nick}!{client.username}@{client.hostname} NICK :{new_nick}")

        self.check_registration(client)

    def handle_user(self, client, parts):
        """Handle USER command"""
        if len(parts) < 5:
            client.send(f":{self.server_name} 461 USER :Not enough parameters")
            return

        client.username = parts[1]
        client.realname = ' '.join(parts[4:])[1:]  # Remove leading :

        self.check_registration(client)

    def check_registration(self, client):
        """Check if client is fully registered and send welcome messages"""
        # Client must have nick, username, and either no CAP negotiation or CAP END received
        can_register = (client.nickname and client.username and
                       (not client.cap_negotiation or client.cap_end_received))

        if can_register and not client.registered:
            client.registered = True

            print(f"Registering client: {client.nickname}")  # Debug

            # Send welcome messages
            client.send(f":{self.server_name} 001 {client.nickname} :Welcome to the IRC Network {client.nickname}!{client.username}@{client.hostname}")
            client.send(f":{self.server_name} 002 {client.nickname} :Your host is {self.server_name}")
            client.send(f":{self.server_name} 003 {client.nickname} :This server was created {datetime.now().strftime('%Y-%m-%d')}")
            client.send(f":{self.server_name} 004 {client.nickname} {self.server_name} 1.0 o o")

    def handle_join(self, client, parts):
        """Handle JOIN command"""
        if not client.registered:
            client.send(f":{self.server_name} 451 :You have not registered")
            return

        if len(parts) < 2:
            client.send(f":{self.server_name} 461 JOIN :Not enough parameters")
            return

        channel_names = parts[1].split(',')

        for channel_name in channel_names:
            if not channel_name.startswith('#'):
                channel_name = '#' + channel_name

            # Create channel if it doesn't exist
            if channel_name not in self.channels:
                self.channels[channel_name] = IRCChannel(channel_name)

            channel = self.channels[channel_name]

            # Add client to channel
            channel.add_client(client)

            # Notify all clients in channel
            join_msg = f":{client.nickname}!{client.username}@{client.hostname} JOIN :{channel_name}"
            channel.broadcast(join_msg)

            # Send topic if exists
            if channel.topic:
                client.send(f":{self.server_name} 332 {client.nickname} {channel_name} :{channel.topic}")

            # Send names list
            self.send_names_list(client, channel)

    def handle_part(self, client, parts):
        """Handle PART command"""
        if not client.registered:
            client.send(f":{self.server_name} 451 :You have not registered")
            return

        if len(parts) < 2:
            client.send(f":{self.server_name} 461 PART :Not enough parameters")
            return

        channel_name = parts[1]
        reason = ' '.join(parts[2:])[1:] if len(parts) > 2 else client.nickname

        if channel_name in self.channels and channel_name in client.channels:
            channel = self.channels[channel_name]

            # Notify all clients in channel
            part_msg = f":{client.nickname}!{client.username}@{client.hostname} PART {channel_name} :{reason}"
            channel.broadcast(part_msg)

            # Remove client from channel
            channel.remove_client(client)

            # Remove empty channels
            if not channel.clients:
                del self.channels[channel_name]

    def handle_privmsg(self, client, parts, full_message):
        """Handle PRIVMSG command"""
        if not client.registered:
            client.send(f":{self.server_name} 451 :You have not registered")
            return

        if len(parts) < 3:
            client.send(f":{self.server_name} 461 PRIVMSG :Not enough parameters")
            return

        target = parts[1]
        message = full_message.split(':', 1)[1] if ':' in full_message else ' '.join(parts[2:])

        if target.startswith('#'):
            # Channel message
            if target in self.channels and target in client.channels:
                channel = self.channels[target]
                msg = f":{client.nickname}!{client.username}@{client.hostname} PRIVMSG {target} :{message}"
                channel.broadcast(msg, exclude=client)
            else:
                client.send(f":{self.server_name} 404 {client.nickname} {target} :Cannot send to channel")
        else:
            # Private message
            target_client = self.find_client_by_nick(target)
            if target_client:
                msg = f":{client.nickname}!{client.username}@{client.hostname} PRIVMSG {target} :{message}"
                target_client.send(msg)
            else:
                client.send(f":{self.server_name} 401 {client.nickname} {target} :No such nick/channel")

    def handle_quit(self, client, parts):
        """Handle QUIT command"""
        reason = ' '.join(parts[1:])[1:] if len(parts) > 1 else "Client Quit"

        # Notify all channels
        for channel_name in client.channels:
            if channel_name in self.channels:
                channel = self.channels[channel_name]
                channel.broadcast(f":{client.nickname}!{client.username}@{client.hostname} QUIT :{reason}")

        self.remove_client(client)

    def handle_ping(self, client, parts):
        """Handle PING command"""
        if len(parts) > 1:
            client.send(f":{self.server_name} PONG {self.server_name} :{parts[1]}")
        else:
            client.send(f":{self.server_name} PONG {self.server_name}")

    def handle_who(self, client, parts):
        """Handle WHO command"""
        if len(parts) < 2:
            return

        target = parts[1]

        if target.startswith('#') and target in self.channels:
            channel = self.channels[target]
            for c in channel.clients:
                client.send(f":{self.server_name} 352 {client.nickname} {target} {c.username} {c.hostname} {self.server_name} {c.nickname} H :0 {c.realname}")
            client.send(f":{self.server_name} 315 {client.nickname} {target} :End of WHO list")

    def handle_names(self, client, parts):
        """Handle NAMES command"""
        if len(parts) > 1:
            channel_name = parts[1]
            if channel_name in self.channels:
                channel = self.channels[channel_name]
                self.send_names_list(client, channel)
        else:
            # Send names for all channels
            for channel in self.channels.values():
                if channel.name in client.channels:
                    self.send_names_list(client, channel)

    def send_names_list(self, client, channel):
        """Send names list for a channel"""
        names = [c.nickname for c in channel.clients]
        names_str = ' '.join(names)
        client.send(f":{self.server_name} 353 {client.nickname} = {channel.name} :{names_str}")
        client.send(f":{self.server_name} 366 {client.nickname} {channel.name} :End of NAMES list")

    def handle_list(self, client, parts):
        """Handle LIST command"""
        client.send(f":{self.server_name} 321 {client.nickname} Channel :Users  Name")
        for channel in self.channels.values():
            client.send(f":{self.server_name} 322 {client.nickname} {channel.name} {len(channel.clients)} :{channel.topic}")
        client.send(f":{self.server_name} 323 {client.nickname} :End of LIST")

if __name__ == "__main__":
    server = IRCServer()
    try:
        server.start()
    except KeyboardInterrupt:
        print("\nShutting down server...")
        server.stop()
