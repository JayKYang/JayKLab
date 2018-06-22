'''
ifex2.py : if 구문 예제
'''

score = int(input("점수를 입력하세요(0 ~ 100):"))

# if score >= 90:
#     print("A")
# else :
#     if score >= 80:
#         print("B")
#     else :
#         if score >= 70:
#             print("C")
#         else :
#             if score >= 60:
#                 print("D")
#             else:
#                 print("F")
#                 
# print("학점입니다.")


if score >= 90:
    print("A")
elif score >= 80:
    print("B")
elif score >= 70:
    print("C")
elif score >= 60:
    print("D")
else :
    print("F")
print("학점 입니다.")