#!/usr/bin/env python

from PIL import Image

X_WIDTH = 320
Y_HEIGHT = 240

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
    
def generateAdjMatrix(x,y):
    #Order 12345
    #      6789...
    adjMatrix = [[0 for i in range(x)] for j in range(y)]
    return adjMatrix
            

    
def linkAll(adjMatrix, x=0, y=0): # Pass by Reference
    #Link horizontally
    for row in range(y):
        for pixel in range(x-1):
            modifyAdjMatrix(adjMatrix, row*x+pixel, row*x+pixel+1, 1)
    #Link vertically
    for row in range(y-1):
        for col in range(x):
            modifyAdjMatrix(adjMatrix, row*y+col, (row+1)*col, 1)
    print(adjMatrix)

class adjMatrix:
    def __init__(self):
        self.width = 320
        self.height = 240
        self.nodes = self.width * self.height
        self.adjMatrix =  [[0 for i in range(self.nodes)] for j in range(self.nodes)]
    def get(self):
        return self.adjMatrix
    def display(self):
        for i in range(len(self.adjMatrix)):
            print(self.adjMatrix[i])
    def coordinatesToPos(self,x,y):
        return y*self.width + x
    def modifyAdjMatrix(self, pos1, pos2, val):
        self.adjMatrix[pos1][pos2] = val
        self.adjMatrix[pos2][pos1] = val
    def linkAll(self):
        for row in range(self.height):
            for pixel in range(self.width-1):
                self.modifyAdjMatrix(self.coordinatesToPos(pixel,row), self.coordinatesToPos(pixel+1,row), 1)
        for col in range(self.width):
            for row in range(self.height-1):
                self.modifyAdjMatrix(self.coordinatesToPos(col,row), self.coordinatesToPos(col,row+1), 1)
        '''
        #Link vertically
        for row in range(y-1):
            for col in range(x):
                self.modifyAdjMatrix(adjMatrix, row*y+col, (row+1)*col, 1)
        '''
        
mapping = adjMatrix()
mapping.linkAll()
mapping.display()

def main(args):
    #im = Image.open(input('Enter image file: '))
    #im = resizeImage(im, X_WIDTH,Y_HEIGHT)
    #pix_val = list(im.getdata())
    #print(im.size)
    #adjMatrix = [[0 for i in range(10)] for j in range(10)]
    #linkAll(adjMatrix)
    #print(adjMatrix)
    #print(pix_val)
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
