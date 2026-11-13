#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <vector>
#include <map>
#include <list>
#include <string>

typedef struct{
    std::vector<std::string> vectorClientes;
    std::map<std::string, int> mapClientes;
    std::vector<std::string> vectorProdutos;
    std::map<int, int> mapProdutos;
    std::vector<std::list<int>> listCompras;
} ListaCompras;

int leituraCSV(char *arquivo, ListaCompras *lista);

#endif