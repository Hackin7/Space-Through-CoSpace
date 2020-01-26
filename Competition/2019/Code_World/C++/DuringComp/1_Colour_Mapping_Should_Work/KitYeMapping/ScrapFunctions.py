def reshape(arr, width, height):
    newArr = [ [0 for j in range(height)] for i in range(width)]
    for i in range(len(arr)):
        newArr[i%width][i//width] = arr[i]
    return newArr
rf=open('bit.txt','r')
data = list(map(int, rf.read().split()))
rf.close()

f=open('./AStar/map.hpp','w')
f.write("const int width = 360, height = 270;int map[360][270] = "+str(reshape(data, 360, 270)).replace("[","{").replace("]","}")+";")
f.close()
