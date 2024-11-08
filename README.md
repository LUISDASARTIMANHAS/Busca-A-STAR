# Busca-A-STAR
Implementação do A*

## Busca A*
• Estratégia:
- Combina o custo do caminho g(n) com o valor da
heurística h(n)

- g(n) = custo do caminho do nó inicial até o nó n

- h(n) = valor da heurística do nó n até um nó

objetivo (distancia em linha reta no caso de
distancias espaciais)

- f(n) = g(n) + h(n)

 - É a técnica de busca mais utilizada.

## A estratégia é completa e ótima.

• Custo de tempo:
- Exponencial com o comprimento da solução,
porém boas funções heurísticas diminuem
significativamente esse custo.

- Custo memória:
- Guarda todos os nós expandidos na memória.
- Nenhum outro algoritmo ótimo garante expandir
menos nós.

guardar dois vetores pra guardar a precisão do A*, os dados serão jogados de um para o outro ate um deles estiver vazio.

***

## Definindo Heurísticas
- Um problema com a geração de novas funções
heurísticas é que muitas vezes não se consegue
obter uma única heurística “claramente melhor”.

- Podemos ter o melhor dos mundos através da
definição:

h(n) = max {h¹(n),..., hm
(n)}.

- Heurística do A*: f(n) = g(n) + h(n)
  - g(n) = custo do caminho
  - h(n) = função heurística
- Qual seria a função heurística h(n) mais
adequada para este problema?
  - A distância em linha reta é uma opção.
  - Essa heurística composta utiliza qualquer função
que seja mais precisa no nó em questão.

O próximo passo é gerar a árvore de
busca e expandir os nós que tiverem
o menor valor resultante da função
heurística f(n).

- f(n) = g(n) + h(n)
EX:

[1,2] = f(n) = ?? + ??

[2,1] = f(n) = ?? + ??
