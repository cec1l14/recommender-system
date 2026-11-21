#ifndef SIMILARIDADECSR_H
#define SIMILARIDADECSR_H
#include "listaCompras.h" 

using namespace std;

struct CSR {
    vector<int> values;
    vector<int>  col_index;
    vector<int>  row_ptr = {0};
};

CSR criaComprasCSR(ListaCompras *lista);
CSR criaInterseccaoCSR(const CSR& matrizCompras);

#endif
