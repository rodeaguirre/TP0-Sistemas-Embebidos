#include "shape.h"
#include "line.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static bool pendiente (line_t *me, float*ret){
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
	printf("x =%d, y =%d, i =%d \n",x,y,i);
}

static void point_calculation(line_t *me){
	float m, b, step, x, y;
	uint32_t length = me->super.array.n_array;
	printf("%d\n",length);

	if(pendiente(me,&m)){ //Pendiente infinita
		printf("Pendiente infinita\n");
		step = (((float)me->end.y)-((float)me->start.y))/(length);
		printf("Calcula step=%f usa length=%d\n",step,length);
		x = me->start.x;
		printf("Calcula x\n");
		for (int i = 0; i<=length; i++){
			y = me->start.y + i*step;
			//printf("%.2f=%d * %.2f",y,i,step);
			array_add_element(&(me->super.array),i,x,round(y));
		}
	}
	else { //Pendiente finita
		printf("Pendiente finita\n");
		step = (((float)me->end.x)-((float)me->start.x))/(length);
		ordenada_origen (me,&b);
		for (int i = 0; i<=length; i++){
			x = (me->start.x) + (i*step);
			y = m*x+b;
			//printf("%.2f=%.2f*%.2f+%.2f , step=%f\n",y,m,x,b,step);
			array_add_element(&(me->super.array),i,round(x),round(y));
		}
	}
	//printf(" start.x =%d, start.y =%d, end.x=%d, end.y=%d\n", me->start.x, me->start.y,me->end.x, me->end.y);
}





bool line_ctor(line_t *me, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
	static size_t n_Lines;
	n_Lines++;
	
	me->start.x=0;
	me->start.y=0;
	me->end.x=x2-x1;
	me->end.y=y2-y1;
	uint32_t length = fmax (abs(x2-x1),abs(y2-y1));
	
	me->super.array.n_array = length;
	
	if (!(shape_ctor(&(me->super), &(me->super.array), fmin(x1,x2) , fmin(y1,y2)))){
		return false;
	}
	printf("Nueva linea (%d,%d)-(%d,%d)\n",x1,y1,x2,y2);
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
