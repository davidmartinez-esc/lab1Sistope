#include "fworker.h"
#include <stdlib.h>
#include "filters.h"
BMPImage* fragment_to_image(BMPFragment* fragment) {
    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    if (image == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para BMPImage en fragment_to_image.\n");
        return NULL;
    }

    // Inicializar los campos de BMPImage con los datos de BMPFragment
    image->width = fragment->width;
    image->height = fragment->height;
    image->data = (RGBPixel*)malloc(fragment->width * fragment->height * sizeof(RGBPixel));
    if (image->data == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para image->data en fragment_to_image.\n");
        free(image);
        return NULL;
    }

    // Copiar los datos de fragment->data a image->data
    int total_pixels = fragment->width * fragment->height;
    memcpy(image->data, fragment->data, total_pixels * sizeof(RGBPixel));

    return image;
}

BMPImage* apply_filters(BMPFragment* fragment) {
    BMPImage* image = fragment_to_image(fragment);
    BMPImage* processed_image = NULL;

    switch (fragment->filter) {
        case 1:
            processed_image = saturate_bmp(image, fragment->p);
            break;
        case 2:
            processed_image = greyscale_bmp(image);
            break;
        case 3:
            processed_image = binarize_bmp(image, fragment->u);
            break;
    }

    free_bmp(image);
    return processed_image;
}



