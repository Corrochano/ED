/**
NOMBRE Y APELLIDOS:
LABORATORIO:
PUESTO:
USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "CarnetPorPuntos.h"


/**
Implementa aquí los métodos de las clases adicionales
*/

 
/**
Debes completar la implementación de las operaciones de CarnetPorPuntos,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
void CarnetPorPuntos::nuevo(const string& dni) {
    if (dicConductores.contiene(dni)) throw EConductorDuplicado();
    DiccionarioHash<unsigned int, Lista<string>>::Iterator it = dicListaPorPuntos.busca(15);
    
    if (it == dicListaPorPuntos.end()) {
        Lista<string> l;
        l.pon_ppio(dni);
        dicListaPorPuntos.inserta(15, l);
    }
    else {
        it.valor().pon_ppio(dni);
    }
    dicConductores.inserta(dni, ConductorInfo(15, dicListaPorPuntos.busca(15).valor().begin()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
void CarnetPorPuntos::quitar(const string& dni, unsigned int puntos) {
    DiccionarioHash<string, ConductorInfo>::Iterator it = dicConductores.busca(dni);
    
    if (it == dicConductores.end()) throw EConductorNoExiste();
    if (puntos == 0) return;

    unsigned int p = it.valor().getPuntos();

    if (p == 0) return;

    if (puntos >= p) p = 0;
    else p -= puntos;

    DiccionarioHash<unsigned int, Lista<string>>::Iterator it2 = dicListaPorPuntos.busca(it.valor().getPuntos());
    it2.valor().eliminar(it.valor().getIt());

    if (!dicListaPorPuntos.contiene(p)) dicListaPorPuntos.inserta(p, Lista<string>());

    DiccionarioHash<unsigned int, Lista<string>>::Iterator it3 = dicListaPorPuntos.busca(p);
    it3.valor().pon_ppio(dni);

    dicConductores.inserta(dni, ConductorInfo(p, dicListaPorPuntos.busca(p).valor().begin()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
void CarnetPorPuntos::recuperar(const string& dni, unsigned int puntos) {
     DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbusca(dni);
    
    if (it == dicConductores.cend()) throw EConductorNoExiste();

    ConductorInfo c = it.valor();

    unsigned int p = c.getPuntos();

    if (p == 15) return;

    if (puntos >= 15 - p) p = 15;
    else p += puntos;

    DiccionarioHash<unsigned int, Lista<string>>::Iterator it2 = dicListaPorPuntos.busca(c.getPuntos());
    it2.valor().eliminar(c.getIt());
 
    if (!dicListaPorPuntos.contiene(p)) dicListaPorPuntos.inserta(p, Lista<string>());

    DiccionarioHash<unsigned int, Lista<string>>::Iterator it3 = dicListaPorPuntos.busca(p);
    it3.valor().pon_ppio(dni);

    dicConductores.inserta(dni, ConductorInfo(p, dicListaPorPuntos.busca(p).valor().begin()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
unsigned int CarnetPorPuntos::consultar(const string& dni) const {
    DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbusca(dni);
    if (it == dicConductores.cend()) throw EConductorNoExiste();

    ConductorInfo c = it.valor();
    return c.getPuntos();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
unsigned int CarnetPorPuntos::cuantos_con_puntos(unsigned int puntos) const {
    if (puntos > 15) throw EPuntosNoValidos();
    DiccionarioHash<unsigned int, Lista<string>>::ConstIterator it = dicListaPorPuntos.cbusca(puntos);
    
    if (it == dicListaPorPuntos.cend()) return 0;
    return it.valor().longitud();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
const Lista<string>& CarnetPorPuntos::lista_por_puntos(unsigned int puntos) const {
    if (puntos > 15) throw EPuntosNoValidos();

    return dicListaPorPuntos.cbusca(puntos).valor();
}

