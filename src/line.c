#include "shape.h"
#include "line.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static bool pendiente (line_t *me, float*ret){
	printf("end.y=%d, start.y =%d, end.x=%d, start.x =%d \n", me->end.y, me->start.y,me->end.x, me->start.x);
	if ((me->end.x)==(me->start.x)){
		return true;
	}
	*ret = ((me->end.y)-(me->start.y))/((me->end.x)-(me->start.x));
	return false;
}


static bool ordenada_origen (line_t *me, float*ret){
	float m;
	if(pendiente (me,&m)){
		return true;
	}
	*ret = ((me->start.y) - m*(me->start.x));
	return false;
}


static void array_add_element (coordinates_array_t* array, int i, uint32_t x, uint32_t y){
	array->coordinates[i].x = x;
	array->coordinates[i].y = y;
}

static void point_calculation(line_t *me){
	float m, b, step, x, y;
	uint32_t length = me->super.array.n_array;

	if(pendiente(me,&m)){ //Pendiente infinita
		step = ((me->end.y)-(me->start.y))/(length);
		x = me->start.x;
		for (int i = 0; i<length; i++){

			y = i*step;
			array_add_element(&(me->super.array),i,x,round(y));
		}
	}
	else { //Pendiente finita
		step = ((me->end.x)-(me->start.x))/(length);
		ordenada_origen (me,&b);
		for (int i = 0; i<length; i++){
			x = ((me->start.x + (i*step)));
			y = m*x+b;
			array_add_element(&(me->super.array),i,round(x),round(y));
		}
	}
}





bool line_ctor(line_t *me, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
	static size_t n_Lines;
	n_Lines++;
	
	me->start.x=x1;
	me->start.y=y1;
	me->end.x=x2;
	me->end.y=y2;
	uint32_t length = fmax (abs(x2-x1),abs(y2-y1));
	
	me->super.array.n_array = length;
	
	if (!(shape_ctor(&(me->super), &(me->super.array), fmin(x1,x2) , fmin(y1,y2)))){
		return false;
	}
	point_calculation(me);

	return true;
}

void line_dtor(line_t *me){
	shape_dtor(&(me->super));
}


bool line_rotate(line_t *me, float angle){
  	float hipotenusa = line_get_length(me);
	float angle_actual = atan((me->end.y)-(me->start.y))/((me->end.x)-(me->start.x));
	float new_angle = angle_actual + angle;
	uint32_t new_end_x = (uint32_t)round(hipotenusa* sin(new_angle)) + (me->start.x);
	uint32_t new_end_y = (uint32_t)round(hipotenusa* cos(new_angle)) + (me->start.y);
	shape_dtor(&(me->super));
	line_ctor (me, me->start.x, me->start.y,new_end_x,new_end_y);
	return true;
}


bool line_scale(line_t *me, float factor){
	/*Considero y=m.x+b*/
	float m, b;
	uint32_t new_end_x,new_end_y;
	
	if(pendiente (me,&m)){
		new_end_y = factor*(me->end.y);
	} else{
		ordenada_origen (me,&b);
		new_end_x = factor*(me->end.x);
		new_end_y = m*(new_end_x) + b ;
	}
	shape_dtor(&(me->super));
	line_ctor (me, me->start.x, me->start.y,new_end_x,new_end_y);
	return true;
}


float line_get_length(line_t *me){
  return sqrt(pow((me->start.x)-(me->end.x),2)+pow((me->start.y)-(me->end.y),2));
}
