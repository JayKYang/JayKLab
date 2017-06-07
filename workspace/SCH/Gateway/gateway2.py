from socket import *
import time
import datetime
import serial

class Gateway(object):
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.GWID = 'GW-ID'
        self.BUFSIZ = 1024
        self.sock = socket(AF_INET, SOCK_STREAM)
        self.sock.connect((self.host, self.port))

    def send(self):
        while True:
            data = input('> ')
            print(data)
            if not data:
                break
            #self.sock.send(data)
            #self.sock.send('%s/%s/%s/%s' % (datetime.datetime.strptime(time.ctime(), '%a %b %d %H:%M:%S %Y'), self.GWID, 'EUI', data))
            self.sock.send(data)
            #self.sock.send('%s' % (data))
            data = self.sock.recv(self.BUFSIZ)
            if not data:
                break

        self.sock.close()

class Lora(object):
	def __init__(self, port, baud):
		self.port = port
		self.baud = baud
		self.Lora = serial.Serial(self.port, self.baud, timeout=1) 

	def open(self):
		Lora.open()
		Lora.write("test")

if __name__ == "__main__":
    while True:
        eth_host = "192.168.0.30"  
        eth_port = "3545"
        ser_port = "/dev/ttyUSB0"
        ser_baud = "115200"
        try:
            eth_port = int(eth_port)
            break
        except ValueError:
            pass

    Gateway(eth_host, eth_port).send()
    Lora(ser_port,ser_baud).open()


#host = "192.168.x.x"           # Server IP
#port_num = xxxx                # Server Port
#Gateway(host, port).send()     # Start Gateway
