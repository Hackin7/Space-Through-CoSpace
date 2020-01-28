
from PIL import Image

import sys
sys.path.append('./Python_Libraries/')
from ImageCalculation import *
    
def main(args):
    im = Image.open(input('Enter image file: '))
    im = resizeImage(im, 240) 
    im.show()
    #pix_val = list(im.getdata())
    pixels = im.load()
    print(im.size) #should be 360 by 270
    print('Generation')
    data = switchYValues(mapData(im.size, pixels,8,5))

    print('Showing Image')
    img, pixels = convertBack(data)
    img.show()

    #with open("./bitmappingTest.txt","w+") as file:
    #    file.write(str(switchYValues(mapData(im.size, pixels))))#pix_val)))
    print('To hpp file')
    with open("../World1/w1map.hpp","w+") as file:
        file.write(f"const int width0 = {im.size[0]},height0 = {im.size[1]};")
        file.write(f"int layout0[width0][height0] = {str(data).replace('[','{').replace(']','}')};")#pix_val)))
        #str(pix_val))
    #print('To py file')
    #with open("./Python_Libraries/PreprocessedMap.py","w+") as file:
    #        file.write(f"data = {str(data)};")#pix_val)))
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
