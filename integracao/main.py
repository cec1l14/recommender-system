import sys
import lista_compras as compras
import sistema_recomendacao as recomendacao

def main():
    if len(sys.argv) < 3:
        print("Uso:")
        print(f"  python {sys.argv[0]} 1 <cod1> <cod2> <cod3> <arquivo1.csv> [arquivo2.csv ...]")
        print(f"  python {sys.argv[0]} 2 <indiceCliente> <arquivo1.csv> [arquivo2.csv ...]")
        print(f"  python {sys.argv[0]} 3 <k> <cod1> <cod2> <cod3> <arquivo1.csv> [arquivo2.csv ...]")
        print(f"  python {sys.argv[0]} 4 <arquivo1.csv> [arquivo2.csv ...]")
        print(f"  python {sys.argv[0]} 5 <indiceCliente> <arquivo1.csv> [arquivo2.csv ...]")
        sys.exit(1)

    opcao = int(sys.argv[1])

    if opcao < 1 or opcao > 5:
        print("Opção inválida.")
        sys.exit(1)

    if opcao == 1:
        primeiro_arquivo = 5

    elif opcao == 2:
        primeiro_arquivo = 3

    elif opcao == 3:
        primeiro_arquivo = 6

    elif opcao == 4:
        primeiro_arquivo = 2

    elif opcao == 5:
        primeiro_arquivo = 3

    if len(sys.argv) <= primeiro_arquivo:
        print("Faltam argumentos.")
        sys.exit(1)

    lista = compras.ListaCompras()
    for arquivo in sys.argv[primeiro_arquivo:]:
        if compras.leitura_csv(f"../{arquivo}", lista) != 0:
            sys.exit(1)

    if opcao == 1:
        compras.testar_lista_compras(lista, sys.argv[2:5])

    elif opcao == 2:
        recomendacao.testar_similaridade(lista, int(sys.argv[2]))

    elif opcao == 3:
        recomendacao.testar_recomendacao(lista, int(sys.argv[2]), sys.argv[3:6])

    elif opcao == 4:
        recomendacao.testar_eficiencia(lista)

    elif opcao == 5:
        print("Cliente mais similar - comparação")
        recomendacao.testar_similaridade_csr(lista, int(sys.argv[2]))
        print()

        print("Tempo de execução - comparação")
        recomendacao.testar_eficiencia_csr(lista)
        print()

        print("Economia de memória - comparação")
        recomendacao.testar_memoria_csr(lista)


if __name__ == "__main__":
    main()
