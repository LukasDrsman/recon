#include "vec.h"

void scale(double *dest, double s, int dims)
{
	for (int i = 0; i < dims; i++) dest[i] *= s;
}

void add(double *dest, double *v, int dims)
{
	for (int i = 0; i < dims; i++) dest[i] += v[i];
}