#include <iostream>
#include "lista.h"

using namespace std;

int main() {
	int n, aux;
	Lista<int> lista;

	cin >> n;

	while (n != -1) {

		for (int i = 0; i < n; i++) {
			cin >> aux;
			lista.pon_final(aux);
		}

		lista.transposicion();
		lista.imprime();
		lista.imprime_inv();
		
		lista.~Lista(); // eliminamos la lista para que no se acumulen
		cin >> n;
	}

	system("PAUSE");
	return 0;
}