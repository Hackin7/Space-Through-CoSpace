
from PIL import Image

import sys
sys.path.append('./Python_Libraries/')
from ImageCalculation import *
    
def main(args):
    im = Image.open(input('Enter image file: '))
    im = resizeImage(im, 360) 
    im.show()
    #pix_val = list(im.getdata())
    pixels = im.load()
    print(im.size) #should be 360 by 270
    #print(mapData(im.size, pix_val))
    #print(pix_val)
    print('Generation')
    data = switchYValues(mapData(im.size, pixels))
    print('Showing Image')
    img, pixels = convertBack(switchYValues(mapData(im.size, pixels)))
    img.show()

    #with open("./bitmappingTest.txt","w+") as file:
    #    file.write(str(switchYValues(mapData(im.size, pixels))))#pix_val)))
    print('To hpp file')
    with open("../World2/Location/map.hpp","w+") as file:
        file.write(f"const int width = {im.size[0]},height = {im.size[1]};")
        file.write(f"int layout[width][height] = {str(data).replace('[','{').replace(']','}')};")#pix_val)))
        #str(pix_val))
    print('To py file')
    with open("./Python_Libraries/PreprocessedMap.py","w+") as file:
            file.write(f"data = {str(data)};")#pix_val)))
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
