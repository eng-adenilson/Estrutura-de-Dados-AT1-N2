#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Funcao para inicializar as cidades a partir do arquivo
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) return NULL;

    int T, N;
    fscanf(file, "%d", &T);
    fscanf(file, "%d", &N);

    if (T < 3 || T > 1000000 || N < 2 || N > 10000) {
        fclose(file);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    estrada->T = T;
    estrada->N = N;
    estrada->C = (Cidade *)malloc(N * sizeof(Cidade));

    for (int i = 0; i < N; i++) {
        fscanf(file, "%d %s", &estrada->C[i].Posicao, estrada->C[i].Nome);
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= T) {
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return estrada;
}

// Funcao para calcular a menor vizinhanca
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1;

    double menorVizinhanca = (double)estrada->T;
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Funcao para encontrar a cidade com a menor vizinhanca
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = (double)estrada->T;
    char *cidade = NULL;
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidade = estrada->C[i].Nome;
        }
    }

    char *resultado = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    strcpy(resultado, cidade);

    free(estrada->C);
    free(estrada);
    return resultado;
}
