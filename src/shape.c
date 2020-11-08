
#include "shape.h"
#include "image.h"


bool shape_ctor(shape_t *me, coordinates_array_t *array, uint32_t position_x, uint32_t position_y){
/*		@params: recibe el puntero al objeto, y la posición en el espacio (posición en x e y)
*		@return: Devuelve verdadero sii encontró memoria para guardar el objeto.
**/

	me->position.x = position_x;
	me->position.y = position_y;
	me->array.n_array = 0;

	me->array = *array; /*Copio el contenido del puntero array*/
	
	if(me->array.coordinates = (coordinates_t*) malloc(array->n_array*sizeof(coordinates_t*)))
		return false;
	for (int i = 0; i<array->n_array; i++){
		me->array.n_array = i+1;
		if(me->array.coordinates[i] = (coordinates_t) malloc(sizeof(coordinates_t))){
			shape_dtor(me);
			return false;
		}
		*(me->array.coordinates[i]) = *(array->coordinates[i]);
	}
	return true
}

void shape_dtor(shape_t *me){
	// Completar


}

bool shape_move(shape_t *me, uint32_t dx, uint32_t dy){
	// Completar
}

bool shape_rotate(shape_t *me, float angle){
	// Completar
}

float shape_distance_from(shape_t *me, shape_t *shape){
	// Completar
}

bool shape_plot(shape_t *me, image_t *image){
	// Completar
}