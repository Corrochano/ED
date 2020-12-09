// Álvaro Corrochano López
#include "lista.h"
#include <iostream>
using namespace std;

bool lee_lista(Lista<int>& lista) {
	int n_elems;
	cin >> n_elems;
	if (n_elems >= 0) {
		while (n_elems-- != 0) {
			int elem;
			cin >> elem;
			lista.pon_final(elem);
		}
		return true;
	}
	else {
		return false;
	}
}

bool ejecuta_caso() {
  Lista<int> lista;
  unsigned int k;
  if (lee_lista(lista)) { 
	  cin >> k;
	  Lista<int> destino;
	  lista.cortaPorK(k, destino);
	  lista.imprime2();
	  cout << "#";
	  lista.imprime_inv2();
	  cout << endl;
	  destino.imprime1();
	  cout << "#";
	  destino.imprime_inv1();
	  cout << endl;
	  return true;
  }
  else {
	return false;  
  }  
}

int main() {
	while (ejecuta_caso()); 
	return 0;
}