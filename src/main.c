
#include <stdio.h>
#include "image.h"

/* Ejemplo de uso de las funciones de la clase "imagen" */

int main(void){
	
	image_t img;
	image_ctor(&img,200,200); // Construyo el objeto "imagen"

	for(int i=0; i<img.n_cols; i++){
		image_write(&img,i,i,HIGH); // Lo modifico como yo quiero
	}

	image_to_file(&img,"im.pbm"); // Lo guardo en un archivo
	image_dtor(&img); // Libero memoria

	return 0;
}