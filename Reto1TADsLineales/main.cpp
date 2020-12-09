#include <iostream>
using namespace std;
#include "lista.h"


// EJERCICIO 20
// procedimiento genérico que muestra por pantalla una lista (asume elementos imprimibles)

template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin(); // iterador a la lista
	while (it != lista.cend()) { // mientras la lista no se haya recorrido entera
		cout << it.elem() << endl; // sacamos el elemento por pantalla
		it.next(); // avanzamos el iterador
	}
}


// EJERCICIO 21
// Implementa un subprograma que reciba una lista de enteros 
// y cuente cuántas posiciones hay en ella tales que el elemento que hay 
// en esa posición es igual a la suma de todos sus precedentes
int numPicos(const Lista<int>& l) {
	int ret = 0, sum = 0; // ret es lo que devolvemos y sum la suma que llevamos de momento
	typename Lista<int>::ConstIterator it = l.cbegin(); // iterador de la lista

	while (it != l.cend()) { // si no se ha terminado de recorrer la lista
		if (it.elem() == sum) { // si el elemento es igual a la suma de los elementos anteriores
			ret++; // a ret se le suma uno
		}
		sum += it.elem(); // se le suma a sum el elemento actual
		it.next(); // el iterador avanza
	}

	return ret; // devuelve el número de picos
}



// EJERCICIO 23
// función que duplica los elementos de una lista de enteros
// si la lista es [1,2,3] la transforma en [1,1,2,2,3,3] 
void repiteElementos(Lista<int>& lista) {
	typename Lista<int>:: Iterator it = lista.begin(); // iterador de la lista

	while (it != lista.end()) { // si no se ha terminado de recorrer la lista
		lista.insertar(it.elem(), it); // se inserta el elemento en el que está el iterador en su misma posición de la lista para duplicar
		it.next(); // el iterador avanza
	}

}


int main() {
	// listas para las pruebas
	Lista<int> listaVacia, lista1, lista2;

	for (int i = 1; i <= 5; i++)
		lista1.pon_final(i);

	for (int i = 1; i <= 5; i++)
		lista2.pon_ppio(i);

	Lista<int> listapicos;
	listapicos.pon_final(1);
	listapicos.pon_final(2);
	listapicos.pon_final(3);
	listapicos.pon_final(6);
	listapicos.pon_final(10);
	listapicos.pon_final(22);


	cout << "\n\n--- EJ 20: USO DE PROCEDIMIENTOS GENERICOS PARA MOSTRAR UNA LISTA ---\n";
	cout << "Lista vacia\n";
	pinta(listaVacia);
	cout << endl;
	cout << "Lista lista1\n";
	pinta(lista1);
	cout << endl;

	cout << "\n\n--- EJ 21: USO DE NUMPICOS PARA CONTAR EL NUMERO DE PICOS DE UNA LISTA ---\n";
	cout << "La lista vacia tiene " << numPicos(listaVacia) << " pico(s)\n";
	cout << "La lista \n";
	pinta(lista1);
	cout << "Tiene " << numPicos(lista1) << " pico(s)\n";
	cout << "La lista \n";
	pinta(lista2);
	cout << "Tiene " << numPicos(lista2) << " pico(s)\n";
	cout << "La lista \n";
	pinta(listapicos);
	cout << "Tiene " << numPicos(listapicos) << " pico(s)\n";
	cout << endl;


	cout << "\n\n--- EJ23: uso de REPITEELEMENTOS para DUPLICAR LOS ELEMENTOS DE lista ---\n";
	cout << "Cuando repito la lista vacia\n";
	pinta(listaVacia);
	cout << endl;
	cout << "Resulta\n";
	repiteElementos(listaVacia);
	pinta(listaVacia);
	cout << endl;
	cout << "Cuando repito la lista\n";
	pinta(lista1);
	cout << "Resulta\n";
	repiteElementos(lista1);
	pinta(lista1);
	cout << endl;


	system("PAUSE");
	return 0;
}