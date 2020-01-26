# convert output diarrhea into something usable
'''
todo: BORING WHITE FLOOR IS MULT

'''
unexploredcol=-1
unexfloorcol =0
wallcol=-2
whitefloorcol=1
redcol=2
cyancol=3
blackcol=5
specialbluecol =7
orangecol=11
graycol=13
yellowcol=17
trapbluecol=19

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
(wallcol,whitergb),\
(unexploredcol,whitergb),\
(whitefloorcol,darkcyanrgb),\
(yellowcol,yellowrgb),\
(trapbluecol,darkgreenrgb),\
(orangecol,orangergb),\
#(,),\
#(,),\
#(,),\
]

colourlist = [\
(-2, whitergb),\
(5,(100,0,0)),\
(-1,whitergb),\
(whitefloorcol,darkcyanrgb),\
(7,yellowrgb),\
(8,darkgreenrgb),\
(1,orangergb),\
(6,(0,100,0)),\
#(,),\
]
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
    for i, j in colourlist:
            if n == i:
                val = True
                map1[x] = j
                break
    if val:continue
    '''
    if n == unexfloorcol:
        map1[x] = blackrgb # unexfloor black
    elif n == wallcol:
        map1[x] = whitergb # wall sth visible idk
    elif n==unexploredcol:
        map1[x] = whitergb # unexplored areas white
    elif n==whitefloorcol:
        map1[x] = darkcyanrgb # boring floor dark green
    elif n==yellowcol:
        map1[x] = yellowrgb  # trap yellow
    elif n==trapbluecol:
        map1[x] = darkgreenrgb  # some cyan trap
    elif n==orangecol:
        map1[x] = orangergb
	'''

    #else:
        # can coexist
    if div(n, graycol):  # gray
            map1[x] = grayrgb
    if div(n, specialbluecol):  # special purple
            map1[x] = purplergb
    
    # can coexist and impt to show
    if div(n,redcol) or div(n,cyancol) or div(n,blackcol): # ok idk how to mix colors other than these
            r = 0
            g = 0
            b = 0
            if div(n, redcol):
                    r = 255
            if div(n, cyancol):
                    g = 255
            if div(n, blackcol):
                    b = 255
            map1[x]=[r,g,b]
            if map1[x]==[255,255,255]:
                    map1[x]=pinkrgb # pink nais color
                    
    if type(map1[x])==int: # oh shit what went wrong
        print(map1[x])
            

map1 = array(map1)
map1 = map1.reshape(360,270,3)
print((map1[0][0]))
img=Image.fromarray(map1.astype('uint8'), 'RGB')
img = img.transpose(Image.ROTATE_90)
img.show()
input()
