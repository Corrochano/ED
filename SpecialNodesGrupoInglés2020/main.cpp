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

int specialAux(Arbin<int> a, int& ret, int ancestros) {
    if (a.esVacio()) return 0;
    
    int yo = 1;
    
    if (a.raiz() % 2 == 0) yo = 0;

    int iz = specialAux(a.hijoIz(), ret, ancestros + yo);   
    int der = specialAux(a.hijoDer(), ret, ancestros + yo);

    if (ancestros > iz + der) ret++;

    return iz + der + yo;
}

int specialNodes(Arbin<int> a) {
    int ret = 0;

    specialAux(a, ret, 0);

    return ret;
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
       cout << specialNodes(lee_arbol(cin)) << endl;
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}