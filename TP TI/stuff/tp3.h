#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "def.h"
#include "nrio.h"
#include "nrarith.h"
#include "nralloc.h"

byte** binariseImage(byte** image, long nrl, long nrh, long ncl, long nch, int seuil);

byte** accumulationTable(byte** image, long nrl, long nrh, long ncl, long nch, int step, long* nrl2, long* nrh2, long* ncl2, long* nch2);

byte** detectMax(byte** image, long nrl, long nrh, long ncl, long nch, byte** accumulationTable, long nrl2, long nrh2, long ncl2, long nch2);
