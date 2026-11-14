#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "listaCompras.h"
#include "similaridade.h"

using namespace std;

typedef struct{
    int produto; // acho melhor guardar como int!
    float rank;
} Ranking;

int *criaListaVizinhos(float **matrizSimilaridade, int cliente, int *numVizinhos, ListaCompras *lista);
Ranking *criaVetorRanqueamento(ListaCompras *lista);
void dizRank(Ranking *rank, float **matrizSimilaridade, int cliente, int *listaVizinhos, int numVizinhos, ListaCompras *lista);
bool comparaRank(Ranking a, Ranking b);
Ranking *criaListaCandidatos(Ranking *rank, int *numCandidatos, ListaCompras *lista);
std::vector<int> recomendaProdutos(float **matrizSimilaridade, int cliente, int k, ListaCompras *lista);
void testarRecomendacao(ListaCompras *lista);

#endif 
