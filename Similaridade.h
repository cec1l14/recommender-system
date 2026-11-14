#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "listaCompras.h"   

int **criaMatrizCompras(ListaCompras *lista);
int **criaMatrizTransposta(int **matrizCompras, ListaCompras *lista);
int **criaInterseccao(int **matrizCompras, int **matrizTransposta, ListaCompras *lista);
float **criaMatrizSimilaridade(int **matrizInterseccao, ListaCompras *lista);

int matchClientes(float **matrizSimilaridade, int cliente, ListaCompras *lista);
float dizSimilaridade(float **matrizSimilaridade, int clienteA, int clienteB, ListaCompras *lista);

void liberdadeMatriz(int **matriz, int linhas);
void liberdadeMatrizFloat(float **matriz, int linhas);

void testarSimilaridade(ListaCompras *lista);

#endif
