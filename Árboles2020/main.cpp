// Álvaro Corrochano López
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

/** Función auxuliar que calcula el número de nodos adivinos que hay en un árbol, retornándolo en el parámetro ret
* @param a el árbol del que calcular el número de adivinos
* @param ret el número de adivinos que hay en el árbol, debe empezar inicializado a 0
* return devuelve el número de pares que hay debajo de un nodo más uno más si su raíz es par
*/
unsigned int adivinos(const Arbin<int>& a, unsigned int& ret) {
	if (a.esVacio()) return 0; //  si el árbol está vacío, return 0

	int iz = adivinos(a.hijoIz(), ret); // me guardo los pares que tengo por debajo de mi hijo izquierdo y llamo a la función con él como parámetro
	int der = adivinos(a.hijoDer(), ret); // me guardo los pares que tengo por debajo de mi hijo derecho y llamo a la función con él como parámetro

	if (iz + der == a.raiz()) ret++; // si los pares que tengo debajo son iguales a mi raíz, soy adivino
	
	return a.raiz() % 2 == 0 ? iz + der + 1 : iz + der; // retorno los pares que tengo por debajo mía más uno más si soy par y si soy impar, los pares que tengo debajo mías
}

/** Indica aquí, razonadamente, la complejidad de numero_adivinos
	Complejidad lineal, O(n) ya que tan solo se "visita" una vez cada nodo del árbol.
*/
unsigned int numero_adivinos(const Arbin<int>& a) {
	unsigned int ret = 0;

	adivinos(a, ret);

	return ret;
}

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		cout << numero_adivinos(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
