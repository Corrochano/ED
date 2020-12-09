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

void esSimetricoAux(Arbin<int> iz, Arbin<int> der, bool& sim) {
    if (!sim) return; // si no simétrico, vuelvo

    if (iz.esVacio() && der.esVacio()) return; // si los dos hijos están vacíos, vuelvo

    if ((iz.esVacio() && !der.esVacio()) || (!iz.esVacio() && der.esVacio())) { sim = false; return; }; // si uno está vacío y el otro no, no son simétrios y vuelvo
    
    if ((!iz.hijoDer().esVacio() && der.hijoIz().esVacio()) || (iz.hijoDer().esVacio() && !der.hijoIz().esVacio())) { sim = false; return; } // si el hijo iz del der y el hijo der del iz no son iguales, no simétrico, vuelvo

    if ((!iz.hijoIz().esVacio() && der.hijoDer().esVacio()) || (!iz.hijoIz().esVacio() && der.hijoDer().esVacio())) { sim = false; return; } // si el hijo iz del iz y el hijo der del der no son iguales, no simétrico, vuelvo

    esSimetricoAux(iz.hijoIz(), der.hijoDer(), sim); // lo compruebo comparando el hijo iz del izquierdo y el der del derecho
    esSimetricoAux(iz.hijoDer(), der.hijoIz(), sim); // lo compruebo comparando el hijo der del izquierdo y el iz del derecho
}

void esSimetrico(Arbin<int> a) { // return ret, ret = camino de pares más largo del árbol
    bool ret = true; // si es simétrico o no

    if (!a.esVacio() && !esHoja(a)) { // si el árbol no es ni vacío ni hoja
        esSimetricoAux(a.hijoIz(), a.hijoDer(), ret); // llama a la función auxiliar con sus hijos como parámetro
    }

    if (ret) cout << "SI\n"; // si es simétrico, saca sí
    else cout << "NO\n"; // si no es simétrico, saca no
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        esSimetrico(lee_arbol(cin));
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}