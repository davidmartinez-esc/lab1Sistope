#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Variables para getopt y las configuraciones de imagen
    char N[100];
    char R[100];
    int f = 3;
    float p = 1.3;
    float u = 0.5;
    float v = 0.5;
    char C[100];
    int w = 0;
    int option;
    int mandatoryN = 0;
    int mandatoryC = 0;
    int mandatoryR = 0;

    while ((option = getopt(argc, argv, "N:f:p:u:v:C:R:W:")) != -1) {
        switch (option) {
            case 'N':
                strcpy(N, optarg);
                mandatoryN = 1;
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
                strcpy(C, optarg);
                mandatoryC = 1;
                break;
            case 'R':
                strcpy(R, optarg);
                strcat(R, ".csv");
                mandatoryR = 1;
                break;
            case 'W':
                w = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s -N prefijo -f valor -p valor -u valor -v valor -C carpeta -R archivo -W workers\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Validaciones
    if (mandatoryN == 0 || mandatoryC == 0 || mandatoryR == 0 || f <= 0 || f > 3 || p <= 0 || u < 0 || u > 1 || v < 0 || v > 1 || w <= 0) {
        fprintf(stderr, "Argumentos inválidos\n");
        exit(EXIT_FAILURE);
    }

    // Crear proceso broker
    pid_t pid = fork();
    if (pid == 0) {
        // Proceso hijo
        char *args[] = {"./broker", N, C, R, argv[2], argv[4], argv[6], argv[8], argv[10], argv[12], NULL};
        execv(args[0], args);
        perror("execv");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Esperar a que el broker termine
    wait(NULL);
    return 0;
}
