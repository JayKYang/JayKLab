'''
    File 접근 예제
'''
inFp = None
inStr = ""
inFp = open("D:/temp/data1.txt", "r")
while True :
    inStr = inFp.readline()
    if inStr =="":
        break
    print(inStr,end="")
    
inFp.close()

print("*** List로 읽기 ***")
inFp = open("D:/temp/data1.txt", "r")
inList =inFp.readline() # 한꺼번에 읽어 List 형태로 저장
print(inList)
print()
for inStr in inList:
    print(inStr,end="")
inFp.close()