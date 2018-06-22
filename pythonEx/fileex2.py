'''
fileex2.py
'''
outFp = None
outStr = ""

outFp = open("D:/temp/data2.txt", "w")
while True:
    outStr = input("내용 입력 : ")
    if outStr != "":
        outFp.writelines(outStr + "\n")
    else :
        break
outFp.close()
print("-----------파일 저장 완료-------------")