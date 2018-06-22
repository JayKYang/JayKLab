'''
dist 자료형과 list 자료형
'''
import operator

tranDic, TranList = {},[]
tranDic = {"Thomas":"토마스" , "Edward":"에드워드", "Henry":"헨리", "Gothen":"고든", "James":"제임스"}
#key = operatior.itemgetter(0) : 정렬의 기준 설정
tranList = sorted(tranDic.items(),key=operator.itemgetter(0))
print(tranList)
tranList = sorted(tranDic.items(),key=operator.itemgetter(1))
print(tranList)
