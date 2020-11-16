
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "image.h"



bool image_ctor(image_t *me, int n_rows, int n_cols){

	me->n_rows = n_rows;
	me->n_cols = n_cols;

	int dim = sizeof(img_data_t *)*n_cols;
	if ( !(me->data = (img_data_t **)malloc(dim) )){
		return false;
	}
	printf("\n\n ====== Imagen creada de %d columnas, total de %d bytes. =======\n\n", n_cols, dim);

	long tot_mem=0;
	dim = sizeof(img_data_t)*n_rows;
	for(int i=0; i<n_cols; i++){
		if ( !(me->data[i] = (img_data_t *)malloc(dim) )){
			for(int j=0;j<i; j++){
				free (me->data[j]);
			}
			return false;
		}
		tot_mem +=dim;
		for(int j=0; j<n_rows; j++){
			image_write(me, i, j, LOW);
		}
	}

	printf("\n\n ====== Matris alocada para las %d (columnas x filas) por %ld bytes\n",
			(n_cols * n_rows), tot_mem);

	return true;
}


void image_dtor(image_t *me){

	int n_cols = me->n_cols;
	
	for(int i=0; i<n_cols; i++){
		free(me->data[i]);
	}

	free(me->data);
}


void image_write(image_t *me, int i, int j, img_data_t value){
	//printf("i=%d,j=%d,value=%d",i,j,value);
	if (i>=0 && i<me->n_rows && j >=0 && j<me->n_cols){
		me->data[i][j] = value;
	}
}	


img_data_t image_read(image_t *me, int i, int j){
	return me->data[j][i];
}


void image_to_file(image_t *me, const char *filename){

	int n_cols, n_rows;
	FILE *filename_ptr;

	n_rows = me->n_rows;
	n_cols = me->n_cols;

	filename_ptr = fopen(filename, "w+");

	fprintf(filename_ptr, "P1\n%d %d\n", n_cols, n_rows);
	for(int i=0; i<n_cols; i++){
		for(int j=0; j<n_rows; j++){
			fprintf(filename_ptr, "%d ", image_read(me, i, j) );
		}
		fprintf(filename_ptr, "\n");
	}

	fclose(filename_ptr);

}
