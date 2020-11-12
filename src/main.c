
#include <stdio.h>
#include "image.h"
#include "rectangle.h"
#include "line.h"
#include "shape.h"


#define MAX_IMG_NAME	20

#define N_ROWS			40 	// Cantidad de filas
#define N_COLS			40		// Cantidad de columnas


/* Ejemplo de uso de las funciones de la clase "imagen" */

int main(void){
	setbuf(stdout,NULL);

	printf("Running main... \n");
	
	image_t img;
	int img_count=0;
	char img_name[MAX_IMG_NAME];
	rectangle_t rectangle;
	line_t line;
	uint32_t position_x = 1,  position_y = 1,  height=7,  width=8;

	rectangle_ctor (&rectangle, position_x,  position_y,  height,  width);
	line_ctor (&line, position_x+2,  position_y+2,  position_x+10,  position_y+2);

/*	for(int l=10; l<180; l=l+2){*/
	for(int l=0; l<4; l++){
		printf("l=%d",l);
		
		// Construyo el objeto "imagen"
		image_ctor(&img,N_ROWS,N_COLS); 
		printf("Llamo shape_move: dx=dy=%d\n",l);
		shape_move(&(rectangle.super), l, l);
		printf("Llamo shape_move: dx=dy=%d\n",l+3);
		shape_move(&(line.super), l, l*2);
		
		// Construyo el objeto "imagen"
		shape_plot(&(rectangle.super), &img);
		shape_plot(&(line.super), &img);
		

		// Lo guardo en un archivo
		sprintf(img_name,"./images/img%.3d.pbm",img_count); 
		printf(img_name);
		image_to_file(&img,img_name); 
		
		// Libero memoria
		image_dtor(&img); 

		++img_count;
	}/**/
	rectangle_dtor(&rectangle);
	 line_dtor(&line);
	return 0;
}

		/* Lo modifico como yo quiera
		for(int i=0; i<l; i++){
			image_write(&img,i,i,HIGH); 
		}
		*/