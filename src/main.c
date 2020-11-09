
#include <stdio.h>
#include "image.h"


#define MAX_IMG_NAME	20

#define N_ROWS			200 	// Cantidad de filas
#define N_COLS			200		// Cantidad de columnas


/* Ejemplo de uso de las funciones de la clase "imagen" */

int main(void){

	printf("Running main... \n");
	
	image_t img;
	int img_count=0;
	char img_name[MAX_IMG_NAME];

	for(int l=10; l<180; l=l+2){

		// Construyo el objeto "imagen"
		image_ctor(&img,N_ROWS,N_COLS); 

		// Lo modifico como yo quiera
		for(int i=0; i<l; i++){
			image_write(&img,i,i,HIGH); 
		}
		
		// Lo guardo en un archivo
		sprintf(img_name,"./images/img%.3d.pbm",img_count); 
		image_to_file(&img,img_name); 
		
		// Libero memoria
		image_dtor(&img); 

		++img_count;
	}

	return 0;
}