#include "tp3.h"

int main(int argc, char *argv[]){

  long nrl, nrh, ncl, nch;
	int row, col;

  byte** loadedImage;


  loadedImage = LoadPGM_bmatrix("image.pgm", &nrl, &nrh, &ncl, &nch);

	for (row = nrl; row < nrh; row++) {
		for (col = ncl; col < nch; col++) {
			if(loadedImage[row][col] >= 240){
				loadedImage[row][col] = 255;
				loadedImage[row-1][col] = 255;
				loadedImage[row+1][col] = 255;
			}
		}
	}

	SavePGM_bmatrix(loadedImage, nrl, nrh, ncl, nch, "result.pgm");

  free_bmatrix(loadedImage, nrl, nrh, ncl, nch);

  return 0;
}
