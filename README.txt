TP1 - Partie B : Welsh-Powell et matrice d'adjacence
=======================================================================

1. CONTENU
- include/graph.h : structure Graph, declarations des fonctions
- src/graph.c : fonctions du graphe et algorithme de Welsh-Powell
- include/examples.h, src/examples.c : construction des deux graphes
- src/main.c : programme de demonstration et exports DOT
- tests/test_graph.c : tests des deux exemples
- graphes/*.dot : fichiers DOT produits par le programme
- documentation/Reponses_partie_B.txt : reponses aux deux questions
- Le compte rendu sera ajoute a part.

2. PREREQUIS
GCC C11. Facultatif : Graphviz pour convertir DOT en PNG.
Le programme peut etre execute dans VS Code / PowerShell (Windows) ou Linux.

3. WINDOWS - POWERSHELL - depuis le dossier TP1_Partie_B
Compilation :
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude src/main.c src/graph.c src/examples.c -o tp1_b.exe
Execution :
.\tp1_b.exe

Tests :
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_graph.c src/graph.c src/examples.c -o test_graph.exe
.\test_graph.exe

4. LINUX / MSYS2 UCRT64 - depuis le dossier TP1_Partie_B
Compilation : make
Execution : make run
Tests : make test
(Sous Windows, le Makefile peut aussi etre utilise avec 'make EXEEXT=.exe'.)

5. RESULTATS OBTENUS
Cycle C7 : 7 sommets, 7 aretes, chi(C7)=3, Welsh-Powell=3.
Couronne H6 : 12 sommets, 30 aretes, chi(H6)=2, Welsh-Powell=6.
Les sommets d'une meme couleur ne sont jamais adjacents.
Les egalites de degre sont departagees par l'indice de sommet croissant.
Les fichiers DOT sont ecrits dans graphes/ (repertoire de travail courant).

6. VISUALISATION DOT (Graphviz installe)
dot -Tpng graphes/cycle_C7.dot -o graphes/cycle_C7.png
dot -Tpng graphes/couronne_H6.dot -o graphes/couronne_H6.png

7. CONVENTIONS
Graphes simples non orientes ; sommets numerotes de 0 a n-1 ; matrice symetrique.
colors[i]=-1 signifie non colore. Pour H6 : a_i = 2(i-1), b_i=2(i-1)+1.
Les graphes sont alloues dynamiquement et liberes en fin de programme.

8. EN CAS DE PROBLEME
Si 'gcc' est introuvable, verifier GCC et C:\msys64\ucrt64\bin dans PATH.
Si fopen ne peut pas creer les fichiers DOT, se placer a la racine TP1_Partie_B.
Si 'dot' est introuvable, installer Graphviz ou ouvrir directement le fichier DOT.
