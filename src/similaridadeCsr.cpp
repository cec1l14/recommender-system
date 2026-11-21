#include <vector>
#include <cstdlib>
#include "similaridadeCsr.h"

using namespace std;

int **criaMatrizCompras(ListaCompras *lista) {
    int linhas = lista->vectorClientes.size();
    int colunas = lista->vectorProdutos.size();

    int **matrizComprasDensa = (int **) malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        matrizComprasDensa[i] = (int *) malloc(colunas * sizeof(int));

        for (int j = 0; j < colunas; j++) {
            matrizComprasDensa[i][j] = 0;
        }
        for (int k : lista->listCompras[i]) {
            matrizComprasDensa[i][k] = 1;
        }
    }
    return matrizComprasDensa;
}

CSR criaComprasCSR(ListaCompras *lista, int **matrizComprasDensa) {
    CSR matrizCompras;
    int linhas = lista->vectorClientes.size();
    int colunas = lista->vectorProdutos.size();

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matrizComprasDensa[i][j] != 0) {
                matrizCompras.values.push_back(matrizComprasDensa[i][j]);
                matrizCompras.col_index.push_back(j);
            }
        }
        matrizCompras.row_ptr.push_back(matrizCompras.values.size());
    }
    return matrizCompras;
}

CSR criaInterseccaoCSR(const CSR& matrizCompras) {
    CSR matrizInterseccao;                    
    int n = matrizCompras.row_ptr.size() - 1;
    int cont = 0;
    
    // o pdf dizia pra alocar n ao quadrado mas ao fazer isso nao tava rodando! (alocacao falhou vei)
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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

            if (soma != 0) {
                matrizInterseccao.values.push_back(soma);
                matrizInterseccao.col_index.push_back(j);
                cont++;
            }
        }
        matrizInterseccao.row_ptr.push_back(cont);   
    }
    return matrizInterseccao;
}

CSR calculaSimilaridade(const CSR& matrizCompras, const CSR& matrizInterseccao) {
    CSR matrizSimilaridade;
    int n = matrizInterseccao.row_ptr.size() - 1;

    for (int i = 0; i < n; i++) {
        
        int produtos = matrizCompras.row_ptr[i + 1] - matrizCompras.row_ptr[i];
        
        for (int k = matrizInterseccao.row_ptr[i]; k < matrizInterseccao.row_ptr[i + 1]; k++) {
            
            int j = matrizInterseccao.col_index[k];
            int interseccao = matrizInterseccao.values[k];

            float similaridade = 1 - (float) interseccao / produtos;

            matrizSimilaridade.values.push_back(similaridade);
            matrizSimilaridade.col_index.push_back(j);
        }
        matrizSimilaridade.row_ptr.push_back(matrizSimilaridade.values.size());
    }
    return matrizSimilaridade;
}

// pacode aula busca binaria <3
float dizSimilaridade(const CSR& matrizSimilaridade, int clienteA, int clienteB) {
    
    int lo = matrizSimilaridade.row_ptr[clienteA];
    int hi = matrizSimilaridade.row_ptr[clienteA + 1] - 1;

    while (lo <= hi) {
        
        int mid = (lo + hi) / 2
        
        if (matrizSimilaridade.col_index[mid] == clienteB){
            return matrizSimilaridade.values[mid];
        }
        
        else if (matrizSimilaridade.col_index[mid] < clienteB){
            lo = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 1;  // nao achou ent nao tem 
}

void liberdadeMatrizCompras(int **matrizComprasDensa, ListaCompras *lista) {  // como so uso malloc nela ai ja deixo o nome bonitinho
    int linhas = lista->vectorClientes.size();
    for (int i = 0; i < linhas; i++) {
        free(matrizComprasDensa[i]);
    }
    free(matrizComprasDensa);
}
