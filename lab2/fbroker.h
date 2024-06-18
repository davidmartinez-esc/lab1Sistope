#ifndef FBROKER_H
#define FBROKER_H

#include "bmp.h"

void send_fragment(int pipefd, BMPImage* image, int start_col, int end_col, int filter, float p, float u, float v);
void receive_fragment(int pipefd, BMPImage* image);

#endif
