#include "rectangle.h"
#include "line.h"
#include "shape.h"
#include "const.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


/*			w1
		--------
	 h2	|      |
		|      |h1
		--------
			w2

*/

static inline void array_add_all (coordinates_array_t* array, shape_t* shape_to_add, int* i){

	coordinate_t coordinate_shape_to_add;
	coordinate_t *coordRect;

	if (((*i)<0 || (*i)>=array->n_array)){
		printf("====================> Error al cargar en rectangulo. Indice invalido: %d", *i);
		return;
	}

	for (int j = 0;j< (shape_to_add->array.n_array);j++,(*i)++){
		coordinate_shape_to_add = shape_to_add->array.coordinates[j];
		coordRect= &array->coordinates[*i];
		coordRect->x = coordinate_shape_to_add.x + shape_to_add->position.x;
		coordRect->y = coordinate_shape_to_add.y + shape_to_add->position.y;

	}
}


static bool init_rectangle (rectangle_t * me, line_t* w1, line_t* w2, line_t* h1, line_t* h2){
	int i=0;
	int length = (w1->super.array.n_array) + (w2->super.array.n_array) + (h1->super.array.n_array) + (h2->super.array.n_array);
	me->super.array.n_array = length;

	printf("initRec: x:%d, y:%d, length=%d\n",me->super.position.x , me->super.position.y, length);
	if (!(shape_ctor(&(me->super), &(me->super.array), me->super.position.x , me->super.position.y))){
		return false;
	}

	//Incorporo los arrays de las lineas al array del rectangulo.
	array_add_all ( &(me->super.array),  &(w1->super), &i);
	array_add_all ( &(me->super.array),  &(w2->super), &i);
	array_add_all ( &(me->super.array),  &(h1->super), &i);
	array_add_all ( &(me->super.array),  &(h2->super), &i);

	//Liberar objetos.
	line_dtor(w1);
	line_dtor(w2);
	line_dtor(h1);
	line_dtor(h2);
	return true;
}

static size_t n_Rectangles;

bool rectangle_ctor(rectangle_t *me, int position_x, int position_y, int height, int width){
	line_t w1;
	line_t w2;
	line_t h1;
	line_t h2;

	n_Rectangles++;
	
	me->super.position.x = position_x;
	me->super.position.y = position_y;
	me->height = height;
	me->width = width;
	me-> rotation_angle = 0;

	line_ctor(&w1, 0 ,  	 0 ,		width-1,  	0);
	line_ctor(&h1, width-1,  0 , 		width-1,  	height-1);
	line_ctor(&w2, width-1,  height-1, 	0 ,  		height-1);
	line_ctor(&h2, 0 , 		 height-1 ,	0 ,  		0 );
	
	return init_rectangle(me, &w1,&h1,&w2,&h2);

}

bool rectangle_rotate(rectangle_t *me, float angle){
	
	printf("Rotating rectangle to angle %.2fPI\n", angle);

	me->rotation_angle += angle;
	angle = me->rotation_angle;
	line_t w1, w2, h1, h2;
	
	int height = me->height, width = me->width;

	line_ctor(&w1, 0 ,  	 0 ,		width-1,  	0);
	line_ctor(&h1, width-1,  0 , 		width-1,  	height-1);
	line_ctor(&w2, width-1,  height-1, 	0 ,  		height-1);
	line_ctor(&h2, 0 , 		 height-1 ,	0 ,  		0 );

	line_rotate(&w1, angle);
	line_rotate(&h1, angle);
	line_rotate(&w2, angle);
	line_rotate(&h2, angle);

	int w1x_end = w1.end.x + w1.super.position.x; //7
	int w1y_end = w1.end.y + w1.super.position.y; //1
	int h1x_end = h1.end.x + w1x_end; //6
	int h1y_end = h1.end.y + w1y_end; //6
	int w2x_end = w2.end.x + h1x_end; //0
	int w2y_end = w2.end.y + h1y_end; //5

	printf("shape_move(&(h1.super), %d, %d)\n", w1x_end, w1y_end);
	shape_move(&(h1.super), w1x_end, w1y_end);
	printf("shape_move(&(w2.super), %d, %d)\n", h1x_end, h1y_end);
	shape_move(&(w2.super), h1x_end, h1y_end);
	printf("shape_move(&(h2.super), %d, %d)\n", w2x_end, w2y_end);
	shape_move(&(h2.super), w2x_end, w2y_end);

	shape_dtor(&(me->super));

	return init_rectangle(me, &w1,&h1,&w2,&h2);
}


void rectangle_dtor(rectangle_t *me){
	n_Rectangles--;
	shape_dtor(&(me->super));
}


int rectangle_get_area(rectangle_t *me){
	return (me->height)*(me->width);
}
