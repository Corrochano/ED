/**
  NOMBRE Y APELLIDOS:
  LABORATORIO:
  PUESTO:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "GestionAdmisiones.h"

/** 
Implementación de las operaciones de la clase Paciente 
*/

Paciente::Paciente(const string& nombre, unsigned int edad, const string& sintomas):
    _nombre(nombre),  _sintomas(sintomas), _edad(edad) {}	

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
iPaciente::iPaciente(Paciente p, int g, Lista<CodigoPaciente>::Iterator it) :
    _p(p), _g(g), _it(it) {};

Paciente iPaciente::getPaciente() const{
    return _p;
}

int iPaciente::getGravedad() const {
    return _g;
}

Lista<CodigoPaciente>::Iterator iPaciente::getIt() const {
    return _it;
}
 
/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de los mismos.
*/ 


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante dado que siempre inicializa el diccionario con 3 listas para los 3 valores.
*/
GestionAdmisiones::GestionAdmisiones() {
    int g = GRAVE;
    for (g; g != LEVE; g--){
        dicGravedad.inserta(g, Lista<CodigoPaciente>());
    }
    dicGravedad.inserta(g, Lista<CodigoPaciente>());
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas, Gravedad gravedad) {
    if (dicPacientes.contiene(codigo)) throw EPacienteDuplicado();
    
    DiccionarioHash<int, Lista<CodigoPaciente>>::Iterator it = dicGravedad.busca(gravedad);

    it.valor().pon_ppio(codigo);
    
    dicPacientes.inserta(codigo, iPaciente(Paciente(nombre, edad, sintomas), gravedad, it.valor().begin()));
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
 Lineal
*/
void GestionAdmisiones::siguiente(CodigoPaciente& codigo, Gravedad& gravedad) const {

    if (!dicGravedad.valorPara(GRAVE).esVacia()) { codigo = dicGravedad.valorPara(GRAVE).ultimo();; gravedad = Gravedad::GRAVE; return; }

    if (!dicGravedad.valorPara(NORMAL).esVacia()) { codigo = dicGravedad.valorPara(NORMAL).ultimo(); gravedad = Gravedad::NORMAL; return; }

    if (!dicGravedad.valorPara(LEVE).esVacia()) { codigo = dicGravedad.valorPara(LEVE).ultimo();; gravedad = Gravedad::LEVE; return; }

    throw ENoHayPacientes();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
Lineal
*/
bool GestionAdmisiones::hay_pacientes() const {  
   
    if (!dicGravedad.valorPara(GRAVE).esVacia()) return true;

    if (!dicGravedad.valorPara(NORMAL).esVacia()) return true;

    if (!dicGravedad.valorPara(LEVE).esVacia()) return true;

    return false;
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 Constante
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
    DiccionarioHash<CodigoPaciente, iPaciente>::ConstIterator it = dicPacientes.cbusca(codigo);
    if (it == dicPacientes.cend()) throw EPacienteNoExiste();

    DiccionarioHash<int, Lista<CodigoPaciente>>::Iterator itG = dicGravedad.busca(it.valor().getGravedad());

    itG.valor().eliminar(it.valor().getIt());
    dicPacientes.borra(codigo);
}
   
