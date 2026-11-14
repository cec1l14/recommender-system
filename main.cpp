/****
 * Implementação do módulo: main
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 12/11/2026
 * Última alteração: xx/11/2026
 * Descrição Geral: contém a função principal do programa, que gerencia a execução do sistema de recomendação.
 ****/

#include <stdio.h>
#include "listaCompras.h"
#include "similaridade.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Arquivo usado: %s <arquivo.csv>\n", argv[0]);
        return 1;
    }

    ListaCompras lista;
    if (leituraCSV(argv[1], &lista) != 0) {
        return 1;
    }

    int opcao = -1;

    while(opcao != 0){
        printf("Sistema de Recomendacao\n");
        printf("Opcao 1 - Testar listaCompras\n");
        printf("Opcao 2 - Testar Similaridade \n");
        printf("Opcao 3 - Testar Recomendacao\n");
        printf("Opcao 0 - sair da execucao\n");
        printf("Opcao a ser escolhida: \n");
        scanf("%d", &opcao);

        if((opcao > 3) || (opcao < 0)){
            printf("Opcao invalida\n");
        } if(opcao == 1){
            testarListaCompras(&lista);
        } if(opcao == 2){
            testarSimilaridade(&lista);
        }
    }
    return 0; 
}