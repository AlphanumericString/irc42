import socket
import threading
import time

class SimpleIRCClient:
    def __init__(self, server, port, nickname, channel, password=None, realname=None):
        self.server = server
        self.port = port
        self.nickname = nickname
        self.channel = channel
        self.password = password
        self.realname = realname or nickname
        self.socket = None
        self.running = False
        self.registered = False

    def connect(self):
        """Connect to the IRC server following RFC 1459"""
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.server, self.port))
            print(f"Connected to {self.server}:{self.port}")
            # RFC 1459: Connection Registration sequence
            # 1. PASS command (if password provided) - must be sent before NICK/USER
            if self.password:
                self.send_raw(f"PASS {self.password}")
            # 2. NICK command
            self.send_raw(f"NICK {self.nickname}")
            # 3. USER command: USER <username> <hostname> <servername> <realname>
            # RFC 1459 format: USER username 0 * :Real Name
            self.send_raw(f"USER {self.nickname} 0 * :{self.realname}")
            # Start listening for registration completion
            self.running = True
            return True
        except Exception as e:
            print(f"Connection failed: {e}")
            return False

    def send_raw(self, message):
        """Send raw IRC command"""
        if self.socket:
            full_message = message + "\r\n"
            self.socket.send(full_message.encode('utf-8'))
            print(f"SENT: {message}")

    def join_channel(self, channel):
        """Join an IRC channel"""
        if not channel.startswith('#'):
            channel = '#' + channel
        self.send_raw(f"JOIN {channel}")

    def send_message(self, channel, message):
        """Send message to channel"""
        if not channel.startswith('#'):
            channel = '#' + channel
        self.send_raw(f"PRIVMSG {channel} :{message}")

    def listen(self):
        """Listen for incoming messages"""
        buffer = ""
        while self.running:
            try:
                data = self.socket.recv(4096).decode('utf-8', errors='ignore')
                if not data:
                    break
                buffer += data
                lines = buffer.split('\r\n')
                buffer = lines[-1]  # Keep incomplete line in buffer
                for line in lines[:-1]:
                    print(f"client rec line: {line}")
                    if line:
                        self.handle_message(line)
            except Exception as e:
                print(f"Listen error: {e}")
                break

    def handle_message(self, message):
        """Handle incoming IRC messages per RFC 1459"""
        print(f"RECV: {message}")
        # Handle PING to stay connected (RFC 1459 section 4.6.2)
        if message.startswith('PING'):
            pong_response = message.replace('PING', 'PONG', 1)
            self.send_raw(pong_response)
            return
        # Parse numeric replies and server messages
        parts = message.split(' ')
        # Check for registration completion (RPL_WELCOME = 001)
        if len(parts) >= 2 and parts[1] == '001':
            print("*** Registration successful! ***")
            self.registered = True
            # Now we can join channels
            if self.channel:
                self.join_channel(self.channel)
            return
        # Handle common numeric replies per RFC 1459
        numeric_replies = {
            '002': 'RPL_YOURHOST',
            '003': 'RPL_CREATED',
            '004': 'RPL_MYINFO',
            '005': 'RPL_BOUNCE',
            '251': 'RPL_LUSERCLIENT',
            '252': 'RPL_LUSEROP',
            '253': 'RPL_LUSERUNKNOWN',
            '254': 'RPL_LUSERCHANNELS',
            '255': 'RPL_LUSERME',
            '332': 'RPL_TOPIC',
            '353': 'RPL_NAMREPLY',
            '366': 'RPL_ENDOFNAMES',
            '372': 'RPL_MOTD',
            '375': 'RPL_MOTDSTART',
            '376': 'RPL_ENDOFMOTD',
            '422': 'ERR_NOMOTD'
        }
        if len(parts) >= 2 and parts[1] in numeric_replies:
            reply_name = numeric_replies[parts[1]]
            if parts[1] in ['332', '353']:  # Topic and names
                print(f"*** {reply_name}: {' '.join(parts[3:])}")
            return
        # Handle errors
        error_replies = {
            '401': 'ERR_NOSUCHNICK',
            '403': 'ERR_NOSUCHCHANNEL',
            '404': 'ERR_CANNOTSENDTOCHAN',
            '431': 'ERR_NONICKNAMEGIVEN',
            '432': 'ERR_ERRONEUSNICKNAME',
            '433': 'ERR_NICKNAMEINUSE',
            '461': 'ERR_NEEDMOREPARAMS',
            '462': 'ERR_ALREADYREGISTRED',
            '464': 'ERR_PASSWDMISMATCH'
        }
        if len(parts) >= 2 and parts[1] in error_replies:
            error_name = error_replies[parts[1]]
            error_msg = ' '.join(parts[3:]).lstrip(':')
            print(f"*** ERROR {parts[1]} ({error_name}): {error_msg}")
            
            # Handle nickname in use
            if parts[1] == '433':
                new_nick = self.nickname + '_'
                print(f"*** Trying new nickname: {new_nick}")
                self.nickname = new_nick
                self.send_raw(f"NICK {self.nickname}")
            return
        
        # Handle JOIN messages
        if 'JOIN' in message and ':' in message:
            try:
                nick = message.split('!')[0].lstrip(':')
                channel = message.split('JOIN')[1].strip().lstrip(':')
                if nick == self.nickname:
                    print(f"*** You joined {channel}")
                else:
                    print(f"*** {nick} joined {channel}")
            except:
                pass
            return
        
        # Handle PART messages  
        if 'PART' in message:
            try:
                nick = message.split('!')[0].lstrip(':')
                channel = message.split('PART')[1].split(':')[0].strip()
                print(f"*** {nick} left {channel}")
            except:
                pass
            return
        
        # Handle QUIT messages
        if 'QUIT' in message:
            try:
                nick = message.split('!')[0].lstrip(':')
                quit_msg = message.split(':', 2)[-1] if ':' in message else ""
                print(f"*** {nick} quit ({quit_msg})")
            except:
                pass
            return
        
        # Handle PRIVMSG (channel messages and private messages)
        if 'PRIVMSG' in message:
            try:
                # RFC 1459 format: :nick!user@host PRIVMSG target :message
                if message.startswith(':') and '!' in message:
                    sender_full = message.split(' ')[0][1:]  # Remove leading ':'
                    sender_nick = sender_full.split('!')[0]
                    
                    msg_parts = message.split(' ', 3)
                    if len(msg_parts) >= 4:
                        target = msg_parts[2]
                        msg_content = msg_parts[3][1:]  # Remove leading ':'
                        
                        if target.startswith('#'):
                            # Channel message
                            print(f"[{target}] <{sender_nick}> {msg_content}")
                        else:
                            # Private message
                            print(f"*{sender_nick}* {msg_content}")
            except Exception as e:
                print(f"Error parsing PRIVMSG: {e}")
            return
    
    def start(self):
        """Start the IRC client"""
        if not self.connect():
            return
        # Start listening thread
        listen_thread = threading.Thread(target=self.listen, daemon=True)
        listen_thread.start()
        print(f"IRC Client started! Connecting as {self.nickname}")
        print("Waiting for registration...")
        # Wait for registration to complete
        timeout = 30  # 30 second timeout
        start_time = time.time()
        while not self.registered and self.running and (time.time() - start_time) < timeout:
            time.sleep(0.1)
        if not self.registered:
            print("Registration failed or timed out!")
            self.disconnect()
            return
        print("Commands:")
        print("  /msg <message>     - Send message to current channel")
        print("  /join <channel>    - Join another channel") 
        print("  /part [channel]    - Leave channel")
        print("  /privmsg <nick> <msg> - Send private message")
        print("  /nick <newnick>    - Change nickname")
        print("  /quit [message]    - Quit client")
        print()
        
        # Main input loop
        try:
            while self.running:
                user_input = input().strip()
                
                if not user_input:
                    continue
                    
                if user_input.startswith('/quit'):
                    quit_msg = user_input[5:].strip() or "Goodbye!"
                    self.send_raw(f"QUIT :{quit_msg}")
                    break
                elif user_input.startswith('/msg '):
                    message = user_input[5:]
                    if self.channel:
                        self.send_message(self.channel, message)
                elif user_input.startswith('/join '):
                    new_channel = user_input[6:].strip()
                    self.join_channel(new_channel)
                elif user_input.startswith('/part'):
                    parts = user_input.split(' ', 1)
                    channel = parts[1] if len(parts) > 1 else self.channel
                    if channel:
                        self.send_raw(f"PART {channel}")
                elif user_input.startswith('/privmsg '):
                    parts = user_input[9:].split(' ', 1)
                    if len(parts) >= 2:
                        nick, message = parts
                        self.send_raw(f"PRIVMSG {nick} :{message}")
                elif user_input.startswith('/nick '):
                    new_nick = user_input[6:].strip()
                    if new_nick:
                        self.send_raw(f"NICK {new_nick}")
                        self.nickname = new_nick
                elif user_input.startswith('/'):
                    print("Unknown command. Available commands: /msg, /join, /part, /privmsg, /nick, /quit")
                elif self.channel:
                    # Default: send to current channel
                    self.send_message(self.channel, user_input)
                else:
                    print("No channel joined. Use /join <channel> first.")
                    
        except KeyboardInterrupt:
            pass
        
        self.disconnect()
    
    def disconnect(self):
        """Disconnect from server"""
        self.running = False
        if self.socket:
            self.send_raw("QUIT :Goodbye!")
            self.socket.close()
        print("Disconnected from IRC server")

# Example usage
if __name__ == "__main__":
    # Configuration - modify these values
    SERVER = "localhost" # local host
    PORT = 6667
    NICKNAME = "toto"     # Change to your desired nickname
    CHANNEL = ""           # Channel to join
    PASSWORD = "toto42" # Server password (if required)
    REALNAME = "Test IRC Client"  # Real name field

    # Create and start IRC client
    client = SimpleIRCClient(SERVER, PORT, NICKNAME, CHANNEL, PASSWORD, REALNAME)
    client.start()
