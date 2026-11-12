#include "examples.h"

/* Construction du cycle C7. */
Graph *buildOddCycle7(void) {
    Graph *g = createGraph(7);
    if (!g) return NULL;
    for (int i = 0; i < 7; i++) addEdge(g, i, (i + 1) % 7);
    return g;
}

/* Construction du graphe couronne H6. */
Graph *buildCrown6(void) {
    Graph *g = createGraph(12);
    if (!g) return NULL;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i != j) addEdge(g, 2*i, 2*j+1);
        }
    }
    return g;
}
