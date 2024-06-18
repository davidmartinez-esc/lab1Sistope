#include "fworker.h"

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

