#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char r, g, b;
} RGBPixel;

typedef struct {
    int width;
    int height;
    RGBPixel* data;
} BMPImage;

BMPImage* read_bmp(const char* filename);
void write_bmp(const char* filename, BMPImage* image);
void free_bmp(BMPImage* image);
BMPImage* create_empty_image(int width, int height);

#endif
