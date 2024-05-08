//Ejemplo de lectura y escritura de imagen BMP en C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    const char* filename = "rb.bmp";
    BMPImage* image = read_bmp(filename);
    if (!image) {
        return 1;
    }

    printf("Ancho de la imagen: %d\n", image->width);
    printf("Alto de la imagen: %d\n", image->height);

    // Acceder a los píxeles de la imagen
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            printf("Pixel (%d, %d): R=%d, G=%d, B=%d\n", x, y, pixel.r, pixel.g, pixel.b);
        }
    }

    BMPImage* new_image = saturate_bmp(image, 1.1f);
    write_bmp("saturated.bmp", new_image);

     
    //0.3f 0.59f 0.11f
    BMPImage* grey_image = greyscale_bmp(image);
    write_bmp("grey.bmp", grey_image);

      //0.3f 0.59f 0.11f
    BMPImage* binary_image = binarize_bmp(image,0.5f);
    write_bmp("binary.bmp", binary_image);

    int nearly_black = is_nearly_black(binary_image, 1.0); // Reemplaza el umbral, va entre 0 y 1

    if (nearly_black) {
        printf("La imagen es casi negra.\n");
    } else {
        printf("La imagen no es casi negra.\n");
    }

    free_bmp(binary_image);
    free_bmp(new_image);
    free_bmp(image);
    free_bmp(grey_image);
    
    return 0;
}
