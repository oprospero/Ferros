from __future__ import division
import cv2
#to show the image
from matplotlib import pyplot as plt
import numpy as np
from math import cos, sin
import pylab

def nothing(x):
    iLowH = x
#read the image
image = cv2.imread('images.jpeg')
imHsv = cv2.cvtColor(image, cv2.COLOR_RGB2HSV)


iLowH = 0;
iHighH = 180;
iLowS = 100;
iHighS = 256;
iLowV = 80;
iHighV = 255;


cv2.namedWindow('Control')
cv2.createTrackbar('LowH:', 'Control', iLowH, 179, nothing)
cv2.createTrackbar('HighH:', 'Control', iHighH, 179, nothing)
cv2.createTrackbar('LowS:', 'Control', iLowS, 256, nothing)
cv2.createTrackbar('HighS:', 'Control', iHighS, 256, nothing)
cv2.createTrackbar('LowV:', 'Control', iLowV, 256, nothing)
cv2.createTrackbar('HighV:', 'Control', iHighV, 256, nothing)
while (True):
    iLowH = cv2.getTrackbarPos('LowH:', 'Control')
    iHighH = cv2.getTrackbarPos('HighH:', 'Control')
    iLowS = cv2.getTrackbarPos('LowS:', 'Control')
    iHighS = cv2.getTrackbarPos('HighS:', 'Control')
    iLowV = cv2.getTrackbarPos('LowV:', 'Control')
    iHighV = cv2.getTrackbarPos('High:', 'Control')

    min_red = np.array([iLowH, iLowS, iLowV])
    max_red = np.array([iHighH, iHighS, iHighV])
    # print(min_red)
    filtered = cv2.inRange(imHsv,min_red,max_red)
    imRgb = cv2.cvtColor(imHsv, cv2.COLOR_HSV2RGB)
    cv2.imshow('image',filtered)
    key = cv2.waitKey(100)
    if key == 'b':
        break

# plt.imshow(image)
# pylab.show(image)

cv2.waitKey()
