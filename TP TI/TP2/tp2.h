#include<stdio.h>
#include<stdlib.h>

#include "def.h"
#include "nrio.h"
#include "nrarith.h"
#include "nralloc.h"

byte** binariseImage(byte** image, long nrl, long nrh, long ncl, long nch, int seuil);

byte** simpleLabeling(byte** image, long nrl, long nrh, long ncl, long nch);

byte** getLabel(byte** image, long nrl, long nrh, long ncl, long nch, byte** labels, int label);
