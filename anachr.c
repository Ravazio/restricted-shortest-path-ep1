// Algoritmos em Grafos
// EP1
// Author: Victor Ravazio de Lima
// RA: 11201920941

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 101 // Quantidade máxima de vértices
#define MAXA 10001 // Quantidade máxima de arcos
#define MAXH 6001 // Quantidade máxima de tempo
#define INF INT_MAX // Infinito tem o maior valor possível de se representar em int usando limits.h

// Vértices
#define Vertex int

// A lista de adjascência de um vértice v é composta por nós do tipo node
typedef struct node *link; 
struct node {
    Vertex w;
    int distance;
    int time;
    link next;
};

// Cria um novo nó para a lista de adjascências
// Tempo: O(1)
link NEW (Vertex w, int distance, int time, link next){
    link p = malloc(sizeof *p);
    p->w = w;
    p->distance = distance;
    p->time = time;
    p->next = next;
    return p;
}

// Contém o endereço para um dígrafo
typedef struct digraph *Digraph; 
// Estrutura do dígrafo
struct digraph {
    int V;
    int A;
    link *adj;
};

// Cria e inicializa um dígrafo (sem arcos)
// Tempo: O(V)
Digraph DIGRAPHinit (int V){
    Vertex v;
    Digraph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc((V+1) * sizeof(link));
    for(v = 1; v <= V; v++){ // O(V)
        G->adj[v] = NULL;
    }
    return G;
}

// Insere arcos no dígrafo G
// Tempo: O(V)
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, int distance, int time){
    link p;
    //if (v == w) return; // Sem laços
    for (p = G->adj[v]; p != NULL; p = p->next){ // O(V), no pior caso, V está ligado a todos os demais vértices -1 
        if (p->w == w) return; // Sem arcos paralelos
    }
    // o novo nó com w aponta para o que o nó do vértice v apontava anteriormente
    G->adj[v] = NEW(w, distance, time, G->adj[v]);
    G->A++;
}

// Exibe o dígrafo G
// Tempo: O(V + A)
void DIGRAPHshow (Digraph G){
    Vertex v;
    link p;
    for (v = 1; v <= G->V; v++){ // O(V)
        printf("%2d: ", v);
        for (p = G->adj[v]; p != NULL; p = p->next){ // O(V + A)
            printf("%2d(%2d km, %2d min) ", p->w, p->distance, p->time);
        }
        printf("\n");
    }
    printf("\n");
}

// Libera a memória do grafo alocado
// Tempo: O(V + A)
void DIGRAPHdestroy(Digraph G) {
    for (Vertex v = 1; v <= G->V; v++) { // O(V)
        link p = G->adj[v];
        while (p != NULL) { // O(V + A)
            link aux = p;
            p = p->next;
            free(aux);
        }
    }
    free(G->adj);
    free(G);
}

// dist[v][tt] = menor distância para chegar em v com tempo exato tt
static int dist_mat[MAXV][MAXH];

// precisa garantir a menor distância entre todos os caminhos que respeitam o tempo máximo
// Tempo: O(V * A * H)
int BellmanFordMooreTimeLimited(Digraph G, Vertex s, Vertex t, int h, int *best_dist, int *best_time){
    int V = G->V;

    // Inicializa arrays
    // O(1) na análise assintótica, pois são limites fixos
    for (int v = 1; v < MAXV; v++) {
        for (int tt = 0; tt < MAXH; tt++) {
            dist_mat[v][tt] = INF;
        }
    }

    // Origem: distância 0, tempo 0
    // todos os demais vão ter custos maiores do que ele nesse momento, fazendo com que o algoritmo "empurre-os" a partir dele
    dist_mat[s][0] = 0;

    for(int k=1; k <= V-1; k++){
        int updated = 0;
        
        // para cada vértice, queremos o menor caminho em distância possível para todos os tempos <= limite
        for(Vertex u = 1; u <= V; u++){ // O(V)
            for(int tt = 0; tt <= h; tt++){ // O(V * H)
                if (dist_mat[u][tt] == INF) continue; // estado inalcançável
                for (link p = G->adj[u]; p != NULL; p = p->next){  // Esse 'for' faz com que percorre todos os arcos a partir do vértice (u), O(V * H * A)
                    Vertex v = p->w;
                    int distance = dist_mat[u][tt] + p->distance;
                    int time = tt + p->time;

                    if (time > h) continue; // estoura limite de tempo

                    if (dist_mat[v][time] > distance){
                        // achei uma distância menor
                        dist_mat[v][time] = distance;
                        updated = 1;
                    }
                }
            }
        }
        if (!updated) break;
    }

    // Escolhe a melhor solução para o destino t em qualquer tempo <= h
    int result_distance = INF;
    int result_time = -1;

    for (int tt = 0; tt <= h; tt++) { // O(H)
        if (dist_mat[t][tt] < result_distance) {
            // melhor distância até t
            result_distance = dist_mat[t][tt];
            result_time = tt;
        // em caso de distancia igual, desempate por menor tempo
        } else if (dist_mat[t][tt] == result_distance && result_distance != INF && (result_time == -1 || tt < result_time)) { 
            result_time = tt;
        }
    }

    // não há caminho com tempo <= h
    if (result_distance == INF) {
        return 0; 
    }

    *best_dist = result_distance;
    *best_time = result_time;
    return 1;
}

// Tempo: O(k * V * H * A)
int main() {
    int n = 1; // n° vértices
    int m; // n° arcos
    int x, y, c, t; 
    int counter = 1; // n° instâncias
    int k; // qtd de entregas
    int cityOrigin, cityDestiny, timeLimity;

    while(n != 0){
        scanf("%d %d", &n, &m); // n cidades(vértices) e m estradas(arcos)
        if(n <= 0 || n >= MAXV || m < 0 || m >= MAXA) break;

        printf("Instancia %d\n", counter);

        Digraph G = DIGRAPHinit(n);

        for (int i = 1; i <= m; i++){ // A
            // Próximas m linhas tem 4 n° inteiros: x y c t
            // 1 <= x <= n: cidade de inicio 
            // 1 <= y <= n: cidade de destino 
            // c >= 0: comprimento da estrada
            // t >= 0: tempo gasto para percorre-lá
            if (scanf("%d %d %d %d", &x, &y, &c, &t) != 4) return 1;
            if (x < 1 || x > n || y < 1 || y > n || c < 0 || t < 0) return 1;

            DIGRAPHinsertA (G, x, y, c, t);
        }

        //DIGRAPHshow(G);

        scanf("%d", &k); // qtd de entregas
        if (k < 0) return 1;

        for (int j = 1; j <= k; j++){ // O(k)
            // Próximas k linhas tem 3 n° inteiros: x y h
            // x: cidade de origem
            // y: cidade de destino
            // 0 <= h <= 6000: tempo limite
            if (scanf("%d %d %d", &cityOrigin, &cityDestiny, &timeLimity) != 3) return 1;

            if (cityOrigin < 1 || cityOrigin > n || cityDestiny < 1 || cityDestiny > n || timeLimity < 0 || timeLimity >= MAXH) return 1;

            if (cityOrigin == cityDestiny) {
                printf("Possivel - 0 km, 0 min\n");
                continue;
            }

            int d, tt;
            int response = BellmanFordMooreTimeLimited(G, cityOrigin, cityDestiny, timeLimity, &d, &tt); // O(k * V * A * H)
            if (!response) {
                printf("Impossivel\n");
            } else {
                printf("Possivel - %d km, %d min\n", d, tt);
            }
        }

        printf("\n");
        counter++;
        DIGRAPHdestroy(G);
    }
    return 0;
}