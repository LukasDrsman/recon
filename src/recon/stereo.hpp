#ifndef STEREO_H
#define STEREO_H

#include <stdio.h>
#include <float.h>
#include <math.h>
#include "../math/vec.hpp"

namespace re
{
	class Stereo
	{
		public:
			Camera l, r;
			double RP[4];

			Stereo(Camera _l, Camera _r)
			:   l(_l), r(_r)
			{
				// precompute constant reconstruction parameters
				RP[0] = l.f[0] * l.O[0];	// l{ fx * cx }
				RP[1] = r.f[0] * r.O[0];	// r{ fx * cx }
				RP[2] = l.O[2] - r.O[2];	// l{ cz } - r{ cz }
				RP[3] = 1 / l.f[1];			// l{ 1 / fy }
			}

			void triangulate(double *dest, double *u, double *v)
			{
				// precompute frequent values
				double pu, pv, R;
				pu = l.p[0] - u[0];
				pv = 1 / (r.p[0] - v[0]);		// pv only used in inverse form
				R = pu * pv;

				dest[0] = (RP[2] * pu - RP[1] * R + RP[0]) / (l.f[0] - r.f[0] * R);
				dest[2] = r.O[2] + r.f[0] * (r.O[0] - dest[0]) * pv;
				dest[1] = (u[1] - l.p[1]) * (dest[2] - l.O[2]) * RP[3] + l.O[1];
			}

			// dest[i] stores index of pr corresponding to pl[i]
			void match(int *dest, double **pl, double **pr, int plc, int prc, double tresh)
			{
				for (int i = 0; i < plc; i++)
				{
					// construct epipolar line
					double e1[3], e2[3], m, dist;
					dist = DBL_MAX;

					// first epipolar point
					l.ptovWO(e1, pl[i]);

					// second epipolar point
					l.ptovCO(e2, pl[i]);
					m::scale(e2, 2.0, 3);
					m::add(e2, l.O, 3);

					// get projections of e1 and e2 to construct an epipolar line
					r.project(e1, e1);							// ignore e1[2]
					r.project(e2, e2);							// ignore e2[2]
					m = (e2[1] - e1[1]) / (e2[0] - e1[0]);		// slope


					// iterate over pr and find the nearest point
					for (int j = 0; j < prc; j++)
					{
						if (dist < tresh) break;					// break when threshold distance reached

						double dy;
						dy = fabs(pr[j][1] - m * (pr[j][0] - e1[0]) + e1[1]);
						if (dy < dist)
						{
							dist = dy;
							dest[i] = j;
						}
					}
				}
			}
	};
}

#endif
