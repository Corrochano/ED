/*
	Ejercicios resueltos de creacion de TADs

	Funcionan para todos los ejemplos dados en "ejemplos.in" y "ejemplos.out" o "leeme.txt", pero no
	garantizo que estén perfectos pues pueden fallar para algún caso extraño.

	Los comentarios explicando la complejidad podrían estar incompletos, pero deberían ser correctos
	al menos en la mayoría de las ocasiones.

	Autor: Álvaro Corrochano López
*/
#include "GestorSurtidores.h"

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación

Constante pues no hace nada.
*/
GestorSurtidores::GestorSurtidores() {
	// nada
}

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación

Constante porque usamos un mapa hash para buscar e insertar.
*/
void GestorSurtidores::an_surtidor(const tSurtidor& surtidor) {
	if (dicSurtidor.contiene(surtidor)) throw ESurtidorDuplicado();

	dicSurtidor.inserta(surtidor, DiccionarioHash<tTipoCombustible, unsigned int>());
	dicListasV.inserta(surtidor, Lista<tVehiculo>());
}

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación

Constante porque solo manejamos diccionarios hash para búsquedas e inserciones.
*/
void GestorSurtidores::carga(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros) {
	DiccionarioHash<tSurtidor, DiccionarioHash<tTipoCombustible, unsigned int>>::Iterator it = dicSurtidor.busca(surtidor);
	if (it == dicSurtidor.end()) throw ESurtidorNoExiste();

	DiccionarioHash<tTipoCombustible, unsigned int>::Iterator it2 = it.valor().busca(tipo_combustible);
	if (it2 == it.valor().end()) {
		it.valor().inserta(tipo_combustible, litros);
	}
	else {
		it.valor().inserta(tipo_combustible, it2.valor() + litros);
	}
}

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación

Constante porque solo usamos diccionarios hash para buscar e insertar aparte de introducir un elemento en una lista
por un extremo.
*/
void GestorSurtidores::pon_en_espera(const tVehiculo& vehiculo, const tSurtidor& surtidor) {
	if (!dicSurtidor.contiene(surtidor) || dicIt.contiene(vehiculo)) throw ELlegadaVehiculo();

	dicListasV.busca(surtidor).valor().pon_ppio(vehiculo);
	dicIt.inserta(vehiculo, dicListasV.busca(surtidor).valor().begin());
	dicVaS.inserta(vehiculo, surtidor);
}

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación

Constante porque las búsquedas y los borrados de elementos son en diccionarios hash o por los extremos de una lista.
*/
ResulVenta GestorSurtidores::vende(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros) {
	if (!dicSurtidor.contiene(surtidor) || dicListasV.busca(surtidor).valor().esVacia() || 
		!dicSurtidor.busca(surtidor).valor().contiene(tipo_combustible) || litros > dicSurtidor.busca(surtidor).valor().busca(tipo_combustible).valor() ||
		litros <= 0) throw EErrorVenta();

	DiccionarioHash<tSurtidor, DiccionarioHash<tTipoCombustible, unsigned int>>::Iterator it = dicSurtidor.busca(surtidor);
	DiccionarioHash<tTipoCombustible, unsigned int>::Iterator it2 = it.valor().busca(tipo_combustible);

	int rest = it2.valor() - litros;
	it.valor().inserta(tipo_combustible, rest);

	tVehiculo v = dicListasV.busca(surtidor).valor().ultimo();

	abandona(v);

	return ResulVenta(v, rest);
}

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación

Constante porque buscamos y eliminamos en un diccionario hash y al eliminar el vehículo
de su cola lo hacemos usando su iterador.
*/
void GestorSurtidores::abandona(const tVehiculo& vehiculo) {
	DiccionarioHash<tVehiculo, Lista<tVehiculo>::Iterator>::Iterator it = dicIt.busca(vehiculo);
	if (it == dicIt.end()) return;
	DiccionarioHash<tVehiculo, tSurtidor>::Iterator it2 = dicVaS.busca(vehiculo);
	
	dicListasV.busca(it2.valor()).valor().eliminar(it.valor());
	dicIt.borra(vehiculo);
	dicVaS.borra(vehiculo);
}