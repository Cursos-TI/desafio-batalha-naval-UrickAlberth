#include <stdio.h>
#include <stdbool.h>

// Dimensões do tabuleiro
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Água
        }
    }
}

// Função para verificar se a posição do navio é válida
bool validarPosicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, 
                   bool horizontal, int tamanho) {
    // Verifica se está dentro dos limites do tabuleiro
    if (horizontal) {
        if (coluna + tamanho > TAM_TABULEIRO) return false;
        // Verifica se há sobreposição
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] != 0) return false;
        }
    } else {
        if (linha + tamanho > TAM_TABULEIRO) return false;
        // Verifica se há sobreposição
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] != 0) return false;
        }
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, 
                    bool horizontal, int tamanho) {
    // Valida a posição antes de posicionar
    if (!validarPosicao(tabuleiro, linha, coluna, horizontal, tamanho)) {
        printf("Posicao invalida para o navio em (%d,%d)\n", linha, coluna);
        return false;
    }
    
    // Posiciona o navio
    if (horizontal) {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = 3; // Marca navio
        }
    } else {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = 3; // Marca navio
        }
    }
    return true;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n   ");
    // Imprime cabeçalho com números de colunas
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
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Coordenadas fixas para os navios
    int navio1_linha = 2, navio1_coluna = 3; // Navio horizontal
    int navio2_linha = 5, navio2_coluna = 7; // Navio vertical
    
    // Posiciona o primeiro navio (horizontal)
    if (posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, true, TAM_NAVIO)) {
        printf("Navio horizontal posicionado em (%d,%d)\n", navio1_linha, navio1_coluna);
    }
    
    // Posiciona o segundo navio (vertical)
    if (posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, false, TAM_NAVIO)) {
        printf("Navio vertical posicionado em (%d,%d)\n", navio2_linha, navio2_coluna);
    }
    
    // Exibe o tabuleiro final
    printf("\nTabuleiro com navios posicionados:\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
