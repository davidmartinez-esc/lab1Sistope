#ifndef FWORKER_H
#define FWORKER_H

#include "bmp.h"

typedef struct {
    int start_col;
    int end_col;
    int width;
    int height;
    float p;
    float u;
    float v;
    int filter;
    RGBPixel data[];
} BMPFragment;

BMPImage* apply_filters(BMPFragment* fragment);

#endif
