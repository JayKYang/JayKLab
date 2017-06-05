import socket
import threading
import MySQLdb

class ThreadedServer(object):
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.host, self.port))
        self.database = MysqlDB()

    def listen(self):
        self.sock.listen(5)
        while True:
            client, address = self.sock.accept()
            client.settimeout(60)
            print ('connect from ', address)
            threading.Thread(target = self.listenToClient,args = (client,address)).start()

    def listenToClient(self, client, address):
        size = 1024
        while True:
            try:
                data = client.recv(size)
                if data:
                    # Set the response to echo back the recieved data 
                    response = data
                    client.send(response)
                    datalist = data.split('/')
                    self.database.insert(datalist[0], datalist[1], datalist[2], datalist[3])
                    print (response)
                else:
                    print('Client disconnected')
                    client.close()
                    return False
            except:
                print('except : Close All')
                client.close()
                self.database.close()
                return False

class MysqlDB(object):
    def __init__(self):
        self.db = MySQLdb.connect(db='luxDB', user='root', passwd='test', host='localhost', port=3306)
        self.cursor = self.db.cursor()

    def insert(self, date, gwid, eui, data):
        self.date = date
        self.gwid = gwid
        self.eui = eui
        self.data = data
        self.cursor.execute('INSERT INTO lux VALUES(NULL,"%s","%s","%s","%s")' % (self.date, self.gwid, self.eui, self.data))
        self.db.commit()

    def close(self):
        self.cursor.close()
        self.db.close()

if __name__ == "__main__":
    while True:
        port_num = input("Port : ")
        try:
            port_num = int(port_num)
            break
        except ValueError:
            pass

    ThreadedServer('',port_num).listen()

# Data Format : ½Ã°£/GW_ID/EUI/data
