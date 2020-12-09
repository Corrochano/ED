#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int tiempoAyudaAux(const Arbin<char>& a, int camino) {
	if (a.esVacio()) return 0;

	int ret = 0;

	if(a.raiz() == 'X') ret = camino * 2;

	int iz = tiempoAyudaAux(a.hijoIz(), camino + 1);
	int der = tiempoAyudaAux(a.hijoDer(), camino + 1);

	return ret + iz + der;
}

int tiempoAyuda(const Arbin<char>& falda) {
	return tiempoAyudaAux(falda, 0);
}

Arbin<char> leeArbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
  		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = leeArbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = leeArbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}

int main() {
	Arbin<char> falda;
	while (cin.peek() != EOF)  {
		cout << tiempoAyuda(leeArbol(cin)) << endl;
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}