def readMapData(filename="../../World2/w2map.hpp"):
    with open(filename) as f:
        data = f.read()
        start = 0
        for i in range(len(data)):
            if data[i] == "{":
                start = i
                break
        mapdata = data[start:-2].replace(",","").replace("{","").split("}")
        for i in range(len(mapdata)):
            if len(mapdata[i])>0 and mapdata[i][0] == '': mapdata[i][1:]
            mapdata[i] = [int(j) for j in mapdata[i].split(" ") if j !='']
        #for i in mapdata[:4]:print(i,len(i))
        print(len(mapdata[0]),len(mapdata))
    return mapdata

if __name__ == "__main__":
    #import sys
    #sys.path.append('./Python_Libraries/')
    mapdata = readMapData()
    from ImageCalculation import *
    im, pixels = convertBack(mapdata)
    im.show()
