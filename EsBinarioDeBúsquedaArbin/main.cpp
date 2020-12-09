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

void esBinarioIz(Arbin<int>a, bool& bin, int min, int max, int ant);

void esBinarioDer(Arbin<int>a, bool& bin, int min, int max, int ant) {
    if (a.esVacio() || !bin) return;

    if (ant == 2 || a == 0) {
        max = a.raiz();
        ant = 2;
    }

    if (!a.hijoDer().esVacio()) {
        if (a.hijoDer().raiz() < a.raiz()) { bin = false; return; }
    }

    if (!a.hijoIz().esVacio()) {
        if (a.hijoIz().raiz() > a.raiz() || a.hijoIz().raiz() < min) { bin = false; return; }
    }

    esBinarioDer(a.hijoDer(), bin, min, max, ant);
    esBinarioIz(a.hijoIz(), bin, min, max, ant);
}

void esBinarioIz(Arbin<int>a, bool& bin, int min, int max, int ant) {
    if (a.esVacio() || !bin) return;

    if (ant == 1 || ant == 0) {
        min = a.raiz();
        ant = 1;
    }

    if (!a.hijoDer().esVacio()) {
        if (a.hijoDer().raiz() < a.raiz() || a.hijoDer().raiz() > max) { bin = false; return; }
    }

    if (!a.hijoIz().esVacio()) {
        if (a.hijoIz().raiz() > a.raiz()) { bin = false; return; }
    }

    esBinarioDer(a.hijoDer(), bin, min, max, ant);
    esBinarioIz(a.hijoIz(), bin, min, max, ant);
}

void esBinarioBusquedaAux(Arbin<int>a, bool& bin, int min, int max, int ant) { // primero = 0, iz = 1. der =  2
    if (a.esVacio() || !bin) return;

    if (min == -1 && max == -1) {

        if (!a.hijoDer().esVacio()) {
            if (a.hijoDer().raiz() < a.raiz()) { bin = false; return; }
        }

        if (!a.hijoIz().esVacio()) {
            if (a.hijoIz().raiz() > a.raiz()) { bin = false; return; }
        }

        if (min == -1) min = a.raiz();
        if (max == -1) max = a.raiz();
    }

    esBinarioIz(a.hijoIz(), bin, min, max, 0);
    esBinarioDer(a.hijoDer(), bin, min, max, 0);
}

/** Devuelve el camino de pares más largo del árbol binario pasado por parámetro, 
Complejidad: a = 2 , b = 1, k = 0;
Por lo que Complejidad = O(2^n)
*/
void esBinarioBusqueda(Arbin<int> a) { // return ret, ret = camino de pares más largo del árbol
    bool ret = true;
    esBinarioBusquedaAux(a, ret, -1, -1, 0);

    if (ret) cout << "SI\n";
    else cout << "NO\n";
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        esBinarioBusqueda(lee_arbol(cin));
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}