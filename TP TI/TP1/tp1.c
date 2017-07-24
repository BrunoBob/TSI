#include<stdio.h>
#include<stdlib.h>

#include "def.h"
#include "nrio.h"
#include "nrarith.h"
#include "nralloc.h"

byte** convolution(byte** image, long nrl, long nrh, long ncl, long nch, int** mask, int divide){
  byte** result;
  int i,j,k,l;
  for(k = 0 ; k < 3 ; k++){
    for(l = 0 ; l < 3 ; l++){
      divide += mask[k][l];
    }
  }
  result = bmatrix(nrl, nrh, ncl, nch);
  set_bmatrix(result, nrl, nrh, ncl, nch, 0);
  for(i = nrl+1 ; i < nrh-1 ; i++){
    for(j = ncl+1 ; j < nch-1 ; j++){
      int value = 0;
      for(k = 0 ; k < 3 ; k++){
        for(l = 0 ; l < 3 ; l++){
          value += image[i + k - 1][j + l -1] * mask[k][l];
        }
      }
      value = abs(value);
      if(value >= 255){
        value = 255;
      }
      else if(value < 0){
        value = 0;
      }
      result[i][j] = (byte)value;
    }
  }
  return result;
}

int main(){

  long nrl, nrh, ncl, nch;

  byte** loadedImage;
  byte** average;
  byte** sobelhorizontal;
  byte** sobelvertical;
	int** maskAverage;
  int** maskSobelHorizontal;
  int** maskSobelVertical;

  loadedImage = LoadPGM_bmatrix("carre.pgm", &nrl, &nrh, &ncl, &nch);

  //Filtre moyenneur
  maskAverage = imatrix(0, 2, 0, 2);
  set_imatrix(maskAverage, 0, 2, 0, 2, 1);
  display_imatrix0(maskAverage, 3, 3, "%d\t", "Mask");
  average = convolution(loadedImage, nrl, nrh, ncl, nch, maskAverage, 9);
  SavePGM_bmatrix(average, nrl, nrh, ncl, nch, "filtreMoyenneur.pgm");


  //Gradient horizontal
  maskSobelHorizontal = imatrix(0, 2, 0, 2);
  maskSobelHorizontal[0][0] = -1;
  maskSobelHorizontal[0][1] = 0;
  maskSobelHorizontal[0][2] = 1;
  maskSobelHorizontal[1][0] = -2;
  maskSobelHorizontal[1][1] = 0;
  maskSobelHorizontal[1][2] = 2;
  maskSobelHorizontal[2][0] = -1;
  maskSobelHorizontal[2][1] = 0;
  maskSobelHorizontal[2][2] = 1;
  display_imatrix0(maskSobelHorizontal, 3, 3, "%d\t", "Mask Sobel horizontal");
  sobelhorizontal = convolution(loadedImage, nrl, nrh, ncl, nch, maskSobelHorizontal, 1);
  SavePGM_bmatrix(sobelhorizontal, nrl, nrh, ncl, nch, "sobelHorizontal.pgm");

  //Gradient vertical
  maskSobelVertical = imatrix(0, 2, 0, 2);
  maskSobelVertical[0][0] = -1;
  maskSobelVertical[0][1] = -2;
  maskSobelVertical[0][2] = -1;
  maskSobelVertical[1][0] = 0;
  maskSobelVertical[1][1] = 0;
  maskSobelVertical[1][2] = 0;
  maskSobelVertical[2][0] = 1;
  maskSobelVertical[2][1] = 2;
  maskSobelVertical[2][2] = 1;
  display_imatrix0(maskSobelVertical, 3, 3, "%d\t", "Mask Sobel vertical");
  sobelvertical = convolution(loadedImage, nrl, nrh, ncl, nch, maskSobelVertical, 1);
  SavePGM_bmatrix(sobelvertical, nrl, nrh, ncl, nch, "sobelvertical.pgm");


  free_bmatrix(loadedImage, nrl, nrh, ncl, nch);
  free_imatrix(maskAverage, 0, 2, 0, 2);
  free_bmatrix(average, nrl, nrh, ncl, nch);
  free_imatrix(maskSobelHorizontal, 0, 2, 0, 2);
  free_bmatrix(sobelhorizontal, nrl, nrh, ncl, nch);
  free_imatrix(maskSobelVertical, 0, 2, 0, 2);
  free_bmatrix(sobelvertical, nrl, nrh, ncl, nch);

  return 0;
}
