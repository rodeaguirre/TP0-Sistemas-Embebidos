#include "rectangle.h"
#include "line.h"
#include "shape.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>


/*			w1
		--------
	 h2	|      |
		|      |h1
		--------
			w2

*/

static void array_add_all (coordinates_array_t* array, shape_t* shape_to_add, int* i){	
	for (int j = 0;j< (shape_to_add->array.n_array);j++,(*i)++){
		array->coordinates[*i].x = shape_to_add->array.coordinates[j].x + shape_to_add->position.x;
		array->coordinates[*i].y = shape_to_add->array.coordinates[j].y + shape_to_add->position.y;
	}

}


static bool init_rectangle (rectangle_t * me, line_t* w1, line_t* w2, line_t* h1, line_t* h2){
	int i;
	uint32_t length = (w1->super.array.n_array) + (w2->super.array.n_array) + (h1->super.array.n_array) + (h2->super.array.n_array);
	me->super.array.n_array = length;

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




bool rectangle_ctor(rectangle_t *me, uint32_t position_x, uint32_t position_y, uint32_t height, uint32_t width){
	static size_t n_Rectangles;
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

	
	return init_rectangle(me, &w1,&w2,&h1,&h2);

}


bool rectangle_rotate(rectangle_t *me, float angle){
	
	line_t w1, w2, h1, h2;
	
	uint32_t height = me->height, width = me->width;

	line_ctor(&w1, 0 ,  	 0 ,		width-1,  	0);
	line_ctor(&h1, width-1,  0 , 		width-1,  	height-1);
	line_ctor(&w2, width-1,  height-1, 	0 ,  		height-1);
	line_ctor(&h2, 0 , 		 height-1 ,	0 ,  		0 );

	line_rotate(&w1, angle);
	line_rotate(&w2, angle);
	line_rotate(&h1, angle);
	line_rotate(&h2, angle);

	
	shape_move(&(h1.super), w1.end.x, w1.end.y);
	shape_move(&(w2.super), h1.end.x, h1.end.y);
	shape_move(&(h2.super), w2.end.x, w2.end.y);

	shape_dtor(&(me->super));

	return init_rectangle(me, &w1,&w2,&h1,&h2);
}


void rectangle_dtor(rectangle_t *me){
	shape_dtor(&(me->super));
}


uint32_t rectangle_get_area(rectangle_t *me){
	return (me->height)*(me->width);
}
