// PON AQUÍ TU NOMBRE Y APELLIDOS, ASÍ COMO EL NÚMERO DE TU DOCUMENTO IDENTIFICATIVO
// NOMBRE: Álvaro
// APELLIDOS: Corrochano López


#include "GestionDeMatriculas.h"

/* Indicar justificadamente la complejidad de la operación
	Complejidad constante dado que solo inicializa mat a 0.
*/
GestionDeMatriculas::GestionDeMatriculas() {
	mat = 0;
}


/* Indicar justificadamente la complejidad de la operación
	Constante dado que solo hace búsqueda e inserción en un hash.
*/
void GestionDeMatriculas::registra_curso(const tCurso& curso, unsigned int plazas) {
	if (dicCursos.contiene(curso)) throw ECursoYaExiste();

	dicCursos.inserta(curso, plazas);
	dicEstCurso.inserta(curso, Diccionario<tEstudiante, int>());
}


/* Indicar justificadamente la complejidad de la operación
	Constante dado que solo hace búsqueda e inserción en un hash.
*/
void GestionDeMatriculas::registra_estudiante(const tEstudiante& estudiante) {
	if (dicEst.contiene(estudiante)) throw EEstudianteYaRegistrado();
	
	dicEst.inserta(estudiante, "");
	dicSolicitud.inserta(estudiante, "");
}


/* Indicar justificadamente la complejidad de la operación
	Constante dado que solo hace búsqueda e inserción en un hash.
*/
void GestionDeMatriculas::registra_solicitud(const tEstudiante& estudiante, const tCurso& curso) {
	DiccionarioHash<tEstudiante, tCurso>::Iterator it = dicSolicitud.busca(estudiante);
	if (!dicCursos.contiene(curso) || it == dicSolicitud.end()) throw ESolicitud();
	if (it.valor() == curso) return;

	DiccionarioHash<tEstudiante, Lista<tEstudiante>::Iterator>::Iterator it2 = dicItdeEst.busca(estudiante);
	
	if (it2 == dicItdeEst.end()) { // si es su primera solicitud
		listaSolicitudes.pon_ppio(estudiante);
		it.valor() = curso;
		dicItdeEst.inserta(estudiante, listaSolicitudes.begin());
	}
	else { // si no lo es
		it.valor() = curso;
	}
}


/* Indicar justificadamente la complejidad de la operación
	Constante dado que solo hace búsqueda e eliminación en un hash.
*/
void GestionDeMatriculas::cancela_solicitud(const tEstudiante& estudiante) {
	DiccionarioHash<tEstudiante, tCurso>::Iterator it = dicSolicitud.busca(estudiante);
	if (it == dicSolicitud.end()) throw EEstudianteNoExiste();

	DiccionarioHash<tEstudiante, Lista<tEstudiante>::Iterator>::Iterator it2 = dicItdeEst.busca(estudiante);
	if (it2 == dicItdeEst.end()) return;

	listaSolicitudes.eliminar(it2.valor());
	dicItdeEst.borra(estudiante);
	it.valor() = "";
}

/* Indicar justificadamente la complejidad de la operación
	Constante, dado que siempre se utilizan funcionen hash y accedemos directamente al último de la lista.

*/
ResultadoSolicitud GestionDeMatriculas::atiende_solicitud() {
	if (listaSolicitudes.esVacia()) throw ENoHaySolicitudes();

	DiccionarioHash<tEstudiante, tCurso>::Iterator it = dicSolicitud.busca(listaSolicitudes.ultimo());
	DiccionarioHash<tCurso, unsigned int>::Iterator it2 = dicCursos.busca(it.valor());

	listaSolicitudes.quita_final();

	if (it2.valor() == 0) return ResultadoSolicitud(it.clave(), it.valor(), false);

	DiccionarioHash<tEstudiante, tCurso>::Iterator it4 = dicEst.busca(it.clave());	
	DiccionarioHash<tCurso, Diccionario<tEstudiante, int>>::Iterator it3 = dicEstCurso.busca(it4.valor());
	if (it3 != dicEstCurso.end()) { // si tiene curso
		Diccionario<tEstudiante, int>::Iterator it5 = it3.valor().busca(it.clave());
		;
		if (it5 != dicEstCurso.busca(it.valor()).valor().end()) { // si está ya matriculado en su anterior curso
			dicCursos.busca(it.clave()).valor() += 1; // añado uno a sus plazas
			dicEstCurso.busca(it4.valor()).valor().borra(it.clave()); // lo borro de ese curso
		}
	}

	it2.setVal(it2.valor()- 1);
	mat += 1;
	dicEstCurso.busca(it.valor()).valor().inserta(it.clave(), mat);

	return ResultadoSolicitud(it.clave(), it.valor(), true);
}

/* Indicar justificadamente la complejidad de la operación
	Lineal dado que ha de recorrer todo el diccionarioArbóreo correspondiente.
*/
Lista<DatosEstudiante> GestionDeMatriculas::estudiantes_en_curso(const tCurso& curso) const {
	DiccionarioHash<tCurso, Diccionario<tEstudiante, int>>::ConstIterator it = dicEstCurso.cbusca(curso);
	if (it == dicEstCurso.cend()) throw ECursoNoExiste();

	Lista<DatosEstudiante> ret = Lista<DatosEstudiante>();
	Diccionario<tEstudiante, int>::ConstIterator it2 = it.valor().cbegin();

	while (it2 != it.valor().cend()) {
		ret.pon_ppio(DatosEstudiante(it2.clave(), it2.valor()));
		it2.next();
	}

	return ret;
}