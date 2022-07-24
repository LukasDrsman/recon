#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include "../conf/paramload.h"

typedef struct Camera
{
	double O[3], C[2], f[3], p[2];
}
camera;

camera cameraNew(char *fname);
void cameraProject(camera this, double* dest, double *v);

#endif