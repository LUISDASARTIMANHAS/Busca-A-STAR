#include "rascunho.h"

int heuristica(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool eh_valido(int x, int y, int mapa[LINHAS][COLUNAS], bool lista_fechada[LINHAS][COLUNAS]) {
    return (x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS &&
           (mapa[x][y] == 8 || mapa[x][y] == 9) && // Permitir objetivo como válido
           !lista_fechada[x][y]);
}


bool esta_na_lista_aberta(TNoCaminho* lista[], int contagem, int x, int y) {
    for (int i = 0; i < contagem; i++) {
        if (lista[i]->x == x && lista[i]->y == y) {
            return true;
        }
    }
    return false;
}

TNoCaminho* criar_no(int x, int y, int custo_g, int custo_h, TNoCaminho* pai) {
    TNoCaminho* no = (TNoCaminho*)malloc(sizeof(TNoCaminho));
    if (!no) {
        perror("Erro ao alocar memória para o nó.");
        exit(EXIT_FAILURE);
    }
    no->x = x;
    no->y = y;
    no->custo_g = custo_g;
    no->custo_h = custo_h;
    no->custo_f = custo_g + custo_h;
    no->pai = pai;
    return no;
}

void reconstruir_caminho(TNoCaminho* atual, int mapa[LINHAS][COLUNAS]) {
    while (atual != NULL) {
        if (atual->x < 0 || atual->x >= LINHAS || atual->y < 0 || atual->y >= COLUNAS) {
            printf("Erro: Coordenadas inválidas (%d, %d).\n", atual->x, atual->y);
            break;
        }
        // Não sobrescreva o ponto de partida ou o objetivo
        if (mapa[atual->x][atual->y] != 8 && mapa[atual->x][atual->y] != 9) {
            mapa[atual->x][atual->y] = 2; // Marca o caminho
        }
        atual = atual->pai;
    }
}

void liberar_lista_aberta(TNoCaminho* lista[], int contagem) {
    for (int i = 0; i < contagem; i++) {
        free(lista[i]);
    }
}

void busca_a_estrela(int mapa[LINHAS][COLUNAS], int inicio_x, int inicio_y, int objetivo_x, int objetivo_y) {
    bool lista_fechada[LINHAS][COLUNAS] = {false};
    TNoCaminho* lista_aberta[LINHAS * COLUNAS];
    int contagem_aberta = 0;

    TNoCaminho* inicio = criar_no(inicio_x, inicio_y, 0, heuristica(inicio_x, inicio_y, objetivo_x, objetivo_y), NULL);
    lista_aberta[contagem_aberta++] = inicio;

    mapa[inicio_x][inicio_y] = 0; // Temporariamente libera o ponto inicial
    while (contagem_aberta > 0) {
        int indice_min = 0;
        for (int i = 1; i < contagem_aberta; i++) {
            if (lista_aberta[i]->custo_f < lista_aberta[indice_min]->custo_f) {
                indice_min = i;
            }
        }

        TNoCaminho* atual = lista_aberta[indice_min];
        lista_aberta[indice_min] = lista_aberta[--contagem_aberta];

        if (atual->x == objetivo_x && atual->y == objetivo_y) {
            reconstruir_caminho(atual, mapa);
            liberar_lista_aberta(lista_aberta, contagem_aberta);
            free(atual);
            printf("Caminho encontrado!\n");
            return;
        }

        lista_fechada[atual->x][atual->y] = true;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int nx = atual->x + dx[i];
            int ny = atual->y + dy[i];

            if (eh_valido(nx, ny, mapa, lista_fechada)) {
                if (!esta_na_lista_aberta(lista_aberta, contagem_aberta, nx, ny)) {
                    TNoCaminho* vizinho = criar_no(nx, ny, atual->custo_g + 1, heuristica(nx, ny, objetivo_x, objetivo_y), atual);
                    lista_aberta[contagem_aberta++] = vizinho;
                }
            }
        }

        free(atual);
    }

    printf("Caminho não encontrado!\n");
    liberar_lista_aberta(lista_aberta, contagem_aberta);
}

void imprimir_mapa(int mapa[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }
}

void ler_mapa(const char* nome_arquivo, int mapa[LINHAS][COLUNAS], int* inicio_x, int* inicio_y, int* objetivo_x, int* objetivo_y) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char c;
            fscanf(arquivo, " %c", &c); // Lê um caractere
            if (c == '*') {
                *inicio_x = i;
                *inicio_y = j;
                mapa[i][j] = 0; // Converte para 0 no mapa
            } else if (c == '#') {
                *objetivo_x = i;
                *objetivo_y = j;
                mapa[i][j] = 0; // Converte para 0 no mapa
            } else {
                mapa[i][j] = c - '0'; // Converte caractere para inteiro
            }
        }
    }

    fclose(arquivo);
}

int main() {
    int mapa[LINHAS][COLUNAS];
    int inicio_x, inicio_y, objetivo_x, objetivo_y;

    // Lê o mapa e identifica o início e o objetivo
    ler_mapa("Mapa.txt", mapa, &inicio_x, &inicio_y, &objetivo_x, &objetivo_y);

    // Executa a busca A*
    busca_a_estrela(mapa, inicio_x, inicio_y, objetivo_x, objetivo_y);

    // Marca o início e o objetivo no mapa novamente
    mapa[inicio_x][inicio_y] = 8; // Representa o início
    mapa[objetivo_x][objetivo_y] = 9; // Representa o objetivo

    // Imprime o resultado
    imprimir_mapa(mapa);

    return 0;
}


