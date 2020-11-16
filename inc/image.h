#ifndef IMAGE_H
#define IMAGE_H


#include <stdbool.h>
#include <stdint.h>

/* Tipo de dato enumerativo utilizado por la imagen. */
typedef enum {LOW, HIGH} img_data_t;


/* Estructura principal, que representa a la imagen*/
typedef struct {
	img_data_t **data; 	// Contenido
	int n_rows; 	// Cantidad de filas
	int n_cols; 	// Cantidad de columnas
} image_t;


/** 	@brief: Contructor del objeto "imagen"
*		@params: recibe el puntero al objeto, la cantidad de filas y columnas
*		@return: Devuelve verdadero sii encontró memoria para guardar el objeto.
**/
bool image_ctor(image_t *me, int n_rows, int n_cols);


/** 	@brief: Destructor del objeto "imagen"
*		@params: Recibe el puntero al objeto.
*		@return: void
**/
void image_dtor(image_t *me);


/** 	@brief: Escribe en una posición de la imagen.
*		@params: Recibe el puntero al objeto, el índice (i,j) de la imagen y el valor a escribir.
*		@return: void
**/
void image_write(image_t *me, int i, int j, img_data_t value);


/** 	@brief: Lee un punto de la imagen
*		@params: Recibe el puntero al objeto y la posición a leer
*		@return: Devuelve el valor leído
**/
img_data_t image_read(image_t *me, int i, int j);


/** 	@brief: Guarda la imagen en un archivo.
*		@params: Recibe el puntero al objeto y el nombre del archivo
*		@return: void
**/
void image_to_file(image_t *me, const char *filename);


#endif