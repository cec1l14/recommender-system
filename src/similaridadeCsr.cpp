#include <stdio.h>
#include <vector>
using namespace std;

struct CSR {
    vector<int> values;
    vector<int>  col_index;
    vector<int>  row_ptr = {0};
};

CSR criaComprasCSR(ListaCompras *lista) {
    CSR matrizCompras;
    int linhas = lista->vectorClientes.size();
    int rowCount = 0;

    for (int i = 0; i < linhas; i++) {
        for (int produto : lista->listaCompras[i]) {
            matrizCompras.values.push_back(1.0);
            matrizCompras.col_index.push_back(produto);
            rowCount++;
        }
        matrizCompras.row_ptr.push_back(rowCount);
    }
    return matrizCompras;
}

CSR criaInterseccaoCSR(const CSR& s) {
    CSR matrizInterseccao;                    
    int row = matrizCompras.row_ptr.size() - 1;
    int cont = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            int inicioI = matrizCompras.row_ptr[i];
            int fimI    = matrizCompras.row_ptr[i + 1];
            int inicioJ = matrizCompras.row_ptr[j];
            int fimJ    = matrizCompras.row_ptr[j + 1];

            int soma = 0;
            
            // pacode aula two pointers ajudou vlw
            while (inicioI < fimI && inicioJ < fimJ) {
                if (matrizCompras.col_index[inicioI] == matrizCompras.col_index[inicioJ]) {
                    soma += matrizCompras.values[inicioI] * matrizCompras.values[inicioJ];
                    inicioI++;
                    inicioJ++;
                } else if (matrizCompras.col_index[inicioI] < matrizCompras.col_index[inicioJ]) {
                    inicioI++;
                } else {
                    inicioJ++;
                }
            }

            if (soma > 0) {
                matrizInterseccao.values.push_back(soma);
                matrizInterseccao.col_index.push_back(j);
                cont++;
            }
        }
        matrizInterseccao.row_ptr.push_back(cont);   
    }
    return matrizInterseccao;
}
