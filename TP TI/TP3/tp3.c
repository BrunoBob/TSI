#include "tp3.h"

int main(int argc, char *argv[]){

  long nrl, nrh, ncl, nch;
	long nrl2, nrh2, ncl2, nch2;

  byte** loadedImage;
  byte** binImage;
	byte** hough;
	byte** result;

  loadedImage = LoadPGM_bmatrix("route4.pgm", &nrl, &nrh, &ncl, &nch);

  binImage = binariseImage(loadedImage, nrl, nrh, ncl, nch, 179);
	hough = accumulationTable(binImage, nrl, nrh, ncl, nch, 1, &nrl2, &nrh2, &ncl2, &nch2);
	result = detectMax(loadedImage, nrl, nrh, ncl, nch, hough, nrl2, nrh2, ncl2, nch2);

  SavePGM_bmatrix(binImage, nrl, nrh, ncl, nch, "binRoute.pgm");
	SavePGM_bmatrix(hough, nrl2, nrh2, ncl2, nch2, "hough.pgm");
	SavePGM_bmatrix(result, nrl, nrh, ncl, nch, "result.pgm");

  free_bmatrix(loadedImage, nrl, nrh, ncl, nch);
  free_bmatrix(binImage, nrl, nrh, ncl, nch);
	free_bmatrix(hough, nrl2, nrh2, ncl2, nch2);
	free_bmatrix(result, nrl, nrh, ncl, nch);

  return 0;
}

byte** binariseImage(byte** image, long nrl, long nrh, long ncl, long nch, int seuil){
  int i,j;
  byte** binImage = bmatrix(nrl, nrh, ncl, nch);

  for(i = nrl ; i < nrh ; i++){
    for(j = ncl ; j < nch ; j++){
      if(image[i][j] > seuil){
        binImage[i][j] = 255;
      }
      else{
        binImage[i][j] = 0;
      }
    }
  }
  return binImage;
}

byte** accumulationTable(byte** image, long nrl, long nrh, long ncl, long nch, int step, long* nrl2, long* nrh2, long* ncl2, long* nch2){
	int diag, angSize, theta, ro;
	byte** accumulationTable;
	int i, j;

	diag = (int) (sqrt(((nrh - nrl) * (nrh - nrl)) + ((nch - ncl) * (nch - ncl)))) + 1;
	angSize = (180 / step) + 1;

	*nrl2 = (long) -diag;
	*nrh2 = (long) diag;
	*ncl2 = 0;
	*nch2 = (long) angSize;

	accumulationTable = bmatrix(*nrl2, *nrh2, *ncl2, *nch2);

	for(i = nrl ; i < nrh ; i++){
    for(j = ncl ; j < nch ; j++){
      if(image[i][j] == 255){
				for(theta = 0 ; theta < 180 ; theta += step){
					ro = j * cos((theta*M_PI/180)) + i * sin(theta*M_PI/180);
					accumulationTable[ro][theta]++;
				}
			}
    }
  }

	return accumulationTable;
}

byte** detectMax(byte** image, long nrl, long nrh, long ncl, long nch, byte** accumulationTable, long nrl2, long nrh2, long ncl2, long nch2){
	int max = 0, maxTheta, maxRo;
	int i, j;

	byte** result = bmatrix(nrl, nrh, ncl, nch);
	copy_bmatrix(image, nrl, nrh, ncl, nch, result, nrl, nrh, ncl, nch);

	for(i = nrl2 ; i < nrh2 ; i++){
    for(j = ncl2 ; j < nch2 ; j++){
			if(accumulationTable[i][j] > max){
				max = accumulationTable[i][j];
				maxRo = i;
				maxTheta = j;
			}
		}
	}

	int x;
	for(x = ncl ; x < nch ; x++){
		int y = (maxRo - (x * cos(maxTheta*M_PI/180))) / sin(maxTheta*M_PI/180);
		if(y > nrl && y < nrh){
					result[y][x] = 0;
		}
	}

	printf("Max = %d %d\n", maxRo, maxTheta);


	return result;
}
