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
			double O[3], P[7];

			Camera(char *fname)
			{
				FILE *fp = fopen(fname, "r");
				double _P[5];
				c::paramload(fp, O, 3);
				c::paramload(fp, _P, 5);

				// projection parameters
				P[0] = _P[2] / _P[0];	// W conversion ratio
				P[1] = _P[3] / _P[1];	// H conversion ratio
				P[2] = _P[4] / P[0];	// x-dir focal length (fx)
				P[3] = _P[4] / P[1];	// y-dir focal length (fy)
				P[4] = 0.5 * _P[0];		// x offset (px)
				P[5] = 0.5 * _P[1];		// y offset (py)
				P[6] = _P[4];			// real focal length (f)
			}

			// project R^3 vector into R^2 camera image (pixel)
			void project(double *dest, double *v)
			{
				double d = 1 / (v[2] - O[2]);
				for (int i = 0; i < 2; i++)
					dest[i] = d * P[2 + i] * (v[i] - O[i]) + P[4 + i];
			}

			// construct an R^3 vector to the camera screen from a pixel
			void pixelVector(double *dest, double *v)
			{
				for (int i = 0; i < 2; i++)
					dest[i] = P[i] * (v[i] - P[4 + i]) + O[i];
				dest[2] = P[6] + O[2];
			}
	};
}

#endif
