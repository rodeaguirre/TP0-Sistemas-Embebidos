#include "shape.h"
#include "line.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>



bool line_ctor(line_t *me, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
	me->start.x=x1;
	me->start.y=y1;
	me->end.x=x2;
	me->end.y=y2;
	uint32_t length = max (abs(x2-x1),abs(y2-y1));
	if(array_init (&(me->super.array), length)){
		point_calculation(coordinates_array_t*)
	}
	if (!(shape_ctor(&(me->super), &(me->super.array), min(x1,x2) , min(y1,y2)))){
		return false;
	}
	return true;
}

static void point_calculation(line_t *me){
	float m = pendiente (me);
	float b = ordenada_origen (me);

	uint32_t length = me->super.array.n_array;

	float step = ((me->end.x)-(me->start.x))/(length);
	
	for (int i = 0; i<length; i++){
		float x = ((me->start.x + (i*step)));
		float y = m*x+b;
		array_add_element(&(me->super.array),i,round(x),round(y));
	}
}


bool line_rotate(line_t *me, float angle){
  	loat hipotenusa = line_get_lenght(me);
	float angle_actual = atan((me->end.y)-(me->start.y))/((me->end.x)-(me->start.x));
	float new_angle = angle_actual + angle;
	uint32_t new_end_x = (uint32_t)round(hipotenusa* sin(new_angle)) + (me->start.x);
	uint32_t new_end_y = (uint32_t)round(hipotenusa* cos(new_angle)) + (me->start.y);
	shape_dtor(&(me->super));
	line_ctor (me, me->start.x, me->start.y,new_end_x,new_end_y);
}


bool line_scale(line_t *me, float factor){
	/*Considero y=m.x+b*/
	float m = pendiente (me);
	float b = ordenada_origen (me);
	uint32_t new_end_x = factor*(me->end.x);
	uint32_t new_end_y = m*(new_end_x) + b ;

	shape_dtor(&(me->super));
	line_ctor (me, me->start.x, me->start.y,new_end_x,new_end_y);
}


float line_get_length(line_t *me){
  return sqrt(pow((me->start.x)-(me->end.x),2)+pow((me->start.y)-(me->end.y),2));
}

static bool array_init (coordinates_array_t* array, uint32_t length){
	if(!(array->coordinates = (coordinates_t*) malloc(length*sizeof(coordinates_t)))){
		return false;
	}
	array->n_array = length;
	return true;
}

static void array_add_element (coordinates_array_t* array, int i, uint32_t x, uint32_t y){
	array->coordinates[i].x = x;
	array->coordinates[i].y = y;
}

static float pentiente (line_t *me){
	return ((me->end.y)-(me->start.y))/((me->end.x)-(me->start.x));
}
static float ordenada_origen (line_t *me){
	return((me->start.y) - m*(me->start.x));
}


	/*
	if(!(me->array.coordinates = (coordinates_t*) malloc((array->n_array)*sizeof(coordinates_t)))){
		return false;
	}

	me->array.n_array = array->array;
	for (int i = 0; i<array->n_array; i++){
		me->array.coordinates[i] = array->coordinates[i];
	}
	*/