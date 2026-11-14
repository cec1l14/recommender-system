#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "listaCompras.h"

typedef struct{
    std::string produto;
    float valor;
} Ranking;

bool compararPorRanking(const Ranking &a, const Ranking &b);
std::vector<int> recomendaProdutos(float **matrizSimilaridade, int cliente, int k, ListaCompras *lista);
void testarRecomendacao(ListaCompras *lista);

#endif 