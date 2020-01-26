from PIL import Image

import sys
sys.path.append('./Python_Libraries/')
from ImageCalculation import *

def standardInputLines():
    lines = []
    while True:
        data = input()
        if data == "": break
        lines.append(data)
    return lines

def cppInput(x1, y1, x2, y2):
    #os.system("g++ astar.cpp -o astar.exe") #Compile on the spot
    cmd = os.popen(f'cd AStar && echo {x1} {y1} {x2} {y2} | astar.exe').read()
    #cmd = os.popen(f'echo {x1} {y1} {x2} {y2} | ./astar').read()
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
    imageFile = "ZonedHalf.png"#input('Enter image file: ')
    im = Image.open(imageFile)
    im = resizeImage(im, 360)
    #im.show()
    pixels = im.load()
    print(im.size)

   
    #lines = standardInputLines()

    x1, y1, x2, y2 = 125, 95, 256, 211 #[int(i) for i in input("Enter coordinates in the form x1 y1 x2 y2:").split()]
    #x1, y1 = 30, 30
    lines = cppInput(x1, y1, x2, y2)

    print("Path Length:",len(lines))
    coordinates = inputToCoordinates(lines)

    newMap = switchYValues(mapData(im.size, pixels))
    newImg, newPixels = convertBack(newMap)
    addCoordinates(coordinates, newPixels,(100,100,0))
    newImg.show()


