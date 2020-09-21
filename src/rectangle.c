#include "shape.h"
#include <stdint.h>
#include <math.h>


typedef struct {
	shape_t super;
	uint32_t height;
	uint32_t width;
	float rotation_angle;
} rectangle_t;



bool rectangle_ctor(rectangle_t *me, uint32_t position_x, uint32_t position_y, 
					uint32_t height, uint32_t width){

}


bool rectangle_rotate(rectangle_t *me, float angle){

}


uint32_t rectangle_get_area(rectangle_t *me){

}
