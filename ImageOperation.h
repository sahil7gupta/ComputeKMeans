/*
Purpose: Contains functions to Reads and writes image data
Author: Sahil Gupta
Parameters: [input image filename] [output image filenane]
Date: 08/04/2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i,j;
extern char cArray[3][100];
extern int iWidth, iHeight;
unsigned int cTemp;

int* ReadImage(FILE* filePointer){
	
	fgets (cArray[0], 99, filePointer);
	printf("%s\n", cArray[0]);
	fgets (cArray[1], 99, filePointer);
	printf("%s\n", cArray[1]);
	fscanf(filePointer,"%d %d\n", &iWidth, &iHeight);
	printf("%d %d \n", iWidth, iHeight);
	fgets (cArray[2], 99, filePointer);
	printf("gray scale Value read - %s\n", cArray[2]);

	int* cImage=malloc(iHeight*iWidth*sizeof(int));

	for (i= 0; i < iHeight*iWidth; i++){
		fscanf(filePointer, "%d ", &cTemp);
		if (cTemp != EOF){
			cImage [i] = cTemp;
		}	
	}

	return cImage;				
}


void WriteImage(FILE* filePointerOut, int* newImage){
	fputs(cArray[0], filePointerOut);
	fputs(cArray[1], filePointerOut);
	fprintf(filePointerOut,"%d %d\n", iWidth, iHeight);
	fputs(cArray[2], filePointerOut);
	for (i= 0; i < iHeight*iWidth; i++){
		if (cTemp != EOF){
			fprintf(filePointerOut, "%d ", newImage[i]);
		}				
	}

}
