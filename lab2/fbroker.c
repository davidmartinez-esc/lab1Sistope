#include "fbroker.h"

void send_fragment(int pipefd, BMPImage* image, int start_col, int end_col, int filter, float p, float u, float v) {
    BMPFragment fragment;
    fragment.start_col = start_col;
    fragment.end_col = end_col;
    fragment.width = image->width;
    fragment.height = image->height;
    fragment.p = p;
    fragment.u = u;
    fragment.v = v;
    fragment.filter = filter;

    int fragment_size = (end_col - start_col) * image->height * sizeof(RGBPixel);
    memcpy(fragment.data, &image->data[start_col], fragment_size);

    write(pipefd, &fragment, sizeof(fragment) + fragment_size);
}

void receive_fragment(int pipefd, BMPImage* image) {
    BMPFragment fragment;
    read(pipefd, &fragment, sizeof(fragment));

    int fragment_size = (fragment.end_col - fragment.start_col) * fragment.height * sizeof(RGBPixel);
    memcpy(&image->data[fragment.start_col], fragment.data, fragment_size);
}
