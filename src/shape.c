
#include "shape.h"
#include "image.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


static bool array_init (coordinates_array_t* array, int length){
	printf("init Array: length=%d\n", length);
	if(!(array->coordinates = (coordinate_t*) calloc(length,sizeof(coordinate_t)))){
		return false;
	}
	array->n_array = length;
	return true;
}


bool shape_ctor(shape_t *me, coordinates_array_t *array, int position_x, int position_y){
	me->position.x = position_x;
	me->position.y = position_y;

  	/*Inicializo el array con el largo necesario, pero no lo lleno.*/
	if(!(array_init (&(me->array), array->n_array))){
		return false;
	}
	me->array.n_array = array->n_array;

	return true;
}

void shape_dtor(shape_t *me){
	free(me->array.coordinates);
}

bool shape_move(shape_t *me, int dx, int dy){
	me->position.x = dx;
	me->position.y = dy;
	printf("shape_move: dx=%d,dy=%d\n",dx,dy);
	return true;
}

float shape_distance_from(shape_t *me, shape_t *shape){
	float dx = me->position.x - shape->position.x; 
	float dy = me->position.y - shape->position.y;

	return sqrt(pow(dx,2)+pow(dy,2));
}

bool shape_plot(shape_t *me, image_t *image){
	int x;
	int y;

	for (int i = 0; i<(me->array.n_array); i++){
		x = me->array.coordinates[i].x + me->position.x;
		y = me->array.coordinates[i].y + me->position.y;

		printf("plot point (%d,%d).\n", x, y);
		image_write(image, x, y, HIGH);	
	}
//	presupongo que el control del tamaño está dentro de image_write
	return true;
}
