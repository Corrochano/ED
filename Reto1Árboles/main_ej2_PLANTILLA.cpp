#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "lista.h"
using namespace std;

// subprograma genérico para visualizar una lista por pantalla
template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin();
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}


/**
SUBPROGRAMA PARA CONSTRUIR UN ARBOL DE ENTEROS A PARTIR DE SU REPRESENTACIÓN EN UNA LÍNEA DEL ARCHIVO DE ENTRADA
Los árboles se representan de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con
	v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
	con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.

Ejemplos:
#  --> arbol vacío
[1] --> arbol hoja
([1]2[3])  --> arbol con raiz 2, hijo derecho 3 e hijo izdo 1
([1]2([3]4#)) --> arbol con raiz 2, hijo derecho (raíz = 4; sin hijo derecho; hijo izdo 3) e hijo izdo 1
*/
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



// numNodos: devuelve el numero de nodos del arbol.
int numNodos(const Arbin<int>& a) {
	if (a.esVacio())return 0;
	return numNodos(a.hijoDer()) + numNodos(a.hijoIz()) + 1;
}

// esHoja: devuelve cierto si el arbol es una hoja (los hijos izquierdo y derecho son vacios).
bool esHoja(const Arbin<int>& a) {
	return !a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

// numHojas: devuelve el numero de hojas del arbol.
int numHojas(const Arbin<int>& a) {
	if (a.esVacio()) return 0;
	if (esHoja(a)) return 1;

	return numHojas(a.hijoDer()) + numHojas(a.hijoIz());
}

//talla: devuelve la talla del arbol.
int talla(const Arbin<int>& a) {
	if (a.esVacio()) return 0;

	int tallaIz = talla(a.hijoIz());
	int tallaDer = talla(a.hijoDer());

	return 1 + (tallaDer > tallaIz ? tallaDer : tallaIz);
}

//frontera: devuelve una lista con todas las hojas del arbol de izquierda a derecha.
Lista<int> frontera(const Arbin<int>& a) {
	Lista<int> ret;

	if (a.esVacio()) return ret;
	
	if (esHoja(a)) {
		ret.pon_final(a.raiz());
		return ret;
	}

	Lista<int> iz = frontera(a.hijoIz());

	while (!iz.esVacia()) {
		ret.pon_final(iz.primero());
		iz.quita_ppio();
	}

	Lista<int> der = frontera(a.hijoDer());

	while (!der.esVacia()) {
		ret.pon_final(der.primero());
		der.quita_ppio();
	}
	
	return ret;
}


//espejo: devuelve un arbol nuevo que es la imagen especular del recibido
Arbin<int> espejo(const Arbin<int>& a) {
	if (a.esVacio()) return a; 

	//Arbin<int> ret = Arbin<int>(a.raiz()); // Esto no funciona pq no tiene hijoDer ni hijoIz
	//
	//ret.hijoDer() = espejo(a.hijoIz());

	//ret.hijoIz() = espejo(a.hijoDer());

	//return ret;

	return Arbin<int>(espejo(a.hijoDer()), a.raiz(), espejo(a.hijoIz()));
}


//minElem: devuelve el elemento mas pequeño de todos los almacenados en el arbol. 
//Es un error ejecutar esta operacion sobre un arbol vacio.
int minElem(const Arbin<int>& a) {
	//if (a.esVacio()) throw EArbolVacio();
	//
	//if (esHoja(a)) return a.raiz();

	//int ret;

	//int iz = minElem(a.hijoIz());
	//int der = minElem(a.hijoDer());

	//iz < der ? ret = iz : ret = der;
	//
	//return ret < a.raiz() ? ret : a.raiz();
	
	if (!a.esVacio()) {
		if (esHoja(a)) {
			return a.raiz();
		}
		else if (a.hijoDer().esVacio()) {
			int minz = minElem(a.hijoIz());
			if (minz < a.raiz()) return minz;
			return a.raiz();
		}
		else if (a.hijoIz().esVacio()) {
			int mind = minElem(a.hijoDer());
			if (mind < a.raiz()) return mind;
			return a.raiz();
		}
		else {
			int mind = minElem(a.hijoDer());
			int minz = minElem(a.hijoIz());
			if (mind < minz) {
				minz = mind;
			}
			if (a.raiz() < minz) {
				return a.raiz();
			}
			return minz;
		}
	}
	throw EArbolVacio();
}



void prueba2(Arbin<int> a) {

	cout << "------------------------" << endl;

	cout << a;
	cout << endl;

	cout << "numNodos:" << numNodos(a) << endl;

	cout << "esHoja:";
	if (esHoja(a))
		cout << " si\n";
	else
		cout << " no\n";

	cout << "numHojas:" << numHojas(a)  << endl;
	cout << "talla:" << talla(a) << endl;

	cout << "frontera:\n";
	pinta(frontera(a));

	cout << "arbol:\n";
	cout << a;
	
	Arbin<int> es = espejo(a);
	cout << "espejo:\n" ;
	cout << es << endl;
	
	if (!a.esVacio()) {
		try {
			cout << "minElem: " << minElem(a) << endl;
		}
		catch (EArbolVacio) {
			cout << "arbol vacio en alguna parte de este arbol\n";
		}
	}
	else
		cout << "No se puede obtener el minElem de un arbol vacio" << endl;

	cout << "------------------------" << endl;
}



int main() {
	Arbin<int> arbol;
	ifstream archivo;

	archivo.open("in.txt");
	while (archivo.peek() != EOF)  {
		Arbin<int> a = lee_arbol(archivo);
		prueba2(a);
		string resto_linea;
		getline(archivo, resto_linea);
	}
	archivo.close();
	return 0;
}
