#include "shape.h"
#include "line.h"
#include <stdint.h>
#include <math.h>


/** 	@brief: Contructor del objeto "línea"
*		@params: recibe el puntero al objeto y las coordenadas para definir el segmento de línea.
*		@return: Devuelve verdadero sii encontró memoria para guardar el objeto.
**/
bool line_ctor(line_t *me, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){

}


/** 	@brief: Rotar al segmento dejando fijo el punto de partida.
*		@params: recibe el puntero al objeto y el ángulo en radianes a rotar
*		@return: Devuelve verdadero si se realizó con éxito la operación
**/
bool line_rotate(line_t *me, float angle){

}


/** 	@brief: Escala al segmento por un factor, dejando fijo el punto de partida.
*		@params: recibe el puntero al objeto y el escalar por el cual multiplicar
*		@return: Devuelve verdadero si se realizó con éxito la operación
**/
bool line_scale(line_t *me, float factor){

}


/** 	@brief: Calcula la longitud del segmento.
*		@params: recibe el puntero al objeto.
*		@return: Devuelve la longitud del segmento.
**/
float line_get_lenght(line_t *me){

}