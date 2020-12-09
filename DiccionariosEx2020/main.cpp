// PON AQUÍ TU NOMBRE Y APELLIDOS, ASÍ COMO EL NÚMERO DE TU DOCUMENTO IDENTIFICATIVO
// NOMBRE: Álvaro
// APELLIDOS: Corrochano López
#include "GestionDeMatriculas.h"

#include <iostream>
#include <string>
using namespace std;


void registra_curso(GestionDeMatriculas& gm) {
	tCurso curso;
	unsigned int plazas;
	cin >> curso >> plazas;
	try {
		gm.registra_curso(curso, plazas);
		cout << "OK" << endl;
	}
	catch (ECursoYaExiste) {
		cout << "CURSO DUPLICADO" << endl;
	}
}

void registra_estudiante(GestionDeMatriculas& gm) {
	tEstudiante estudiante;
	cin >> estudiante;
	try {
		gm.registra_estudiante(estudiante);
		cout << "OK" << endl;
	}
	catch (EEstudianteYaRegistrado) {
		cout << "ESTUDIANTE YA REGISTRADO" << endl;
	}
}

void registra_solicitud(GestionDeMatriculas& gm) {
	tEstudiante estudiante;
	tCurso curso;
	cin >> estudiante >> curso;
	try {
		gm.registra_solicitud(estudiante, curso);
		cout << "OK" << endl;
	}
	catch (ESolicitud) {
		cout << "ERROR SOLICITUD" << endl;
	}
}

void cancela_solicitud(GestionDeMatriculas& gm) {
	try {
		tEstudiante estudiante;
		cin >> estudiante;
		gm.cancela_solicitud(estudiante);
		cout << "OK" << endl;
	}
	catch (EEstudianteNoExiste) {
		cout << "ESTUDIANTE NO EXISTE" << endl;
	}
}

void atiende_solicitud(GestionDeMatriculas& gm) {
	try {
		ResultadoSolicitud resul = gm.atiende_solicitud();
		cout << "MATRICULA DE " << resul.estudiante << " EN " << resul.curso << " ";
		if (resul.aceptada) {
			cout << "ACEPTADA" << endl;
		}
		else {
			cout << "NO ACEPTADA" << endl;
		}
	}
	catch (ENoHaySolicitudes) {
		cout << "NO HAY SOLICITUDES" << endl;
	}
}

void estudiantes_en_curso(GestionDeMatriculas& gm) {
	try {
		tCurso curso;
		cin >> curso;
		Lista<DatosEstudiante> estudiantes = gm.estudiantes_en_curso(curso);
		Lista<DatosEstudiante>::ConstIterator iestudiante = estudiantes.cbegin();
		while (iestudiante != estudiantes.cend()) {
			cout << "[estudiante: " << iestudiante.elem().estudiante << ", num matricula:" << iestudiante.elem().num_matricula << "]";
			iestudiante.next();
		}
		cout << endl;
	}
	catch (ECursoNoExiste) {
		cout << "CURSO NO EXISTE" << endl;
	}
}


int main() {
	GestionDeMatriculas gm;
	string comando;
	while(cin >> comando) {
		if (comando == "registra_curso") registra_curso(gm);
        else if (comando == "registra_estudiante") registra_estudiante(gm);
		else if (comando == "registra_solicitud") registra_solicitud(gm);
		else if (comando == "cancela_solicitud")  cancela_solicitud(gm);
		else if (comando == "atiende_solicitud")  atiende_solicitud(gm);
		else if (comando == "estudiantes_en_curso")  estudiantes_en_curso(gm);
	}
	return 0;
}