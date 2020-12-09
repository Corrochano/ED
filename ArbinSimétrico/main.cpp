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
    if (!sim) return; // si no sim�trico, vuelvo

    if (iz.esVacio() && der.esVacio()) return; // si los dos hijos est�n vac�os, vuelvo

    if ((iz.esVacio() && !der.esVacio()) || (!iz.esVacio() && der.esVacio())) { sim = false; return; }; // si uno est� vac�o y el otro no, no son sim�trios y vuelvo
    
    if ((!iz.hijoDer().esVacio() && der.hijoIz().esVacio()) || (iz.hijoDer().esVacio() && !der.hijoIz().esVacio())) { sim = false; return; } // si el hijo iz del der y el hijo der del iz no son iguales, no sim�trico, vuelvo

    if ((!iz.hijoIz().esVacio() && der.hijoDer().esVacio()) || (!iz.hijoIz().esVacio() && der.hijoDer().esVacio())) { sim = false; return; } // si el hijo iz del iz y el hijo der del der no son iguales, no sim�trico, vuelvo

    esSimetricoAux(iz.hijoIz(), der.hijoDer(), sim); // lo compruebo comparando el hijo iz del izquierdo y el der del derecho
    esSimetricoAux(iz.hijoDer(), der.hijoIz(), sim); // lo compruebo comparando el hijo der del izquierdo y el iz del derecho
}

void esSimetrico(Arbin<int> a) { // return ret, ret = camino de pares m�s largo del �rbol
    bool ret = true; // si es sim�trico o no

    if (!a.esVacio() && !esHoja(a)) { // si el �rbol no es ni vac�o ni hoja
        esSimetricoAux(a.hijoIz(), a.hijoDer(), ret); // llama a la funci�n auxiliar con sus hijos como par�metro
    }

    if (ret) cout << "SI\n"; // si es sim�trico, saca s�
    else cout << "NO\n"; // si no es sim�trico, saca no
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