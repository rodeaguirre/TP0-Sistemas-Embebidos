#include "rectangle.h"
#include <stdint.h>
#include <math.h>


bool rectangle_ctor(rectangle_t *me, uint32_t position_x, uint32_t position_y, uint32_t height, uint32_t width){
	return true;
}


bool rectangle_rotate(rectangle_t *me, float angle){
	return true;
}


uint32_t rectangle_get_area(rectangle_t *me){
	return (me->height)*(me->width);
}
