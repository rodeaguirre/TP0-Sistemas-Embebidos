
#include "shape.h"
#include "image.h"


bool shape_ctor(shape_t *me, coordinates_array_t *array, uint32_t position_x, uint32_t position_y){
	me->position.x = position_x;
	me->position.y = position_y;
	me->array.n_array = 0;

	me->array = *array; /*Copio el contenido del puntero array*/
	
	if(me->array.coordinates = (coordinates_t*) malloc(array->n_array*sizeof(coordinates_t)))
		return false;
	me->array.n_array = array->array;
	for (int i = 0; i<array->n_array; i++){
		me->array.coordinates[i] = array->coordinates[i];
	}
	return true
}

void shape_dtor(shape_t *me){
	free(me->array.coordinates);
}

bool shape_move(shape_t *me, uint32_t dx, uint32_t dy){
	me->position.x += dx;
	me->position.x += dy;
	for (int i = 0; i<ma->array.n_array; i++){
		me->array.coordinates[i].x +=dx;
		me->array.coordinates[i].y +=dy;
	}
}

bool shape_rotate(shape_t *me, float angle){
	
}

float shape_distance_from(shape_t *me, shape_t *shape){
	// Completar
}

bool shape_plot(shape_t *me, image_t *image){
	// Completar
}