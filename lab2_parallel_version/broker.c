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

void send_image_through_pipe(int fd, BMPImage *image) {
    printf("EMPEZÓ EL SEND IMAGE \n");
    size_t image_size;
    size_t data_size = image->width * image->height * sizeof(RGBPixel);

    // Calcular el tamaño total que se va a enviar (tamaño de la estructura + datos)
    image_size = sizeof(BMPImage) + data_size;

    // Escribir el tamaño primero para que el receptor sepa cuánto leer
    write(fd, &image_size, sizeof(size_t));

    // Luego escribir la estructura BMPImage
    write(fd, image, sizeof(BMPImage));
    
    RGBPixel pixel = image->data[1 * image->width + 20];
    printf("Pixel R=%d, G=%d, B=%d\n", pixel.r, pixel.g, pixel.b);
    write(fd,&pixel,sizeof(RGBPixel));
    // Y finalmente los datos de píxeles
    //write(fd, image->data, data_size);
    printf("SE EJECUTÓ ENVIAR COSAS POR EL PIPE DE FORMA EFECTIVA\n");

    return;
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
   
    int i=0;

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
    

    
    workers[0] = fork();

    if (workers[0] == 0) {
            //SOY EL HIJO
            printf("    SOY UN WORKER, MI NUMERO ES %d CON PID %d\n", 1, getpid());

            
            sprintf(bufferHeight, "%d", image->height);
            sprintf(bufferWidth, "%d", image->width);
            sprintf(bufferReadEnd,"%d",fd[0]);

            char* argv[]={"./worker", bufferHeight, bufferWidth,bufferReadEnd,NULL};

            execv(argv[0], argv);
            sleep(1); 
            return 0; 
    } else if (workers[0] < 0) {
            // Error al hacer fork
            perror("fork");
    } else {
        //SOY EL PADRE
            char buffer[10]="2121";
    
            printf("  CREADO WORKER %d CON PID %d\n", i+1, workers[0]);
            printf("JUSTO ANTES DEL WRITE DEL PIPE DE LA IMAGEN \n");
            //write(fd[1], buffer, sizeof(char)*10);
            send_image_through_pipe(fd[1],image);
            
         
        }
    

    // Esperar a que todos los hijos terminen

    wait(NULL);

    printf("ANTES DEL FREE");
    free_bmp(image);

    printf("  EL nombre del archivo es %s \n",N);
    printf("  Los valores ingresados son:\n NombreArchivo=%s\n numerodefiltros(f)=%i\n factor de saturacion(p)=%f \n Umbral para binarizar(u)=%f \n Umbral para clasificar(v)=%f \n NombreCarpeta(C)=%s \n NombreLogCsv(R)=%s \n numerodetrabajdores(W)=%i\n",N, f, p,u,v,C,R,W);
    printf("  Terminó el BROKER \n");
    
    exit(21);
    return 0;
}
