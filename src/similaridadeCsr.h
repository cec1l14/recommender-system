#ifndef SIMILARIDADECSR_H
#define SIMILARIDADECSR_H
#include "listaCompras.h" 

struct CSR {
    vector<float> values;
    vector<int>  col_index;
    vector<int>  row_ptr = {0};
};
int **criaMatrizCompras(ListaCompras *lista);
CSR criaComprasCSR(ListaCompras *lista, int **matrizComprasDensa);
CSR criaInterseccaoCSR(const CSR& matrizCompras);

#endif
