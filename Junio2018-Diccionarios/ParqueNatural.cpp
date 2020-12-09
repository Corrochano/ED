/*
	Ejercicios resueltos de creacion de TADs

	Funcionan para todos los ejemplos dados en "ejemplos.in" y "ejemplos.out" o "leeme.txt", pero no
	garantizo que estén perfectos pues pueden fallar para algún caso extraño.

	Los comentarios explicando la complejidad podrían estar incompletos, pero deberían ser correctos
	al menos en la mayoría de las ocasiones.

	Autor: Álvaro Corrochano López
*/
#include "ParqueNatural.h"

/*
  COMPLEJIDAD
	Constante porque no hace nada.
*/
ParqueNatural::ParqueNatural() {
	// no se hace nada
}

/*
  COMPLEJIDAD
	mapa_ecosistemas es un mapa hash, así que la búsqueda tiene coste
	constante al igual que la inserción de un nuevo elemento.
*/
void ParqueNatural::an_ecosistema(const string& ecosistema) {
	if (dicEcoNumEsp.contiene(ecosistema)) throw EEcosistemaDuplicado();

	dicEcoNumEsp.inserta(ecosistema, DiccionarioHash<string, int>());
	dicUltEspecies.inserta(ecosistema, Lista<string>());
}

/*
  COMPLEJIDAD
	- Viendo las complejidades de las 2 funciones a las que se llaman, el coste será constante a menos que introduzcamos una nueva
	especie en el parque (no en un ecosistema), en cuyo caso será logarítmico en el diccionario alfabético.
*/
void ParqueNatural::an_ejemplares(const string & ecosistema, const string & especie, int n) {
	DiccionarioHash<string, DiccionarioHash<string, int>>::Iterator it = dicEcoNumEsp.busca(ecosistema);
	if (it == dicEcoNumEsp.end()) throw EEcosistemaNoExiste();
	DiccionarioHash<string, int>::Iterator it2 = it.valor().busca(especie);
	
	if (it2 == it.valor().end()) { // Si la especie no está
		it.valor().inserta(especie, n);
		dicEspAlfa.inserta(especie, 0);
		dicUltEspecies.busca(ecosistema).valor().pon_ppio(especie);
	}
	else { // si sí está
		it.valor().inserta(especie, n + it2.valor());
	}

	DiccionarioHash<string, int>::Iterator it3 = dicNumEsp.busca(especie);
	if (it3 == dicNumEsp.end()) {
		dicNumEsp.inserta(especie, n);
	}
	else {
		dicNumEsp.inserta(especie, n + dicNumEsp.busca(especie).valor());
	}
}



/*
  COMPLEJIDAD
	- Constante si no existe el ecosistema, o si n es menor que 0.
	- Si no, lineal en el valor del parámetro n. Si n fuera mayor que el numero de especies de un ecosistema el coste pasa a
	ser lineal en el número de especies.
*/
Lista<string> ParqueNatural::lista_especies_ecosistema(const string& ecosistema, int n) const {
	DiccionarioHash<string, Lista<string>>::ConstIterator it = dicUltEspecies.cbusca(ecosistema);
	if (it == dicUltEspecies.cend()) throw EEcosistemaNoExiste();
	Lista<string> ret = Lista<string>();
	Lista<string>::ConstIterator it2 = it.valor().cbegin();
	

	for (int i = 0; i < n && it2!= it.valor().cend(); i++) {
		ret.pon_final(it2.elem());
		it2.next();
	}

	return ret;
}

/*
  COMPLEJIDAD
	- Constante porque hacemos búsquedas en diccionarios hash.
*/
int ParqueNatural::numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const {
	DiccionarioHash<string, DiccionarioHash<string, int>>::ConstIterator it = dicEcoNumEsp.cbusca(ecosistema);
	if (it == dicEcoNumEsp.cend()) throw EEcosistemaNoExiste();

	DiccionarioHash<string, int>::ConstIterator it2 = it.valor().cbusca(especie);

	if (it2 == it.valor().cend()) { // Si la especie no está
		return 0;
	}
	else { // si sí está
		return it2.valor();
	}

}

/*
  COMPLEJIDAD
   - Lineal en el número de especies del parque ya que recorremos una estructura arbórea para construir la lista.
*/
Lista<string> ParqueNatural::lista_especies_parque() const {
	Lista<string> ret = Lista<string>();
	Diccionario<string, int>::ConstIterator it = dicEspAlfa.cbegin();

	while (it != dicEspAlfa.cend()) {
		ret.pon_final(it.clave());
		it.next();
	}

	return ret;
}

/*
  COMPLEJIDAD
	- Constante porque hacemos búsquedas en una tabla hash.
*/
int ParqueNatural::numero_ejemplares_en_parque(const string& especie) const {
	return dicNumEsp.contiene(especie) ? dicNumEsp.cbusca(especie).valor() : 0;
}