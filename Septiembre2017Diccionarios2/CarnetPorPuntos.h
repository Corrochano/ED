/**
NOMBRE Y APELLIDOS:
LABORATORIO:
PUESTO:
USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/
#ifndef _CARNET_POR_PUNTOS_H
#define _CARNET_POR_PUNTOS_H

#include "lista.h"
#include <string>
#include "DiccionarioHash.h"
using namespace std;

class EConductorDuplicado {};
class EConductorNoExiste {};
class EPuntosNoValidos {};

class ConductorInfo {
public:
    ConductorInfo(unsigned int puntos, Lista<string>::Iterator it) :
        _puntos(puntos), _it(it) {};

    unsigned int getPuntos() {
        return _puntos;
    }

    Lista<string>::Iterator getIt() {
        return _it;
    }

    void setPuntos(unsigned int puntos) {
        _puntos = puntos;
    }

    void setIt(Lista<string>::Iterator it) {
        _it = it;
    }

private:
    unsigned int _puntos;
    typename Lista<string>::Iterator _it;
};

class CarnetPorPuntos {
public:
   void nuevo(const string& dni);
   void quitar(const string& dni, unsigned int puntos);
   void recuperar(const string& dni, unsigned int puntos);
   unsigned int consultar(const string& dni) const;
   unsigned int cuantos_con_puntos(unsigned int puntos) const;
   const Lista<string>& lista_por_puntos(unsigned int puntos) const;
private:
    DiccionarioHash<string, ConductorInfo> dicConductores;
    DiccionarioHash<unsigned int, Lista<string>> dicListaPorPuntos;
};

#endif