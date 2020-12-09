#include <iostream>
#include "lista.h"

using namespace std;

int compañeros(Lista<int> l) {
	
	if (l.esVacia()) return 0; // Si está vacía, hay 0

	int ret = 0; // variable de retorno
	typename Lista<int>::Iterator it = l.begin(); // iterador de la lista
	typename Lista<int>::Iterator itSig = l.begin(); // iterador que va una posición por delante en la lista

	itSig.next(); // lo ponemos por delante

	while (itSig != l.end() && !l.esVacia()) { // Si la lista no se queda vacía y mientras no llegue al final
		if (it.elem() == itSig.elem()) { // si son iguales
			l.eliminar(it); // elimino uno de la lista
			l.eliminar(itSig); // elimino el otro de la lista

			it = l.begin(); // nos volvemos a poner al principio
			itSig = l.begin(); // ponemos este al principio también
			ret++; // aumentamos en 1 la variable de retorno

			if (itSig != l.end()) { // si el siguiente no es ya el final
				itSig.next(); // lo ponemos delante nuestra
			}

		}
		else { // si nos iguales
			it.next(); // avanzo
			itSig.next(); // avanza el siguiente a mí
		}
	}

	return ret; // retornamos la variable de retorno

}



int main() {
	int n, aux;
	Lista<int> lista;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> aux;
		while (aux != -1) {
			lista.pon_final(aux);
			cin >> aux;
		}

		cout << compañeros(lista) << '\n';
		lista.~Lista(); // eliminamos la lista para que no se acumulen
	}

	system("PAUSE");
	return 0;
}