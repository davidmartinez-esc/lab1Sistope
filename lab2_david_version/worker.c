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


int main(int argc, char *argv[]) {
    printf("Empezó el WORKER \n");
   
    int height=atoi(argv[1]);
    int width=atoi(argv[2]);
   

   
    printf("Terminó el WORKER \n");
    exit(21);
    return 0;
}
