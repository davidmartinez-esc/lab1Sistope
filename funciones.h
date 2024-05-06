#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Entradas: Recibe un archivo con extensión.
// Salidas: Retorna un puntero al archivo de imagen tipo BMP con el contenido que leyó del archivo. En caso contrario retorna NULL.
// Descripción: Esta función lee una imagen BMP desde un archivo especificado y la carga en memoria. 
// Primero intenta abrir el archivo en modo de lectura binaria ("rb"), si no puede abrir el archivo, imprime un mensaje de error y retorna NULL.
// Luego, lee la cabecera BMP y verifica si es un archivo BMP válido comprobando el campo de tipo de la cabecera.
// Si la cabecera no indica que es un archivo BMP válido, imprime un mensaje de error, cierra el archivo y retorna NULL.
// Después de leer la cabecera, lee la cabecera de información BMP para obtener detalles como el ancho, alto y el desplazamiento a los datos de imagen.
// Luego, crea una estructura BMPImage y reserva memoria para almacenar los datos de la imagen.
// Luego, se desplaza a la posición indicada por el desplazamiento en la cabecera BMP para comenzar a leer los datos de la imagen.
// Durante la lectura de los datos de la imagen, se aplica un relleno si es necesario para asegurar que el ancho de la imagen sea múltiplo de 4 bytes.
// Los datos de la imagen se leen en una estructura RGBPixel y se almacenan en el arreglo de datos de la imagen.
// Una vez que se han leído todos los datos de la imagen, se cierra el archivo y se retorna el puntero a la estructura BMPImage que contiene la imagen leída.

BMPImage* read_bmp(const char* filename);

// Entradas: El nombre del archivo a crear y el puntero a la imagen creada.
// Salidas: void, solo crea el archivo resultante.
// Descripción: Guarda la imagen leida en un archivo con el nombre indicado por parametros. 
// En primer lugar se encarga de abrir el archivo en modo escritura binaria ("wb"), en caso de que no pueda abrirlo lo cierra y retorna NULL.
// Escribe la cabecera de la imagen BMP, donde se encuentra la información respecto a su ancho, alto, cantidad de color y profundidad de bits.
// Luego empieza a escribir los datos de la image, realizandolo pixel por pixel comenzando desde la esquina izquierda y aplica relleno en caso de ser necesario
// para que sea multiplo de 4 bytes. Una vez termina se cierra la función y crea el archivo. 

void write_bmp(const char* filename, BMPImage* image);

// Entradas: Un puntero a una imagen creada.
// Salidas: void
// Descripción: Esta funcion se encarga de liberar la memoria utilizada por la imagen al momento de su lectura y manipulación.

void free_bmp(BMPImage* image);

// Entradas: Un puntero a imagen que es la imagen que se desea saturar y un factor de punto flotante que indica la cantidad de saturación que se desea aplicar a cada pixel. 
// Salidas: Un puntero a imagen con la imagen ya saturada según el factor entregado.
// Descripción: La función se encarga de guardar memoria para la nueva imagen binarizada saturada, posteriormente guarda memoria para un pixel de la imagen para ir alterandolos 
// posteriormente de forma que cada pixel es separado segun rojo, azul y verde. 
// Luego la imagen es recorrida y cada pixel RGB es multiplicado por el factor ingresado. 
// Una vez hecho esto se le asigna a la imagen nueva los pixeles nuevos y se retorna.

BMPImage* saturate_bmp(BMPImage* image, float factor);

// Entradas: Un puntero a imagen que es la imagen a la que se desea aplicar escala de grises.
// Salidas: Un puntero a imagen con la imagen en escala de grises.
// Descripción: Caso similar a la función de saturar, se guarda espacio para la nueva imagen binarizada que se va a crear así como también para un pixel que represente el RGB de la imagen,
// solo que en este caso se crea una nueva variable donde cada pixel de la imagen, que fue recorrida mediante dos ciclos, es multiplicado por valores fijos que producen
// escala de grises, en este caso siendo pixel.red * 0.3, pixel.blue * 0.11 y pixel.green * 0.59.
// Una vez realizado todo este procedimiento se asignan los valores grises a cada pixel y luego se guardan en la nueva imagen binarizada y es retornada al usuario.

BMPImage* greyscale_bmp(BMPImage* image);

// Entradas: Un puntero a imagen que es la imagen que se desea saturar y un factor de punto flotante que indica el umbral al que se compara cada pixel, debe ser entre 0 y 1. 
// Salidas: Un puntero a imagen con la imagen ya binarizada.
// Descripción: Esta función binariza una imagen en escala de grises basada en un umbral especificado. 
// Primero, convierte la imagen original a escala de grises utilizando la función grayscale_bmp para simplificar el proceso de binarización
// y mejorar la consistencia en los resultados. 
// Luego, crea una nueva estructura BMPImage para almacenar la imagen binarizada y reserva memoria para los datos de la imagen. 
// Para binarizar la imagen se itera sobre cada píxel de la imagen en escala de grises y se compara su valor de gris con el umbral. 
// Si el valor de gris del píxel es mayor que el umbral, se asigna blanco al píxel en la imagen binarizada, en caso contrario (menor o igual al umbral), 
// se asigna negro al píxel en la imagen binarizada. 
// Una vez que se ha binarizado toda la imagen, se libera la memoria de la imagen en escala de grises y se retorna la imagen binarizada.

BMPImage* binarize_bmp(BMPImage* image, float threshold);