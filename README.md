# Sistema de Recomendação

Projeto, implementado na linguagem de programação C (com recursos de C++), para a disciplina Programação Estruturada, no curso Ciência de Dados e Inteligência Artificial (Universidade Federal da Paraíba).

O sistema recomenda produtos a clientes a partir do histórico de compras, usando filtragem colaborativa baseada em vizinhança (user-based): recomendam-se a um cliente os produtos comprados por clientes parecidos com ele.

Em suma, o projeto, até agora, está dividido em três implementações básicas:

- Módulo Lista de Compras: leitura dos arquivos CSV de vendas e organização das compras de cada cliente;
- Módulo Similaridade: cálculo da distância entre os clientes, a partir das compras em comum;
- Módulo Recomendação: ranqueamento e sugestão de produtos para um cliente.

## Estrutura do projeto

```
recommender-system/
├── README.md
├── LICENSE
├── src/
│   ├── main.cpp
│   ├── listaCompras.cpp / listaCompras.h
│   ├── similaridade.cpp / similaridade.h
│   └── recomendacao.cpp / recomendacao.h
└── data/
    └── dados_venda_cluster_*.csv
```

## Módulo Lista de Compras

Lê os arquivos CSV de vendas, em que cada linha é uma compra no formato `DATA_COMPRA,COD_CLIENTE,COD_PRODUTO,NOME_PRODUTO`, e guarda, para cada cliente, os produtos que ele comprou.

A leitura é feita em duas fases: na primeira, cada cliente e cada produto recebem um índice interno; na segunda, os índices dos produtos são adicionados à lista de compras de cada cliente. Linhas mal formatadas são ignoradas, e compras repetidas do mesmo produto por um cliente são guardadas uma única vez.

Estrutura de dados: a struct `ListaCompras` reúne `vectorClientes` e `mapClientes` (código original ↔ índice do cliente), `vectorProdutos` e `mapProdutos` (nome e código original ↔ índice do produto) e `listCompras` (para cada cliente, a lista dos índices dos produtos comprados).

## Módulo Similaridade

Calcula o quanto os clientes se parecem. Primeiro, monta a matriz binária de compras `A` (clientes × produtos), em que 1 indica que o cliente comprou o produto. Depois, calcula a interseção entre os clientes pelo produto `A × Aᵀ` e a similaridade pela distância de Jaccard assimétrica:

| Valor de S[i][j] | Significado |
|---|---|
| 0 | o cliente j comprou tudo o que o cliente i comprou |
| entre 0 e 1 | j comprou parte dos produtos de i (quanto menor, mais parecidos) |
| 1 | nenhum produto em comum |

A fórmula é `S[i][j] = 1 - |Pi ∩ Pj| / |Pi|`, em que `Pi` é o conjunto de produtos comprados pelo cliente `i`.

## Módulo Recomendação

Para um cliente, o sistema segue os passos abaixo:

| Passo | O que acontece |
|---|---|
| 1 | Os vizinhos do cliente são os clientes com similaridade menor que 1. |
| 2 | Todos os produtos começam com valor 1 em um vetor de ranqueamento. |
| 3 | Para cada produto de um vizinho que o cliente ainda não comprou, o valor do produto é multiplicado pela similaridade do vizinho. |
| 4 | Os produtos com valor menor que 1 são ordenados do menor para o maior valor. |
| 5 | Os `k` primeiros são recomendados. |

Quanto mais vizinhos parecidos compraram um produto, menor (melhor) fica o valor dele.

## Como clonar

```bash
git clone https://github.com/cec1l14/recommender-system.git
```

## Como compilar

É necessário um compilador C++ com suporte a C++11, como o `g++`.

```bash
cd recommender-system/src
g++ -std=c++11 -Wall -o a.exe *.cpp
```

## Como executar

O primeiro argumento escolhe o módulo a testar, e os arquivos CSV vêm sempre no final (pode-se passar mais de um).

Módulo Lista de Compras (mostra os produtos comprados por 3 clientes, pelos códigos originais):

```bash
.\a.exe 1 <cod1> <cod2> <cod3> <arquivo1.csv> [arquivo2.csv ...]
```

Módulo Similaridade (mostra o cliente mais similar, pelo índice interno):

```bash
.\a.exe 2 <indiceCliente> <arquivo1.csv> [arquivo2.csv ...]
```

Módulo Recomendação (mostra os `k` produtos recomendados para 3 clientes, pelos códigos originais):

```bash
.\a.exe 3 <k> <cod1> <cod2> <cod3> <arquivo1.csv> [arquivo2.csv ...]
```

Exemplos:

```bash
.\a.exe 1 99EIP501 99PXGH01 99BVWE01 data\dados_venda_cluster_1.csv
.\a.exe 2 0 data\dados_venda_cluster_1.csv
.\a.exe 3 5 99EIP501 99PXGH01 99BVWE01 data\dados_venda_cluster_1.csv
```

Aparecerão os nomes dos produtos comprados (opção 1) ou dos 5 produtos recomendados (opção 3) para cada um dos 3 clientes. Se algum código não existir nos arquivos, é exibida a mensagem `Cliente nao encontrado.`

## Integrantes

| | Nome | GitHub |
|---|---|---|
| <img src="https://github.com/cec1l14.png" width="40"> | Cecília Candeia | [@cec1l14](https://github.com/cec1l14) |
| <img src="https://github.com/techteus.png" width="40"> | Matheus Fernandes | [@techteus](https://github.com/techteus) |
