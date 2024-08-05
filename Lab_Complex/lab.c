#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void gerarArquivo();
void lerArquivo();
void preencherVetor(int *vet, int n);
void insercao(int vet[], int n, int *count);
void bs(int vet[], int n, int *count);

int main()
{
    char opt = '\0';
    srand(time(NULL));
    while (opt != 'S')
    {
        printf("\nT - gerar um arquivo esforcocomputacional.txt.\n");
        printf("R - ler o arquivo esforcocomputacional.txt.\n");
        printf("S - encerrar programa.\n");
        scanf(" %c", &opt);

        if (opt == 'T')
        {
            gerarArquivo();
        }
        else if (opt == 'R')
        {
            lerArquivo();
        }
        else if (opt == 'S')
        {
            printf("Encerrando o programa...\n");
        }
        else
        {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}

void gerarArquivo()
{
    FILE *teste = fopen("testes.txt", "r");
    if (teste == NULL)
    {
        perror("Erro ao abrir o arquivo testes.txt");
        return;
    }

    FILE *esf = fopen("esforcocomputacional.txt", "w");
    if (esf == NULL)
    {
        perror("Erro ao abrir o arquivo esforcocomputacional.txt");
        fclose(teste);
        return;
    }

    int n;
    while (fscanf(teste, "%d", &n) != EOF)
    {
        int *vet = (int *)malloc(n * sizeof(int));
        if (vet == NULL)
        {
            perror("Erro ao alocar memória");
            fclose(teste);
            fclose(esf);
            return;
        }
        preencherVetor(vet, n);

        int *vet_copy = (int *)malloc(n * sizeof(int));
        if (vet_copy == NULL)
        {
            perror("Erro ao alocar memória");
            free(vet);
            fclose(teste);
            fclose(esf);
            return;
        }

        for (int i = 0; i < n; i++)
        {
            vet_copy[i] = vet[i];
        }

        int bs_count = 0;
        int is_count = 0;
        bs(vet_copy, n, &bs_count);
        insercao(vet, n, &is_count);
        fprintf(esf, "%d, %d, %d\n", n, bs_count, is_count);

        free(vet);
        free(vet_copy);
    }
    fclose(teste);
    fclose(esf);
}

void preencherVetor(int vet[], int n)
{
    for (int i = 0; i < n; i++)
    {
        vet[i] = rand() % 10000;
    }
}

void insercao(int vet[], int n, int *count)
{
    *count = 0;
    for (int i = 1; i < n; i++)
    {
        int key = vet[i];
        int j = i - 1;

        while (j >= 0 && vet[j] > key)
        {
            vet[j + 1] = vet[j];
            j = j - 1;
        }
        vet[j + 1] = key;
        (*count)++; // Contando iterações do for
    }
}

// Algoritmo de ordenação por bolha
void bs(int vet[], int n, int *count)
{
    *count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (vet[j] > vet[j + 1])
            {
                int temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
            (*count)++; // Contando iterações do for interno
        }
    }
}
void lerArquivo()
{
    FILE *esf = fopen("esforcocomputacional.txt", "r");
    if (esf == NULL)
    {
        perror("Erro ao abrir o arquivo testes.txt");
        return;
    }
    int linhas = 0;
    int n, is_count, bs_count;
    int bs_mcaso = 10001;
    int bs_pcaso = -1;
    int bs_media = 0;
    int is_mcaso = 10001;
    int is_pcaso = -1;
    int is_media = 0;
    while (fscanf(esf, "%d, %d, %d\n", &n, &bs_count, &is_count) != EOF)
    {
        // Melhor caso para Bubble Sort
        if (bs_count < bs_mcaso)
        {
            bs_mcaso = bs_count;
        }
        // Pior caso para Bubble Sort
        if (bs_count > bs_pcaso)
        {
            bs_pcaso = bs_count;
        }
        // Melhor caso para Insertion Sort
        if (is_count < is_mcaso)
        {
            is_mcaso = is_count;
        }
        // Pior caso para Insertion Sort
        if (is_count > is_pcaso)
        {
            is_pcaso = is_count;
        }

        linhas++;
        bs_media += bs_count;
        is_media += is_count;
    }
    printf("\n\nmelhor caso bubbleSort %d , pior caso bubbleSort %d , media bubbleSort %d\n", bs_mcaso, bs_pcaso, bs_media / linhas);
    printf("\nmelhor caso insertSort %d, pior caso insertSort %d, media insertSort %d\n\n", is_mcaso, is_pcaso, is_media / linhas);

    fclose(esf);
}