import socket
import threading
import time

SERVER = "localhost" # local host
PORT = 6667
NICKNAME = "toto"     # Change to your desired nickname
CHANNEL = ""           # Channel to join
PASSWORD = "toto42" # Server password (if required)
REALNAME = "Test IRC Client"  # Real name field

server = SERVER
port = PORT
nickname = NICKNAME
channel = CHANNEL
password = PASSWORD
realname = REALNAME or NICKNAME
# socket = None
running = False
registered = False

def send_raw(socket, message):
    """Send raw IRC command"""
    if socket:
        full_message = message + "\r\n"
        socket.send(full_message.encode('utf-8'))
        print(f"SENT: {message}")


socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect((server, port))

print(f"Connected to {server}:{port}")
# RFC 1459: Connection Registration sequence
# 1. PASS command (if password provided) - must be sent before NICK/USER
if password:
    send_raw(socket, f"PASS {password}")
# 2. NICK command
send_raw(socket, f"NICK {nickname}")
# 3. USER command: USER <username> <hostname> <servername> <realname>
# RFC 1459 format: USER username 0 * :Real Name
send_raw(socket, f"USER {nickname} 0 * :{realname}")
# Start listening for registration completion
running = True
