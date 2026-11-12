#include "examples.h"
#include <stdio.h>
#include <stdlib.h>

static int runCase(const char *name, Graph *g, int expectedColors, const char *dotFile) {
    if (!g) { fprintf(stderr, "Erreur d'allocation du graphe %s.\n", name); return 0; }
    printf("\n===== %s =====\n", name);
    displayAdjacency(g);
    welshPowell(g);
    displayDegres(g);
    displayColoring(g);
    int ok = verifyColoring(g) && countColors(g) == expectedColors;
    printf("Coloration valide : %s\n", verifyColoring(g) ? "OUI" : "NON");
    printf("Test nombre attendu (%d) : %s\n", expectedColors, ok ? "OK" : "ECHEC");
    if (!dotExport(g, dotFile)) { fprintf(stderr, "Export DOT impossible : %s\n", dotFile); ok = 0; }
    else printf("Fichier DOT genere : %s\n", dotFile);
    freeGraph(g);
    return ok;
}

int main(void) {
    int ok1 = runCase("Cycle impair C7 : chi=3", buildOddCycle7(), 3, "graphes/cycle_C7.dot");
    int ok2 = runCase("Couronne H6 : chi=2", buildCrown6(), 6, "graphes/couronne_H6.dot");
    if (!ok1 || !ok2) return EXIT_FAILURE;
    printf("\nTOUS LES TESTS DE DEMONSTRATION SONT REUSSIS.\n");
    return EXIT_SUCCESS;
}
