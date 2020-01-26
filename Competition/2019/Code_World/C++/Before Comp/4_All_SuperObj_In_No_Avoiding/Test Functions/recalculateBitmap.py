from PIL import Image, ImageDraw

from PreprocessedMap import data

colourData = [(1, (0,255,0)),\
              (2, (255,0,0)),\
              (3, (0,0,255)),\
              (4, (0,168,243)),\
              (5, (0,0,0)),\
              (6, (100,0,0)),\
              ]
img = Image.new('RGB', (len(data), len(data[0])), (255,255,255))
pixels = img.load()
for i in range(len(data)):
    for j in range(len(data[i])):
        for val, colour in colourData:
            if data[i][-j-1] == val:
                pixels[i,j] = colour
img.show()
