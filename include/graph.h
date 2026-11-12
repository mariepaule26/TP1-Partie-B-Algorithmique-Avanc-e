#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

/* Graphe simple non oriente, avec des sommets de 0 a n-1. */
typedef struct Graph {
    int n;
    int **A;        /* matrice d'adjacence */
    int *colors;    /* -1 si le sommet n'est pas encore colore */
    int *degrees;   /* degre de chaque sommet */
} Graph;

Graph *createGraph(int n);
int addEdge(Graph *g, int u, int v);
void computeDegrees(Graph *g);
int neighborUsingColor(const Graph *g, int vertex, int color);
void welshPowell(Graph *g);
int countColors(const Graph *g);
int verifyColoring(const Graph *g);
void displayAdjacency(const Graph *g);
void displayDegres(const Graph *g);
void displayColoring(const Graph *g);
int dotExport(const Graph *g, const char *fileName);
void freeGraph(Graph *g);

#endif
