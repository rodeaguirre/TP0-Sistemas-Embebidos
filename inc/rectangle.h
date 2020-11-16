#ifndef RECTANGLE_H
#define RECTANGLE_H 


#include "line.h"
#include "shape.h"
#include <stdint.h>

/* Estructura principal que representa la clase "rectángulo" */
typedef struct {
	shape_t super; 			// Clase de la cual se hereda
	int height;		// Altura del rectángulo
	int width;			// Ancho del rectángulo
	float rotation_angle;	// Ángulo en el cual se encuentra rotada la figura
} rectangle_t;


/** 	@brief: Contructor del objeto "rectángulo"
*		@params: recibe el puntero al objeto, la posición en el espacio (posición en x e y), la altura y el ancho del rectángulo
*		@return: Devuelve verdadero sii encontró memoria para guardar el objeto.
**/
bool rectangle_ctor(rectangle_t *me, int position_x, int position_y, 
					int height, int width);

/** 	@brief: Rota al rectángulo un cierto ángulo.
*		@params: recibe el puntero al objeto y el valor en radianes a rotar.
*		@return: Devuelve verdadero si la operación resultó exitosa.
**/
bool rectangle_rotate(rectangle_t *me, float angle);


/** 	@brief: Devuelve el área del rectángulo.
*		@params: recibe el puntero al objeto.
*		@return: Devuelve el valor del área.
**/
int rectangle_get_area(rectangle_t *me);


int rectangle_get_area(rectangle_t *me);

void rectangle_dtor(rectangle_t *me);


#endif