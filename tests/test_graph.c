#include "examples.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    Graph *c = buildOddCycle7();
    assert(c && c->n == 7);
    computeDegrees(c);
    for (int i = 0; i < 7; i++) assert(c->degrees[i] == 2);
    welshPowell(c);
    assert(countColors(c) == 3 && verifyColoring(c));
    /* On verifie aussi qu'on peut relancer l'algorithme. */
    welshPowell(c);
    assert(countColors(c) == 3 && verifyColoring(c));
    freeGraph(c);

    Graph *h = buildCrown6();
    assert(h && h->n == 12);
    computeDegrees(h);
    for (int i = 0; i < 12; i++) assert(h->degrees[i] == 5);
    for (int i = 0; i < 6; i++) {
        assert(h->A[2*i][2*i+1] == 0);
        for (int j = 0; j < 6; j++) if (i != j) assert(h->A[2*i][2*j+1] == 1);
    }
    welshPowell(h);
    assert(countColors(h) == 6 && verifyColoring(h));
    freeGraph(h);
    printf("TESTS AUTOMATIQUES : OK\n");
    return 0;
}
