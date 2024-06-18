#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fworker.h"

int main() {
    BMPFragment fragment;
    read(STDIN_FILENO, &fragment, sizeof(fragment));

    BMPImage* fragment_image = apply_filters(&fragment);
    write(STDOUT_FILENO, fragment_image, sizeof(*fragment_image) + fragment_image->width * fragment_image->height * sizeof(RGBPixel));
    free_bmp(fragment_image);

    return 0;
}
