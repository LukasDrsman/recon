#ifndef STEREO_H
#define STEREO_H

#include <stdio.h>
#include <float.h>
#include <math.h>
#include "../math/vec.h"
#include "./camera.h"

typedef struct Stereo
{
	camera l, r;
	double RP[4];
}
stereo;

stereo stereoNew(camera l, camera r);
void stereoTriangulate(stereo this, double *dest, double *u, double *v);

#endif
