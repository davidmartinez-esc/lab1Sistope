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

BMPImage* receive_image_from_pipe(int fd) {
    size_t image_size;
    BMPImage *image;
    size_t data_size;

    // Leer el tamaño total de los datos que se van a recibir
    if (read(fd, &image_size, sizeof(size_t)) < sizeof(size_t)) {
        perror("Error al leer el tamaño de la imagen desde el pipe");
        return NULL;
    }

    // Verificar que el tamaño sea válido
    if (image_size < sizeof(BMPImage)) {
        fprintf(stderr, "Tamaño de imagen recibido inválido.\n");
        return NULL;
    }

    // Almacenar el tamaño de los datos de píxeles
    data_size = image_size - sizeof(BMPImage);

    // Asignar memoria para la imagen
    image = (BMPImage*)malloc(sizeof(BMPImage));
    if (!image) {
        perror("Error al asignar memoria para la imagen BMP");
        return NULL;
    }

    // Leer la estructura BMPImage del pipe
    if (read(fd, image, sizeof(BMPImage)) < sizeof(BMPImage)) {
        perror("Error al leer la estructura BMPImage desde el pipe");
        free(image);
        return NULL;
    }

    image->width=640;
    image->height=426;
    

    // Asignar memoria para los datos de píxeles
    image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height);

    if (!image->data) {
        perror("Error al asignar memoria para los datos de píxeles");
        free(image);
        return NULL;
    }


    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel;
            read(fd, &pixel, sizeof(RGBPixel));
            
            image->data[y * image->width + x] = pixel;
        }
    }
    
    write_bmp("./generadaEnWorker.bmp", image);
    // Leer los datos de píxeles del pipe
    /*
    if (read(fd, image->data, data_size) < data_size) {
        perror("Error al leer los datos de píxeles desde el pipe");
        free(image->data);
        free(image);
        return NULL;
    }
    */
    printf("SE EJECUTÓ LEER COSAS POR EL PIPE DE FORMA EFECTIVA \n");

    return image;
}

int main(int argc, char *argv[]) {
    printf("    Empezó el WORKER \n");
   
    int height=atoi(argv[1]);
    int width=atoi(argv[2]);
    int indexPipe=atoi(argv[3]);
    char buffer[10];


    BMPImage* nuevaImagen = receive_image_from_pipe(indexPipe);
   

    
    for (int y = 0; y < nuevaImagen->height; y++) {
        for (int x = 0; x < nuevaImagen->width; x++) {
            RGBPixel pixel = nuevaImagen->data[y * nuevaImagen->width + x];
            printf("Pixel (%d, %d): R=%d, G=%d, B=%d\n", x, y, pixel.r, pixel.g, pixel.b);
        }
    }
    

    //read(indexPipe,nuevaImagen, sizeof(BMPImage));
    
    printf("EL ANCHO DE LA IMAGEN LEIDA DIRECTAMENTE DESDE LA IMAGEN ES %d \n",nuevaImagen->width);
    
   
    printf("    EL INDEX DEL READ DEL PIPE ES %d \n",indexPipe);
    //read(indexPipe, buffer, sizeof(char)*10);
    //printf("    EL MENSAJE LEIDO ES %s \n",buffer);
   
    printf("  WORKER Ancho de la imagen: %d\n", width);
    printf("   WORKER Alto de la imagen: %d\n", height);





    printf("    Terminó el WORKER con PID %d\n",getpid());

    exit(21);
    return 0;
}
