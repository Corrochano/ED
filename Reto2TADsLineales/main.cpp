#include <iostream>
using namespace std;
#include "lista.h"


// EJERCICIO 20
// procedimiento genérico que muestra por pantalla una lista (asume elementos imprimibles)

template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin();
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}



// EJERCICIO 24
// subprograma que reciba dos listas de enteros ordenados crecientemente 
// y devuelva una nueva lista ordenada con la unión de los enteros de las 
// dos listas iniciales
Lista<int> mezclar(const Lista<int>& l1, const Lista<int>& l2) {
	Lista<int> ret; // Lista que devuelvo
	typename Lista<int>::ConstIterator it1 = l1.cbegin(); // iterador de lista 1
	typename Lista<int>::ConstIterator it2 = l2.cbegin(); // iterador de lista 2

	while (it1 != l1.cend() || it2 != l2.cend()) { // si aguno no ha terminado aún
		if (it1 != l1.cend()) { // si lista 1 no ha terminado
			if (it2 != l2.cend()) { // si lista 2 tampoco ha terminado
				if (it1.elem() <= it2.elem()) { // si el elemento de lista 1 es menor o igual que el de lista 2
					ret.pon_final(it1.elem()); // pon al final el elemento de lista 1
					it1.next(); // y avanza el iterador de lista 1
				}
				else { // si es menor el de lista 2
					ret.pon_final(it2.elem()); // pon al final el elemento de lista 2
					it2.next(); // y avanza el iterador de lista 2
				}
			}
			else { // si lista 2 a terminado
				ret.pon_final(it1.elem()); // pon al final el elemento de lista 1
				it1.next(); // y avanza el iterador de lista 1
			}
		}
		else { // si lista 1 ha terminado, solo queda lista 2
			ret.pon_final(it2.elem()); // pon al final el elemento de lista 2
			it2.next(); // y avanza el iterador de lista 2
		}
	}

	return ret; // return la lista de retorno
}


// EJERCICIO 25
// subprograma que elimina los números pares de una lista de enteros
void quitaPares(Lista<int>& lista) {
	
	if (lista.esVacia()) return; // Si la lista está vacía, vuelve

	typename Lista<int>::Iterator it = lista.begin(); // iterador a la lista
	typename Lista<int>::Iterator aux = lista.begin(); // iterador que apunta al siguiente al iterador a la lista

	aux.next(); // avanzo el aux para que apunte al siguiente

	while (it != lista.end()) { // mientras la lista no se haya recorrido entera

		if (it.elem() % 2 == 0) { // si el número es par
			
			lista.eliminar(it); // lo elimina de lista
			
			it = aux; // igual it a aux que es su siguiente pq si no se pierde, así que avanzo it a su siguiente
			
			if (aux != lista.end()) { // si aux no ha llegado al final
				aux.next(); // avanzo aux
			}
		
		}
		else { // si no es par
			
			it.next(); // avanzo it
			
			if (aux != lista.end()) {// y si aux no ha llegado al final
				aux.next(); // avanzo aux
			}

		}
	}
}

int main() {

	// listas para las pruebas
	Lista<int> listaVacia, lista1, lista2, lo1, lo2;

	for (int i = 1; i <= 6; i++)
		for (int repeticiones = 1; repeticiones <= 2; repeticiones++)
			lista1.pon_final(i);

	for (int i = 2; i <= 6; i = i + 2)
		lista2.pon_ppio(i);

	for (int i = 1; i < 10; i = i + 2)
		lo1.pon_final(i);

	for (int i = 0; i <= 10; i = i + 2)
		lo2.pon_final(i);



	cout << "\n\n--- EJ24: uso de MEZCLAR para MEZCLAR DOS LISTAS ORDENADAS ---\n";

	cout << "Cuando mezclo dos listas vacias resulta\n";
	pinta(mezclar(listaVacia, listaVacia));
	cout << endl;

	cout << "Cuando mezclo la lista vacia con \n";
	pinta(lo1);
	cout << "Resulta\n";
	pinta(mezclar(listaVacia, lo1));

	cout << "Cuando mezclo\n";
	pinta(lo1);
	cout << "con la lista vacia resulta\n";
	pinta(mezclar(lo1, listaVacia));

	cout << "Cuando mezclo\n";
	pinta(lo1);
	cout << "con\n";
	pinta(lo2);
	cout << "Resulta\n";
	pinta(mezclar(lo1, lo2));

	cout << "Cuando mezclo\n";
	pinta(lo2);
	cout << "con\n";
	pinta(lo1);
	cout << "Resulta\n";
	pinta(mezclar(lo2, lo1));



	cout << "\n\n--- EJ25: uso de ELIMINAR para ELIMINAR LOS PARES DE lista ---\n";

	cout << "Cuando elimino los numeros pares de la lista vacia resulta\n";
	quitaPares(listaVacia);
	pinta(listaVacia);
	cout << endl;

	cout << "Cuando elimino los numeros pares de la lista\n";
	pinta(lista1);
	cout << "Resulta\n";
	quitaPares(lista1);
	pinta(lista1);
	cout << endl;

	cout << "Cuando elimino los numeros pares de la lista\n";
	pinta(lista2);
	cout << "Resulta\n";
	quitaPares(lista2);
	pinta(lista2);
	cout << endl;



	system("PAUSE");
	return 0;
}