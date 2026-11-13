#include <stdio.h>
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

    // primeira fase de leitura

    while(r>0){
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
            printf("Erro ao ler a linha: %s,%s,%d,%s\n", data, cliente, produto, nome);
            fscanf(f, "%*[^\n]");
        }

        r = fscanf(f, " %8[^,],%19[^,],%6[^,],%199[^\r\n]", data, cliente, produto, nome);
    }
    fclose(f);

    // segunda fase de leitura

    
    return 0;
}