// �lvaro Corrochano L�pez
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

/** Funci�n auxuliar que calcula el n�mero de nodos adivinos que hay en un �rbol, retorn�ndolo en el par�metro ret
* @param a el �rbol del que calcular el n�mero de adivinos
* @param ret el n�mero de adivinos que hay en el �rbol, debe empezar inicializado a 0
* return devuelve el n�mero de pares que hay debajo de un nodo m�s uno m�s si su ra�z es par
*/
unsigned int adivinos(const Arbin<int>& a, unsigned int& ret) {
	if (a.esVacio()) return 0; //  si el �rbol est� vac�o, return 0

	int iz = adivinos(a.hijoIz(), ret); // me guardo los pares que tengo por debajo de mi hijo izquierdo y llamo a la funci�n con �l como par�metro
	int der = adivinos(a.hijoDer(), ret); // me guardo los pares que tengo por debajo de mi hijo derecho y llamo a la funci�n con �l como par�metro

	if (iz + der == a.raiz()) ret++; // si los pares que tengo debajo son iguales a mi ra�z, soy adivino
	
	return a.raiz() % 2 == 0 ? iz + der + 1 : iz + der; // retorno los pares que tengo por debajo m�a m�s uno m�s si soy par y si soy impar, los pares que tengo debajo m�as
}

/** Indica aqu�, razonadamente, la complejidad de numero_adivinos
	Complejidad lineal, O(n) ya que tan solo se "visita" una vez cada nodo del �rbol.
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
