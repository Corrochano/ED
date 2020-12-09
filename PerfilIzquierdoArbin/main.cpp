#include <iostream>
#include <string>
#include "Arbin.h"
#include "Lista.h"
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

void perfilIzquierdoAux(Arbin<int> a, Lista<int>& l, int alt) { // alt = 1 la primera vez
    if (a.esVacio()) return; // si el árbo, está vacío, vuelvo

    if (l.longitud() < alt) l.pon_ppio(a.raiz()); // si la longitud de la lista es menor a mi altura (pq guarda 1 por altura), guardo mi raíz en la lista
    //Ej: si es la primera, longitud es 0 y altura 1, por tanto lo  mete.
    alt++; // aumento la altura para pasárelo a los de debajo mía

    perfilIzquierdoAux(a.hijoIz(), l, alt); // llamamos a la función para mi hijo izquierdo

    perfilIzquierdoAux(a.hijoDer(), l, alt); // llamamos a la función para mi hijo derecho
}

void perfilIzquierdo(Arbin<int> a) {
    Lista<int> l;
    perfilIzquierdoAux(a, l, 1);

    cout << "\n-------------------------------------------------------\n";
   
    if (l.esVacia()) {
        cout << "Nada";
    }
    else {

        while (!l.esVacia()) {
            cout << l.ultimo() << " ";
            l.quita_final();
        }
    }

    cout << "\n-------------------------------------------------------\n";
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        perfilIzquierdo(lee_arbol(cin));
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}