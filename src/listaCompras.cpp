/****
 * Implementação do módulo: listaCompras
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 12/11/2026
 * Última alteração: 15/11/2026
 * Descrição Geral: apresenta funções para leitura de arquivos CSV e teste da estrutura de dados ListaCompras.
 ****/

#include <stdio.h>
#include <iostream>
#include "listaCompras.h"
using namespace std;

int leituraCSV(char *arquivo, ListaCompras *lista){
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char data[9];
    char cliente[20];
    char nome[200];
    int produto, r;

    fscanf(f, "%*[^\n]");
    r = fscanf(f, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome);

    while(r>=0){
        if(r==4){
            if(lista->mapClientes.find(cliente) == lista->mapClientes.end()){
                lista->mapClientes[cliente] = lista->vectorClientes.size();
                lista->vectorClientes.push_back(cliente);
                lista->listCompras.push_back(list<int>()); // alteração sugerida pelo professor (evita a abertura dupla dos arquivos)
            }
            if(lista->mapProdutos.find(produto) == lista->mapProdutos.end()){
                lista->mapProdutos[produto] = lista->vectorProdutos.size();
                lista->vectorProdutos.push_back(nome);
            }

            int indiceCliente = lista->mapClientes[cliente];
            int indiceProduto = lista->mapProdutos[produto];

            int verificacao = 0; // para não haver problemas nas duplicatas. o pdf não explicita isso, mas é importante essa verificação

            for (int p : lista->listCompras[indiceCliente]) {
                if (p == indiceProduto) {
                    verificacao = 1;
                }
            }
            if (verificacao == 0) {
                lista->listCompras[indiceCliente].push_back(indiceProduto);
            }
        } else{
            fscanf(f, "%*[^\n]");
        }

        r = fscanf(f, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome);
    }
    fclose(f);
    return 0;
}

void testarListaCompras(ListaCompras *lista, char *codigos[]){
    int i;

    for (i = 0; i < 3; i++) {
        printf("Cliente %s:\n", codigos[i]);

        if (lista->mapClientes.find(codigos[i]) == lista->mapClientes.end()) {
            printf("Cliente nao encontrado.\n");
        } else {
            int indice = lista->mapClientes[codigos[i]];
            for (int p : lista->listCompras[indice]) {
                cout << lista->vectorProdutos[p] << endl;
            }
        }
    }
}