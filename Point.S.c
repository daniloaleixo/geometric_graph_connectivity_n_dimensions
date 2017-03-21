#include"Point.h"
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

#define mINF -5 /* menos infinito */
#define MINF +5 /* mais infinito */
#define PI 3.1415926535897


float GaussianDistribution();
points hypershpereDist(points coords);


int D = 0;

points randPoint()
{
    points coords = mallocSafe(D * sizeof(float));

    int i;
    for(i = 0; i < D; i++)
    {
        coords[i] = GaussianDistribution();
    }

    coords = hypershpereDist(coords);


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


/* criamos duas variaveis dentro de uma distribuiçao normal, atraves do metodo de Box-Muller, depois
selecionamos aleatoriamente uma das duas, usamos a distruibuiçao normal, porque se gerarmos pontos
na superficie da esfera a tendencia é eles se concentrarem nos pólos, por isso normalizamos
os numeros gerados, para termos menos pontos nos polos e mais no equador, uniformizando
assim a distribuiçao */
float GaussianDistribution()
{
    float u1 = rand() %100 / 100.0;
    float u2 = rand() %100 / 100.0;

    float a = sqrt(-2 * log(u1)) * cos(2 * PI * u2);
    float b = sqrt(-2 * log(u1)) * sin(2 * PI * u2);

    int x =rand() % 2 + 1;
    /* depuraçao printf("%d\n", x);*/
    /* depuraçao printf("%f\n%f\n", a, b);*/
    if(a == MINF || b == MINF || a == mINF || b == mINF) return GaussianDistribution();
    if(x == 1) return a;
    else return b;
}

/* com os pontos gerados em uma distribuiçao normal, colocamos eles dentro da esfera
e dividimos pelo raio */
points hypershpereDist(points coords)
{
    int i;

    float x = 0;
    for(i = 0; i < D; i++)
    {
        x = x + coords[i] * coords[i];
    }
    x = sqrt(x);
    x = 1 /(2 * x); /* multiplicamos por 2 para os pontos se encontrarem na superficie de uma hiperesfera de raio 1/2*/

    for(i = 0; i < D; i++)
    {
        coords[i] *= x;
    }
    return coords;
}

void setDimension(int dimension)
{
    D = dimension;
}

