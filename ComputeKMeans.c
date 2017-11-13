/*
Purpose: It Computes the KMean algorithm on an input image and generates K cluster specific images. Each generated new cluster specific image has the particular cluster’s all pixels set as 255 and all other pixels as 0.
Author: Sahil Gupta
Parameters: [input image filename] [No of images to output(value of K)] [output FolderName] 
Date: 08/04/2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ImageOperation.h"

int i,j,k;
int* cImage;
int iWidth,iHeight;
char cArray[3][100];

int assign_k(int val, int mean_values[]){
	int min_val=0;
	int min=abs(mean_values[0]-val);
	for (int i=0;i<k;i++){
		if (abs(mean_values[i]-val)<min){
			min=abs(mean_values[i]-val);
			min_val=i;
		}
	}
	return min_val;
}

void main(int argc, char* argv[])
{

		if(argc!=4){
			printf("ERROR: Usage: HideMessage [input image filename] \n");
			return;
		}

		time_t t;
		srand((unsigned) time(&t));
		int change,store_change;
		k=atoi(argv[2]);

		char TempArray[99]="./";
		char newarray[99];
			
		FILE *filePointer = NULL;
		FILE** filePointerOut = malloc(sizeof(FILE*)*k);
		filePointer = fopen(argv[1],"r");
		strcat(TempArray,argv[3]);
		strcpy(newarray,TempArray);
		mkdir(TempArray, 0777);

		for (i=0;i<k;i++){
			strcpy(TempArray,newarray);
			sprintf(TempArray, "%s/%d.pgm",newarray, i);
			filePointerOut[i] = fopen(TempArray,"w");	
		}			
		if (filePointer == NULL)
		{
			printf("cannot open file");	
		}
		else
		{	
			cImage=ReadImage(filePointer);
			for (i=0;i<k;i++){
				fputs(cArray[0], filePointerOut[i]);
			}
			for (i=0;i<k;i++){
				fputs(cArray[1], filePointerOut[i]);
			}
			for (i=0;i<k;i++){
				fprintf(filePointerOut[i],"%d %d\n", iWidth, iHeight);
			}
			for (i=0;i<k;i++){
				fputs(cArray[2], filePointerOut[i]);
			}
			
			int k_values[iHeight*iWidth];
			int mean_values[k];
			int count_k[k];
			
			for (i=0;i<k;i++){
				mean_values[i]=rand()%256;
			}

		do {
			change=0;store_change=0;

			for (i = 0; i< iHeight*iWidth; i++){
				change=(k_values[i]==assign_k(cImage[i],mean_values))?0:1;
				k_values[i]=assign_k(cImage[i],mean_values);
				if(change==1) store_change=1;
			}

			for (i=0;i<k;i++){
					mean_values[i]=0;
					count_k[i]=0;
			}	

			for (i = 0; i< iHeight*iWidth; i++){
					mean_values[k_values[i]]=mean_values[k_values[i]]+cImage[i]; count_k[k_values[i]]++;
			}

			for (i=0;i<k;i++){
				if (count_k[i]!=0){
					mean_values[i]=mean_values[i]/count_k[i];
				}			
			}

			for (i = 0; i< iHeight*iWidth; i++)
			{
				for (j=0;j<k;j++){
					if (k_values[i]==j){
						fprintf(filePointerOut[j], "%d ", 255);
					}
					else{
						fprintf(filePointerOut[j], "%d ", 0);
					}
				}
					
			}

		} while(store_change==1);
		
		}

		fclose(filePointer);
		for (i=0;i<k;i++){
			fclose(filePointerOut[i]);
		}
	
}
