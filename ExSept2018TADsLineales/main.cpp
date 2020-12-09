#include "lista.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
IMPORTANTE: 
EN ESTE EJERCICIO DEBE USARSE EL ARCHIVO LISTA.H PROPORCIONADO JUNTO A ESTE ARCHIVO,
DADO QUE ESTE MAIN.CPP EMPLEA DOS OPERACIONES DEL TAD LISTA (imprime E imprime_inv) QUE SOLAMENTE SE ENCUENTRAN 
INCLUIDAS EN DICHO LISTA.H
*/

/**
Este programa lee por la entrada estándar líneas que contienen secuencias de enteros.
Dichos enteros son los elementos de una lista, la cual después se invierte y se imprime
en ambos sentidos

Formato de la entrada
==================================
Cada línea contiene la lista de enteros sobre la que operar 
(en caso de lista vacía, la línea estará vacía)

Formato de la salida
=================================
Para cada línea de entrada de la forma 
X0 X1 X2 ... Xn
se genera como salida una línea de la forma
Y0 Y1 Y2 ... Yn #Z0 Z1 Z2 ... Zn
donde:
 (1) Y0 Y1 Y2 ... Yn es el resultado de aplicar la 
     operación 'invertir' sobre la lista X0 X1 X2 ... Xn
 (2) Z0 Z1 Z2 ... Zn es Y0 Y1 Y2 ... Yn escrita al revés 
     (es decir, Z0 = Yn, Z1 = Yn-1 .... Zn = Y0) 	 


Ejemplo de entrada:
1
1 2
1 2 3
1 2 3 4

Salida producida: 
1
1 #1
1 2
2 1 #1 2
1 2 3
3 2 1 #1 2 3
1 2 3 4
4 3 2 1 #1 2 3 4
**/


int main() {
  string linea;
  while (!cin.eof()) {
	  getline(cin, linea);
	  stringstream slinea(linea);
	  int valor;
	  Lista<int> lista;
	  while (slinea >> valor) {
		  lista.pon_final(valor);
	  }
	  lista.invertir();
	  lista.imprime();
	  cout << "#";
	  lista.imprime_inv();
	  cout << endl;
  }
}
