/* ***********************************************

Nome: Danilo Aleixo Gomes de Souza
N USP: 7972370

Prof: Yoshiharu Kohayakawa

EP2.c
Calculando a densidade normalizada de um grafo de D dimensoes, distruibuidos
uniformemente em um hipercubo ou numa hiperesfera

************************************************ */




#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"Point.h"
#include"StringOps.h"

/* Conexao onde guardaremos informaçoes das arestas */
typedef struct conexao
{
    float distancia;
    struct conexao *proxConexao;
    int numeroVertice;
} Conexao;

/* Ponto onde guardaremos informaçoes dos vertices */
typedef struct ponto
{
    points coords ;
    int nVertice;
    Conexao *conectadoCom;
} Ponto;


#define TRUE 1
#define FALSE 0


/*declaraçao de funçoes utilizadas */
float menorDistanciaBusca(Ponto *grafo, int n, int D);
float densidadeNormalizada(Ponto *grafo, int n, int m, int queroVerLimiar, int queroVerVerts, int D);
void montaGrafo(Ponto *grafo, int N, float d, int D, int queroVerVerts);
Ponto *geraPontosAleatorios(Ponto *grafo, int N, int C, int D);
int conexo(Ponto *grafo, int n);
int recursao(Ponto *grafo, int n, int *jaVisitei, int pontoAnalisado, int *cont);

/* ---------------------------- */


int main(int argc, char *argv[])
{
    Ponto *grafo; /* vetor de Pontos q guardarao as informaçoes do grafo */
    int N = 0; /* numero de pontos do grafo */
    int M = 0; /* numero de istancias que geram a densidade */
    float d = 0; /* distancia entre os pontos */
    int C = FALSE; /* dar os vertices pela linha de comando */
    int queroVerVerts = FALSE; /* se o usuario entrar com -v queroVerVerts = True */
    int queroVerLimiar = FALSE; /* imprime os limiares de conexidade */
    int L = 0; /* verificar menor distancia pelos pontos passados pela linha de comando*/
    int D = 0; /*Dimensoes*/
    int seed = 1; /* inicializamos a semente com 1 */
    int grafoConexo;
    float densNormalizada;
    int i, j;


    int numeroEntradas = argc - 1;

    if(numeroEntradas == 0)
    {
        printf("Modo de utlização   ep1 <entradas> \n"
               "As possiveis entradas sao: \n"
               "\n"
               "-M  para denotar o numero de instancias para a densidade normalizada \n"
               "-N  para denotar o numero de pontos do grafo \n"
               "-D numero de dimensoes \n "
               "-d para informar a distancia minima entre dois vertices que forma uma aresta  \n"
               "-s para mudar a semente da funcao que gera as coordenadas randomicas \n"
               "-v para mostrar as coordenadas dos vertices ou para mostrar os limiares de conexividade das M instancias\n"
               "-V para mostrar as coordenadas dos vertices do M grafos gerados \n"
               "-C para entrar com as coordenadas dos vertices pela linha de comando para testar sua conexividade \n"
               "-L para entrar com as coordenadas dos vertices pela linha de comando e calcular a menor distancia que torna o grafo conexo \n "
               "\n");
    }

    /* Vamos ler as entradas dada pela linha de comando */
    while (numeroEntradas > 0)
    {
        switch(argv[numeroEntradas][1])
        {
        case 'M':
            M = (int) extraiNumero(argv[numeroEntradas]);
            break;

        case 'N':
            N = (int) extraiNumero(argv[numeroEntradas]);
            break;

        case 'd':
            d =  extraiNumero(argv[numeroEntradas]);
            break;

        case 's':
            seed =  (int)extraiNumero(argv[numeroEntradas]);
            break;

        case 'v':
            queroVerVerts = TRUE;
            break;

        case 'V':
            queroVerLimiar = TRUE;
            break;

        case 'C':
            C = TRUE;
            break;

        case 'L':
            L = TRUE;
            break;

        case 'D':
            D =  extraiNumero(argv[numeroEntradas]);
            break;

        default:
            fprintf(stderr, "Entrada Invalida \n"
                    "As possiveis entradas sao: \n"
                    "\n"
                    "-M  para denotar o numero de instancias para a densidade normalizada \n"
                    "-N  para denotar o numero de pontos do grafo \n"
                    "-D numero de dimensoes \n "
                    "-d para informar a distancia minima entre dois vertices que forma uma aresta  \n"
                    "-s para mudar a semente da funcao que gera as coordenadas randomicas \n"
                    "-v para mostrar as coordenadas dos vertices ou para mostrar os limiares de conexividade das M instancias\n"
                    "-V para mostrar as coordenadas dos vertices do M grafos gerados \n"
                    "-C para entrar com as coordenadas dos vertices pela linha de comando para testar sua conexividade \n"
                    "-L para entrar com as coordenadas dos vertices pela linha de comando e calcular a menor distancia que torna o grafo conexo \n "
                    "\n");
            exit(-1);
        }

        numeroEntradas--;
    }

    /*inicializamos o srand */
    srand(seed);

    /* vamos testar a conectividade do grafo */
    if(d != 0)
    {
        if(C == TRUE)
        {
            printf("Digite o numero de pontos: \n");
            scanf("%d", &N);

            printf("Digite o numero de pontos e numero de dimensoes (n pontos, n dimensoes)\n");
            scanf("\n  (%d, %d)",  &N, &D);
            setDimension(D);


        }

        grafo = geraPontosAleatorios(grafo, N, C, D);


        montaGrafo(grafo, N, d, D, queroVerVerts);
        grafoConexo = conexo(grafo, N);
        if(grafoConexo == FALSE) printf("O grafo nao e conexo\n");
        else printf("O grafo e conexo\n");
    }

    /* testamos o limiar de conexidade*/
    if(M != 0)
    {
        i = queroVerLimiar;
        queroVerLimiar = queroVerVerts;
        queroVerVerts = i;

        densNormalizada = menorDistanciaBusca(grafo, N, D);

        printf("A densidade normalizada e %f\n", densNormalizada);

    }

    /*caso queiramos encontrar a menor distancia de um grafo passado pela linha de comando */
    if(L == TRUE)
    {

        printf("Digite o numero de pontos: \n");
        scanf("%d", &N);

        printf("Digite o numero de pontos e numero de dimensoes (n pontos, n dimensoes)\n");
        scanf("\n  (%d, %d)",  &N, &D);
        setDimension(D);

        grafo = geraPontosAleatorios(grafo, N, 1, D);

        densNormalizada = menorDistanciaBusca(grafo, N, D);
        printf("A menor distancia que torna o grafo conexo e %f\n", densNormalizada);

    }

    return 0;

}

/* ________________________FUNCOES AUXILIARES ___________________________ */


/* essa funçao cria as coordenadas aleatorias dos vertices */
Ponto *geraPontosAleatorios(Ponto *grafo, int N, int C, int D)
{
    int i, j;
    float x;


    /* alocamos o vetor dos pontos do grafo */
    grafo = mallocSafe(N * sizeof(Ponto));

    /* setamos a dimensao */
    setDimension(D);


    if(C == TRUE)
    {


        printf("Digite as coordenadas dos %d pontos \n", N);
        for(i = 0; i < N; i++)
        {
            grafo[i].coords = mallocSafe(D * sizeof(float));

            for(j = 0; j < D; j++)
            {
                scanf("%f", &x);
                grafo[i].coords[j] = x;
            }
            grafo[i].nVertice = i;
            grafo[i].conectadoCom = NULL;
        }

    }
    else
    {
        for(i = 0; i < N; i++)
        {
            grafo[i].coords = randPoint();
            grafo[i].nVertice = i;
            grafo[i].conectadoCom = NULL;
        }
    }

    return grafo;
}

/* cria as arestas do grafo, por meio de uma lista de adjacencia */
void montaGrafo(Ponto *grafo, int N, float d, int D, int queroVerVerts)
{
    int i, j, k;
    Conexao *aux1, *aux2, *auxil;
    float dist;

    setDimension(D);


    /* lista de adjacencia */
    for(i = 0; i < N; i++)
    {

        /* verificamos os pontos que podem estar ligados */
        for(j = i + 1; j < N; j++)
        {
            /* se a dist for menor que o d, entao temos uma aresta */
            dist = distance(grafo[i].coords, grafo[j].coords);
            if(dist <= d)
            {
                aux1 = mallocSafe(sizeof(Conexao));
                aux1->distancia = dist;
                aux1->proxConexao = grafo[i].conectadoCom;
                aux1->numeroVertice = j;
                grafo[i].conectadoCom = aux1;

                /* como a aresta e uma ligaçao de dois vertices, colocamos essa mesma
                aresta no ponto j */
                aux2 = mallocSafe(sizeof(Conexao));
                aux2->distancia = dist;
                aux2->proxConexao = grafo[j].conectadoCom;
                aux2->numeroVertice = i;
                grafo[j].conectadoCom = aux2;
            }

        }

        /* se quisermos ver os vertices */
        if(queroVerVerts == TRUE)
        {
            printf("ponto %d ", grafo[i].nVertice);
            for(k = 0; k < D; k++)
            {
                printf("%f   ",grafo[i].coords[k]);
            }
            printf("conectadoCom: ");
            if(grafo[i].conectadoCom == NULL) printf("NULL\n");
            else
            {
                for(auxil = grafo[i].conectadoCom; auxil != NULL; auxil = auxil->proxConexao )
                {
                    printf("%d, ", auxil->numeroVertice);
                }
            }
            printf("\n");
        }

    }/* fim do primeiro for*/

}

/* verifica se o grafo e conexo com N vertices*/
int conexo(Ponto *grafo, int n)
{
    int jaVisitei[n];
    int i;
    int pontoAnalisado = 0;
    for(i = 0; i < n; i++) jaVisitei[i] = FALSE; /* resetamos o vetor */
    int cont = 0;

    return recursao(grafo, n, jaVisitei, pontoAnalisado, &cont);

}

/* parte recursiva da verificaçao de conexidade*/
int recursao(Ponto *grafo, int n, int *jaVisitei, int pontoAnalisado, int *cont)
{
    Conexao *aux;

    /* Testamos se todos os pontos ja foram analisados
    se ja visitamso todos os pontos retornamos TRUE */
    if(*cont == n) return TRUE;

    jaVisitei[pontoAnalisado] = TRUE;
    *cont = *cont + 1;

    /* fazemos chamadas recursivas para analisar os outros pontos */
    for(aux = grafo[pontoAnalisado].conectadoCom; aux != NULL; aux = aux->proxConexao)
    {
        if(jaVisitei[aux->numeroVertice] == FALSE) recursao(grafo, n, jaVisitei, aux->numeroVertice, cont);
    }

    /* Testamos se todos os pontos ja foram analisados
    se ja visitamso todos os pontos retornamos TRUE */
    if(*cont > n - 1) return TRUE;
    else return FALSE;

}

/* calcumos a densidade normalzada de N vertices para M instancias */
float densidadeNormalizada(Ponto *grafo, int n, int m, int queroVerLimiar, int queroVerVerts, int D)
{
    float limiarConect;
    float mediaLimiar = 0;
    int loop = m;
    int i, j;
    Ponto *copiaGrafo = grafo;

    /* fazemos o procedimento M vezes */
    while(loop > 0)
    {
        copiaGrafo = geraPontosAleatorios(copiaGrafo, n, 0, D); /* geramos o grafo */

        if(queroVerVerts == TRUE)
        {
            for(i = 0; i < n; i++)
            {
                printf("ponto: %d", copiaGrafo[i].nVertice);
                for(j = 0; j < D; j++)
                {
                    printf("%f   ",grafo[i].coords[j]);
                }
            }
            printf("\n");
        }

        /* calcula-se a menor Distancia */
        limiarConect = menorDistanciaBusca(copiaGrafo, n, D);
        mediaLimiar += limiarConect;
        if(queroVerLimiar == TRUE) printf("O limiar de conectividade e %f\n", limiarConect);
        loop--;
        free(copiaGrafo);

    }

    return mediaLimiar / m;
}
/* usamos uma busca binaria para achar um d cada vez mais proximo do menor d que torna o grafo conexo */
float menorDistanciaBusca(Ponto *grafo, int n, int D)
{
    float menorDist = 0;
    float inicioIntervalo = 0, finalIntervalo = 2, meio;
    float erro = pow(10, -6); /* erro */
    int eConexo;
    int i;



    while( (finalIntervalo - inicioIntervalo) > erro )
    {
        meio = (finalIntervalo + inicioIntervalo) /2 ;

        montaGrafo(grafo, n, meio, D, 0);
        eConexo = conexo(grafo, n);

        for(i = 0; i < n; i++) grafo[i].conectadoCom = NULL; /* resetamos o grafo */

        if(eConexo == TRUE) finalIntervalo = meio;
        else inicioIntervalo = meio;

    }
    menorDist = meio;


    printf("Menor Distancia: %f\n", menorDist);
    return menorDist;


}



