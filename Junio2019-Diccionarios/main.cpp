#include "GestorSurtidores.h"
#include <iostream>
using namespace std;


void an_surtidor(GestorSurtidores& surtidores) {
	tSurtidor surtidor;
	cin >> surtidor;
	cout << "an_surtidor " << surtidor << "=>";
	try {
		surtidores.an_surtidor(surtidor);
		cout << "OK" << endl;
	}
	catch (ESurtidorDuplicado) {
		cout << "SURTIDOR_DUPLICADO" << endl;
	}
}

void carga(GestorSurtidores& surtidores) {
	tSurtidor surtidor;
	tTipoCombustible combustible;
	unsigned int litros;
	cin >> surtidor;
	cin >> combustible;
	cin >> litros;
	cout << "carga " << surtidor << " " << combustible << " " << litros << "=>";
	try {
		surtidores.carga(surtidor, combustible, litros);
		cout << "OK" << endl;
	}
	catch (ESurtidorNoExiste) {
		cout << "SURTIDOR_NO_EXISTE" << endl;
	}
}

void pon_en_espera(GestorSurtidores& surtidores) {
	tSurtidor surtidor;
	tVehiculo vehiculo;
	cin >> vehiculo;
	cin >> surtidor;
	cout << "pon_en_espera " << vehiculo << " " << surtidor <<  "=>";
	try {
		surtidores.pon_en_espera(vehiculo, surtidor);
		cout << "OK" << endl;
	}
	catch (ELlegadaVehiculo) {
		cout << "ERROR_PUESTA_ESPERA" << endl;
	}
}

void vende(GestorSurtidores& surtidores) {
	tSurtidor surtidor;
	tTipoCombustible combustible;
	unsigned int litros;
	cin >> surtidor;
	cin >> combustible;
	cin >> litros;
	cout << "vende " << surtidor << " " << combustible <<  " " << litros << "=>";
	try {
		ResulVenta resul = surtidores.vende(surtidor,combustible,litros);
		cout << "VEHICULO:" << resul._vehiculo <<", QUEDAN: " << resul._litros_que_quedan << endl;
	}
	catch (EErrorVenta) {
		cout << "ERROR_VENTA" << endl;
	}
}

void abandona(GestorSurtidores& surtidores) {
	tVehiculo vehiculo;
	cin >> vehiculo;
	cout << "abandona " << vehiculo <<  "=>";
	surtidores.abandona(vehiculo);	
	cout << "OK" << endl;
}




int main() {
	GestorSurtidores surtidores;
	string comando;
	while (cin >> comando) {
		if (comando == "an_surtidor") an_surtidor(surtidores);
		else if (comando == "carga") carga(surtidores);
		else if (comando == "pon_en_espera") pon_en_espera(surtidores);
		else if (comando == "vende") vende(surtidores);
		else if (comando == "abandona") abandona(surtidores);
	}
	return 0;
}

