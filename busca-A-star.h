// Feito por: Lucas Garcia E Luis Augusto
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "libs/fileSys.cpp"

#define RASCUNHO_H // Define o identificador

#define LINHAS 10
#define COLUNAS 10


typedef struct NoCaminho {
   int x, y;
   int custo_g; // Custo do início até o nó atual
   int custo_h; // Heurística (distância até o objetivo)
   int custo_f; // Custo total: custo_g + custo_h
   struct NoCaminho* pai; // Nó pai para reconstrução do caminho
} TNoCaminho;


void lerMapa(char* arquivo, int mapa[LINHAS][COLUNAS]);
void imprimirMapa(int mapa[LINHAS][COLUNAS]);
void buscaAestrela(int mapa[LINHAS][COLUNAS], int inicio_x, int inicio_y, int objetivo_x, int objetivo_y);
