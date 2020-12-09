#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;

Arbin<int> lee_arbol(istream& in) {
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

bool branchysAux(const Arbin<int>& a, int& branchys, int camino) {
    if (a.esVacio()) return false;

    if (a.raiz() % 2 != 0) camino = 0;
    if (esHoja(a)) { branchys += camino + 1; return true; };

    bool iz = branchysAux(a.hijoDer(), branchys, camino + 1);
    bool der;

    if (!iz) {
        der = branchysAux(a.hijoIz(), branchys, camino + 1);
    }
    else {
        der = branchysAux(a.hijoIz(), branchys, camino);
    }

    if (!iz && !der) return false;

    if (a.raiz() % 2 != 0) return false;
    else return true;
}

bool branchyAux2(const Arbin<int>& a, int& branchys) {
    if (a.esVacio()) return false;

    if (esHoja(a)) {
        branchys++;
        if (a.raiz() % 2 == 0) return true;
        else return false;
    }

    bool der = branchyAux2(a.hijoDer(), branchys);
    bool iz = branchyAux2(a.hijoIz(), branchys);

    if (der || iz) branchys++;

    if (a.raiz() % 2 == 0 && (der || iz)) return true;
    else return false;
}

int branchys(const Arbin<int>& a) {
    int ret = 0;
   // branchysAux(a, ret, 0);
    branchyAux2(a, ret);
    return ret;
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        cout << branchys(lee_arbol(cin)) << endl;
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}