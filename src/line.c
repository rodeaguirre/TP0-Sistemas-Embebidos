#include "shape.h"
#include "line.h"
#include <stdint.h>
#include <math.h>




bool line_ctor(line_t *me, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
  /** 	@brief: Contructor del objeto "línea"
*		@params: recibe el puntero al objeto y las coordenadas para definir el segmento de línea.
*		@return: Devuelve verdadero sii encontró memoria para guardar el objeto.
**/
	me->start.x=x1;
	me->start.y=y1;
	me->end.x=x2;
	me->end.y=y2;

	me->super.position.x=x1;
	me->super.position.y=y1;


}


bool line_rotate(line_t *me, float angle){
  // Completar
}


bool line_scale(line_t *me, float factor){
  // Completar
}


float line_get_lenght(line_t *me){
  // Completar
}
