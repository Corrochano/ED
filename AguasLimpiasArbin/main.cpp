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

int numTramosAux(Arbin<int> a, int & numTramos) {
    if (a.esVacio()) return 0;

    if (esHoja(a)) {
        return 1;
    }

    int iz = numTramosAux(a.hijoIz(), numTramos);
    int der = numTramosAux(a.hijoDer(), numTramos);

    if (iz < 0) iz = 0;
    if (der < 0) der = 0;

    int cauceLocal = iz + der - a.raiz();

    if (iz >= 3) numTramos++;
    if (der >= 3) numTramos++;

    return cauceLocal;
}

int aguasLimpias(Arbin<int> a) {
    int numTramos = 0;
    numTramosAux(a, numTramos);

    return numTramos;
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        cout << aguasLimpias(lee_arbol(cin)) << endl;
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}