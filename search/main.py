#!/usr/bin/env python3

import cv2 as cv
import numpy as np
from sys import argv
from matplotlib import pyplot as plt


def main():
	l = cv.imread(argv[1], cv.IMREAD_GRAYSCALE)
	r = cv.imread(argv[2], cv.IMREAD_GRAYSCALE)

	plt.subplot(121), plt.imshow(l)
	plt.subplot(122), plt.imshow(r)

	plt.show()


if __name__ == "__main__":
	main()