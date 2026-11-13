/****
 * Implementação do módulo: listaCompras
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 12/11/2026
 * Última alteração: xx/11/2026
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

    // primeira fase de leitura (associação dos índices de clientes e produtos)

    while(r>=0){
        if(r==4){
            if(lista->mapClientes.find(cliente) == lista->mapClientes.end()){
                lista->mapClientes[cliente] = lista->vectorClientes.size();
                lista->vectorClientes.push_back(cliente);
            }
            if(lista->mapProdutos.find(produto) == lista->mapProdutos.end()){
                lista->mapProdutos[produto] = lista->vectorProdutos.size();
                lista->vectorProdutos.push_back(nome);
            }
        } else{
            printf("Erro ao ler a linha atual");
            fscanf(f, "%*[^\n]");
        }

        r = fscanf(f, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome);
    }
    fclose(f);

    // segunda fase de leitura

    while (lista->listCompras.size() < lista->vectorClientes.size()) {
        lista->listCompras.push_back(list<int>());
    }

    f = fopen(arquivo, "r");
    if (f == NULL) {
        return 1;
    }

    fscanf(f, "%*[^\n]");
    r = fscanf(f, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome);

    while(r>=0){
        if(r==4){
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
        
    } else {
            fscanf(f, "%*[^\n]");
        }
    
    r = fscanf(f, " %8[^,],%19[^,],%d,%199[^\r\n]", data, cliente, &produto, nome);
    }
    fclose(f);
    return 0;
}

void testarListaCompras(ListaCompras *lista){
    char codigo[20];
    int i;

    for (i = 0; i < 3; i++) {
        printf("Codigo do cliente: ");
        scanf("%19s", codigo);

        if (lista->mapClientes.find(codigo) == lista->mapClientes.end()) {
            printf("Cliente nao encontrado.\n");
        } else {
            int indice = lista->mapClientes[codigo];
            for (int p : lista->listCompras[indice]) {
                cout << lista->vectorProdutos[p] << endl;
            }
        }
    }
}