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
int caminoParesAux(Arbin<int> a, int& camino_largo) { // devuelvo mi camino de pares más grande, contándome a mí mismo si soy par
    if (a.esVacio()) return 0; // si el árbol es vacío, return 0

    int local; // si cuento o no

    if (a.raiz() % 2 != 0) local = 0; // si soy impar, no cuento
    else local = 1; // pero si soy par, sí

    if (esHoja(a)) { // si soy hoja
        if (local > camino_largo) camino_largo = local; // si cuento y soy mayor que el camino largo actual, se actualiza el caminoLargo actual
        return local; // retorno si cuento o no
    }

    int iz = caminoParesAux(a.hijoIz(), camino_largo); // compruebo el camino de mi lado izquierdo
    int der = caminoParesAux(a.hijoDer(), camino_largo); // compruebo el camino de mi lado derecho

    iz += local; // me sumo a mi lado izquierdo si cuento
    der += local; // me sumo a mi lado derecho si cuento
    
    if (a.raiz() % 2 == 0) { // si soy par
        if (iz + der - local > camino_largo) camino_largo = iz + der - local; // si mi camino iz + mi camino der - yo si cuento es mayor que el caminoLargo, este se actualiza
        return iz > der ? iz : der; // si iz > der return iz, si no, return der
    }
    else { // si soy impar
       if (iz > camino_largo) camino_largo = iz; // si iz mayor que camino_largo, camino_largo = iz
       if (der > camino_largo) camino_largo = der; // si der mayor que camino_largo, camino_largo = der
       return 0; // retorno 0 pq soy impar
    }
    
}

/** Devuelve el camino de pares más largo del árbol binario pasado por parámetro, 
Complejidad: a = 2 , b = 1, k = 0;
Por lo que Complejidad = O(2^n)
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