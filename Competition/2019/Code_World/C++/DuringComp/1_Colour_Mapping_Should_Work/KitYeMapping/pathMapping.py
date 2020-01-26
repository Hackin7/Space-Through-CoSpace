from PIL import Image

import sys

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


import Map
    
if __name__ == '__main__':
    print("Show the Path on the Image")
    print("Make sure to compile astar.cpp into astar.exe first")

    coordinates = inputToCoordinates(cppInput(98, 130, 98, 77))
    newImg =  Map.img;
    newPixels = Map.img.load()    
    #newImg, newPixels = convertBack(newMap)
    addCoordinates(coordinates, newPixels,(100,100,0))
    newImg.show()


