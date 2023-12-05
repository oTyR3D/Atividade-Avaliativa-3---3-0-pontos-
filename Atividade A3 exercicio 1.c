#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Produto
{
    int codigo;
    char nome[50];
    int quantidade;
    char descricao[100];
    float preco;
    struct Produto *prox;
} Produto;

Produto *inicializarListaVazia()
{
    return NULL;
}

Produto *criarNovoProduto()
{
    Produto *novoProduto;
    novoProduto = (Produto *)malloc(sizeof(Produto));
    if (novoProduto == NULL)
    {
        printf("Erro na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoProduto->codigo = rand();
    novoProduto->prox = NULL;
    return novoProduto;
}

void cadastrarProduto(Produto **estoque)
{
    Produto *novoProduto = criarNovoProduto();

    printf("Digite o nome do produto: ");
    scanf("%s", novoProduto->nome);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o preço individual do produto: ");
    scanf("%f", &novoProduto->preco);

    novoProduto->prox = *estoque;
    *estoque = novoProduto;

    printf("Produto cadastrado com sucesso!\n");
}

void adicionarNovoProduto(Produto **estoque)
{
    Produto *novoProduto = criarNovoProduto();

    printf("Digite o nome do novo produto: ");
    scanf("%s", novoProduto->nome);

    printf("Descreva o produto: ");
    getchar();
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin);
    novoProduto->descricao[strcspn(novoProduto->descricao, "\n")] = '\0';

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o preço individual do produto: ");
    scanf("%f", &novoProduto->preco);

    novoProduto->prox = *estoque;
    *estoque = novoProduto;

    printf("Novo produto adicionado com sucesso!\n");
}

void buscarProduto(Produto *estoque)
{
    int codigo;
    printf("Buscar Produto\n");

    printf("Código do produto: ");
    scanf("%d", &codigo);

    Produto *atual = estoque;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            printf("Produto encontrado:\n");
            printf("Código: %d\n", atual->codigo);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preço: %.2f\n", atual->preco);
            return;
        }
        atual = atual->prox;
    }

    printf("Produto não encontrado.\n");
}

void imprimirEstoque(Produto *estoque)
{
    printf("Lista de Produtos\n");

    Produto *atual = estoque;

    while (atual != NULL)
    {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               atual->codigo, atual->nome, atual->quantidade, atual->preco);
        atual = atual->prox;
    }
}

void excluirProduto(Produto **estoque)
{
    int codigo;
    printf("Excluir Produto\n");

    printf("Código do produto: ");
    scanf("%d", &codigo);

    Produto *atual = *estoque;
    Produto *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
        {
            if (anterior == NULL)
            {
                *estoque = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("Produto removido com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Produto não encontrado.\n");
}

void imprimirRelatorioProdutos(Produto *estoque)
{
    printf("\nRelatório dos Produtos\n");

    Produto *atual = estoque;

    while (atual != NULL)
    {
        printf("Código: %d\n", atual->codigo);
        printf("Nome: %s\n", atual->nome);
        printf("Descrição: %s\n", atual->descricao);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Preço: %.2f\n", atual->preco);
        printf("Total do Estoque de Produtos: R$ %.2f\n", atual->quantidade * atual->preco);

        atual = atual->prox;
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    Produto *estoque = inicializarListaVazia();
    int opcao;

    do
    {
        printf("\n1: Cadastrar Produto");
        printf("\n2: Buscar Produto");
        printf("\n3: Imprimir Estoque");
        printf("\n4: Excluir Produto");
        printf("\n5: Adicionar Novo Produto");
        printf("\n6: Imprimir Relatório dos Produtos");
        printf("\n0: Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarProduto(&estoque);
            break;
        case 2:
            buscarProduto(estoque);
            break;
        case 3:
            imprimirEstoque(estoque);
            break;
        case 4:
            excluirProduto(&estoque);
            break;
        case 5:
            adicionarNovoProduto(&estoque);
            break;
        case 6:
            imprimirRelatorioProdutos(estoque);
            break;
        case 0:
            printf("Programa encerrado!\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    Produto *atual = estoque;
    while (atual != NULL)
    {
        Produto *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}
