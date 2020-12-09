/*
	Ejercicios resueltos de creacion de TADs

	Funcionan para todos los ejemplos dados en "ejemplos.in" y "ejemplos.out" o "leeme.txt", pero no
	garantizo que estén perfectos pues pueden fallar para algún caso extraño.

	Los comentarios explicando la complejidad podrían estar incompletos, pero deberían ser correctos
	al menos en la mayoría de las ocasiones.

	Autor: Álvaro Corrochano López
*/
#ifndef __SURTIDORES_H
#define __SURTIDORES_H

#include "DiccionarioHash.h"
#include "lista.h"
#include <string>
using namespace std;

typedef string tVehiculo;
typedef string tSurtidor;
typedef string tTipoCombustible;

/* Excepciones */
class ESurtidorDuplicado {};
class ESurtidorNoExiste {};
class ELlegadaVehiculo {};
class EErrorVenta {};

/* Clase para representar los objetos devueltos
   por la operación 'vende' */
class ResulVenta {
public:
	tVehiculo _vehiculo;
	unsigned int _litros_que_quedan;
	ResulVenta(tVehiculo vehiculo, unsigned int litros_que_quedan) {
		_vehiculo = vehiculo;
		_litros_que_quedan = litros_que_quedan;
	}
};

class GestorSurtidores {
public:
	GestorSurtidores();
	void an_surtidor(const tSurtidor& surtidor);
	void carga(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros);
	void pon_en_espera(const tVehiculo& vehiculo, const tSurtidor& surtidor);
	ResulVenta vende(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros);
	void abandona(const tVehiculo& vehiculo);
private:
	DiccionarioHash<tSurtidor, DiccionarioHash<tTipoCombustible, unsigned int>> dicSurtidor;
	DiccionarioHash<tVehiculo, Lista<tVehiculo>::Iterator> dicIt;
	DiccionarioHash<tSurtidor, Lista<tVehiculo>> dicListasV;
	DiccionarioHash<tVehiculo, tSurtidor> dicVaS;
};

#endif