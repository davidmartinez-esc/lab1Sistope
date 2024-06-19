#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

    // Imprimir argumentos para depuración
    printf("Argumentos recibidos:\n");
    printf("N: %s\n", N);
    printf("R: %s\n", R);
    printf("C: %s\n", C);
    printf("f: %d\n", f);
    printf("p: %.2f\n", p);
    printf("u: %.2f\n", u);
    printf("v: %.2f\n", v);
    printf("W: %d\n", w);

    // Crear proceso broker
    printf("Creando proceso broker...\n");
    pid_t pid = fork();
    if (pid == 0) {
        // Proceso hijo
        char f_str[10], p_str[10], u_str[10], v_str[10], w_str[10];
        sprintf(f_str, "%d", f);
        sprintf(p_str, "%.2f", p);
        sprintf(u_str, "%.2f", u);
        sprintf(v_str, "%.2f", v);
        sprintf(w_str, "%d", w);

        char *args[] = {"./broker", N, C, R, f_str, p_str, u_str, v_str, w_str, NULL};
        printf("Ejecutando broker con args: ");
        for (int i = 0; args[i] != NULL; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");

        execv(args[0], args);
        perror("execv");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Esperar a que el broker termine
    int status;
    wait(&status);
    printf("Broker terminado con estado %d\n", WEXITSTATUS(status));

    return 0;
}