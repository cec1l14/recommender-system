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
CSR criaComprasCSR(ListaCompras *lista, int **matrizComprasDensa);
CSR criaInterseccaoCSR(const CSR& matrizCompras);

#endif
