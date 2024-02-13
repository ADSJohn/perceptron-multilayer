#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constantes
#define QTD_ENTRADAS 2
#define QTD_PESOS1 4
#define QTD_PESOS2 4
#define QTD_ARESTAS 2
#define QTD_CAMADAS 2

float *mutiplicaEntradaPorPesosAdicionaBias(float entradas[QTD_ENTRADAS], float (*pesos)[QTD_ARESTAS], float bias[QTD_CAMADAS], int camada);
int main(int argc, char const *argv[])
{
	float entradas[2] = {0.05, 0.1};
	float pesos1[2][2] = {{0.15, 0.2}, {0.25, 0.3}};
	float pesos2[2][2] = {{0.4, 0.45}, {0.5, 0.55}};
	float bias[2] = {0.35, 0.6};

	int camada = 0;
	float *resultadosDaMultiplicacao = mutiplicaEntradaPorPesosAdicionaBias(entradas, pesos1, bias, camada);

	free(resultadosDaMultiplicacao);
	return 0;
}

/**Propagando a entrada na primeira camada*/
float *mutiplicaEntradaPorPesosAdicionaBias(float entradas[QTD_ENTRADAS], float (*pesos)[QTD_ARESTAS], float bias[QTD_CAMADAS], int camada)
{
	float *resultados = (float *)malloc(QTD_ENTRADAS * sizeof(float));
	for (int e = 0; e < QTD_ENTRADAS; e++)
	{
		float soma = 0;
		for (int p = 0; p < QTD_ARESTAS; p++)
		{
			soma += entradas[p] * pesos[e][p];
		}
		resultados[e] = (soma + bias[camada]) * 1;
	}
	return resultados;
}