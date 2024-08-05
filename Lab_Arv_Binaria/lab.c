#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int conteudo;
    struct no *esquerda, *direita;
} No;

typedef struct
{
    No *raiz;
} ArvB;

void inserirDireita(No *no, int valor);
void inserirEsquerda(No *no, int valor)
{
    if (no->esquerda == NULL)
    {
        No *novo = malloc(sizeof(No));
        if (novo == NULL)
        {
            perror("Erro ao alocar memória para novo nó");
            exit(EXIT_FAILURE);
        }
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    }
    else
    {
        if (valor < no->esquerda->conteudo)
        {
            inserirEsquerda(no->esquerda, valor);
        }
        else
        {
            inserirDireita(no->esquerda, valor);
        }
    }
}

void inserirDireita(No *no, int valor)
{
    if (no->direita == NULL)
    {
        No *novo = malloc(sizeof(No));
        if (novo == NULL)
        {
            perror("Erro ao alocar memória para novo nó");
            exit(EXIT_FAILURE);
        }
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    }
    else
    {
        if (valor > no->direita->conteudo)
        {
            inserirDireita(no->direita, valor);
        }
        else
        {
            inserirEsquerda(no->direita, valor);
        }
    }
}

void inserir(ArvB *arv, int valor)
{
    if (arv->raiz == NULL)
    {
        No *novo = malloc(sizeof(No));
        if (novo == NULL)
        {
            perror("Erro ao alocar memória para novo nó");
            exit(EXIT_FAILURE);
        }
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    }
    else
    {
        if (valor < arv->raiz->conteudo)
        {
            inserirEsquerda(arv->raiz, valor);
        }
        else
        {
            inserirDireita(arv->raiz, valor);
        }
    }
}

void imprimir(No *raiz)
{
    if (raiz != NULL)
    {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

void liberarArvore(No *raiz)
{
    if (raiz != NULL)
    {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

void imprimirArvoreArquivo(No *raiz, FILE *arquivo)
{
    if (raiz != NULL)
    {
        fprintf(arquivo, "%d\n", raiz->conteudo);
        imprimirArvoreArquivo(raiz->esquerda, arquivo);
        imprimirArvoreArquivo(raiz->direita, arquivo);
    }
}

void gerarArquivo(ArvB *arv)
{
    FILE *teste = fopen("Breast_Cancer.csv", "r");
    if (teste == NULL)
    {
        perror("Erro ao abrir o arquivo Breast_Cancer.csv");
        return;
    }

    char *linha = NULL;
    size_t tamanhoLinha = 0;
    int age, tumor;
    while (getline(&linha, &tamanhoLinha, teste) != -1)
    {
        if (sscanf(linha, "%d,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d", &age, &tumor) == 2)
        {
            int soma = age + tumor;
            inserir(arv, soma);
        }
    }

    free(linha);
    fclose(teste);
}

void emitirRelatorio(ArvB *arv)
{
    FILE *res = fopen("res.txt", "w");
    if (res == NULL)
    {
        perror("Erro ao abrir o arquivo res.txt");
        return;
    }

    printf("Elementos na árvore:\n");
    imprimir(arv->raiz);
    printf("\n");

    imprimirArvoreArquivo(arv->raiz, res);
    fclose(res);
}

int main()
{
    ArvB arv;
    arv.raiz = NULL;

    int opt = 0;
    while (opt != 3)
    {
        printf("\n1 - Gerar arquivo\n");
        printf("2 - Emitir relatorio\n");
        printf("3 - Encerrar programa\n");
        scanf(" %d", &opt);
        getchar(); // Consumir newline left in buffer

        switch (opt)
        {
        case 1:
            gerarArquivo(&arv);
            break;
        case 2:
            emitirRelatorio(&arv);
            break;
        case 3:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }

    liberarArvore(arv.raiz); // Liberar a memória alocada para a árvore antes de encerrar o programa
    return 0;
}
