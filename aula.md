# Sistema de Recomendação
Segundo projeto da disciplina "Programação Estruturada", em Ciência de Dados e Inteligência Artificial (UFPB), implementado totalmente em C.

## Aula (27/10/2026)

Stream -> abstração lógica que representa uma fonte ou um destino de dados em movimento.

FILE *fopen(const char *nome, const char *modo)\
   -> abre um arquivo e o associa  a um fluxo de dados\
   -> funcionam tanto os caminhos relativos quanto os absolutos

Não esquecer de fechar um arquivo ao final da aplicação.

int fclose(FILE * stream) -> fechamento de arquivo

**Sugestão para verificação:**

  if (ptrStream == NULL) {\
  /*O arquivo não pode ser aberto.*/\
  /*Geralmente se mostra uma mensagem de erro.*/\
  } else {\
  /*Aqui o arquivo pode ser executado normalmente.*/
  }\
  
  **Leitura de arquivo:** fscanf(FILE * stream, const char *formato, ...)

  ### Exemplo de código

 <img width="435" height="521" alt="codigoexemplo" src="https://github.com/user-attachments/assets/110e33c0-cfad-40cf-b7c9-eefc7c53a045" />

-> Deve-se usar a biblioteca <vector>, de c++, no projeto

É válido pontuar que serão adiantados os conteúdos de 'Estrutura de Dados'. Entretanto, as ideias serão abstraídas e usadas apenas as necessárias para a implementação.

**map** -> equivale ao dicionário em python (tabela de associação)\
*será bastante utilizado

**Primeiro entregável**: leitura dos dados e organização destes em vector, list e map.

find -> verificação de duplicação no map. Se a duplicação existir, acessa-se a lista e adiciona-se o novo produto.

## Aula (12/11/2026)

função main()

- receber indo da linha de comando
- leitura dos dados
- uso de argc e argv
- instanciar listaCompras
- função void
- funções de teste

arquivo dados:

lista compras -> leitura e armazenamento de dados
- struct listaCompras
	- vector contendo índices (códigos) dos clientes
	- map que mapeia código do cliente a código interno 
	- vector de código de produtos
	- map de código de produtos a código interno
	- vector de vector (leitura dos dados)
	- int * matriz compras()

.h: 

readData -> recebe o caminho dos dados
proibido uso de variáveis estáticas e globais

entrega 4: adição de uma nova função à etapa 3