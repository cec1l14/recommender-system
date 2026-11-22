# Sistema de Recomendação

Projeto de Programação Estruturada (Ciência de Dados e Inteligência Artificial, UFPB), em C, com recuros de C++ e Python (etapa final).
Em suma, o sistema recomenda produtos a um cliente a partir do que clientes parecidos com ele compraram, por meio de uma filtragem colaborativa baseada em usuário.

## Estrutura do projeto

```
recommender-system/
├── README.md
├── LICENSE
├── src/
│   ├── main.cpp
│   ├── listaCompras.cpp / listaCompras.h
│   ├── similaridade.cpp / similaridade.h
│   ├── similaridadeCsr.cpp / similaridadeCsr.h
│   └── recomendacao.cpp / recomendacao.h
├── data/
│   └── dados_venda_cluster_*.csv
├── docs/
│   └── aula.md
└── python/
```

## Compilar

```bash
git clone https://github.com/cec1l14/recommender-system.git
cd recommender-system
g++ -std=c++11 -o a.exe src/*.cpp
```

## Executar

```bash
.\a.exe 1 <cod1> <cod2> <cod3> <arquivo.csv>        
.\a.exe 2 <indice> <arquivo.csv>                   
.\a.exe 3 <k> <cod1> <cod2> <cod3> <arquivo.csv>    
.\a.exe 4 <arquivo.csv>
.\a.exe 5 <arquivo.csv>                             
```

## Exemplos

### Lista de Compras

Produtos comprados por 3 clientes, pelos códigos originais:

```bash
.\a.exe 1 99CL9Y01 9O6OSM01 99KKM901 data\dados_venda_cluster_1.csv
```

```
Cliente 99CL9Y01:
TABLET NB316 M7S 16GB QUAD CORE PRETO
PEN DRIVE 16GB PD688 TWIST ROSA MULTILASER
CAIXA AMPLIFICADA MCO-07 MULTI CONNECT
Cliente 9O6OSM01:
TABLET NB730 MINI MS50G PRATA/PRETO
PEN DRIVE 16GB PD688 TWIST ROSA MULTILASER
Cliente 99KKM901:
SMARTPHONE SAMSUNG GAL J2 CORE 16GB PRETO
RADIO RECEPTOR 2 FXS RM PFT22AC
PEN DRIVE 16GB PD688 TWIST ROSA MULTILASER
DVD D-15 KARAOKE MONDIAL
RADIO RECEPTOR 7 FXS RM PFT73AC
```

### Similaridade

Cliente mais parecido com o cliente de índice 0 (0 = comprou tudo o que ele comprou, 1 = nada em comum):

```bash
.\a.exe 2 0 data\dados_venda_cluster_1.csv
```

```
Cliente mais similar: 1, com similaridade = 0.667
```

### Recomendação

Os 3 produtos mais bem recomendados para cada um de 3 clientes:

```bash
.\a.exe 3 3 99EIP501 99PXGH01 99BVWE01 data\dados_venda_cluster_1.csv
```

```
Cliente 99EIP501:
PEN DRIVE 16GB PD588 TWIST PRETO
PEN DRIVE 8GB PD587 TWIST PRETO
SUPORTE UNIV. BEDIN BU-25
Cliente 99PXGH01:
PEN DRIVE 16GB PD588 TWIST PRETO
SUPORTE TV UNIVERSAL LCD/LED 10 A 71 SBRUB750
PEN DRIVE 8GB PD687 TWIST ROSA
Cliente 99BVWE01:
SUPORTE TV UNIVERSAL LCD/LED 10 A 71 SBRUB750
PEN DRIVE 16GB PD588 TWIST PRETO
PEN DRIVE 8GB PD587 TWIST PRETO
```

Se algum código não existir no arquivo, é exibida a mensagem `Cliente nao encontrado.`

### Tempo dos algoritmos de similaridade

Compara o algoritmo padrão com o adaptado.

```bash
.\a.exe 4 data\dados_venda_cluster_1.csv
```

```
Algoritmo padrao:  0.326 segundos
Algoritmo adaptado: 0.156 segundos
```

### Matriz esparsa (CSR): tempo e memória

Compara a matriz de similaridade construída com o algoritmo padrão, com o adaptado e em formato CSR (que guarda só os valores diferentes de zero), e compara a memória da matriz de compras na forma densa e em CSR.

```bash
.\a.exe 5 data\dados_venda_cluster_1.csv
```

```
Tempo de execucao - comparacao
Algoritmo padrao:    0.397 segundos
Algoritmo adaptado:  0.137 segundos
Matriz CSR:   0.077 segundos

Economia de memoria - comparacao
Matriz de compras densa: 0.521 MB
Matriz de compras CSR:   0.014 MB
Reducao: 37.6 vezes
```

## Integrantes

| | Nome | GitHub |
|---|---|---|
| <img src="https://github.com/cec1l14.png" width="40"> | Cecília Candeia | [@cec1l14](https://github.com/cec1l14) |
| <img src="https://github.com/techteus.png" width="40"> | Matheus Fernandes | [@techteus](https://github.com/techteus) |

## Referências

CASAVELLA, Eduardo. Argumentos em linha de comando. **Linguagem C**, [S. l.], 30 maio 2012. Disponível em: https://linguagemc.com.br/argumentos-em-linha-de-comando/. Acesso em: 20 nov. 2026.

**IMPLEMENTAÇÃO de um sistema de recomendação**. [S. l.: s. n.], [2026?]. Material didático da disciplina de Programação Estruturada, Universidade Federal da Paraíba. 28 p. Documento em PDF.

LABPIB. **Algoritmos e Estruturas de Dados - USP - matrizes esparsas**. [S. l.]: YouTube, [2011?]. Playlist de vídeos. Disponível em: https://www.youtube.com/playlist?list=PLDE07C44D7E8F091A. Acesso em: 20 nov. 2026.
