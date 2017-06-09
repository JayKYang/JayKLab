from socket import *
import time
import datetime
import serial
import multiprocessing
from multiprocessing import Process
BUFSZ = 1024


class Gateway(multiprocessing.Process):
	def __init__(self,host,port):
		self.host=host
		self.port=port

		self.sock = socket(AF_INET, SOCK_STREAM)
		self.sock.connect((self.host,self.port))
	#	threading.Thread(target = self.recv(self.sock)).start()

	def send(self,send_msg):
		self.send_msg = send_msg

	def TCP_readThread(self,sock):
		print("sock open")
		while True:
			try:
				#recv_msg = self.sock.recv(BUFSZ)
                if not self.sock.recv(BUFSZ):
                    print("2")
					break
				else:
                    print("3")
					print ("recv_msg: "+recv_msg.decode('utf-8'))
					LoraComm.send(recv_msg)

				#if recv_msg:
				#print ("recv_msg: "+recv_msg)
			except:
				print("except : Close All")
				self.sock.close()
				return False
	def __del__(self):
		self.sock.close()

class LoRa(multiprocessing.Process):
	def __init__(self,port,baudrate):
		self.port=port
		self.baudrate=baudrate
		self.ser = serial.Serial(self.port,self.baudrate)
	#	threading.Thread(target = self.recv(self.ser)).start()

	def send(self,send_msg):
		self.ser.write(bytes(send_msg,encoding='ascii'))

	def Comm_readThread(self,ser):
		print("Lora open")
		while True:
			recv_msg = ser.readline(BUFSZ)
			if not recv_msg:
				break
			else:
				print ("recv_msg: "+recv_msg('utf-8'))
				TCPComm.send(recv_msg)

	def __del__(self):
		self.ser.close()

if __name__ == "__main__":
	sock_host = "192.168.0.30"
	sock_port = 3545
	ser_port = "/dev/ttyUSB0"
	ser_baud = 115200


	TCPComm = Gateway(sock_host, sock_port)
	LoraComm = LoRa(ser_port, ser_baud)

	TCPThread = Process(target = TCPComm.TCP_readThread(TCPComm.sock)).start()
	TCPThread.join()

	CommThread = Process(target = LoraComm.Comm_readThread(LoraComm.ser)).start()
	CommThread.join()
