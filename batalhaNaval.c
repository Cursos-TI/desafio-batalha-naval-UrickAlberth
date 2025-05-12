#include <stdio.h>
#include <stdbool.h>

// Dimensões do tabuleiro e tamanho dos navios
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    // Itera sobre todas as posições do tabuleiro
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Define como água
        }
    }
}

// Função para verificar se a posição do navio é válida
bool validarPosicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, 
                   int tipo, int tamanho) {
    // Tipo: 0 (horizontal), 1 (vertical), 2 (diagonal crescente), 3 (diagonal decrescente)
    
    // Verifica limites e sobreposição
    if (tipo == 0) { // Horizontal
        if (coluna + tamanho > TAM_TABULEIRO) return false;
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] != 0) return false; // Verifica sobreposição
        }
    } else if (tipo == 1) { // Vertical
        if (linha + tamanho > TAM_TABULEIRO) return false;
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] != 0) return false; // Verifica sobreposição
        }
    } else if (tipo == 2) { // Diagonal crescente (linha e coluna aumentam)
        if (linha + tamanho > TAM_TABULEIRO || coluna + tamanho > TAM_TABULEIRO) return false;
        for (int k = 0; k < tamanho; k++) {
            if (tabuleiro[linha + k][coluna + k] != 0) return false; // Verifica sobreposição
        }
    } else if (tipo == 3) { // Diagonal decrescente (linha aumenta, coluna diminui)
        if (linha + tamanho > TAM_TABULEIRO || coluna < tamanho - 1) return false;
        for (int k = 0; k < tamanho; k++) {
            if (tabuleiro[linha + k][coluna - k] != 0) return false; // Verifica sobreposição
        }
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
bool POSITIONARNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, 
                    int tipo, int tamanho) {
    // Valida a posição antes de posicionar
    if (!validarPosicao(tabuleiro, linha, coluna, tipo, tamanho)) {
        printf("Posicao invalida para o navio em (%d,%d)\n", linha, coluna);
        return false;
    }
    
    // Posiciona o navio
    if (tipo == 0) { // Horizontal
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = 3; // Marca navio
        }
    } else if (tipo == 1) { // Vertical
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = 3; // Marca navio
        }
    } else if (tipo == 2) { // Diagonal crescente
        for (int k = 0; k < tamanho; k++) {
            tabuleiro[linha + k][coluna + k] = 3; // Marca navio
        }
    } else if (tipo == 3) { // Diagonal decrescente
        for (int k = 0; k < tamanho; k++) {
            tabuleiro[linha + k][coluna - k] = 3; // Marca navio
        }
    }
    return true;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    // Imprime cabeçalho com números de colunas
    printf("\n   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Imprime linhas do tabuleiro
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    
    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Coordenadas fixas para os navios
    // Navio 1: Horizontal (linha 2, coluna 3)
    if (POSITIONARNavio(tabuleiro, 2, 3, 0, TAM_NAVIO)) {
        printf("Navio horizontal posicionado em (2,3)\n");
    }
    
    // Navio 2: Vertical (linha 5, coluna 7)
    if (POSITIONARNavio(tabuleiro, 5, 7, 1, TAM_NAVIO)) {
        printf("Navio vertical posicionado em (5,7)\n");
    }
    
    // Navio 3: Diagonal crescente (linha 0, coluna 0)
    if (POSITIONARNavio(tabuleiro, 0, 0, 2, TAM_NAVIO)) {
        printf("Navio diagonal crescente posicionado em (0,0)\n");
    }
    
    // Navio 4: Diagonal decrescente (linha 0, coluna 9)
    if (POSITIONARNavio(tabuleiro, 0, 9, 3, TAM_NAVIO)) {
        printf("Navio diagonal decrescente posicionado em (0,9)\n");
    }
    
    // Exibe o tabuleiro final
    printf("\nTabuleiro com navios posicionados:\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
