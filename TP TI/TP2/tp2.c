#include "tp2.h"

int main(int argc, char *argv[]){

  long nrl, nrh, ncl, nch;

  byte** loadedImage;
  byte** binImage;
  byte** labelsImage;
  byte** labelImage;

  loadedImage = LoadPGM_bmatrix("rice.pgm", &nrl, &nrh, &ncl, &nch);

  binImage = binariseImage(loadedImage, nrl, nrh, ncl, nch, 115);

  labelsImage = simpleLabeling(binImage, nrl, nrh, ncl, nch);

  labelImage = getLabel(loadedImage, nrl, nrh, ncl, nch, labelsImage, atoi(argv[1]));

  SavePGM_bmatrix(binImage, nrl, nrh, ncl, nch, "binRice.pgm");
  SavePGM_bmatrix(labelsImage, nrl, nrh, ncl, nch, "labelsImage.pgm");
  SavePGM_bmatrix(labelImage, nrl, nrh, ncl, nch, "labelImage.pgm");

  free_bmatrix(loadedImage, nrl, nrh, ncl, nch);
  free_bmatrix(binImage, nrl, nrh, ncl, nch);
  free_bmatrix(labelsImage, nrl, nrh, ncl, nch);
  free_bmatrix(labelImage, nrl, nrh, ncl, nch);

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

byte** simpleLabeling(byte** image, long nrl, long nrh, long ncl, long nch){
  int i,j;
  int** labelImage = imatrix(nrl, nrh, ncl, nch);
  int label = 1;

  for(i = nrl ; i < nrh ; i++){
    for(j = ncl ; j < nch ; j++){
      labelImage[i][j] = 0;
    }
  }

  for(i = nrl ; i < nrh-1 ; i++){
    for(j = ncl ; j < nch-1 ; j++){
      if((image[i+1][j+1] == image[i+1][j]) && (image[i+1][j+1] != image[i][j+1])){
        labelImage[i+1][j+1] = labelImage[i+1][j];
      }
      else if((image[i+1][j+1] == image[i][j+1]) && (image[i+1][j+1] != image[i+1][j])){
        labelImage[i+1][j+1] = labelImage[i][j+1];
      }
      else if((image[i+1][j+1] != image[i+1][j]) && (image[i+1][j+1] != image[i][j+1])){
        labelImage[i+1][j+1] = label;
        label ++;
      }
      else if((image[i+1][j+1] == image[i+1][j]) && (image[i+1][j+1] == image[i][j+1]) && (labelImage[i+1][j] == labelImage[i][j+1])){
        labelImage[i+1][j+1] = labelImage[i][j+1];
      }
      else if((image[i+1][j+1] == image[i+1][j]) && (image[i+1][j+1] == image[i][j+1]) && (labelImage[i+1][j] != labelImage[i][j+1])){
        labelImage[i+1][j+1] = labelImage[i][j+1];

        int  k, l;
        for(k = nrl+1 ; k < nrh-1 ; k++){
          for(l = ncl+1 ; l < nch-1 ; l++){
            if(labelImage[k][l] == labelImage[i+1][j]){
              labelImage[k][l] = labelImage[i][j+1];
            }
          }
        }
      }
    }
  }
  for(i = nrl ; i < nrh ; i++){
    for(j = ncl ; j < nch ; j++){
      labelImage[i][j] = (labelImage[i][j] * 255) / label;
    }
  }

  byte** result = bmatrix(nrl, nrh, ncl, nch);
  for(i = nrl ; i < nrh ; i++){
    for(j = ncl ; j < nch ; j++){
      result[i][j] = (labelImage[i][j] * 255) / label;
      if(result[i][j] != 82){
        //printf("label : %d\n", result[i][j]);
      }
    }
  }
  return result;
}

byte** getLabel(byte** image, long nrl, long nrh, long ncl, long nch, byte** labels, int label){
  int i,j;
  byte** labelImage = bmatrix(nrl, nrh, ncl, nch);
  int mass = 0;
  int massX = 0;
  int massY = 0;

  for(i = nrl ; i < nrh ; i++){
    for(j = ncl ; j < nch ; j++){
      if(labels[i][j] == label){
        labelImage[i][j] = 255;
        mass++;
        massX += j;
        massY += i;
      }
      else{
        labelImage[i][j] = 0;
      }
    }
  }

  massX = massX/mass;
  massY = massY/mass;



  printf("mass = %d %d %d\n", mass, massX, massY);
  return labelImage;
}
