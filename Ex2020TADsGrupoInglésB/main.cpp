#include <iostream>

#include "lista.h"

using namespace std;

int fuerzasArmadas(Lista<int> l) {

	if (l.esVacia()) return 0; // Si es vacía, devuelvo 0

	typename Lista<int>::ConstIterator it = l.cbegin(); // iterador de la lista desde el inicio hasta el 7
	typename Lista<int>::ConstIterator it7 = l.cbegin(); // iterador de la lista después del 7 hasta el final
	bool tengo7 = false; // para saber si tengo el 7 ya
	int ret = 0; // variable de retorno

	while (it7 != l.cend() && ret != -1 && it.elem() != 7) { // si no ha llegado el del 7 al final y ret no es -1 y no ha llegado al 7 el primero
		
		if (!tengo7) { // si no tengo el 7
			if (it7.elem() == 7) { // si he llegado al 7
				tengo7 = true; // ahora tengo el 7
			}

			it7.next(); // avanzo el iterador del 7
		}
		else { // si tengo el 7
			
			if (it.elem() == it7.elem()) { // si tengo lo mismo en ambos iteradores
				ret++; // aumento la variable de retorno
			}
			else { // si no tienen lo mismo
				ret = -1; // devuelvo -1
			}

			it.next(); // aumento el iterador
			it7.next(); // aumento el iterador del 7
		}

	}

	if (it7 != l.cend()) return -1; // si el iterador el 7 no ha llegado al final, devuelvo -1
	if (it.elem() != 7) return -1; // si el iterador no ha llegado al 7, devuelvo -1

	return ret; // devuelvo la variable de retorno

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

		cout << fuerzasArmadas(lista) << '\n';
		
		lista.~Lista(); // eliminamos la lista para que no se acumulen
	}

	system("PAUSE");
	return 0;
}