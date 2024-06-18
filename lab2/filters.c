#include "filters.h"

BMPImage* saturate_bmp(BMPImage* image, float p) {
    BMPImage* new_image = create_empty_image(image->width, image->height);
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel* pixel = &image->data[y * image->width + x];
            new_image->data[y * image->width + x].r = (unsigned char)(pixel->r * p);
            new_image->data[y * image->width + x].g = (unsigned char)(pixel->g * p);
            new_image->data[y * image->width + x].b = (unsigned char)(pixel->b * p);
        }
    }
    return new_image;
}

BMPImage* greyscale_bmp(BMPImage* image) {
    BMPImage* new_image = create_empty_image(image->width, image->height);
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel* pixel = &image->data[y * image->width + x];
            unsigned char grey = (unsigned char)(0.3 * pixel->r + 0.59 * pixel->g + 0.11 * pixel->b);
            new_image->data[y * image->width + x].r = grey;
            new_image->data[y * image->width + x].g = grey;
            new_image->data[y * image->width + x].b = grey;
        }
    }
    return new_image;
}

BMPImage* binarize_bmp(BMPImage* image, float threshold) {
    BMPImage* new_image = create_empty_image(image->width, image->height);
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel* pixel = &image->data[y * image->width + x];
            unsigned char grey = (unsigned char)(0.3 * pixel->r + 0.59 * pixel->g + 0.11 * pixel->b);
            unsigned char binary = grey > threshold * 255 ? 255 : 0;
            new_image->data[y * image->width + x].r = binary;
            new_image->data[y * image->width + x].g = binary;
            new_image->data[y * image->width + x].b = binary;
        }
    }
    return new_image;
}
