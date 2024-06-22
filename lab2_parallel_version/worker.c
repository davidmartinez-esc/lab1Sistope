//Ejemplo de lectura y escritura de imagen BMP en C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funciones.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
BMPImage*  readBMPImage(int readEnd,int width,int height) {
    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    image->width = width;
    image->height = height;
    image->data = (RGBPixel *)malloc(width* height * sizeof(RGBPixel));

    size_t size=width * height * sizeof(RGBPixel);
    read(readEnd, image->data, size);
}

int main(int argc, char *argv[]) {
    printf("    Empezó el WORKER \n");
   
    int height=atoi(argv[1]);
    int width=atoi(argv[2]);
    int indexPipe=atoi(argv[3]);
    char buffer[10];

    BMPImage* imagenLeida=readBMPImage(indexPipe,width,height);

    printf("    EL INDEX DEL READ DEL PIPE ES %d \n",indexPipe);
    //read(indexPipe, buffer, sizeof(char)*10);
    //printf("    EL MENSAJE LEIDO ES %s \n",buffer);
    printf("    Terminó el WORKER con PID %d\n",getpid());
    exit(21);
    return 0;
}
