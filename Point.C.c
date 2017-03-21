#include"Point.h"
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

float CubicDistribution();

/* numero de dimensoes, é acessada atraves do setter */
int D = 0;

points randPoint()
{
    points coords = mallocSafe(D * sizeof(float));
    int i;


    for(i = 0; i < D; i++)
    {
        coords[i] = CubicDistribution();
    }


    return coords;
}

float distance (points p1, points p2)
{
	int i;
	float dist = 0;
	for(i = 0; i < D; i++)
	{
	    dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	    /* depuraçao printf("dist: %f\n", prodInterno);*/
	}
	return sqrt(dist);
}

/* geramos numeros entre 0 e 1 / sqrt(D) */
float CubicDistribution()
{
    float x;

    x = rand() %10000 /10000;

    x *= (1 * sqrt(D));

    return x;

}

void setDimension(int dimension)
{
    D = dimension;
}

