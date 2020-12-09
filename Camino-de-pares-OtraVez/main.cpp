#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;

Arbin<int> lee_arbol(istream& in) {
    //char c;
    //in >> c;
    //switch (c) {
    //case '.': return Arbin<int>();
    //case '*': {
    //    Arbin<int> iz = lee_arbol(in);
    //    int raiz = 1;
    //    Arbin<int> dr = lee_arbol(in);
    //    return Arbin<int>(iz, raiz, dr);
    //}
    //default: return Arbin<int>();
    //}

    char c;
    in >> c;
    switch (c) {
    case '#': return Arbin<int>();
    case '[': {
        int raiz;
        in >> raiz;
        in >> c;
        return Arbin<int>(raiz);
    }
    case '(': {
        Arbin<int> iz = lee_arbol(in);
        int raiz;
        in >> raiz;
        Arbin<int> dr = lee_arbol(in);
        in >> c;
        return Arbin<int>(iz, raiz, dr);
    }
    default: return Arbin<int>();
    }
}

bool esHoja(const Arbin<int>& a) {
    return (!a.esVacio() && (a.hijoDer().esVacio() && a.hijoIz().esVacio()));
}

// Función auxiliar para hallar el camino de pares más largo del árbol binario pasado por parámetro, invocada en caminoPares
int caminoParesAux(Arbin<int> a, int& camino_largo) {
    if (a.esVacio()) return 0;

    int iz = caminoParesAux(a.hijoIz(), camino_largo);
    int der = caminoParesAux(a.hijoDer(), camino_largo );
    
    if (a.raiz() % 2 == 0) { 
        if (iz + der + 1 > camino_largo) camino_largo = iz + der +1;
        return iz > der ? iz + 1 : der + 1; 
    }
    
    if (iz > camino_largo) camino_largo = iz;
    if (der > camino_largo) camino_largo = der;

    return 0;
}

/** Devuelve el camino de pares más largo del árbol binario pasado por parámetro, 
Complejidad Lineal O(n) pq visita cada nodo una sola vez.
*/
int caminoPares(Arbin<int> a) { // return ret, ret = camino de pares más largo del árbol
    int ret = 0;
    caminoParesAux(a, ret);

    return ret;
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
       cout << caminoPares(lee_arbol(cin)) << endl;
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}