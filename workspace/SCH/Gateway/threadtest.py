from socket import *
import threading
import time
import datetime
import serial


BUFSZ = 1024
exit_serThread = False # for exit threading

class Gateway(object):
	def __init__(self,host,port):
		threading.Thread.__init__(self)
		self.host=host
		self.port=port

		self.sock = socket(AF_INET, SOCK_STREAM)
		self.sock.connect((self.host,self.port))
	#	threading.Thread(target = self.recv(self.sock)).start()

	# signal func from threading for exit
	def handler(signum, frame):
		exitThread = True

	def Thread_Comm(ser):
		print("sock open")
		global exit_serThread

		while not exitThread:
			#exist data
			try:
				#recv_msg = self.sock.recv(BUFSZ)
				if not self.sock.recv(BUFSZ):
					break
				else:
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

class LoRa(object):
	def __init__(self,port,baudrate):
		threading.Thread.__init__(self)
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

#	TCPThread = threading.Thread(target = TCPComm.TCP_readThread(TCPComm.sock))
#	TCPThread.start()
#	TCPThread.join()

#	CommThread = threading.Thread(target = LoraComm.Comm_readThread(LoraComm.ser))
#	CommThread.start()
#	CommThread.join()
