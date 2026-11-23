/****
 * Implementação do módulo: main
 * Autores: Cecília Candeia e Matheus Fernandes
 * Data de Criação: 12/11/2026
 * Última alteração: 23/11/2026
 * Descrição Geral: contém a função principal do programa, que gerencia a execução do sistema de recomendação.
 ****/

#include <stdio.h>
#include <stdlib.h>
#include "listaCompras.h"
#include "similaridade.h"
#include "similaridadeCsr.h"
#include "recomendacao.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso:\n");
        printf("  %s 1 <cod1> <cod2> <cod3> <arquivo1.csv> [arquivo2.csv ...]\n", argv[0]);
        printf("  %s 2 <indiceCliente> <arquivo1.csv> [arquivo2.csv ...]\n", argv[0]);
        printf("  %s 3 <k> <cod1> <cod2> <cod3> <arquivo1.csv> [arquivo2.csv ...]\n", argv[0]);
        printf("  %s 4 <arquivo1.csv> [arquivo2.csv ...]\n", argv[0]);
        printf("  %s 5 <indiceCliente> <arquivo1.csv> [arquivo2.csv ...]\n", argv[0]);
        return 1;
    }

    int opcao = atoi(argv[1]);
    int primeiroArquivo;

    if (opcao == 1) {
        primeiroArquivo = 5;
    } else if (opcao == 2) {
        primeiroArquivo = 3;
    } else if (opcao == 3) {
        primeiroArquivo = 6;
    } else if (opcao == 4) {
        primeiroArquivo = 2;
    } else if (opcao == 5) {
        primeiroArquivo = 3;
    } else {
        printf("Opcao invalida\n");
        return 1;
    }

    if (argc <= primeiroArquivo) {
        printf("Faltam argumentos.\n");
        return 1;
    }

    ListaCompras lista;
    for (int i = primeiroArquivo; i < argc; i++) {
        if (leituraCSV(argv[i], &lista) != 0) {
            return 1;
        }
    }

    if (opcao == 1) {
        testarListaCompras(&lista, &argv[2]);
    } else if (opcao == 2) {
        testarSimilaridade(&lista, atoi(argv[2]));
    } else if (opcao == 3) {
        testarRecomendacao(&lista, atoi(argv[2]), &argv[3]);
    } else if (opcao == 4){
        testarEficiencia(&lista);
    } else if (opcao == 5){
        printf("Cliente mais similar - comparacao\n");
        testarSimilaridade(&lista, atoi(argv[2]));
        printf("\n");

        printf("Tempo de execucao - comparacao\n");
        testarEficienciaCSR(&lista);
        printf("\n");

        printf("Economia de memoria - comparacao\n");
        testarMemoriaCSR(&lista);
    }

    return 0;
}