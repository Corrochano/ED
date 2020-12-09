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

// Funci�n auxiliar para hallar el di�metro del �rbol binario pasado por par�metro, invocada en diametro
int diametroAux(Arbin<int> a, int& diametro) { // devuelvo mi camino m�s grande, cont�ndome a m� mismo
    if (a.esVacio()) return 0; // si es vac�o, devuelvo 0

    if (esHoja(a)) { // si soy hoja
        if (1 > diametro) diametro = 1; // si 1 es mayor que di�metro (que empieza a 0) di�metro = 1
        return 1; // devuelvo 1
    }
    
   int iz = diametroAux(a.hijoIz(), diametro); // mi rama izquierda es igual a la funci�n con mi hijo izquierdo

   int der = diametroAux(a.hijoDer(), diametro); // mi rama derecha es igual a la funci�n con mi hijo derecho

   iz++; // aumento iz pq estoy yo
   der++; // aumento der pq estoy yo

   if (iz + der - 1 > diametro) diametro = iz + der - 1; // si iz + der - 1 (pq si no me cuento yo 2 veces) es mayor que di�metro, di�metro = iz + der -1

   return iz > der ? iz : der; // si iz > der, return iz, si no, return der

}

/** Devuelve el di�metro del �rbol binario pasado por par�metro, 
Complejidad: a = 2, b = 1, k = 0;
Por lo que Complejidad = O(2^n)
*/
int diametro(Arbin<int> a) { // return ret, ret = di�metro del �rbol
    int ret = 0;
    diametroAux(a, ret);

    return ret;
}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
       cout << diametro(lee_arbol(cin)) << endl;
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}