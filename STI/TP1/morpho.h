#include<stdio.h>
#include<stdlib.h>

#include "def.h"
#include "nrio.h"
#include "nrarith.h"
#include "nralloc.h"

byte** dilation(byte** image, long nrl, long nrh, long ncl, long nch);

byte** erosion(byte** image, long nrl, long nrh, long ncl, long nch);
