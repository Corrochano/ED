#include <iostream>
#include "lista.h"

using namespace std;


void imprimir(const Lista<int>& lista) {
	typename Lista<int>::ConstIterator it = lista.cbegin();

	while (it != lista.cend()) {
		cout << it.elem();
		it.next();
	}

	//cout << '\n';

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

		lista.reordenar();
		imprimir(lista);
		lista.imprime_inv();

		lista.~Lista(); // eliminamos la lista para que no se acumulen
	}
	system("PAUSE");
	return 0;
}