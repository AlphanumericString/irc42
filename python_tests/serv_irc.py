#!/usr/bin/env python3
"""
Minimal IRC Server for demonstration purposes
Supports: nicknames, channels, join/quit, private messages
"""

import socket
import threading
import time
from datetime import datetime

class IRCServer:
    def __init__(self, host='localhost', port=6667):
        self.host = host
        self.port = port
        self.clients = {}  # socket -> client info
        self.channels = {}  # channel_name -> set of clients
        self.server_name = "minimal.irc.server"

    def start(self):
        """Start the IRC server"""
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind((self.host, self.port))
        self.socket.listen(5)

        print(f"IRC Server started on {self.host}:{self.port}")

        try:
            while True:
                client_socket, address = self.socket.accept()
                print(f"Connection from {address}")

                client_thread = threading.Thread(
                    target=self.handle_client,
                    args=(client_socket, address)
                )
                client_thread.daemon = True
                client_thread.start()

        except KeyboardInterrupt:
            print("\nShutting down server...")
            self.socket.close()

    def handle_client(self, client_socket, address):
        """Handle individual client connections"""
        client_info = {
            'socket': client_socket,
            'address': address,
            'nickname': None,
            'username': None,
            'realname': None,
            'channels': set(),
            'registered': False
        }

        self.clients[client_socket] = client_info

        try:
            while True:
                data = client_socket.recv(1024).decode('utf-8').strip()
                if not data:
                    break

                print(f"Received from {address}: {data}")
                self.process_message(client_socket, data)

        except Exception as e:
            print(f"Error handling client {address}: {e}")
        finally:
            self.disconnect_client(client_socket)

    def process_message(self, client_socket, message):
        """Process IRC messages from clients"""
        parts = message.split(' ', 1)
        command = parts[0].upper()
        params = parts[1] if len(parts) > 1 else ""

        client = self.clients[client_socket]

        if command == "NICK":
            self.handle_nick(client_socket, params)
        elif command == "USER":
            self.handle_user(client_socket, params)
        elif command == "JOIN":
            self.handle_join(client_socket, params)
        elif command == "PART":
            self.handle_part(client_socket, params)
        elif command == "PRIVMSG":
            self.handle_privmsg(client_socket, params)
        elif command == "QUIT":
            self.handle_quit(client_socket, params)
        elif command == "PING":
            self.send_message(client_socket, f"PONG {self.server_name}")
        else:
            self.send_error(client_socket, "421", f"{command} :Unknown command")

    def handle_nick(self, client_socket, nickname):
        """Handle NICK command"""
        nickname = nickname.strip()
        client = self.clients[client_socket]

        # Check if nickname is already in use
        for other_client in self.clients.values():
            if other_client['nickname'] == nickname and other_client != client:
                self.send_error(client_socket, "433", f"{nickname} :Nickname is already in use")
                return

        old_nick = client['nickname']
        client['nickname'] = nickname

        if old_nick:
            # Notify channels about nick change
            for channel_name in client['channels']:
                self.broadcast_to_channel(channel_name,
                    f":{old_nick} NICK {nickname}", exclude=client_socket)

        # Complete registration if both NICK and USER received
        if client['username'] and not client['registered']:
            self.complete_registration(client_socket)

    def handle_user(self, client_socket, params):
        """Handle USER command"""
        parts = params.split(' ', 3)
        if len(parts) < 4:
            self.send_error(client_socket, "461", "USER :Not enough parameters")
            return

        client = self.clients[client_socket]
        client['username'] = parts[0]
        client['realname'] = parts[3].lstrip(':')

        # Complete registration if both NICK and USER received
        if client['nickname'] and not client['registered']:
            self.complete_registration(client_socket)

    def complete_registration(self, client_socket):
        """Complete client registration"""
        client = self.clients[client_socket]
        client['registered'] = True

        # Send welcome messages
        self.send_message(client_socket,
            f"001 {client['nickname']} :Welcome to {self.server_name}")
        self.send_message(client_socket,
            f"002 {client['nickname']} :Your host is {self.server_name}")
        self.send_message(client_socket,
            f"003 {client['nickname']} :Server created {datetime.now()}")
        self.send_message(client_socket,
            f"004 {client['nickname']} {self.server_name} v1.0 o o")

    def handle_join(self, client_socket, channel_name):
        """Handle JOIN command"""
        channel_name = channel_name.strip()
        if not channel_name.startswith('#'):
            channel_name = '#' + channel_name

        client = self.clients[client_socket]
        if not client['registered']:
            self.send_error(client_socket, "451", ":You have not registered")
            return

        # Add channel if it doesn't exist
        if channel_name not in self.channels:
            self.channels[channel_name] = set()

        # Add client to channel
        self.channels[channel_name].add(client_socket)
        client['channels'].add(channel_name)

        # Notify channel about join
        self.broadcast_to_channel(channel_name,
            f":{client['nickname']} JOIN {channel_name}")

        # Send channel info
        self.send_names_list(client_socket, channel_name)

    def handle_part(self, client_socket, channel_name):
        """Handle PART command"""
        channel_name = channel_name.strip()
        if not channel_name.startswith('#'):
            channel_name = '#' + channel_name

        client = self.clients[client_socket]

        if channel_name in client['channels']:
            # Remove client from channel
            self.channels[channel_name].discard(client_socket)
            client['channels'].discard(channel_name)

            # Notify channel about part
            self.broadcast_to_channel(channel_name,
                f":{client['nickname']} PART {channel_name}")

            # Remove empty channels
            if not self.channels[channel_name]:
                del self.channels[channel_name]

    def handle_privmsg(self, client_socket, params):
        """Handle PRIVMSG command (channel messages and private messages)"""
        parts = params.split(' ', 1)
        if len(parts) < 2:
            self.send_error(client_socket, "461", "PRIVMSG :Not enough parameters")
            return

        target = parts[0]
        message = parts[1].lstrip(':')
        client = self.clients[client_socket]

        if target.startswith('#'):
            # Channel message
            if target in self.channels and client_socket in self.channels[target]:
                self.broadcast_to_channel(target,
                    f":{client['nickname']} PRIVMSG {target} :{message}",
                    exclude=client_socket)
            else:
                self.send_error(client_socket, "404", f"{target} :Cannot send to channel")
        else:
            # Private message
            target_client = self.find_client_by_nick(target)
            if target_client:
                self.send_message(target_client['socket'],
                    f":{client['nickname']} PRIVMSG {target} :{message}")
            else:
                self.send_error(client_socket, "401", f"{target} :No such nick")

    def handle_quit(self, client_socket, reason=""):
        """Handle QUIT command"""
        reason = reason.lstrip(':') if reason else "Client quit"
        client = self.clients[client_socket]

        # Notify all channels the client was in
        for channel_name in client['channels'].copy():
            self.broadcast_to_channel(channel_name,
                f":{client['nickname']} QUIT :{reason}")

        self.disconnect_client(client_socket)

    def disconnect_client(self, client_socket):
        """Clean up when client disconnects"""
        if client_socket in self.clients:
            client = self.clients[client_socket]

            # Remove from all channels
            for channel_name in client['channels'].copy():
                if channel_name in self.channels:
                    self.channels[channel_name].discard(client_socket)
                    if not self.channels[channel_name]:
                        del self.channels[channel_name]

            # Remove client
            del self.clients[client_socket]
            print(f"Client {client['address']} disconnected")

        try:
            client_socket.close()
        except:
            pass

    def find_client_by_nick(self, nickname):
        """Find client by nickname"""
        for client in self.clients.values():
            if client['nickname'] == nickname:
                return client
        return None

    def broadcast_to_channel(self, channel_name, message, exclude=None):
        """Send message to all clients in a channel"""
        if channel_name in self.channels:
            for client_socket in self.channels[channel_name]:
                if client_socket != exclude:
                    self.send_message(client_socket, message)

    def send_names_list(self, client_socket, channel_name):
        """Send list of users in channel"""
        if channel_name in self.channels:
            client = self.clients[client_socket]
            names = []
            for client_sock in self.channels[channel_name]:
                if client_sock in self.clients:
                    names.append(self.clients[client_sock]['nickname'])

            names_str = ' '.join(names)
            self.send_message(client_socket,
                f"353 {client['nickname']} = {channel_name} :{names_str}")
            self.send_message(client_socket,
                f"366 {client['nickname']} {channel_name} :End of NAMES list")

    def send_message(self, client_socket, message):
        """Send message to client"""
        try:
            client_socket.send(f"{message}\r\n".encode('utf-8'))
        except:
            self.disconnect_client(client_socket)

    def send_error(self, client_socket, code, message):
        """Send error message to client"""
        client = self.clients[client_socket]
        nick = client['nickname'] or '*'
        self.send_message(client_socket, f"{code} {nick} {message}")

if __name__ == "__main__":
    server = IRCServer()
    server.start()
