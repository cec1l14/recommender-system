/****
 * Implementação do módulo: recomendação
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 14/11/2026
 * Última alteração: 15/11/2026
 * Descrição Geral: contém funções para recomendação de produtos a partir da similaridade entre clientes, criação de listas de vizinhos, ranqueamento e recomendação de produtos. 
 ****/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"

using namespace std;

int *criaListaVizinhos(float **matrizSimilaridade, int cliente, int *numVizinhos, ListaCompras *lista) {
    
    int clientes = lista->vectorClientes.size();
    
    *numVizinhos = 0;
    
    if (cliente < 0 || cliente >= clientes) {
        cout << "Indice de cliente invalido." << "\n";
        return 0;
    }
    
    int vizinhos = 0;
    for (int i = 0; i < clientes; i++) {



        if (i == cliente) {
            continue;
        }
        if (matrizSimilaridade[cliente][i] < 1) {
            vizinhos++;
        }
    }
    
    if (vizinhos == 0) {
        return 0;
    }
    
int *listaVizinhos = (int *) malloc(vizinhos * sizeof(int));

    
    int posVizinho = 0;
    for (int i = 0; i < clientes; i++) {
        if (i == cliente) {
            continue;
        }
        if (matrizSimilaridade[cliente][i] < 1) {
            listaVizinhos[posVizinho] = i;
            posVizinho++;
        }
    }
    
    *numVizinhos = vizinhos;
    return listaVizinhos;
}
    
Ranking *criaVetorRanqueamento(ListaCompras *lista) {
    
    int produtos = lista->vectorProdutos.size();
    
    Ranking *rank = (Ranking *) malloc(produtos * sizeof(Ranking));
    
    for (int produto = 0; produto < produtos; produto++) {
        rank[produto].produto = produto;
        rank[produto].rank = 1;
    }
    return rank;
}
    
void dizRank(Ranking *rank, float **matrizSimilaridade, int cliente, int *listaVizinhos, int numVizinhos, ListaCompras *lista) {
    
    int produtos = lista->vectorProdutos.size();
    
    int *listaComprados = (int *) malloc(produtos * sizeof(int));
    
    for (int produto = 0; produto < produtos; produto++) {
        listaComprados[produto] = 0;
    }
        
    for (int produto : lista->listCompras[cliente]) {
        listaComprados[produto] = 1;
    }
    
    for (int i = 0; i < numVizinhos; i++) {
        int vizinho = listaVizinhos[i];
    
        for (int produto : lista->listCompras[vizinho]) {
                
            if (listaComprados[produto] == 0) {
                rank[produto].rank *= matrizSimilaridade[cliente][vizinho];
            }
        }
    }
    
    // como é vetor auxiliar ja posso dar o free que fica blz
    free(listaComprados);
}
    
    
bool comparaRank(const Ranking &a, const Ranking &b) {
        
    if (a.rank != b.rank) {
        return a.rank < b.rank;      
    }
        return a.produto < b.produto;    
    } 

Ranking *criaListaCandidatos(Ranking *rank, int *numCandidatos, ListaCompras *lista) {
    
    int produtos = lista->vectorProdutos.size();
    
    *numCandidatos = 0;
    
    int candidatos = 0;
    for (int produto = 0; produto < produtos; produto++) {
        if (rank[produto].rank < 1) {
            candidatos++;
        }
    }
    
    if (candidatos == 0) {
        return 0;
    }
    
Ranking *listaCandidatos = (Ranking *) malloc(candidatos * sizeof(Ranking));

    
    int posCandidato = 0;
        
    for (int produto = 0; produto < produtos; produto++) {
            
        if (rank[produto].rank < 1) {
            listaCandidatos[posCandidato] = rank[produto];
            posCandidato++;
        }
    }
        
    sort(listaCandidatos, listaCandidatos + candidatos, comparaRank);
        
    *numCandidatos = candidatos;
    return listaCandidatos;
}

vector<int> recomendaProdutos(float **matrizSimilaridade, int cliente, int k, ListaCompras *lista){
    vector<int> recomendados;

    int clientes = lista->vectorClientes.size();
    if (cliente < 0 || cliente >= clientes) {
        return recomendados; // vector vazio quando nao ha clientes encontrados
    }

    int numVizinhos = 0;
    int numCandidatos = 0;

    int *listaVizinhos = criaListaVizinhos(matrizSimilaridade, cliente, &numVizinhos, lista);
    Ranking *rank = criaVetorRanqueamento(lista);
    dizRank(rank, matrizSimilaridade, cliente, listaVizinhos, numVizinhos, lista);
    Ranking *listaCandidatos = criaListaCandidatos(rank, &numCandidatos, lista);

    int i;
    for (i = 0; i < k && i < numCandidatos; i++) {
        recomendados.push_back(listaCandidatos[i].produto);
    }

    free(listaVizinhos);
    free(rank);
    free(listaCandidatos);

    return recomendados;
}

void testarRecomendacao(ListaCompras *lista, int k, char *codigos[]){
    int clientes = lista->vectorClientes.size();
    int produtos = lista->vectorProdutos.size();

    int **matrizCompras = criaMatrizCompras(lista);
    int **matrizTransposta = criaMatrizTransposta(matrizCompras, lista);
    int **matrizInterseccao = criaInterseccao(matrizCompras, matrizTransposta, lista);
    float **matrizSimilaridade = criaMatrizSimilaridade(matrizInterseccao, lista);

    int i;

    for (i = 0; i < 3; i++) {
        printf("Cliente %s:\n", codigos[i]);

        if (lista->mapClientes.find(codigos[i]) == lista->mapClientes.end()) {
            printf("Cliente nao encontrado.\n");
        } else {
            int indice = lista->mapClientes[codigos[i]];
            vector<int> recomendados = recomendaProdutos(matrizSimilaridade, indice, k, lista);

            if (recomendados.size() == 0) {
                printf("Nenhum produto para recomendar.\n");
            }
            for (int p : recomendados) {
                cout << lista->vectorProdutos[p] << endl;
            }
        }
    }

    liberdadeMatriz(matrizCompras, clientes);
    liberdadeMatriz(matrizTransposta, produtos);
    liberdadeMatriz(matrizInterseccao, clientes);
    liberdadeMatrizFloat(matrizSimilaridade, clientes);
}