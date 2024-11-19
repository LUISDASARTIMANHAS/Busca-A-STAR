#include "rascunho.h"

int heuristica(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool eh_valido(int x, int y, int mapa[LINHAS][COLUNAS], bool lista_fechada[LINHAS][COLUNAS]) {
    return (x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS && mapa[x][y] == 0 && !lista_fechada[x][y]);
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
        mapa[atual->x][atual->y] = 2;
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

void ler_mapa(const char* nome_arquivo, int mapa[LINHAS][COLUNAS]) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        printf("Caminho fornecido: %s\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            fscanf(arquivo, "%d", &mapa[i][j]);
        }
    }

    fclose(arquivo);
}

int main() {
    int mapa[LINHAS][COLUNAS];
    ler_mapa("Mapa.txt", mapa);

    int inicio_x = 0, inicio_y = 0;
    int objetivo_x = 9, objetivo_y = 9;

    busca_a_estrela(mapa, inicio_x, inicio_y, objetivo_x, objetivo_y);
    imprimir_mapa(mapa);

    return 0;
}