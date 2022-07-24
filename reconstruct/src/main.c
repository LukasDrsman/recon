#include <stdlib.h>
#include <stdio.h>
#include "./recon/camera.h"
#include "./recon/stereo.h"

int main(int argc, char *argv[])
{
	char e[4] = {'x', 'y', 'z', 'w'};
	if (argc < 3) return 1;

	camera c1 = cameraNew(argv[1]);
	camera c2 = cameraNew(argv[2]);
	stereo st = stereoNew(c1, c2);

	double v[3] = {30.0, 1.0, 100.0};
	double p1[2], p2[2], r[3];

	cameraProject(c1, p1, v);
	cameraProject(c2, p2, v);

	stereoTriangulate(st, r, p1, p2);

	for (int i = 0; i < 2; i++)
		printf("%c: %f\t%f\n", e[i], p1[i], p2[i]);

	for (int i = 0; i < 3; i++)
		printf("%c: %f\n", e[i], r[i]);
}
