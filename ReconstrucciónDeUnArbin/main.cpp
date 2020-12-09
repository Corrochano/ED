#include <iostream>
#include <string>
#include "Arbin.h"
#include "lista.h"
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

void reconstruccionAux(Arbin<int> a, Lista<int>& l) {
    if (a.esVacio()) return;
    
    if (esHoja(a)) {
        l.pon_final(a.raiz());
        return;
    }

    reconstruccionAux(a.hijoIz(), l);
    reconstruccionAux(a.hijoDer(), l);

    l.pon_final(a.raiz());
}

void reconstruccion(Arbin<int> a) {
    Lista<int> l;

    reconstruccionAux(a, l);

    cout << "\n-------------------------------------------------------\n";

    if (l.esVacia()) {
        cout << "Nada";
    }
    else {

        while (!l.esVacia()) {
            cout << l.primero() << " ";
            l.quita_ppio();
        }
    }

    cout << "\n-------------------------------------------------------\n";
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        reconstruccion(lee_arbol(cin));
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}