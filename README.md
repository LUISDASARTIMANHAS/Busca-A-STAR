# Projeto de Implementação do Algoritmo A*

## Descrição

Este projeto acadêmico consiste na implementação do algoritmo de busca A* (A-estrela) em linguagem C. O objetivo é encontrar o caminho de menor custo entre um ponto inicial e um ponto final em um mapa bidimensional, representado por uma matriz. O mapa pode conter obstáculos, que são considerados intransponíveis pelo algoritmo.

## Proposta

A proposta deste trabalho é aplicar os conceitos de algoritmos de busca heurística, estudados na disciplina de Inteligência Artificial, em um problema prático de busca de caminho. O algoritmo A* foi escolhido por ser uma das técnicas mais eficientes e amplamente utilizadas para este tipo de problema, garantindo a otimalidade e a completude da busca quando utilizada uma heurística admissível.

## Objetivo

O principal objetivo deste projeto é desenvolver uma implementação funcional e eficiente do algoritmo A*, capaz de:

- Ler um mapa de um arquivo de texto.
- Permitir que o usuário defina as coordenadas de início e fim.
- Calcular o caminho de menor custo, evitando obstáculos.
- Exibir o mapa com o caminho encontrado.

## Tecnologias Utilizadas

- **Linguagem de Programação:** C
- **Compilador:** GCC (MinGW)
- **Editor de Código:** Visual Studio Code

## Algoritmo A*

O algoritmo A* utiliza uma função de avaliação `f(n)` para decidir qual nó da fronteira de busca deve ser expandido em seguida. A função é definida como:

`f(n) = g(n) + h(n)`

Onde:

- `g(n)`: é o custo do caminho percorrido desde o nó inicial até o nó `n`.
- `h(n)`: é o valor da heurística, que estima o custo do caminho do nó `n` até o nó objetivo.

Neste projeto, a heurística utilizada é a **Distância de Manhattan**, que é calculada pela soma das diferenças absolutas das coordenadas `x` e `y` entre o nó atual e o nó objetivo.

## Estrutura do Projeto

- **`busca-A-star.c`**: Contém a implementação principal do algoritmo A*, a lógica de manipulação do mapa e a função `main`.
- **`busca-A-star.h`**: Arquivo de cabeçalho com as declarações de funções e estruturas de dados.
- **`data/Mapa.txt`**: Arquivo de texto que representa o mapa a ser percorrido.
- **`libs/`**: Contém bibliotecas auxiliares.

## Como Compilar e Executar

1.  **Compilar:**
    ```bash
    gcc busca-A-star.c -o busca-A-star.exe -lm
    ```
2.  **Executar:**
    ```bash
    ./busca-A-star.exe
    ```

## Autores

- Lucas Garcia
- Luis Augusto