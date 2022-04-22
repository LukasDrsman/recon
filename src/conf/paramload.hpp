#ifndef PARAMLOAD_H
#define PARAMLOAD_H
#include <stdlib.h>
#include <stdio.h>

namespace c
{
    void paramload(FILE *fp, double *arr, double paramc)
    {
        for (int i = 0; i < paramc; i++)
        {
            int c, idx;
            double pos, realpos;
            pos = 1.0;
            realpos = 1.0;
            idx = -1;
            arr[i] = 0.0;

            while ((c = fgetc(fp)) != ' ')
            {
                if (c == '\n') break;
                if (c == '.')
                {
                    for (int j = 0; j < idx; j++)
                    {
                        realpos *= 10.0;
                    }
                    continue;
                }

                arr[i] += pos * (c - 48);
                pos *= 0.1;
                idx++;
            }

            arr[i] *= realpos;
        }
    }
}

#endif
