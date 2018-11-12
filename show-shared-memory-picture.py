import mmap
import numpy
import cv2 as cv2
import time
import sys

file = sys.argv[1]
print(file)

with open(file, 'r+b') as f:
    mm = mmap.mmap(f.fileno(), 0)
    img = numpy.ndarray(shape=(1080, 1920, 3), dtype=numpy.uint8, buffer = mm)
    cv2.namedWindow("Image")
    cv2.imshow("Image",img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    mm.close()
