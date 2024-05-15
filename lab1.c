//Ejemplo de lectura y escritura de imagen BMP en C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funciones.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Se crean las variables para el getopt, la clasificacion de las imagenes y la creacion de estas
    char N[100];
    char R[100];
    int f=3;
    float p=1.3;
    float u=0.5;
    float v=0.5;
    char C[100];

    char pathSaturated[100]="./";
    char pathGreyScale[100]="./";
    char pathBinary[100]="./";
    
    int option;
    int mandatoryN=0;
    int mandatoryC=0;
    int mandatoryR=0;

    char* image_names[] = {"saturated.bpm", "grey.bpm", "binary.bpm"};
    int classifications[] = {0, 0, 0};
    //int num_images = sizeof(image_names) / sizeof(image_names[0]);

    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:")) != -1){
        switch(option){
            case 'N':
                strcpy(N, optarg);
                strcat(N,".bmp");
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
                strcat(R,".csv");
                mandatoryR=1;
                break;
        }
    }
    
    if(f<=0){
        printf("La flag f no puede tomar el valor 0 o menor que este");
        return 1;
    }

    if(p<=0){
        printf("La flag p no puede tomar el valor 0 o menor que este");
        return 1;
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
    
    // Se lee la imagen que se desea procesar

    const char* filename = N;
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
    // Se crean las imagenes y se escriben solamente las deseadas
        mkdir(C,S_IRWXU);

        strcat(pathSaturated,C);
        strcat(pathSaturated,"/saturated.bmp");

        strcat(pathGreyScale,C);
        strcat(pathGreyScale,"/grey.bmp");

        strcat(pathBinary,C);
        strcat(pathBinary,"/binary.bmp");

        // 1.1f
        BMPImage* new_image = saturate_bmp(image,p);

        if(f>=1){
            write_bmp(pathSaturated, new_image);
        }
    
        BMPImage* grey_image = greyscale_bmp(image);

        if(f>=2){
            write_bmp(pathGreyScale, grey_image);
        }
        
        BMPImage* binary_image = binarize_bmp(grey_image,u);
        
        if(f>=3){
            write_bmp(pathBinary, binary_image);
        }
        
    // Se hace la clasificacion de cada imagen creada
    int isSaturatedNearly_black = is_nearly_black(new_image, v);
    int isGreyNearly_black = is_nearly_black(grey_image, v);
    int isBinaryNearly_black = is_nearly_black(binary_image, v);


    // Se asigna cada espacio del arreglo a su clasificacion si es casi negro
    classifications[0]=isSaturatedNearly_black;
    classifications[1]=isGreyNearly_black;
    classifications[2]=isBinaryNearly_black;
    
    /*
    if (isSaturatedNearly_black==1) {
        printf("La imagen es casi negra.\n");
    } else {
        printf("La imagen no es casi negra.\n");
    }
    */

    //printf("Los valores ingresados son:\n  PREFIJO=%s\n  numerodefiltros(f)=%i\n factor de saturacion(p)=%f \n Umbral para binarizar(u)=%f \n Umbral para clasificar(v)=%f \n C=%s \n R=%s \n",N, f, p,u,v,C,R);
    //printf("STRING %s",pathSaturated);

    // Se crea el archivo csv con las clasificaciones
    create_csv(R, image_names, classifications, f);

    // Se libera cada imagen
    free_bmp(new_image);
    
    free_bmp(grey_image);
  
    free_bmp(binary_image);
    
    free_bmp(image);

    
    return 0;
}
