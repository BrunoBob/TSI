#include "morpho.h"

int main(){
  return 0;
}

byte** erosion(byte** image, long nrl, long nrh, long ncl, long nch){
  byte** result = bmatrix(nrl, nrh, ncl, nch);

  byte** mask = bmatrix(0,2,0,2);
}

byte** dilation(byte** image, long nrl, long nrh, long ncl, long nch){

}
