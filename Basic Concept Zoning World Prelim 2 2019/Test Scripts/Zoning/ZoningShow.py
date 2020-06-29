from tkinter import *
from tkinter.filedialog import askopenfilename
from PIL import Image
from PIL import ImageTk
from PIL import ImageGrab
from ctypes import windll #Makes app DPI Aware
user32 = windll.user32
user32.SetProcessDPIAware()

###Drawing Path
text_ids=[]

import sys,os
from sys import stdin, stdout
sys.path.append('../Python_Libraries/')

from ImageCalculation import *

#from PreprocessedMap import data
from hppToMap import readMapData
data = readMapData("../../World2/w2map.hpp")
def imageObj(im, pixels):
    print(stack)
    lines = cppInput(stack[0],stack[1],stack[2],stack[3])
    coordinates = inputToCoordinates(lines)
    newMap = data#switchYValues(mapData(im.size, pixels))
    newImg, newPixels = convertBack(newMap)
    addCoordinates(coordinates, newPixels,(100,100,0))
    return newImg

if __name__ == "__main__":
    root = Tk()

    im, pixels = convertBack(data)
    widths, heights = im.size
    img=ImageTk.PhotoImage(im)
    
    #setting up a tkinter canvas with scrollbars
    frame = Frame(root, bd=2, relief=SUNKEN,height=heights,width=widths)
    frame.grid_rowconfigure(0, weight=1)
    frame.grid_columnconfigure(0, weight=1)
    canvas = Canvas(frame, bd=0)
    canvas.grid(row=0, column=0, sticky=N+S+E+W)
    frame.pack(fill=BOTH,expand=1)

    #adding the image
    canvasImage = canvas.create_image(0,0,image=img,anchor="nw")
    # canvas.config(scrollregion=canvas.bbox(ALL))

    zoneMapping = {}
    zones = []
    with open("zone.txt") as f:
        for line in f:
            if " " in line:
                x,y,node=map(int,line.split())
                zoneMapping[x,y] = node
                
                x = x/(360/widths)
                y = (heights-y)/(270/heights)
                if node not in zones:
                    zones.append(node)
                    text_id = canvas.create_text(x-15,y-10,text=str(node),font = "Times 20 bold")

    print(zones)

    with open("../../World2/zones.hpp", "w") as f:
        w, h = 360,270
        zoneData = [[0 for j in range(h)] for i in range(w)]
        for i in range(w):
            for j in range(h):
                try:
                    zoneData[i][j] = zoneMapping[i,j]
                except: pass#print("failed:",i,j)
        print(len(zoneData), len(zoneData[0]))
        f.write(f"int zones[width][height] = {str(zoneData).replace('[','{').replace(']','}')};")
            
    #mouseclick event
    def printZone(event):
        x = round(event.x/(widths/360))
        y = round((heights-event.y)/(heights/270))
        print("Zone No:",zoneMapping[x,y])
        pass
    canvas.bind("<Button 1>",printZone)
    root.mainloop()
	
	
	
	
	
	
	
