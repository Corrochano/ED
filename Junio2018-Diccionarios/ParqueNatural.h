/*
	Ejercicios resueltos de creacion de TADs

	Funcionan para todos los ejemplos dados en "ejemplos.in" y "ejemplos.out" o "leeme.txt", pero no
	garantizo que estén perfectos pues pueden fallar para algún caso extraño.

	Los comentarios explicando la complejidad podrían estar incompletos, pero deberían ser correctos
	al menos en la mayoría de las ocasiones.

	Autor: Álvaro Corrochano López
*/
#ifndef _PARQUE_NATURAL_H
#define _PARQUE_NATURAL_H

#include "DiccionarioHash.h"
#include "diccionario.h"
#include "pila.h"
#include "lista.h"
#include <string>
using namespace std;

/*
 Excepciones levantadas por las operaciones
*/
class EEcosistemaDuplicado {};

class EEcosistemaNoExiste {};

class ParqueNatural {
public:
	ParqueNatural();
	void an_ecosistema(const string& ecosistema);
	void an_ejemplares(const string& ecosistema, const string& especie, int n);
	Lista<string> lista_especies_ecosistema(const string& ecosistema, int n) const;
	int numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const;
	Lista<string> lista_especies_parque() const;
	int numero_ejemplares_en_parque(const string& especie) const;

private:
	DiccionarioHash<string, DiccionarioHash<string, int>> dicEcoNumEsp; //Ecosistema-Especies-numEjemeplares de esa especie
	DiccionarioHash<string, Lista<string>> dicUltEspecies; // Ecosistema-ListaDeEspecies
	DiccionarioHash<string, int> dicNumEsp; // especie/numEjemplares
	Diccionario<string, int> dicEspAlfa; // el int da igual, importante el string que es especies
};

#endif