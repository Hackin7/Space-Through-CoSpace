from PIL import Image

def resizeImage(img, x=0, y=0):
    if x == 0 and y == 0:
        return None
    elif x == 0:
        hpercent = (y/float(img.size[1]))
        x = int((float(img.size[0])*float(hpercent)))
    elif y == 0:
        wpercent = (x/float(img.size[0]))
        y = int((float(img.size[1])*float(wpercent)))
    return img.resize((x,y), Image.ANTIALIAS)    
    
def mapData(size, pixels):
    data = [[0 for y in range(size[1])] for x in range(size[0])]
    #For a path
    for x in range(size[0]):
        for y in range(size[1]):
            if pixels[x,y] == (0,168,243): #Light Blue 
                data[x][y] = 3
            if pixels[x,y] == (0,0,0): 
                data[x][y] = 1
                margin = 10
                #generate Margin around area to prevent collision with walls and stuff
                for m in range(1,margin):
                    for n in range(1, margin):
                        if x+m < size[0]:
                            if y+n < size[1]:
                                if pixels[x+m,y+n] != (0,0,0):  data[x+m][y+n] = 2
                            if y-n > 0:
                                if pixels[x+m,y-n] != (0,0,0):  data[x+m][y-n] = 2
                        if x+m > 0:
                            if y+n < size[1]:
                                if pixels[x-m,y+n] != (0,0,0):  data[x-m][y+n] = 2
                            if y-n > 0:
                                if pixels[x-m,y-n] != (0,0,0):  data[x-m][y-n] = 2
    return data

def switchYValues(data):
    newData = []
    for x in range(len(data)):
        yval = [0 for i in range(len(data[0]))]
        for y in range(len(data[0])):
            yval[y] = data[x][-y-1]
        newData.append(yval)
    return newData

def convertBack(data):
    img = Image.new('RGB', (len(data), len(data[0])), (255,255,255))
    pixels = img.load()
    for i in range(len(data)):
        for j in range(len(data[i])):
            if data[i][-j-1] == 1:
                pixels[i,j] = (0,0,0)
            if data[i][-j-1] == 2:
                pixels[i,j] = (100,0,0)
            if data[i][-j-1] == 3:
                pixels[i,j] = (0,168,243)
    return img, pixels

def standardInputLines():
    lines = []
    while True:
        data = input()
        if data == "": break
        lines.append(data)
    return lines

def cppInput(x1, y1, x2, y2):
    #os.system("g++ astar.cpp -o astar.exe") #Compile on the spot
    cmd = os.popen(f'echo {x1} {y1} {x2} {y2} | astar.exe').read()
    lines = cmd.split("\n")
    return lines[:-1]
    
def inputToCoordinates(lines):
    coordinates = []
    for line in lines:
        coordinates.append( [int(i) for i in line.split()] )
    return coordinates
    
def addCoordinates(coordinates, pixels, colour):
    for x,y in coordinates:
        pixels[x,-y-1] = colour

import os
    
if __name__ == '__main__':
    print("Show the Path on the Image")
    print("Make sure to compile astar.cpp into astar.exe first")
    imageFile = "Simplified.png"#input('Enter image file: ')
    im = Image.open(imageFile)
    im = resizeImage(im, 360)
    #im.show()
    pixels = im.load()
    print(im.size)

   
    #lines = standardInputLines()

    x1, y1, x2, y2 = 98, 130, 300, 190 #[int(i) for i in input("Enter coordinates in the form x1 y1 x2 y2:").split()]
    lines = cppInput(x1, y1, x2, y2)

    print("Path Length:",len(lines))
    coordinates = inputToCoordinates(lines)

    newMap = switchYValues(mapData(im.size, pixels))
    newImg, newPixels = convertBack(newMap)
    addCoordinates(coordinates, newPixels,(255,0,0))
    newImg.show()

