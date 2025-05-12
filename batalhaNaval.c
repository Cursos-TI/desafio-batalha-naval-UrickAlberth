#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Dimensões do tabuleiro, navios e matrizes de habilidade
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Água
        }
    }
}

// Função para inicializar matriz de habilidade com zeros
void inicializarHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0; // Não afetado
        }
    }
}

// Função para criar matriz de habilidade Cone (topo na linha 0, base na linha 4)
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    // Cone: linha 0 tem 1 posição, linha 1 tem 2, linha 2 tem 3, etc.
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        int largura = i + 1; // Número de posições afetadas na linha
        int inicio = (TAM_HABILIDADE - largura) / 2; // Centraliza
        for (int j = inicio; j < inicio + largura; j++) {
            habilidade[i][j] = 1; // Marca como afetado
        }
    }
}

// Função para criar matriz de habilidade Cruz (centro em [2][2])
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    // Cruz: linha e coluna central
    int centro = TAM_HABILIDADE / 2; // Índice 2
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        habilidade[i][centro] = 1; // Coluna central
        habilidade[centro][i] = 1; // Linha central
    }
}

// Função para criar matriz de habilidade Octaedro (losango, centro em [2][2])
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    // Octaedro: forma de losango centrada
    int centro = TAM_HABILIDADE / 2; // Índice 2
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Distância de Manhattan para formar losango
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1; // Marca como afetado
            }
        }
    }
}

// Função para verificar se a posição do navio é válida
bool validarPosicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, 
                   int tipo, int tamanho) {
    // Tipo: 0 (horizontal), 1 (vertical), 2 (diagonal crescente), 3 (diagonal decrescente)
    if (tipo == 0) { // Horizontal
        if (coluna + tamanho > TAM_TABULEIRO) return false;
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] != 0) return false;
        }
    } else if (tipo == 1) { // Vertical
        if (linha + tamanho > TAM_TABULEIRO) return false;
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] != 0) return false;
        }
    } else if (tipo == 2) { // Diagonal crescente
        if (linha + tamanho > TAM_TABULEIRO || coluna + tamanho > TAM_TABULEIRO) return false;
        for (int k = 0; k < tamanho; k++) {
            if (tabuleiro[linha + k][coluna + k] != 0) return false;
        }
    } else if (tipo == 3) { // Diagonal decrescente
        if (linha + tamanho > TAM_TABULEIRO || coluna < tamanho - 1) return false;
        for (int k = 0; k < tamanho; k++) {
            if (tabuleiro[linha + k][coluna - k] != 0) return false;
        }
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, 
                    int tipo, int tamanho) {
    if (!validarPosicao(tabuleiro, linha, coluna, tipo, tamanho)) {
        printf("Posicao invalida para o navio em (%d,%d)\n", linha, coluna);
        return false;
    }
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

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int linha_origem, int coluna_origem) {
    // Calcula deslocamento para centralizar a matriz de habilidade
    int offset = TAM_HABILIDADE / 2; // Índice 2
    // Itera sobre a matriz de habilidade
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Calcula posição correspondente no tabuleiro
            int tab_linha = linha_origem + (i - offset);
            int tab_coluna = coluna_origem + (j - offset);
            // Verifica se está dentro dos limites do tabuleiro
            if (tab_linha >= 0 && tab_linha < TAM_TABULEIRO && 
                tab_coluna >= 0 && tab_coluna < TAM_TABULEIRO) {
                // Aplica habilidade apenas se a posição na matriz de habilidade é 1
                if (habilidade[i][j] == 1) {
                    tabuleiro[tab_linha][tab_coluna] = 5; // Marca área afetada
                }
            }
        }
    }
}

// Função para exibir o tabuleiro com caracteres distintos
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf(" ~ "); // Água
            else if (tabuleiro[i][j] == 3) printf(" N "); // Navio
            else if (tabuleiro[i][j] == 5) printf(" * "); // Área afetada
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro e matrizes de habilidade
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidadeCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona os navios
    posicionarNavio(tabuleiro, 2, 3, 0, TAM_NAVIO); // Horizontal
    posicionarNavio(tabuleiro, 5, 7, 1, TAM_NAVIO); // Vertical
    posicionarNavio(tabuleiro, 0, 0, 2, TAM_NAVIO); // Diagonal crescente
    posicionarNavio(tabuleiro, 0, 9, 3, TAM_NAVIO); // Diagonal decrescente
    
    // Cria as matrizes de habilidade
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Aplica as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 7, 2); // Cone centrado em (7,2)
    aplicarHabilidade(tabuleiro, habilidadeCruz, 4, 4); // Cruz centrada em (4,4)
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 8, 8); // Octaedro centrado em (8,8)
    
    // Exibe o tabuleiro com navios e áreas de habilidade
    printf("\nTabuleiro com navios e areas de efeito das habilidades:\n");
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
