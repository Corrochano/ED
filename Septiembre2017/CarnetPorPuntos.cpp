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

    listaDNIs.pon_ppio(dni);
    ConductorInfo c = ConductorInfo(15, listaDNIs.begin());
    dicConductores.inserta(dni, c);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
void CarnetPorPuntos::quitar(const string& dni, unsigned int puntos) {
    DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbusca(dni);
    
    if (it == dicConductores.cend()) throw EConductorNoExiste();
    if (puntos == 0) return;

    ConductorInfo c = it.valor();

    int p = c.getPuntos();

    if (p == 0) return;

    if (puntos >= p) p = 0;
    else p -= puntos;

    listaDNIs.eliminar(c.getIt());
    listaDNIs.pon_ppio(dni);
    c.setIt(listaDNIs.begin());
    c.setPuntos(p);

    dicConductores.inserta(dni, c);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
void CarnetPorPuntos::recuperar(const string& dni, unsigned int puntos) {
     DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbusca(dni);
    
    if (it == dicConductores.cend()) throw EConductorNoExiste();

    ConductorInfo c = it.valor();

    int p = c.getPuntos();

    if (p == 15) return;

    if (puntos >= 15 - p) p = 15;
    else p += puntos;

    listaDNIs.eliminar(c.getIt());
    listaDNIs.pon_ppio(dni);
    c.setIt(listaDNIs.begin());
    c.setPuntos(p);

    dicConductores.inserta(dni, c);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Constante
*/
unsigned int CarnetPorPuntos::consultar(const string& dni) const {
    if (!dicConductores.contiene(dni)) throw EConductorNoExiste();

    DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbusca(dni);
    ConductorInfo c = it.valor();
    return c.getPuntos();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Lineal
*/
unsigned int CarnetPorPuntos::cuantos_con_puntos(unsigned int puntos) const {
    if (puntos > 15) throw EPuntosNoValidos();

    unsigned int ret = 0;
    DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbegin();

    ConductorInfo c;

    while (it != dicConductores.cend()) {
        c = it.valor();
        if (c.getPuntos() == puntos) ret++;
        it.next();
    }

    return ret;
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
    Lineal (¿cuadrático?)
*/
const Lista<string>& CarnetPorPuntos::lista_por_puntos(unsigned int puntos) const {
    if (puntos > 15) throw EPuntosNoValidos();

    Lista<string> ret;
    DiccionarioHash<string, ConductorInfo>::ConstIterator it = dicConductores.cbegin();

    ConductorInfo c;

    while (it != dicConductores.cend()) {
        c = it.valor();
        if (c.getPuntos() == puntos) {
            ret.pon_ppio(c.getIt().elem());
        }
        it.next();
    }

    const Lista<string>& constRet = ret;

    return constRet;
}

