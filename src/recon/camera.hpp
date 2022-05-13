#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include "../conf/paramload.hpp"

namespace re
{
	class Camera
	{
		public:
			// camera parameters
			double O[3], C[2], f[3], p[2];

			Camera(char *fname)
			{
				FILE *fp = fopen(fname, "r");
				double _P[5];
				c::paramload(fp, O, 3);
				c::paramload(fp, _P, 5);

				// projection parameters
				C[0] = _P[2] / _P[0];	// W conversion ratio
				C[1] = _P[3] / _P[1];	// H conversion ratio
				f[0] = _P[4] / C[0];	// x-dir focal length (fx)
				f[1] = _P[4] / C[1];	// y-dir focal length (fy)
				f[2] = _P[4];			// real focal length (f)
				p[0] = 0.5 * _P[0];		// x offset (px)
				p[1] = 0.5 * _P[1];		// y offset (py)
			}

			// project R^3 vector into R^2 camera image (pixel)
			void project(double *dest, double *v)
			{
				double d = 1 / (v[2] - O[2]);
				for (int i = 0; i < 2; i++)
					dest[i] = d * f[i] * (v[i] - O[i]) + p[i];
			}

			// construct an R^3 vector to the camera screen from a pixel (from world origin)
			void ptovrWO(double *dest, double *v)
			{
				for (int i = 0; i < 2; i++)
					dest[i] = C[i] * (v[i] - p[i]) + O[i];
				dest[2] = f[2] + O[2];
			}

			// construct an R^3 vector to the camera screen from a pixel (from camera origin)
			void ptovCO(double *dest, double *v)
			{
				for (int i = 0; i < 2; i++)
					dest[i] = C[i] * (v[i] - p[i]);
				dest[2] = f[2];
			}
	};
}

#endif
