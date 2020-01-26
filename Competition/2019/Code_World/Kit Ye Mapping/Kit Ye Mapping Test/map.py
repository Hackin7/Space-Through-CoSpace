# convert output diarrhea into something usable
from numpy import array
from PIL import Image
rf=open('bit.txt','r')
map1 = list(map(int, rf.read().split()))
for x in range(len(map1)):
    if map1[x] == 0:
        map1[x] = [255, 0, 0] # unknown areas red
    elif map1[x] == 1:
        map1[x] = [0, 0, 0] # black explored
    elif map1[x] == -1:
        map1[x] = [255, 255, 255]

map1 = array(map1)
map1 = map1.reshape(270,480,3)
print(map1)
img=Image.fromarray(map1.astype('uint8'), 'RGB')
img.show()
input()
