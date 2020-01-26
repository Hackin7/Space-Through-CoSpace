from PIL import Image, ImageDraw

import sys
sys.path.append('./Python_Libraries/')
from PreprocessedMap import data
from ImageCalculation import *
colourData = [(1, (0,255,0)),\
              (2, (255,0,0)),\
              (3, (0,0,255)),\
              (4, (0,168,243)),\
              (5, (0,0,0)),\
              (6, (100,0,0)),\
              ]
img, pixels = convertBack(data)
img.show()
