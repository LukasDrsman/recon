#include "paramload.h"

// loads parameters from a line of space-separated config and moves the fp caret
void paramload(FILE *fp, double *dest, double paramc)
{
	for (int i = 0; i < paramc; i++)
	{
		int c, idx;
		double pos, realpos;
		pos = 1.0;
		realpos = 1.0;
		idx = -1;
		dest[i] = 0.0;

		while ((c = fgetc(fp)) != ' ')
		{
			if (c == '\n') break;
			if (c == '.')
			{
				for (int j = 0; j < idx; j++)
					realpos *= 10.0;
				continue;
			}

			dest[i] += pos * (c - 48);
			pos *= 0.1;
			idx++;
		}

		dest[i] *= realpos;
	}
}