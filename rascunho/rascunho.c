#include "rascunho.h"

int heuristica(int x1, int y1, int x2, int y2) {
   return abs(x1 - x2) + abs(y1 - y2);
}


bool ehValido(int x, int y, int mapa[LINHAS][COLUNAS], bool lista_fechada[LINHAS][COLUNAS]) {
   return (x >= 0 && x < LINHAS && y >= 0 && y < COLUNAS &&
           mapa[x][y] != 1 && !lista_fechada[x][y]);
}


bool estaListaAberta(TNoCaminho* lista[], int contagem, int x, int y) {
   for (int i = 0; i < contagem; i++) {
       if (lista[i] && lista[i]->x == x && lista[i]->y == y) {
           return true;
       }
   }
   return false;
}


TNoCaminho* criarNo(int x, int y, int custo_g, int custo_h, TNoCaminho* pai) {
   TNoCaminho* no = (TNoCaminho*)malloc(sizeof(TNoCaminho));
   if (!no) {
       perror("Erro ao alocar memória");
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


void reconstruirCaminho(TNoCaminho* atual, int mapa[LINHAS][COLUNAS]) {
   while (atual != NULL) {
       if (mapa[atual->x][atual->y] != 3 && mapa[atual->x][atual->y] != 4) {
           mapa[atual->x][atual->y] = 2;  // Marca o caminho
       }
       atual = atual->pai;
   }
}


void liberarListaAberta(TNoCaminho* lista[], int contagem) {
   for (int i = 0; i < contagem; i++) {
       if (lista[i]) {
           free(lista[i]);
       }
   }
}


void buscaAestrela(int mapa[LINHAS][COLUNAS], int inicio_x, int inicio_y, int objetivo_x, int objetivo_y) {
   bool lista_fechada[LINHAS][COLUNAS] = {false};
   TNoCaminho* lista_aberta[LINHAS * COLUNAS] = {NULL};
   int contagem_aberta = 0;


   TNoCaminho* inicio = criarNo(inicio_x, inicio_y, 0, heuristica(inicio_x, inicio_y, objetivo_x, objetivo_y), NULL);
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


       printf("Explorando nó: (%d, %d)\n", atual->x, atual->y);


       if (atual->x == objetivo_x && atual->y == objetivo_y) {
           printf("Nó objetivo alcançado: (%d, %d)\n", atual->x, atual->y);
           reconstruirCaminho(atual, mapa);
           liberarListaAberta(lista_aberta, contagem_aberta);
           free(atual);
           return;
       }


       lista_fechada[atual->x][atual->y] = true;


       int dx[] = {0, 0, 1, -1};
       int dy[] = {1, -1, 0, 0};


       for (int i = 0; i < 4; i++) {
           int nx = atual->x + dx[i];
           int ny = atual->y + dy[i];


           if (!ehValido(nx, ny, mapa, lista_fechada)) {
               continue;
           }


           if (!estaListaAberta(lista_aberta, contagem_aberta, nx, ny)) {
               TNoCaminho* vizinho = criarNo(nx, ny, atual->custo_g + 1,
                                              heuristica(nx, ny, objetivo_x, objetivo_y), atual);
               lista_aberta[contagem_aberta++] = vizinho;
           }
       }
   }


   liberarListaAberta(lista_aberta, contagem_aberta);
   printf("Caminho não encontrado.\n");
}


void imprimirMapa(int mapa[LINHAS][COLUNAS]) {
    int j = 0;
    for (j = 0; j < COLUNAS; j++) {
        printf(" Y%d",j);
    }
    printf("\n",j);
    for (int i = 0; i < LINHAS; i++) {
        printf("x%d ",i);
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 3) {
                printf("I "); // Marca o ponto inicial
            } else if (mapa[i][j] == 4) {
                printf("F "); // Marca o ponto final
            } else {
                printf("%d  ", mapa[i][j]);
            }
        }
        printf("\n");
    }
}


void corrigirMapa(int mapa[LINHAS][COLUNAS], int inicio_x, int inicio_y, int objetivo_x, int objetivo_y) {
   mapa[inicio_x][inicio_y] = 3; // Marca o ponto inicial com 3
   mapa[objetivo_x][objetivo_y] = 4; // Marca o ponto final com 4
}


void lerMapa(const char* arquivo, int mapa[LINHAS][COLUNAS]){
   FILE* f = fopen(arquivo, "r");
   if (!f) {
       perror("Erro ao abrir o arquivo");
       exit(EXIT_FAILURE);
   }


   for (int i = 0; i < LINHAS; i++) {
       for (int j = 0; j < COLUNAS; j++) {
           if (fscanf(f, "%d", &mapa[i][j]) != 1) {
               printf("Erro na leitura do mapa. Dados insuficientes.\n");
               fclose(f);
               exit(EXIT_FAILURE);
           }
       }
   }


   fclose(f);
}


void solicitarCoordenadas(int* x, int* y, const char* tipo, int mapa[LINHAS][COLUNAS]) {
   do {
       printf("Digite as coordenadas do ponto %s (x y): ", tipo);
       scanf("%d %d", x, y);


       if (*x < 0 || *x >= LINHAS || *y < 0 || *y >= COLUNAS || mapa[*x][*y] == 1) {
           printf("Coordenada inválida! Escolha uma posição dentro do mapa que não seja um obstáculo.\n");
       } else {
           break;
       }
   } while (true);
}


int main() {
   int mapa[LINHAS][COLUNAS];
   int inicioX, inicioY, objetivoX, objetivoY;


   lerMapa("../Mapa.txt", mapa);


   printf("Mapa Inicial:\n");
   imprimirMapa(mapa);


   solicitarCoordenadas(&inicioX, &inicioY, "inicial", mapa);
   solicitarCoordenadas(&objetivoX, &objetivoY, "final", mapa);


   corrigirMapa(mapa, inicioX, inicioY, objetivoX, objetivoY);


   printf("\nMapa Após Correção (se necessário):\n");
   imprimirMapa(mapa);


   buscaAestrela(mapa, inicioX, inicioY, objetivoX, objetivoY);


   printf("\nMapa com Caminho Traçado:\n");
   imprimirMapa(mapa);


   return 0;
}
