#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* Fonctions du graphe et coloration de Welsh-Powell. */
Graph *createGraph(int n) {
    if (n <= 0) return NULL;
    Graph *g = calloc(1, sizeof(*g));
    if (g == NULL) return NULL;
    g->n = n;
    g->A = calloc((size_t)n, sizeof(*g->A));
    g->colors = malloc((size_t)n * sizeof(*g->colors));
    g->degrees = calloc((size_t)n, sizeof(*g->degrees));
    if (!g->A || !g->colors || !g->degrees) {
        freeGraph(g);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        g->A[i] = calloc((size_t)n, sizeof(**g->A));
        if (!g->A[i]) {
            freeGraph(g);
            return NULL;
        }
        g->colors[i] = -1;
    }
    return g;
}

int addEdge(Graph *g, int u, int v) {
    if (!g || u < 0 || v < 0 || u >= g->n || v >= g->n || u == v) return 0;
    g->A[u][v] = 1;
    g->A[v][u] = 1;
    return 1;
}

void computeDegrees(Graph *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        g->degrees[i] = 0;
        for (int j = 0; j < g->n; j++) g->degrees[i] += (g->A[i][j] != 0);
    }
}

int neighborUsingColor(const Graph *g, int vertex, int color) {
    if (!g || vertex < 0 || vertex >= g->n) return 0;
    for (int i = 0; i < g->n; i++) {
        if (g->A[vertex][i] && g->colors[i] == color) return 1;
    }
    return 0;
}

/* Trie les sommets par degre decroissant. */
static void sortByDecreasingDegree(const Graph *g, int *order) {
    for (int i = 0; i < g->n; i++) order[i] = i;
    for (int i = 1; i < g->n; i++) {
        int current = order[i];
        int j = i - 1;
        while (j >= 0 && g->degrees[order[j]] < g->degrees[current]) {
            order[j + 1] = order[j];
            j--;
        }
        order[j + 1] = current;
    }
}

void welshPowell(Graph *g) {
    if (!g) return;
    computeDegrees(g);
    for (int i = 0; i < g->n; i++) g->colors[i] = -1;
    int *verticesOrder = malloc((size_t)g->n * sizeof(*verticesOrder));
    if (!verticesOrder) {
        fprintf(stderr, "Erreur : allocation du tableau d'ordre impossible.\n");
        return;
    }
    sortByDecreasingDegree(g, verticesOrder);
    printf("Ordre Welsh-Powell :");
    for (int i = 0; i < g->n; i++) printf(" %d", verticesOrder[i]);
    printf("\n");

    int c = 0;
    for (int i = 0; i < g->n; i++) {
        int u = verticesOrder[i];
        if (g->colors[u] != -1) continue;
        g->colors[u] = c;
        printf("Couleur %d : %d", c, u);
        for (int j = i + 1; j < g->n; j++) {
            int v = verticesOrder[j];
            if (g->colors[v] == -1 && !neighborUsingColor(g, v, c)) {
                g->colors[v] = c;
                printf(" %d", v);
            }
        }
        printf("\n");
        c++;
    }
    free(verticesOrder);
}

int countColors(const Graph *g) {
    if (!g) return 0;
    int max = -1;
    for (int i = 0; i < g->n; i++) if (g->colors[i] > max) max = g->colors[i];
    return max + 1;
}

int verifyColoring(const Graph *g) {
    if (!g) return 0;
    for (int i = 0; i < g->n; i++) {
        if (g->colors[i] < 0) return 0;
        for (int j = i + 1; j < g->n; j++) {
            if (g->A[i][j] && g->colors[i] == g->colors[j]) return 0;
        }
    }
    return 1;
}

void displayAdjacency(const Graph *g) {
    if (!g) return;
    printf("Matrice d'adjacence :\n    ");
    for (int i = 0; i < g->n; i++) printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < g->n; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < g->n; j++) printf("%2d ", g->A[i][j]);
        printf("\n");
    }
}

void displayDegres(const Graph *g) {
    if (!g) return;
    printf("Degres :\n");
    for (int i = 0; i < g->n; i++) printf("Sommet %d : %d\n", i, g->degrees[i]);
}

void displayColoring(const Graph *g) {
    if (!g) return;
    printf("Nombre de couleurs : %d\n", countColors(g));
    for (int c = 0; c < countColors(g); c++) {
        printf("Couleur %d :", c);
        for (int i = 0; i < g->n; i++) if (g->colors[i] == c) printf(" %d", i);
        printf("\n");
    }
}

int dotExport(const Graph *g, const char *fileName) {
    if (!g || !fileName || !verifyColoring(g)) return 0;
    FILE *f = fopen(fileName, "w");
    if (!f) { perror("Ouverture fichier DOT"); return 0; }
    static const char *palette[] = {"#e76f51", "#457b9d", "#80b918", "#f4a261", "#b084cc", "#52b69a", "#ef476f", "#ffd166"};
    const int paletteSize = (int)(sizeof(palette) / sizeof(palette[0]));
    fprintf(f, "graph G {\n  graph [layout=neato, overlap=false, splines=true];\n  node [shape=circle, style=filled, fontname=Arial];\n");
    for (int i = 0; i < g->n; i++) {
        fprintf(f, "  %d [fillcolor=\"%s\", label=\"%d (c%d)\"];\n", i, palette[g->colors[i] % paletteSize], i, g->colors[i]);
    }
    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) if (g->A[i][j]) fprintf(f, "  %d -- %d;\n", i, j);
    }
    fprintf(f, "}\n");
    int ok = (fclose(f) == 0);
    return ok;
}

void freeGraph(Graph *g) {
    if (!g) return;
    if (g->A) {
        for (int i = 0; i < g->n; i++) free(g->A[i]);
    }
    free(g->A);
    free(g->colors);
    free(g->degrees);
    free(g);
}
