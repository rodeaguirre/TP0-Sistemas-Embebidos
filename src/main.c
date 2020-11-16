
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "image.h"
#include "rectangle.h"
#include "line.h"
#include "shape.h"
#include "const.h"

#define MAX_IMG_NAME	20

#define N_SECONDS 3
#define N_FRAME_X_SECONDS 24
#define N_FRAMES (N_SECONDS * N_FRAME_X_SECONDS)

#define N_ROWS			200 	// Cantidad de filas
#define N_COLS			N_ROWS	// Cantidad de columnas


/* Ejemplo de uso de las funciones de la clase "imagen" */

int main(void){
	setbuf(stdout,NULL);

	printf("Running main... \n");
	
	image_t img;
	int img_count=0;
	char img_name[MAX_IMG_NAME];
	rectangle_t rectangle;
	line_t line;

	const float final_angle = M_2_PI;
	const float step_angle  = final_angle / N_FRAMES;
	const float step_move   = (float)N_ROWS / ((float) N_FRAMES);
	const float step_factor = 1.0f - ((1.0f / N_FRAMES)*4);
//	const float step_factor = 0.8f;

	int dx=0;
	int dy=0;

	int position_x = 1,  position_y = 1,  height=50,  width=30;

	rectangle_ctor (&rectangle, position_x,  position_y,  height,  width);
	line_ctor (&line, position_x+(width/2),  position_y+(height/2),
			position_x+width-3,  position_y+height-3);

	for(int l=0; l<N_FRAMES; l++){
		printf("l=%d\n",l);
		
		// Construyo el objeto "imagen"
		image_ctor(&img,N_ROWS,N_COLS); 

		// Muevo el rectangulo
		dx=round((float)rectangle.super.position.x + step_move);
		dy=round((float)rectangle.super.position.y + step_move);
		printf("Llamo shape_move: dx=dy=%d\n",l);
		shape_move(&(rectangle.super), dx, dy);

//		//muevo la linea
//		dx=round((float)line.super.position.x + step_move);
//		dy=round((float)line.super.position.y + step_move);
//		printf("Llamo shape_move\n");
//		shape_move(&(line.super), dx, dy);
		
		// ploteo las figuras en la imagen.
		shape_plot(&(rectangle.super), &img);
		shape_plot(&(line.super), &img);

		// Lo guardo en un archivo
		sprintf(img_name,"./images/img%.3d.pbm",img_count); 
		printf("Image name: %s\n", img_name);
		image_to_file(&img,img_name); 
		
		// Libero memoria
		image_dtor(&img); 

		// Roto el rectangulo para la siguiente iteración
		printf("Rotamos el rectangulo a un angulo de: %.2f\n\n", step_angle);
		rectangle_rotate(&(rectangle), step_angle);
		// Roto la linea para la siguiente iteración
		printf("Rotamos la linea a un angulo de: %.2f\n\n", step_angle*2);
		line_rotate(&(line), step_angle*2);
		// Escalo la linea
		printf("EEscalamos la linea por el factor: %.2f\n\n", step_factor);
		line_scale(&(line), step_factor);

		++img_count;
	}/**/
	rectangle_dtor(&rectangle);
	line_dtor(&line);
	return 0;
}
