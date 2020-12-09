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

bool branchysAux(Arbin<int> a, int& ret) {
    if(a.esVacio()) return true;

    bool iz = branchysAux(a.hijoIz(), ret);
    bool der = branchysAux(a.hijoDer(), ret);

    if (iz || der) {
        ret++;
        if (a.raiz() % 2 == 0) return true;
        else return false;
    }

    else return false;
}

int branchys(Arbin<int> a) {
    int ret = 0;

    if (!a.esVacio()) {
        branchysAux(a, ret);
    }

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