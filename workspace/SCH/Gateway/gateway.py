from socket import *
import time
import datetime

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
            data = raw_input('> ')
            if not data:
                break
            self.sock.send('%s/%s/%s/%s' % (datetime.datetime.strptime(time.ctime(), '%a %b %d %H:%M:%S %Y'), self.GWID, 'EUI', data))
            data = self.sock.recv(self.BUFSIZ)
            if not data:
                break
            print data

        self.sock.close()

if __name__ == "__main__":
    while True:
        host = raw_input("IP : ")
        port = input("Port : ")
        try:
            port = int(port)
            break
        except ValueError:
            pass

    Gateway(host, port).send()

#host = "192.168.x.x"           # Server IP
#port_num = xxxx                # Server Port
#Gateway(host, port).send()     # Start Gateway
