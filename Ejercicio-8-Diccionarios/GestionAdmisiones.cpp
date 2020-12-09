/**
  NOMBRE Y APELLIDOS: Álvaro Corrcohano López
  LABORATORIO:
  PUESTO:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "GestionAdmisiones.h"

/** 
Implementación de las operaciones de la clase Paciente 
*/

Paciente::Paciente(const string& nombre, unsigned int edad, const string& sintomas):
    _nombre(nombre), _sintomas(sintomas), _edad(edad) {}	

unsigned int Paciente::edad() const {
   return _edad;	
}
const string& Paciente::nombre() const {
   return _nombre;	
}
const string& Paciente::sintomas() const {
   return _sintomas;	
}

/**
Implementa aquí los métodos de las clases adicionales
*/
iPaciente::iPaciente(Paciente p, Lista<CodigoPaciente>::Iterator it) :
    _p(p), _it(it) {};

Paciente iPaciente::getPaciente() const{
    return _p;
}

Lista<CodigoPaciente>::Iterator iPaciente::getIt() const{
    return _it;
}
 
/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
GestionAdmisiones::GestionAdmisiones() {}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas) {
    if (dicPacientes.contiene(codigo)) throw EPacienteDuplicado();

    colaPacientes.pon_ppio(codigo);
    dicPacientes.inserta(codigo, iPaciente(Paciente(nombre, edad, sintomas), colaPacientes.begin()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {
    DiccionarioHash<CodigoPaciente, iPaciente>::ConstIterator it = dicPacientes.cbusca(codigo);
    if (it == dicPacientes.cend()) throw EPacienteNoExiste();

    nombre = it.valor().getPaciente().nombre();
    edad = it.valor().getPaciente().edad();
    sintomas = it.valor().getPaciente().sintomas();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
void GestionAdmisiones::siguiente(CodigoPaciente& codigo) const {
    if (colaPacientes.esVacia()) throw ENoHayPacientes();
    codigo = colaPacientes.ultimo();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
bool GestionAdmisiones::hay_pacientes() const {  
    return !colaPacientes.esVacia();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
    DiccionarioHash<CodigoPaciente, iPaciente>::ConstIterator it = dicPacientes.cbusca(codigo);
    if (it == dicPacientes.cend()) throw EPacienteNoExiste();

    colaPacientes.eliminar(it.valor().getIt());
    dicPacientes.borra(codigo);
}
   
