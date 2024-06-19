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
    printf("Empezó el broker \n");
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

  

   

    printf("EL nombre del archivo es %s \n",N);
    printf("Los valores ingresados son:\n NombreArchivo=%s\n numerodefiltros(f)=%i\n factor de saturacion(p)=%f \n Umbral para binarizar(u)=%f \n Umbral para clasificar(v)=%f \n NombreCarpeta(C)=%s \n NombreLogCsv(R)=%s \n numerodetrabajdores(W)=%i\n",N, f, p,u,v,C,R,W);
    printf("Terminó el broker \n");
    exit(21);
    return 0;
}
