/****
 * Implementação do módulo: recomendação
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 14/11/2026
 * Última alteração: xx/11/2026
 * Descrição Geral: 
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
    
    
    bool comparaRank(Ranking a, Ranking b) {
        
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
    
}

void testarRecomendacao(ListaCompras *lista){

}
