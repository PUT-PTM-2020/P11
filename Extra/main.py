import tkinter as tk
import socket
import sys

PORT = 3333
IP_VERSION = 'IPv4'
IPV4 = '192.168.18.62'
family_addr = socket.AF_INET
host = IPV4

try:
    sock = socket.socket(family_addr, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 2)
    sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
except socket.error as msg:
    print('Could not create socket: ' + str(msg[0]) + ': ' + msg[1])
    sys.exit(1)

try:
    sock.connect((host, PORT))
except socket.error as msg:
    print('Could not open socket: ', msg)
    sock.close()
    sys.exit(1)

key_down = False

window = tk.Tk()

def handle_keypress(event):
    global key_down, sock
    if key_down:
        return
    key_down = True
    
    if event.char == 'a':
        sock.sendall("C3 ".encode())
    if event.char == 'q':
        sock.sendall("CS3".encode())
    if event.char == 's':
        sock.sendall("D3 ".encode())
    if event.char == 'w':
        sock.sendall("DS3".encode())
    if event.char == 'd':
        sock.sendall("E3 ".encode())
    if event.char == 'f':
        sock.sendall("F3 ".encode())
    if event.char == 'r':
        sock.sendall("FS3".encode())
    if event.char == 'g':
        sock.sendall("G3 ".encode())
    if event.char == 't':
        sock.sendall("GS3".encode())
    if event.char == 'h':
        sock.sendall("A3 ".encode())
    if event.char == 'y':
        sock.sendall("AS3".encode())
    if event.char == 'j':
        sock.sendall("H3 ".encode())
    if event.char == 'k':
        sock.sendall("C4 ".encode())

def handle_keyrelease(event):
    global key_down, sock
    key_down = False
    sock.sendall("pp ".encode())

window.bind("<KeyPress>", handle_keypress)
window.bind("<KeyRelease>", handle_keyrelease)

window.mainloop()
sock.close()