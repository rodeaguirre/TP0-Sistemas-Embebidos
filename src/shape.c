
#include "shape.h"
#include "image.h"


bool shape_ctor(shape_t *me, coordinates_array_t *array, uint32_t position_x, uint32_t position_y){
	
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