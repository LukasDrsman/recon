#ifndef STEREO_H
#define STEREO_H

#include <stdio.h>

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
                RP[0] = l.P[2] * l.O[0];    // l{ fx * cx }
                RP[1] = r.P[2] * r.O[0];    // r{ fx * cx }
                RP[2] = l.O[2] - r.O[2];    // l{ cz } - r{ cz }
                RP[3] = 1 / l.P[3];         // l{ 1 / fy }
            }

            void triangulate(double *dest, double *u, double *v)
            {
                // precompute frequent values
                double pu, pv, R;
                pu = l.P[4] - u[0];
                pv = 1 / (r.P[4] - v[0]);
                R = pu * pv;

                dest[0] = (RP[2] * pu - RP[1] * R + RP[0]) / (l.P[2] - r.P[2] * R);
                dest[2] = r.O[2] + r.P[2] * (r.O[0] - dest[0]) * pv;
                dest[1] = (u[1] - l.P[5]) * (dest[2] - l.O[2]) * RP[3] + l.O[1];
            }
    };
}

#endif
