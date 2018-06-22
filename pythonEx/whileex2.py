'''
    나라별 수도정보를 dict 형태로 저장하고, 나라이름을 입력받아 수도를 출력하는 프로그램 작성하기
'''

contries = {"한국":"서울","일본":"도쿄","중국":"베이징","미국":"워싱턴"}
while(True) :
    contry = input(str(list(contries.keys())) + " 중 어떤 나라의 수도를 알고 싶으세요?")
    if contry in contries :
        print("<%s> 의 수도는 <%s> 입니다." % (contry, contries.get(contry)))
    elif contry == "끝" :
        contries.pop("미국")
        for k in contries.keys() :
            print("%s --> %s" % (k,contries[k]))
        break
    else :
        print("그런 나라는 없습니다. 입력하시겠습니까<Y/N>?")
        yesno = input();
        if yesno == 'Y' :
            capt = input(contry+"의 수도를 입력하세요 : ")
            contries[contry] = capt