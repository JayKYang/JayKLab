'''
fileex4
'''
inFp = None
inStr = ""
inFp = open("D:/temp/data4.txt", "r", encoding="utf-8")
while True :
    inStr = inFp.readline()
    if inStr =="":
        break
    print(inStr,end="")
    
inFp.close()
