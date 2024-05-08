//Ejemplo de lectura y escritura de imagen BMP en C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funciones.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char N[100];
    char R[100];
    int f=3;
    float p=1.3;
    float u=0.5;
    float v=0.5;
    char C[100];
    
    int option;
    int mandatoryN=0;
    int mandatoryC=0;
    int mandatoryR=0;

   const char* nombreArchivo = "resultados.csv";
    char* image_names[] = {"imagen1.jpg", "imagen2.jpg", "imagen3.jpg"};
    int classifications[] = {1, 0, 1};
    int num_images = sizeof(image_names) / sizeof(image_names[0]);

    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:")) != -1){
        switch(option){
            case 'N':
                strcpy(N, optarg);
                mandatoryN=1;
                
                break;
            case 'f':
                f = atoi(optarg);
                break;
            case 'p':
                p = atof(optarg);
                break;
            case 'u':
                u = atof(optarg);
                break;
            case 'v':
                v = atof(optarg);
                break;
            case 'C':
                strcpy(C,optarg);
                mandatoryC=1;
                break;
            case 'R':
                strcpy(R,optarg);
                mandatoryR=1;
                break;
        }
    }
    
    if(mandatoryN == 0){
        printf("Se debe ingresar el nombre del prefijo de la imagen (img, imagen y photo)\n");
        return 1;
    }
    if(mandatoryC == 0){
        printf("Se debe ingresar el nombre de la carpeta con los archivos resultantes \n");
        return 1;
    }
    if(mandatoryR == 0){
        printf("Se debe ingresar el nombre del archivo .csv con las clasificaciones \n");
        return 1;
    }
    

    


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
    
    printf("Los valores ingresados son:\n  N=%s\n  f=%i\n  p=%f u=%f v=%f C=%s R=%s \n",N, f, p,u,v,C,R);

    create_csv(nombreArchivo, image_names, classifications, num_images);

    free_bmp(binary_image);
    free_bmp(new_image);
    free_bmp(image);
    free_bmp(grey_image);
    
    return 0;
}
