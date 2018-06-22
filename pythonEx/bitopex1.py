'''
    bitopex1.py : 비트 연산자 
'''
from test.test_long import MASK

a=ord('A')
mask=0x0F
print("%x & %x = %x" % (a,mask,a&mask))
'''
    a : 01000001
 mask : 00001111
 ----------------
        00000001
'''
print("%x | %x = %x" % (a,mask,a|mask))
'''
    a : 01000001
 mask : 00001111
 ----------------
        01001111
'''
mask = ord('a') - ord('A')
print("%d" % mask)
'''
    'a' : 01100001
    'A' : 01000001
    mask: 00100000
'''
b= a^mask
'''
      a : 01000001 'A' 
    mask: 00100000
-------------------
    b   : 01100001 'a' 
'''

print("%c ^ %d = %c" % (a,mask,b))
'''
      b : 01100001 'a' 
    mask: 00100000
-------------------
      a : 01000001 'A' 
'''
a=b^mask
print("%c ^ %d = %c" % (a,mask,b))
