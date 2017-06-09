from socket import *
import time
import datetime
import serial
import threading

BUFSZ = 1024

class Gateway(object):
	def __init__(self,host,port):

		self.host=host
		self.port=port

		self.sock = socket(AF_INET, SOCK_STREAM)
		self.sock.connect((self.host,self.port))
#		threading.Thread(target = self.recv(self.sock)).start()

	def send(self,send_msg):
		self.send_msg = send_msg

	def recv(self,sock):
		print("sock open")
		while True:
			try:
				print("dd")
				recv_msg = self.sock.recv(BUFSZ)
				if recv_msg:
					print ("recv_msg: "+recv_msg)
			except:
				print("except : Close All")
				self.sock.close()
				return False
	def __del__(self):
		self.sock.close()

class LoRa(object):
	def __init__(self,port,baudrate):
		self.port=port
		self.baudrate=baudrate
		self.ser = serial.Serial(self.port,self.baudrate)
#		threading.Thread(target = self.recv(self.ser)).start()

	def send(self,send_msg):
		self.ser.write(bytes(send_msg,encoding='ascii'))

	def recv(selfa,ser):
		print("Lora open")
		while True:
			recv_msg = ser.readline()
			print(recv_msg)
			if not recv_msg:
				break
			else:
				response = recv_msg
				TCPComm.send(response)
	def __del__(self):
		self.ser.close()

if __name__ == "__main__":
	sock_host = "192.168.0.30"
	sock_port = 3545
	ser_port = "/dev/ttyUSB0"
	ser_baud = 115200

	TCPComm = Gateway(sock_host, sock_port)
	#threading.Thread(target = TCPComm.recv(TCPComm.sock)).start()

	LoraComm = LoRa(ser_port, ser_baud)

	threading.Thread(target = LoraComm.recv(LoraComm.ser)).start()
