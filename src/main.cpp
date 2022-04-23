#include <stdlib.h>
#include <stdio.h>
#include "./recon/camera.hpp"
#include "./recon/stereo.hpp"

int main(int argc, char *argv[])
{
	char e[4] = {'x', 'y', 'z', 'w'};
	if (argc < 3) return 1;

	re::Camera c1 = re::Camera(argv[1]);
	re::Camera c2 = re::Camera(argv[2]);
	re::Stereo st = re::Stereo(c1, c2);

	double v[3] = {30.0, 2.0, 100.0};
	double p1[2], p2[2], r[3];

	c1.project(p1, v);
	c2.project(p2, v);

	st.triangulate(r, p1, p2);

	for (int i = 0; i < 2; i++) {
		printf("%c: %f\t%f\n", e[i], p1[i], p2[i]);
	}

	for (int i = 0; i < 3; i++) {
		printf("%c: %f\n", e[i], r[i]);
	}
}
