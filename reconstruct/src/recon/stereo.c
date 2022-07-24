#include "stereo.h"

stereo stereoNew(camera l, camera r)
{
	stereo this;

	// precompute constant reconstruction parameters
	this.RP[0] = l.f[0] * l.O[0];	// l{ fx * cx }
	this.RP[1] = r.f[0] * r.O[0];	// r{ fx * cx }
	this.RP[2] = l.O[2] - r.O[2];	// l{ cz } - r{ cz }
	this.RP[3] = 1 / l.f[1];		// l{ 1 / fy }

	this.l = l;
	this.r = r;

	return this;
}


void stereoTriangulate(stereo this, double *dest, double *u, double *v)
{
	// precompute frequent values
	double pu, pv, R;
	pu = this.l.p[0] - u[0];
	pv = 1 / (this.r.p[0] - v[0]);		// pv only used in inverse form
	R = pu * pv;

	dest[0] = (this.RP[2] * pu - this.RP[1] * R + this.RP[0]) / (this.l.f[0] - this.r.f[0] * R);
	dest[2] = this.r.O[2] + this.r.f[0] * (this.r.O[0] - dest[0]) * pv;
	dest[1] = (u[1] - this.l.p[1]) * (dest[2] - this.l.O[2]) * this.RP[3] + this.l.O[1];
}


