#include <iostream>

#include "lista.h"
#include "pila.h"

using namespace std;

/*
void invierte(Lista<char>& l, int i, int k) { // OJO fallo si se cambia el último elem.
	if (l.esVacia()) return;
	if (i + k > l.longitud()) k = l.longitud() - i;

	int total = i + k;
	Lista<char> aux;

	typename Lista<char>::Iterator it = l.begin();

	int j = 0;

	while (it != l.end()) {
		
		if ((i - 1 <= j && j < total - 1)) {
			aux.pon_ppio(it.elem());
			it = l.eliminar(it);
		}
		else if (j >= total - 1) {
			aux.pon_final(it.elem());
			it = l.eliminar(it);
		}
		else {
			it.next();
		}

		j++;
	}

	for (int j = 0; j < aux.longitud(); j++) {
		l.pon_final(aux.elem(j));
	}

	aux.~Lista();

}
*/

void invierte(Lista<char>& l, int i, int k) { // falla lo mismo que usando lista en vez de pila. 
	if (l.esVacia()) return;
	if (i + k > l.longitud()) k = l.longitud() - i;

	Pila<char> aux;

	typename Lista<char>::Iterator it = l.begin();

	int pos = 1;

	while (it != l.end() && k > 0) {

		if (pos < i) {
			pos++;
			it.next();
		}
		else {
			k--;
			aux.apila(it.elem());
			it = l.eliminar(it);
		}
	}

	while(!aux.esVacia()) {
		l.insertar(aux.cima(), it);
		aux.desapila();
	}

	aux.~Pila();

}


/*
void invierte(Lista<char> lista, int i, int k) { // Código Pablo
	Lista<char>::Iterator it = lista.begin();
	Lista<char> laux;
	if (lista.esVacia()) { return; }
	int pos = i + k - 2;
	int lauxi = 0;
	int e = 0;
	if (pos > lista.longitud()) {   //!!
		pos = lista.longitud();
	}
	for (int j = pos, e = i; e < lista.longitud(); j--, e++) {
		if (e < j) {
			laux.pon_final(it.elem());
			it.set(lista.elem(j));
		}
		if (e > j) {
			it.set(laux.elem(lauxi));
			lauxi++;
		}
		it.next();
	}
}
*/

void imprime(const Lista<char>& l) {
	typename Lista<char>::ConstIterator it = l.cbegin();

	while (it != l.cend()) {
		cout << it.elem();
		it.next();
	}

	cout << '\n';

}

int main() {

	int n, l, k;
	char aux, basura;
	Lista<char> lista;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> aux;
		while (aux != '0') {
			lista.pon_final(aux);
			cin >> aux;
		}

		//cin >> basura;
		cin >> l;
		cin >> k;
		
		invierte(lista, l, k);

		imprime(lista);

		lista.~Lista();

	}

	system("PAUSE");

	return 0;
}