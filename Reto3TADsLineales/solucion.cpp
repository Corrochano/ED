#include <iostream>
using namespace std;
#include "lista.h"

// procedimiento genérico que muestra por pantalla una lista (asume elementos imprimibles)
template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin();
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}


int main() {
	Lista<int> lista;
	Lista<int> listaVacia;
	
	listaVacia.insertarPorPosicion(100, 0);
	cout << "Al insertar el 100 en una lista vacia resulta la lista\n";
	pinta(listaVacia);

	for (int i = 1; i <= 10; i++)
		lista.pon_final(i);
	cout << "\nEn la lista con los valores del 1 al 10...\n";
	pinta(lista);

	for (int i = lista.longitud(); i >= 0; i--) 
		lista.insertarPorPosicion(100, i);

	cout << "Insertamos el 100 por el principio, por el final y entre medias de todos los elementos y resulta...\n";
	pinta(lista);
	   	

	system("pause");
	return 0;
}