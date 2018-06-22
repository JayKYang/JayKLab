'''
fileex3.py 파일 복사
'''
inFp, outFp = None, None
inStr = ""

inFp = open("D:/temp/data1.txt","r")
outFp = open("D:/temp/data3.txt","w")

inList = inFp.readline()
for inStr in inList :
    outFp.writelines(inStr)
inFp.close()
outFp.close()
print("---- 파일 복사 완료 ----")