
#include <stdio.h>
#include "image.h"
#include "rectangle.h"
#include "line.h"
#include "shape.h"


#define MAX_IMG_NAME	20

#define N_ROWS			200 	// Cantidad de filas
#define N_COLS			200		// Cantidad de columnas


/* Ejemplo de uso de las funciones de la clase "imagen" */

int main(void){
	setbuf(stdout,NULL);

	printf("Running main... \n");
	
	image_t img;
	int img_count=0;
	char img_name[MAX_IMG_NAME];
	rectangle_t rectangle;
	uint32_t position_x = 100,  position_y = 100,  height=20,  width=30;

	rectangle_ctor (&rectangle, position_x,  position_y,  height,  width);

	for(int l=10; l<180; l=l+2){
		printf("l=%d",l);
		// Construyo el objeto "imagen"
		image_ctor(&img,N_ROWS,N_COLS); 
		shape_move(&(rectangle.super), l, l);
		shape_plot(&(rectangle.super), &img);
		/* Lo modifico como yo quiera
		for(int i=0; i<l; i++){
			image_write(&img,i,i,HIGH); 
		}
		*/
		// Lo guardo en un archivo

		sprintf(img_name,"./images/img%.3d.pbm",img_count); 
		printf(img_name);
		image_to_file(&img,img_name); 
		
		// Libero memoria
		image_dtor(&img); 

		++img_count;
	}
	rectangle_dtor(&rectangle);
	return 0;
}