#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "fbroker.h"

int main(int argc, char *argv[]) {
    if (argc != 10) {
        fprintf(stderr, "Uso: %s N C R f p u v W\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *N = argv[1];
    char *C = argv[2];
    char *R = argv[3];
    int f = atoi(argv[4]);
    float p = atof(argv[5]);
    float u = atof(argv[6]);
    float v = atof(argv[7]);
    int w = atoi(argv[8]);

    int pipefds[w][2];
    for (int i = 0; i < w; i++) {
        if (pipe(pipefds[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Proceso worker
            dup2(pipefds[i][0], STDIN_FILENO);
            close(pipefds[i][1]);
            char *args[] = {"./worker", NULL};
            execv(args[0], args);
            perror("execv");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        close(pipefds[i][0]);
    }

    // Dividir la imagen y enviar fragmentos a los workers
    BMPImage* image = read_bmp(N);
    int cols_per_worker = image->width / w;
    for (int i = 0; i < w; i++) {
        int start_col = i * cols_per_worker;
        int end_col = (i == w - 1) ? image->width : start_col + cols_per_worker;
        send_fragment(pipefds[i][1], image, start_col, end_col, f, p, u, v);
        close(pipefds[i][1]);
    }

    // Recibir los fragmentos procesados y ensamblar la imagen
    BMPImage* processed_image = create_empty_image(image->width, image->height);
    for (int i = 0; i < w; i++) {
        receive_fragment(pipefds[i][0], processed_image);
        close(pipefds[i][0]);
    }

    write_bmp("output.bmp", processed_image);
    free_bmp(image);
    free_bmp(processed_image);

    return 0;
}
