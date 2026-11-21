#ifndef SIMILARIDADECSR_H
#define SIMILARIDADECSR_H
#include "listaCompras.h"
#include "similaridade.h"

using namespace std;

struct CSR {
    vector<float> values;
    vector<int>  col_index;
    vector<int>  row_ptr = {0};
};

int **criaMatrizCompras(ListaCompras *lista);
CSR criaComprasCSR(ListaCompras *lista, int **matrizComprasDensa);
CSR criaInterseccaoCSR(const CSR& matrizCompras);
CSR calculaSimilaridade(const CSR& matrizCompras, const CSR& matrizInterseccao);
int matchClientes(const CSR& matrizSimilaridade, int cliente, ListaCompras *lista);
float dizSimilaridade(const CSR& matrizSimilaridade, int clienteA, int clienteB);
void liberdadeMatrizCompras(int **matrizComprasDensa, ListaCompras *lista);

#endif
