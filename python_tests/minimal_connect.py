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


def listen_for_registration(socket):
    """Listen for registration completion"""
    global registered, running
    i = 0
    while not registered and running:
        try:
            i += 1
            response = socket.recv(4096).decode('utf-8')
            print(f"RECEIVED ({i}): {response.strip()}")
            if "003" in response:
                registered = True
                print("Registration complete.")
        except socket.error as e:
            print(f"Socket error: {e}")
            break
        except Exception as e:
            print(f"Error: {e}")
            break


socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect((server, port))
# Start a thread to listen for registration completion
registration_thread = threading.Thread(target=listen_for_registration, args=(socket,))
running = True
registration_thread.start()
# Wait for the thread to start
time.sleep(1)
# Send initial connection commands

print(f"Connected to {server}:{port}")
# RFC 1459: Connection Registration sequence
# 1. PASS command (if password provided) - must be sent before NICK/USER
send_raw(socket, f"PASS {password}")
# 2. NICK command
send_raw(socket, f"NICK {nickname}")
# 3. USER command: USER <username> <hostname> <servername> <realname>
# RFC 1459 format: USER username 0 * :Real Name
send_raw(socket, f"USER {nickname} 0 * :{realname}")
# Start listening for registration completion

print("Exiting program.")
socket.close()
registration_thread.join()
# Exit the program
