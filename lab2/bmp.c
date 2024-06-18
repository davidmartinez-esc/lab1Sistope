#include "bmp.h"

BMPImage* read_bmp(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    image->width = width;
    image->height = height;
    image->data = (RGBPixel*)malloc(width * height * sizeof(RGBPixel));

    for (int y = 0
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fread(&image->data[y * width + x], sizeof(RGBPixel), 1, file);
        }
    }

    fclose(file);
    return image;
}

void write_bmp(const char* filename, BMPImage* image) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        return;
    }

    unsigned char header[54] = {
        0x42, 0x4D,           // BMP signature
        0, 0, 0, 0,           // File size (will be filled later)
        0, 0, 0, 0,           // Reserved
        54, 0, 0, 0,          // Offset to pixel data
        40, 0, 0, 0,          // DIB header size
        0, 0, 0, 0,           // Width (will be filled later)
        0, 0, 0, 0,           // Height (will be filled later)
        1, 0,                 // Planes
        24, 0,                // Bits per pixel
        0, 0, 0, 0,           // Compression (none)
        0, 0, 0, 0,           // Image size (can be 0 for uncompressed)
        0, 0, 0, 0,           // X pixels per meter
        0, 0, 0, 0,           // Y pixels per meter
        0, 0, 0, 0,           // Total colors
        0, 0, 0, 0            // Important colors
    };

    int width = image->width;
    int height = image->height;
    int imageSize = width * height * 3;

    *(int*)&header[2] = 54 + imageSize;
    *(int*)&header[18] = width;
    *(int*)&header[22] = height;

    fwrite(header, sizeof(unsigned char), 54, file);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fwrite(&image->data[y * width + x], sizeof(RGBPixel), 1, file);
        }
    }

    fclose(file);
}

void free_bmp(BMPImage* image) {
    if (image) {
        free(image->data);
        free(image);
    }
}

BMPImage* create_empty_image(int width, int height) {
    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    image->width = width;
    image->height = height;
    image->data = (RGBPixel*)malloc(width * height * sizeof(RGBPixel));
    memset(image->data, 0, width * height * sizeof(RGBPixel));
    return image;
}
