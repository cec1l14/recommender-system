/****
 * Implementação do módulo: similaridade
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 13/11/2026
 * Última alteração: xx/11/2026
 * Descrição Geral: contém funções para cálculo de similaridade entre clientes, criação de matrizes de compras, transposta, interseção e similaridade, além de funções auxiliares para gerenciamento de memória.
 ****/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "listaCompras.h"  
#include "similaridade.h" 

using namespace std;

int **criaMatrizCompras(ListaCompras *lista) {
    int linhas = lista->vectorClientes.size();
    int colunas = lista->vectorProdutos.size();

    int **matrizCompras = (int **) malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        matrizCompras[i] = (int *) malloc(colunas * sizeof(int));

        for (int j = 0; j < colunas; j++) {
            matrizCompras[i][j] = 0;
        }
        for (int k : lista->listCompras[i]) {
            matrizCompras[i][k] = 1;
        }
    }
    return matrizCompras;
}

int **criaMatrizTransposta(int **matrizCompras, ListaCompras *lista) {
    int linhas = lista->vectorClientes.size();
    int colunas = lista->vectorProdutos.size();

    int **matrizTransposta = (int **) malloc(colunas * sizeof(int *));

    for (int j = 0; j < colunas; j++) {
        matrizTransposta[j] = (int *) malloc(linhas * sizeof(int));

        for (int i = 0; i < linhas; i++) {
            matrizTransposta[j][i] = matrizCompras[i][j];
        }
    }
    return matrizTransposta;
}

int **criaInterseccao(int **matrizCompras, int **matrizTransposta, ListaCompras *lista) {
    int linhas = lista->vectorClientes.size();
    int colunas = lista->vectorProdutos.size();

    int **matrizInterseccao = (int **) malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        matrizInterseccao[i] = (int *) malloc(linhas * sizeof(int));

        for (int j = 0; j < linhas; j++) {
            int interseccao = 0;
            for (int k = 0; k < colunas; k++) {
                interseccao += matrizCompras[i][k] * matrizTransposta[k][j];
            }
            matrizInterseccao[i][j] = interseccao;
        }
    }
    return matrizInterseccao;
}

float **criaMatrizSimilaridade(int **matrizInterseccao, ListaCompras *lista) {
    int linhas = lista->vectorClientes.size();

    float **matrizSimilaridade = (float **) malloc(linhas * sizeof(float *));

    for (int i = 0; i < linhas; i++) {
        matrizSimilaridade[i] = (float *) malloc(linhas * sizeof(float));

        for (int j = 0; j < linhas; j++) {
            if (matrizInterseccao[i][i] == 0) {
                matrizSimilaridade[i][j] = 1.0;
            } else {
                matrizSimilaridade[i][j] = 1.0 - (float) matrizInterseccao[i][j] / matrizInterseccao[i][i];
            }
        }
    }
    return matrizSimilaridade;
}

int matchClientes(float **matrizSimilaridade, int cliente, ListaCompras *lista) {
    int clientes = lista->vectorClientes.size();

    if (cliente < 0 || cliente >= clientes) {
        cout << "Indice de cliente invalido." << "\n";
        return -1;
    }

    int matchIndice = -1;
    float matchValor = 1;

    for (int i = 0; i < clientes; i++) {
        if (i == cliente) {
            continue;
        }
        if (matrizSimilaridade[cliente][i] < matchValor) {
            matchValor = matrizSimilaridade[cliente][i];
            matchIndice = i;
        }
    }
    return matchIndice;
}

float dizSimilaridade(float **matrizSimilaridade, int clienteA, int clienteB, ListaCompras *lista) {
    int clientes = lista->vectorClientes.size();

    if (clienteA < 0 || clienteA >= clientes) {
        cout << "Indice do primeiro cliente invalido." << "\n";
        return -1;
    }
    if (clienteB < 0 || clienteB >= clientes) {
        cout << "Indice do segundo cliente invalido." << "\n";
        return -1;
    }
    return matrizSimilaridade[clienteA][clienteB];
}

void liberdadeMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void liberdadeMatrizFloat(float **matriz, int linhas){
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void testarSimilaridade(ListaCompras *lista){
    int clientes = lista->vectorClientes.size();
    int produtos = lista->vectorProdutos.size();

    int **matrizCompras = criaMatrizCompras(lista);
    int **matrizTransposta = criaMatrizTransposta(matrizCompras, lista);
    int **matrizInterseccao = criaInterseccao(matrizCompras, matrizTransposta, lista);
    float **matrizSimilaridade = criaMatrizSimilaridade(matrizInterseccao, lista);

    int indice;
    printf("Escolha o indice referente ao cliente (0 a %d): \n", clientes - 1);
    scanf("%d", &indice);

    int match = matchClientes(matrizSimilaridade, indice, lista);

    if(match == -1){
        printf("Nao ha similaridade.\n");
    } else {
        printf("Cliente mais similar: %d, com similaridade = %.3f\n", match,
        dizSimilaridade(matrizSimilaridade, indice, match, lista));
    }

    liberdadeMatriz(matrizCompras, clientes);
    liberdadeMatriz(matrizInterseccao, clientes);
    liberdadeMatriz(matrizTransposta, produtos);
    liberdadeMatrizFloat(matrizSimilaridade, clientes);
}