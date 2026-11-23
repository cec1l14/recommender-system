/****
 * Implementação do módulo: main
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 12/11/2026
 * Última alteração: 23/11/2026
 * Descrição Geral: contém a matemática para cálculo de similaridade entre clientes, criação de matrizes de compras, transposta, interseção e similaridade, além de funções auxiliares para gerenciamento de memória.
 ****/

#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "similaridadeCsr.h"

using namespace std;

int **criaMatrizDensa(ListaCompras *lista) {
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

CSR criaSimilaridadeCSR(const CSR& matrizCompras, const CSR& matrizInterseccao) {
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

pair<int, float> matchClientesCSR(const CSR& matrizSimilaridade, int cliente, ListaCompras *lista) {
    int clientes = lista->vectorClientes.size();

    if (cliente < 0 || cliente >= clientes) {
        cout << "Indice de cliente invalido." << "\n";
        return {-1, 1.0};
    }

    int matchIndice = -1;
    float matchValor = 1;

    for (int k = matrizSimilaridade.row_ptr[cliente]; k < matrizSimilaridade.row_ptr[cliente + 1]; k++) {
        int j = matrizSimilaridade.col_index[k];
        if (j == cliente) {
            continue;
        }
        if (matrizSimilaridade.values[k] < matchValor) {
            matchValor = matrizSimilaridade.values[k];
            matchIndice = j;
        }
    }
    return {matchIndice, matchValor};
}


void liberdadeMatrizCompras(int **matrizComprasDensa, ListaCompras *lista) {  // como so uso malloc nela ai ja deixo o nome bonitinho
    int linhas = lista->vectorClientes.size();
    for (int i = 0; i < linhas; i++) {
        free(matrizComprasDensa[i]);
    }
    free(matrizComprasDensa);
}

// mesmo padrão antigo, mas com as novas funções!
void testarSimilaridadeCSR(ListaCompras *lista, int indice){

    int **matrizComprasDensa = criaMatrizCompras(lista);
    CSR matrizCompras = criaComprasCSR(lista, matrizComprasDensa);
    liberdadeMatrizCompras(matrizComprasDensa, lista);
    CSR matrizInterseccao = criaInterseccaoCSR(matrizCompras);
    CSR matrizSimilaridade = criaSimilaridadeCSR(matrizCompras, matrizInterseccao);

    auto matchPar = matchClientesCSR(matrizSimilaridade, indice, lista);
    
    int matchIndice = matchPar.first;
    float matchValor = matchPar.second;

    if(matchIndice == -1){
        printf("Nao ha similaridade.\n");
    } else {
        printf("Cliente mais similar: %d, com similaridade = %.3f\n", matchIndice,
        matchValor);
    }

}

void testarEficienciaCSR(ListaCompras *lista){
    int clientes = lista->vectorClientes.size();

    // código para a matriz densa padrão

    clock_t inicio = clock();
    float **padrao = dizSimilaridadeEficiente(lista, ALGORITMO_PADRAO);
    clock_t fim = clock();
    double tempoPadrao = double(fim - inicio) / CLOCKS_PER_SEC;
    printf("Algoritmo padrao:    %.3f segundos\n", tempoPadrao);
    liberdadeMatrizFloat(padrao, clientes);

    // código para a matriz densa adaptada

    inicio = clock();
    float **densa = dizSimilaridadeEficiente(lista, ALGORITMO_ADAPTADO);
    fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    printf("Algoritmo adaptado:  %.3f segundos\n", tempo);
    liberdadeMatrizFloat(densa, clientes);

    // código para a matriz esparsa

    inicio = clock();
    int **comprasDensa = criaMatrizDensa(lista);
    CSR compras = criaComprasCSR(lista, comprasDensa);
    liberdadeMatrizCompras(comprasDensa, lista);
    CSR interseccao = criaInterseccaoCSR(compras);
    CSR similaridade = criaSimilaridadeCSR(compras, interseccao);
    fim = clock();
    double tempoCSR = double(fim - inicio) / CLOCKS_PER_SEC;
    printf("Matriz CSR:   %.3f segundos\n", tempoCSR);
}

void testarMemoriaCSR(ListaCompras *lista) {
    int clientes = lista->vectorClientes.size();
    int produtos = lista->vectorProdutos.size();

    int **comprasDensa = criaMatrizDensa(lista);
    CSR compras = criaComprasCSR(lista, comprasDensa);
    liberdadeMatrizCompras(comprasDensa, lista);

    double densa = (double) clientes * produtos * 4 / (1024 * 1024);
    double esparsa = (compras.values.size() + compras.col_index.size() + compras.row_ptr.size()) * 4.0 / (1024 * 1024);

    printf("Matriz de compras densa: %.3f MB\n", densa);
    printf("Matriz de compras CSR:   %.3f MB\n", esparsa);
    printf("Reducao: %.1f vezes\n", densa / esparsa);
}
