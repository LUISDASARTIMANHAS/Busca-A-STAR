#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#ifndef RASCUNHO_H // Verifica se o identificador não foi definido
#define RASCUNHO_H // Define o identificador

#define ROWS 10
#define COLS 10

typedef struct PathNode {
    int x, y;
    int g_cost; // Custo do início até o nó atual
    int h_cost; // Heurística (distância até o objetivo)
    int f_cost; // Custo total: g_cost + h_cost
    struct PathNode* parent; // Nó pai para reconstrução do caminho
} TPathNode;

void read_map(const char* filename, int map[ROWS][COLS]);
void print_map(int map[ROWS][COLS]);
void a_star(int map[ROWS][COLS], int start_x, int start_y, int goal_x, int goal_y);

#endif // Finaliza o cabeçalho


