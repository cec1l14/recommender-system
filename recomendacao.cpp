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

bool compararPorRanking(const Ranking &a, const Ranking &b){
    return a.valor < b.valor;
}

vector<int> recomendaProdutos(float **matrizSimilaridade, int cliente, int k, ListaCompras *lista){
    
}

void testarRecomendacao(ListaCompras *lista){

}