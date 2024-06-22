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

void writeBMPImage(int fd, BMPImage *image) {
    size_t size=image->width * image->height * sizeof(RGBPixel);
    write(fd, image->data, size);
}

int main(int argc, char *argv[]) {
    printf("  Empezó el broker \n");
    char* N = argv[1];
    int f=atoi(argv[2]);
    float p=atof(argv[3]);
    float u=atof(argv[4]);
    float v=atof(argv[5]);
    int W=atoi(argv[6]);
    char C[100];
    char R[100];

    strcpy(C,argv[7]);
    strcpy(R,argv[8]);

    char pathSaturated[100]="./";
    char pathGreyScale[100]="./";
    char pathBinary[100]="./";

    char* image_names[] = {"saturated.bpm", "grey.bpm", "binary.bpm"};
    int classifications[] = {0, 0, 0};

    char bufferWidth[10];
    char bufferHeight[10];
    char bufferReadEnd[10];

    pid_t workers[W];
   
    int i;

    int fd[2];

    if(pipe(fd) == -1){
        // control de error
        return 0;
    }

    //DE AQUI EMPIEZA EL CODIGO IMPORTANTE

    const char* filename = N;
    BMPImage* image = read_bmp(filename);

    if (!image) {
        exit(1);
        return 1;
    }

    printf("  Ancho de la imagen: %d\n", image->width);
    printf("  Alto de la imagen: %d\n", image->height);

    // Acceder a los píxeles de la imagen
    /*
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            printf("Pixel (%d, %d): R=%d, G=%d, B=%d\n", x, y, pixel.r, pixel.g, pixel.b);
        }
    }
    */
    

    for (i = 0; i < W; ++i) {
        workers[i] = fork();

        if (workers[i] == 0) {
            
            printf("    SOY UN WORKER, MI NUMERO ES %d CON PID %d\n", i+1, getpid());

            
            sprintf(bufferHeight, "%d", image->height);
            sprintf(bufferWidth, "%d", image->width);
            sprintf(bufferReadEnd,"%d",fd[0]);

            char* argv[]={"./worker", bufferHeight, bufferWidth,bufferReadEnd,NULL};

            execv(argv[0], argv);
            sleep(1); 
            return 0; 
        } else if (workers[i] < 0) {
            // Error al hacer fork
            perror("fork");
        } else {
            // Proceso padre

            //close(fd[0]);

            printf("JUSTO ANTES DEL WRITE DE LA IMAGEN");
            write(fd[1],image, sizeof(BMPImage));
            

            printf("  CREADO WORKER %d CON PID %d\n", i+1, workers[i]);

         
        }
    }

    // Esperar a que todos los hijos terminen
    for (i = 0; i < W; ++i) {
        waitpid(workers[i], NULL, 0);
    }

  
    free_bmp(image);

    printf("  EL nombre del archivo es %s \n",N);
    printf("  Los valores ingresados son:\n NombreArchivo=%s\n numerodefiltros(f)=%i\n factor de saturacion(p)=%f \n Umbral para binarizar(u)=%f \n Umbral para clasificar(v)=%f \n NombreCarpeta(C)=%s \n NombreLogCsv(R)=%s \n numerodetrabajdores(W)=%i\n",N, f, p,u,v,C,R,W);
    printf("  Terminó el BROKER \n");
    
    exit(21);
    return 0;
}
