/**
Este programa lee árboles de la entrada estándar, 
codificados de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada árbol leído, escribe en la salida estándar
el número de nodos singulares de dicho árbol.
	
Algunos casos representativos:

#
[0]
[5]
(([4]3[-3])1[-4])

-El primero representa el árbol vacío. Al no tener nodos,
un árbol vacío tiene 0 nodos sigulares.
-El segundo representa un árbol con un único nodo, cuyo valor
es 0. Dicho nodo es singular, ya que: (i) como no tiene 
ascestros, la suma de los ancestros es 0, (ii) como no
tiene descendientes, la suma de los descendientes es 0. 
-El tercero representa otro árbol con un único nodo, cuyo
valor es 5. Por la misma razón que en el segundo ejemplo,
este nodo es singular.
-El cuarto representa el siguiente árbol:
     
	       1
		  /  \
		  3  -4
         / \  
        4  -3 

Este árbol tiene 2 nodos sigulares: la raíz, y la raíz del hijo 
izquierdo. 

Por tanto, la salida del programa para estos casos será:

0
1
1
2

Algunos casos de prueba más:

ENTRADAS
(((#-2[-2])0#)0[-1])
(#-1[0])
([2]1[2])
(#-2(((#0([2]0(((((#1#)0(#0#))0(#-1[-2]))0(((#0#)2#)0[2]))0#)))2#)-1#))
((((#0[1])1#)1((#2(([-2]1#)1([2]1#)))0#))0(#0(#2[-1])))

SALIDAS ASOCIADAS
1
1
0
0
1



*/
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool esHoja(const Arbin<int>& a) {
	return (!a.esVacio() && (a.hijoDer().esVacio() && a.hijoIz().esVacio()));
}

int numSingulares(const Arbin<int> a, int& sing, int antepasados) { // return la suma de las raíces del árbol y sus hijos
	if (a.esVacio()) return 0; // si es vacío, devuelve 0

	if (esHoja(a)) { // si soy hoja
		if (antepasados == 0) sing++; // si mis antepasados suman 0, soy singular
		return a.raiz(); // devuelvo mi raíz
	}

	int iz = numSingulares(a.hijoIz(), sing, antepasados + a.raiz()); // miro mi hijo izquierdo y me guardo las raíces que hay en él
	int der = numSingulares(a.hijoDer(), sing, antepasados + a.raiz()); // miro mi hijo derecho y me guardo las raíces que hay en él

	if (iz + der == antepasados) sing++; // si la suma de mis hijos es igual a la de mis antepasados, soy singular

	return iz + der + a.raiz(); // devuelvo la suma de las raíces de mis hijos + mi raíz
}

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
*/
unsigned int numero_singulares(const Arbin<int>& a) {
	int ret = 0;

	numSingulares(a, ret, 0);

	return ret;
}


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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		cout << numero_singulares(lee_arbol(cin)) << endl;
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
