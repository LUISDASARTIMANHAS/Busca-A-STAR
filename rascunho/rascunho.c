#include "rascunho.h"

// Função para calcular a heurística Manhattan
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Função para verificar se uma posição é válida no mapa
bool is_valid(int x, int y, int map[ROWS][COLS], bool closed_list[ROWS][COLS]) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && map[x][y] == 0 && !closed_list[x][y]);
}

// Função para reconstruir o caminho
void reconstruct_path(TPathNode* current, int map[ROWS][COLS]) {
    while (current != NULL) {
        map[current->x][current->y] = 2; // Marcar o caminho no mapa
        current = current->parent;
    }
}

// Função para o algoritmo A*
void a_star(int map[ROWS][COLS], int start_x, int start_y, int goal_x, int goal_y) {
    bool closed_list[ROWS][COLS] = {false};
    TPathNode* open_list[ROWS * COLS];
    int open_count = 0;

    TPathNode* start = (TPathNode*)malloc(sizeof(TPathNode));
    start->x = start_x;
    start->y = start_y;
    start->g_cost = 0;
    start->h_cost = heuristic(start_x, start_y, goal_x, goal_y);
    start->f_cost = start->g_cost + start->h_cost;
    start->parent = NULL;

    open_list[open_count++] = start;

    while (open_count > 0) {
        int min_index = 0;
        for (int i = 1; i < open_count; i++) {
            if (open_list[i]->f_cost < open_list[min_index]->f_cost) {
                min_index = i;
            }
        }

        TPathNode* current = open_list[min_index];
        open_list[min_index] = open_list[--open_count];

        if (current->x == goal_x && current->y == goal_y) {
            reconstruct_path(current, map);
            printf("Caminho encontrado!\n");
            free(current);
            return;
        }

        closed_list[current->x][current->y] = true;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (is_valid(nx, ny, map, closed_list)) {
                TPathNode* neighbor = (TPathNode*)malloc(sizeof(TPathNode));
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g_cost = current->g_cost + 1;
                neighbor->h_cost = heuristic(nx, ny, goal_x, goal_y);
                neighbor->f_cost = neighbor->g_cost + neighbor->h_cost;
                neighbor->parent = current;

                open_list[open_count++] = neighbor;
            }
        }
        free(current);
    }

    printf("Caminho não encontrado!\n");
}

// Função para imprimir o mapa
void print_map(int map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == 1)
                printf("█");
            else if (map[i][j] == 2)
                printf(".");
            else
                printf(" ");
        }
        printf("\n");
    }
}

// Função para ler o mapa de um arquivo
void read_map(const char* filename, int map[ROWS][COLS]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        perror("Detalhes do erro");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(file, "%d", &map[i][j]) != 1) {
                printf("Erro ao ler os dados do mapa na posição (%d, %d).\n", i, j);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }


    fclose(file);
}

int main() {
    int map[ROWS][COLS];
    read_map("/home/lucas/Documentos/ifes-2ano/Busca-A-STAR/rascunho/Mapa.txt", map);

    int start_x = 0, start_y = 0;
    int goal_x = 9, goal_y = 9;

    a_star(map, start_x, start_y, goal_x, goal_y);
    print_map(map);

    return 0;
}
