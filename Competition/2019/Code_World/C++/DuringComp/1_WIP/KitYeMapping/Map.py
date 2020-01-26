# convert output diarrhea into something usable
'''
todo: BORING WHITE FLOOR IS MULT

'''
unexploredcol=-1
unexfloorcol =-2
wallcol=5
whitefloorcol=0
redcol=2
cyancol=3
blackcol=4
specialbluecol =-3
orangecol=1
graycol=9
yellowcol=7
trapbluecol=8
border = 6

cyanrgb=[0,255,255]
redrgb=[255,0,0]
bluergb=[0,0,255]
greenrbg=[0,255,0]
brownrgb=[120,0,0]
orangergb=[255,128,0]
purplergb=[102,0,102]
yellowrgb=[255,255,0]
pinkrgb=[255,0,127]
peachrgb=[255,102,102]
darkcyanrgb=[0,102,102]
whitergb=[255,255,255]
blackrgb=[0,0,0]
grayrgb=[128,128,128]
violetrgb=[153,0,76]
darkgreenrgb=[0,51,0]

colourlist = [\
(unexfloorcol, blackrgb),\
(wallcol,pinkrgb),\
(unexploredcol,whitergb),\
(whitefloorcol,darkcyanrgb),\
(yellowcol,yellowrgb),\
(trapbluecol,darkgreenrgb),\
(orangecol,orangergb),\
(graycol,grayrgb),\
(redcol,redrgb),\
(cyancol,bluergb),\
(blackcol,blackrgb),\
(border,(100,0,0))#Border is red
#(,),\
#(,),\
#(,),\
]
'''
colourlist = [\
(-2, whitergb),\
(5,(100,0,0)),\
(-1,whitergb),\
(whitefloorcol,darkcyanrgb),\
(7,yellowrgb),\
(8,darkgreenrgb),\
(1,orangergb),\
(6,(0,100,0)),\
(9,(100,0,0))\
#(,),\
]
'''
def div(x,y):
    if x%y==0:
        return True
    else:
        return False
from numpy import array
from PIL import Image
rf=open('bit.txt','r')
map1 = list(map(int, rf.read().split()))
for x in range(len(map1)):
    val = False
    # cant coexist colors
    n = map1[x]
    map1[x] = (50,0,0)
    for i, j in colourlist:
            if n == i:
                val = True
                map1[x] = j
                break
    if val:continue
    print(n)

map1 = array(map1)
map1 = map1.reshape(360,270,3)
print((map1[0][0]))
img=Image.fromarray(map1.astype('uint8'), 'RGB')
img = img.transpose(Image.ROTATE_90)
img.show()
input()
