from socket import *
import time
import datetime
import serial
import threading

BUFSZ = 1024
sock_host = "192.168.0.30"
sock_port = 3545
ser_port = "/dev/ttyUSB0"
ser_baud = 115200

def sock_send(send_msg):
	sock.send(send_msg)

def sock_recv(sock):
	print("sock open")
	while True:
		try:
			print("check1")
			#recv_msg = sock.recv(BUFSZ)
			recv_msg = ser.readline()
			if recv_msg:
				print ("recv_msg: " + recv_msg)
		except:
			print("except : Close All")
			sock.close()
			return False




def ser_send(send_msg):
	ser.write(bytes(send_msg,encoding='ascii'))

def ser_recv(ser):
	print("Lora open")
	while True:
		recv_msg = ser.read(BUFSZ)
		print(bytes(recv_msg))
		try:
			if not recv_msg:
				pass
			else:
				response = recv_msg
				TCPComm.send(response)
		except:
			print("except : Close Ser")
			ser.close()
			return False

# socket open
sock = socket(AF_INET, SOCK_STREAM)
sock.connect((sock_host,sock_port))

# serial open
ser = serial.Serial(ser_port,ser_baud)

#threading.Thread(target = sock_recv(sock)).start()
#ser_recv(ser)
#threading.Thread(target = ser_recv(ser)).start()




ser.close()
