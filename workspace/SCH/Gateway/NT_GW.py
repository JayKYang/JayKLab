import socket
import time
import datatime
import serial
import threading

sock_host = "192.168.0.30"
sock_self.port = 3545
sock_BUFSZ = 1024

class Gateway(object):
	def eth_open(self):
		sock = socket(AF_INET, SOCK_STREAM)
		sock.connect((sock_host,sock_port))
		threading.Thread(target = self.recv).start()
	def send(self,send_msg):
		if not send_msg:
			break

	def recv(self):
		while True:
			try:
				recv_msg = self.sock.recv(sock_BUFSZ)
				if recv_msg:
					response = data
					client.send
	
if __name__ == "__main__":
	ser_port = "/dev/ttyUSB0"
	ser_baud = "115200"
		
	Gateway()

	while True:
	


