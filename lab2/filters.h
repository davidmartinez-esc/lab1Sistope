#ifndef FILTERS_H
#define FILTERS_H

#include "bmp.h"

BMPImage* saturate_bmp(BMPImage* image, float p);
BMPImage* greyscale_bmp(BMPImage* image);
BMPImage* binarize_bmp(BMPImage* image, float threshold);

#endif
