# EP 1 - Algoritmos em Grafos

Projeto desenvolvido para a disciplina de **Algoritmos em Grafos 2025.3** da **UFABC**, voltado à solução do problema proposto no EP1 com uma implementação em C baseada em programação dinâmica para grafos direcionados com restrição de tempo.

## Sobre o projeto

O programa recebe uma malha viária orientada, uma lista de entregas e um limite máximo de tempo para cada transporte. Para cada consulta, ele verifica se existe um caminho entre origem e destino que respeite o tempo limite e, quando possível, retorna o caminho de **menor distância**, desempregando por **menor tempo** entre os caminhos de mesma distância.

O problema é resolvido com uma adaptação do algoritmo de **Bellman-Ford-Moore**, usando um estado auxiliar que combina vértice e tempo acumulado para preservar a restrição temporal.

## Regras do problema

- As estradas são direcionadas.
- Cada aresta possui dois pesos: distância em quilômetros e tempo em minutos.
- O programa processa várias instâncias até encontrar `0 0` na entrada.
- Para cada entrega, a resposta informa se ela é possível dentro do tempo limite e, em caso positivo, mostra distância e tempo obtidos.

## Estratégia de solução

A solução constrói um dígrafo com lista de adjacência e executa uma variação do Bellman-Ford-Moore limitada por tempo. O estado dinâmico considera a melhor distância para alcançar cada vértice com tempo exato acumulado, permitindo filtrar soluções que ultrapassem o limite da consulta.

O desempate exigido no enunciado também é tratado: entre caminhos com a menor distância, escolhe-se o de menor tempo.

## Recorrência usada

A ideia central da programação dinâmica é:

```text
D[v][t] = menor distância para chegar ao vértice v usando exatamente t minutos
```

Para cada aresta `u -> v` com distância `c` e tempo `w`, a transição é:

```text
D[v][t + w] = min(D[v][t + w], D[u][t] + c)
```

com `D[s][0] = 0` para a origem `s` e `D[v][t] = ∞` quando o estado for inalcançável.

## Tecnologias utilizadas

- **C**
- Estruturas de dados com lista de adjacência
- `stdio.h`, `stdlib.h`, `limits.h`

## Arquivos do projeto

| Arquivo | Função |
|---|---|
| `anachr.c` | Implementação principal da solução do EP |
| `entrada-3.txt` | Exemplo de instância de entrada para testes |
| `mkanachr.c` | Gerador de instâncias aleatórias para validação local |

## Como compilar

```bash
gcc anachr.c -o anachr
```

## Como executar

Com o executável compilado, rode o programa redirecionando a entrada padrão:

```bash
./anachr < entrada-3.txt
```

O programa lê várias instâncias até encontrar `0 0` no final da entrada.

## Exemplo de saída

A saída segue exatamente o formato pedido no enunciado:

```text
Instancia 1
Possivel - 5 km, 3 min
Impossivel
Possivel - 6 km, 4 min
...
```

## Complexidade

A solução utiliza um estado adicional para tempo, o que torna o algoritmo polinomial em relação ao número de vértices, arestas e limite de tempo considerado. A análise de tempo está comentada no código, conforme solicitado no enunciado.

## Observações

Este projeto foi desenvolvido como Exercício Programa individual da UFABC, e a entrada e a saída devem seguir rigorosamente o contrato descrito no PDF para que a correção automática funcione corretamente.
