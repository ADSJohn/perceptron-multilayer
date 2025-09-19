#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_LINHAS 5
#define N_COLUNAS 6

float **inicializaPesos(float **pesos, int lin, int col)
{
    int i, j;
    pesos = malloc(lin * sizeof(float *));
    for (i = 0; i < lin; i++)
    {
        pesos[i] = malloc(col * sizeof(float));
    }
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            pesos[i][j] = (float)rand() / RAND_MAX;
        }
    }
    return pesos;
}

float **alocaMatriz(float **matriz, int numero_linhas, int numero_colunas)
{
    int i = 0;
    matriz = malloc(numero_linhas * sizeof(float *));
    for (i = 0; i < numero_linhas; i++)
    {
        matriz[i] = malloc(numero_colunas * sizeof(float));
    }
    return matriz;
}

void liberaMatriz(float **matriz, int lin)
{
    if (matriz == NULL)
    {
        printf("Matril nula");
    }
    else
    {
        int i;
        for (i = 0; i < lin; i++)
        {
            free(matriz[i]);
        }
        free(matriz);
        printf("Memoria liberada!");
    }
}

void lerArquivo(float **dados)
{

    FILE *file = fopen("dados.txt", "r");
    int i = 0;
    int j = 0;

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    for (i = 0; i < N_LINHAS; i++)
    {
        for (j = 0; j < N_COLUNAS; j++)
        {
            fscanf(file, "%f", &dados[i][j]);
        }
    }
    fclose(file);
    file = NULL;
}

float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}

void imprimeMatriz(float **matriz, int numero_linhas, int numero_colunas)
{
    int i = 0, j = 0;
    for (i = 0; i < numero_linhas; i++)
    {
        for (j = 0; j < numero_colunas; j++)
        {
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
}

float *propagacao(float *entradas, float **pesos, float bias, int l, int c, float *saida)
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            saida[i] += (entradas[j] * pesos[i][j]);
        }
        saida[i] += (bias * 1);
        saida[i] = sigmoid(saida[i]);
    }
    return saida;
}

float *deltaO(float *saidaEspearada, float *uo, int l, float *delta)
{
    int i;
    for (i = 0; i < l; i++)
    {
        delta[i] = -(saidaEspearada[i] - uo[i]) * uo[i] * (1 - uo[i]);
    }
    return delta;
}

float *deltaH(float **pesos, float *deltao, float *uh, int l, int c, float *deltah)
{
    printf("ok");
    int i, j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            deltah[i] += (pesos[j][i] * deltao[j]);
        }
        deltah[i] *= uh[i] * (1 - uh[i]);
    }
    return deltah;
}

void atualizaPesos(float **pesos, float *entradas, float *delta, float taxaAprendizagem, int l, int c)
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            pesos[i][j] = pesos[i][j] - taxaAprendizagem * delta[i] * entradas[j];
        }
    }
}

int main()
{

    float **matriz = alocaMatriz(NULL, N_LINHAS, N_COLUNAS);
    lerArquivo(matriz);
    imprimeMatriz(matriz, N_LINHAS, N_COLUNAS);

    // srand(time(NULL));

    // float **pesos1;
    // float **pesos2;
    // float **matriz;
    // float bias[2] = {0.5, 0.3};
    // float *saidaEsperada = malloc(1 * sizeof(float));
    // saidaEsperada[0] = 0.95;
    // float *uh = malloc(sizeof(float) * camadas[1]);
    // float *uo = malloc(camadas[2] * sizeof(float));
    // int epoca = 0;
    // float *deltao = malloc(camadas[2] * sizeof(float));
    // float *deltah = malloc(camadas[1] * sizeof(float));

    // pesos1 = inicializaPesos(pesos1, camadas[1], camadas[0]);
    // pesos2 = inicializaPesos(pesos2, camadas[2], camadas[1]);

    // entradas = alocaMatriz(entradas, 1, 7);
    // lerArquivo(entradas);

    // while (epoca < 1000)
    // {
    //     imprimeMatriz(pesos1, camadas[1], camadas[0]);
    //     printf("\n");
    //     imprimeMatriz(pesos2, camadas[2], camadas[1]);
    //     uh = propagacao(entradas[0], pesos1, bias[0], camadas[1], camadas[0], uh);
    //     uo = propagacao(uh, pesos2, bias[1], camadas[2], camadas[1], uo);
    //     deltao = deltaO(saidaEsperada, uo, camadas[2], deltao);
    //     printf("Aqui...");
    //     deltah = deltaH(pesos2, deltao, uh, camadas[1], camadas[2], deltah);

    //     atualizaPesos(pesos2, uh, deltao, 0.5, camadas[2], camadas[1]);
    //     atualizaPesos(pesos1, entradas[0], deltah, 0.5, camadas[1], camadas[0]);

    //     printf("Epoca: %d\n", epoca);
    //     printf("Erro: %f\n", (saidaEsperada[0] - uo[0]));
    //     printf("Saida: %f\n", uo[0]);
    //     epoca++;
    // }

    // liberaMatriz(pesos1, camadas[1]);
    // liberaMatriz(pesos2, camadas[2]);
    // free(saidaEsperada);
    // liberaMatriz(entradas, 1);
    // free(uh);
    // free(uo);

    return 0;
}