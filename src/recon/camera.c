#include "camera.h"

camera cameraNew(char *fname)
{
	camera this;

	FILE *fp = fopen(fname, "r");
	double P[5];
	paramload(fp, this.O, 3);
	paramload(fp, P, 5);

	// projection parameters
	this.C[0] = P[2] / P[0];		// W conversion ratio
	this.C[1] = P[3] / P[1];		// H conversion ratio
	this.f[0] = P[4] / this.C[0];	// x-dir focal length (fx)
	this.f[1] = P[4] / this.C[1];	// y-dir focal length (fy)
	this.f[2] = P[4];				// real focal length (f)
	this.p[0] = 0.5 * P[0];			// x offset (px)
	this.p[1] = 0.5 * P[1];			// y offset (py)

	return this;
}

// project R^3 vector into R^2 camera image (pixel)
void cameraProject(camera this, double* dest, double *v)
{
	double d = 1 / (v[2] - this.O[2]);
	for (int i = 0; i < 2; i++)
		dest[i] = d * this.f[i] * (v[i] - this.O[i]) + this.p[i];
}