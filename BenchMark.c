#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 10000  // Define o número máximo de elementos no arquivo

// Função para gerar números aleatórios e gravar no arquivo
void gerarArquivo(int quantidade) {
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", rand() % 1000);  // Gera números aleatórios entre 0 e 999
    }

    fclose(arquivo);
}

// Função para realizar a busca linear
void buscaLinear(int numero, int quantidade) {
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int elemento;
    clock_t inicio, fim;

    inicio = clock();

    while (fscanf(arquivo, "%d", &elemento) != EOF) {
        if (elemento == numero) {
            printf("Número encontrado usando busca linear.\n");
            break;
        }
    }

    fim = clock();

    fclose(arquivo);

    printf("Tempo de execução da busca linear: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}

// Função para realizar a busca sentinela
void buscaSentinela(int numero, int quantidade) {
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int elemento;
    clock_t inicio, fim;

    inicio = clock();

    fscanf(arquivo, "%d", &elemento);  // Leitura do primeiro elemento

    while (elemento != numero) {
        if (fscanf(arquivo, "%d", &elemento) == EOF) {
            printf("Número não encontrado usando busca sentinela.\n");
            fclose(arquivo);
            return;
        }
    }

    printf("Número encontrado usando busca sentinela.\n");

    fim = clock();

    fclose(arquivo);

    printf("Tempo de execução da busca sentinela: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}

// Função para realizar a busca binária
void buscaBinaria(int numero, int quantidade) {
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int *numeros = malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        perror("Erro de alocação de memória");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%d", &numeros[i]);
    }

    clock_t inicio, fim;

    inicio = clock();

    int inicioBusca = 0;
    int fimBusca = quantidade - 1;
    int meio;

    while (inicioBusca <= fimBusca) {
        meio = (inicioBusca + fimBusca) / 2;

        if (numeros[meio] == numero) {
            printf("Número encontrado usando busca binária.\n");
            free(numeros);
            fclose(arquivo);
            return;
        } else if (numeros[meio] < numero) {
            inicioBusca = meio + 1;
        } else {
            fimBusca = meio - 1;
        }
    }

    printf("Número não encontrado usando busca binária.\n");

    free(numeros);
    fim = clock();

    fclose(arquivo);

    printf("Tempo de execução da busca binária: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}

// Função para realizar a ordenação por Insertion Sort
void insertionSort(int quantidade) {
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int *numeros = malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        perror("Erro de alocação de memória");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%d", &numeros[i]);
    }

    clock_t inicio, fim;

    inicio = clock();

    for (int i = 1; i < quantidade; i++) {
        int chave = numeros[i];
        int j = i - 1;

        while (j >= 0 && numeros[j] > chave) {
            numeros[j + 1] = numeros[j];
            j = j - 1;
        }

        numeros[j + 1] = chave;
    }

    fim = clock();

    fclose(arquivo);

    printf("Tempo de execução do Insertion Sort: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    // Reescreve o arquivo ordenado
    arquivo = fopen("numeros.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", numeros[i]);
    }

    fclose(arquivo);

    free(numeros);
}

// Função para realizar a ordenação por Bubble Sort
void bubbleSort(int quantidade) {
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int *numeros = malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        perror("Erro de alocação de memória");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%d", &numeros[i]);
    }

    clock_t inicio, fim;

    inicio = clock();

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                // Troca os elementos se estiverem fora de ordem
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    fim = clock();

    fclose(arquivo);

    printf("Tempo de execução do Bubble Sort: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

    // Reescreve o arquivo ordenado
    arquivo = fopen("numeros.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", numeros[i]);
    }

    fclose(arquivo);

    free(numeros);
}

// Função para realizar a ordenação por Quick Sort
void quickSort(int *numeros, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(numeros, inicio, fim);

        quickSort(numeros, inicio, pivo - 1);
        quickSort(numeros, pivo + 1, fim);
    }
}

// Função auxiliar para o Quick Sort
int particiona(int *numeros, int inicio, int fim) {
    int pivo = numeros[fim];
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (numeros[j] < pivo) {
            i++;
            troca(&numeros[i], &numeros[j]);
        }
    }

    troca(&numeros[i + 1], &numeros[fim]);
    return i + 1;
}

// Função auxiliar para o Quick Sort
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função principal
int main() {
    int quantidade, escolha, numero;

    printf("Digite a quantidade de números a serem gerados: ");
    scanf("%d", &quantidade);

    gerarArquivo(quantidade);

    printf("\nMenu:\n");
    printf("1. Busca de elemento\n");
    printf("2. Classificação de elementos\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            printf("Digite o número a ser buscado: ");
            scanf("%d", &numero);

            // Executa as operações de busca
            buscaLinear(numero, quantidade);
            buscaSentinela(numero, quantidade);
            buscaBinaria(numero, quantidade);
            break;
        case 2:
            // Executa as operações de classificação
            insertionSort(quantidade);
            bubbleSort(quantidade);

            // Reabre o arquivo para o Quick Sort
            FILE *arquivo;
            arquivo = fopen("numeros.txt", "r");

            if (arquivo == NULL) {
                perror("Erro ao abrir o arquivo");
                exit(EXIT_FAILURE);
            }

            int *numeros = malloc(quantidade * sizeof(int));
            if (numeros == NULL) {
                perror("Erro de alocação de memória");
                fclose(arquivo);
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < quantidade; i++) {
                fscanf(arquivo, "%d", &numeros[i]);
            }

            fclose(arquivo);

            clock_t inicio, fim;

            inicio = clock();
            quickSort(numeros, 0, quantidade - 1);
            fim = clock();

            printf("Tempo de execução do Quick Sort: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

            // Reescreve o arquivo ordenado
            arquivo = fopen("numeros.txt", "w");

            if (arquivo == NULL) {
                perror("Erro ao abrir o arquivo");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < quantidade; i++) {
                fprintf(arquivo, "%d ", numeros[i]);
            }

            fclose(arquivo);

            free(numeros);
            break;
        default:
            printf("Escolha inválida.\n");
            break;
    }

    return 0;
}
