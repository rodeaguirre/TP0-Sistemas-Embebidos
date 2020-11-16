#include "shape.h"
#include "line.h"
#include "const.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static bool pendiente (line_t *me, float*ret){
	if ((me->end.x)==(me->start.x)){
		return true;
	}
	*ret = (((float)me->end.y)-((float)me->start.y))/(((float)me->end.x)-((float)me->start.x));
	return false;
}


static bool ordenada_origen (line_t *me, float*ret){
	float m;
	if(pendiente (me,&m)){
		return true;
	}
	*ret = ((float)me->start.y) - m*((float)me->start.x);
	return false;
}


static inline void array_add_element (coordinates_array_t* array, int i, int x, int y){
	if ((i<0 || i>=array->n_array)){
		printf("====================> Error al cargar en linea. Indice invalido: %d", i);
		return;
	}
	array->coordinates[i].x = x;
	array->coordinates[i].y = y;
	printf("x =%d, y =%d, i =%d \n",x,y,i);
}

static void point_calculation(line_t *me){
	printf("point_calculation\n");
	float m, b, step, x, y;
	int length = me->super.array.n_array;
	printf("length=%d\n",length);

	if(pendiente(me,&m)){ //Pendiente infinita
		printf("Pendiente infinita\n");
		step = ((((float)me->end.y)-((float)me->start.y)))/(length-1);
		printf("Calcula step=%f usa length=%d\n",step,length);
		x = me->start.x;
		printf("Calcula x\n");
		for (int i = 0; i<length; i++){
			y = me->start.y + i*step;
			printf("%.2f=%d * %.2f",y,i,step);
			array_add_element(&(me->super.array),i,x,round(y));
		}
	}
	else { //Pendiente finita
		printf("Pendiente finita\n");
		step = ((((float)me->end.x)-((float)me->start.x)))/(length-1);
		ordenada_origen (me,&b);
		for (int i = 0; i<length; i++){
			x = ((float)me->start.x) + (((float)i)*step);
			y = m*x+b;
			printf("%.2f=%.2f*%.2f+%.2f , step=%f\n",y,m,x,b,step);
			array_add_element(&(me->super.array),i,round(x),round(y));
		}
	}
	printf(" start.x =%d, start.y =%d, end.x=%d, end.y=%d\n", me->start.x, me->start.y,me->end.x, me->end.y);
}

static size_t n_Lines;
bool line_ctor(line_t *me, int x1, int y1, int x2, int y2){
	n_Lines++;
	printf("\n===> Nueva linea (%d,%d)-(%d,%d)\n",x1,y1,x2,y2);
	
	int pos_shape_x = x1; //>x2)?x2:x1;
	int pos_shape_y = y1; //>y2)?y2:y1;

	printf("pos_shape_x=%d, pos_shape_y=%d\n", pos_shape_x, pos_shape_y);

	me->start.x=0;
	me->start.y=0;
	me->end.x=x2-x1;
	me->end.y=y2-y1;
	int length = fmax (abs(me->end.x),abs(me->end.y))+1;
	
	me->super.array.n_array = length;
	
	if (!(shape_ctor(&(me->super), &(me->super.array), pos_shape_x, pos_shape_y))){
		return false;
	}

	printf("Coord internas: (%d,%d)-(%d,%d)\n",me->start.x,me->start.y,me->end.x,me->end.y);
	point_calculation(me);

	return true;
}

void line_dtor(line_t *me){
	n_Lines--;
	shape_dtor(&(me->super));
}

bool line_rotate(line_t *me, float angle){
	printf("\n\nline_rotate: (%d,%d)->(%d,%d)\n",me->start.x, me->start.y,me->end.x, me->end.y);
  	float hipotenusa = line_get_length(me);
  	printf("hipotenusa=%.2f\n",hipotenusa);

  	float lado_a = abs(((float)me->end.y)-((float)me->start.y));
  	float lado_b = abs(((float)me->end.x)-((float)me->start.x));
  	float angle_actual;
  	float beta_actual;
  	if (lado_b == 0){
		printf("tangente=infinita, lado_a=%.2f, lado_b=%.2f\n", lado_a, lado_b);
		if (me->end.y>0){
			angle_actual = M_PI_2;
		}else{
			angle_actual = 3*M_PI_2;
		}
  	}else{
		float tangente = lado_a/lado_b;
		printf("tangente=%.2f, lado_a=%.2f, lado_b=%.2f\n", tangente, lado_a, lado_b);
		beta_actual = atan(tangente);
		if (me->end.x>0){
			if (me->end.y>0){
				angle_actual = beta_actual;
			}else{
				angle_actual = M_2_PI - beta_actual;
			}
		}else{
			if (me->end.y>0){
				angle_actual = M_PI - beta_actual;
			}else{
				angle_actual = M_PI + beta_actual;
			}
		}
  	}

	float new_angle = angle_actual + angle;
	while (new_angle > M_2_PI){
		new_angle -= M_2_PI;
	}
	int sigX=1;
	int sigY=1;
	if (new_angle < M_PI_2){
		beta_actual = new_angle;
	}else if (new_angle < M_PI){
		beta_actual = M_PI - new_angle;
		sigX=-1;
	}else if (new_angle < M_3_PI_2){
		beta_actual = new_angle - M_PI;
		sigX=-1;
		sigY=-1;
	}else{
		beta_actual = M_2_PI - new_angle;
		sigY=-1;
	}
	printf("Rotate: angles, actual=%.2f, param=%.2f, new=%.2f, beta=%.2f, sigX=%d, sigY=%d\n",
			angle_actual, angle, new_angle, beta_actual, sigX, sigY);
	float calc_end_x=sigX * hipotenusa* cos(beta_actual) + ((float)me->start.x);
	float calc_end_y=sigY * hipotenusa* sin(beta_actual) + ((float)me->start.y);
	int new_end_x = (int)round(calc_end_x);
	int new_end_y = (int)round(calc_end_y);
	shape_dtor(&(me->super));
	printf("Generamos la linea rotada: (%d,%d)->(%d,%d)\n",me->start.x, me->start.y,new_end_x,new_end_y);

	return line_ctor(me,
			me->start.x + me->super.position.x,
			me->start.y + me->super.position.y,
			new_end_x   + me->super.position.x,
			new_end_y   + me->super.position.y);
}

bool line_scale(line_t *me, float factor){
	/*Considero y=m.x+b*/
	float m, b;
	int new_end_x,new_end_y;
	
	if(pendiente (me,&m)){
		new_end_x = me->end.x;
		new_end_y = factor*(me->end.y);
	} else{
		ordenada_origen (me,&b);
		new_end_x = round(factor*((float)me->end.x));
		new_end_y = round(m*((float)new_end_x) + b) ;
	}
	shape_dtor(&(me->super));
	line_ctor (me,
			me->start.x + me->super.position.x,
			me->start.y + me->super.position.y,
			new_end_x   + me->super.position.x,
			new_end_y   + me->super.position.y
			);
	return true;
}

float line_get_length(line_t *me){
  return sqrt(pow(((float)me->end.x)-((float)me->start.x),2)+pow(((float)me->end.y)-((float)me->start.y),2));
}
