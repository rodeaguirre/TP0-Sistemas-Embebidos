
#include "shape.h"
#include "image.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


bool shape_ctor(shape_t *me, coordinates_array_t *array, uint32_t position_x, uint32_t position_y){
	me->position.x = position_x;
	me->position.y = position_y;
	//me->array.n_array = 0;
	
	if (array == NULL) 
		return false;	
	me->array = *array; /*Es absurdo*/
	return true;
}

void shape_dtor(shape_t *me){
	free(me->array.coordinates);
}

bool shape_move(shape_t *me, uint32_t dx, uint32_t dy){
	me->position.x += dx;
	me->position.x += dy;
	return true;
}

float shape_distance_from(shape_t *me, shape_t *shape){
	float dx = me->position.x - shape->position.x; 
	float dy = me->position.y - shape->position.y;

	return sqrt(pow(dx,2)+pow(dy,2));
}

bool shape_plot(shape_t *me, image_t *image){
	uint32_t x;
	uint32_t y;

	for (int i = 0; i<(me->array.n_array); i++){
		x = me->array.coordinates[i].x + me->position.x;
		y = me->array.coordinates[i].y + me->position.y;
		image_write(image, x, y, HIGH);	
	}
//	presupongo que el control del tamaño está dentro de image_write
	return true;
}
