#include "SistemaVentas.h"
#include <iostream>
using namespace std;


void an_oferta(SistemaVentas& ventas) {
	tProducto producto;
	unsigned int num_unidades;
	cin >> producto;
	cin >> num_unidades;
	try {
		ventas.an_oferta(producto, num_unidades);
		cout << "OK" << endl;
	}
	catch (EErrorAltaProducto) {
		cout << "ERROR" << endl;
	}
}

void pon_en_espera(SistemaVentas& ventas) {
	tProducto producto;
	tCliente cliente;
	cin >> cliente;
	cin >> producto;
	try {
		ventas.pon_en_espera(cliente, producto);
		cout << "OK" << endl;
	}
	catch (EProductoNoExiste) {
		cout << "ERROR" << endl;
	}
}

void cancela_espera(SistemaVentas& ventas) {
	tProducto producto;
	tCliente cliente;
	cin >> cliente;
	cin >> producto;
	try {
		ventas.cancela_espera(cliente, producto);
		cout << "OK" << endl;
	}
	catch (EProductoNoExiste) {
		cout << "ERROR" << endl;
	}
}

void num_en_espera(const SistemaVentas& ventas) {
	tProducto producto;
	cin >> producto;
	try {
		
		cout << ventas.num_en_espera(producto) << endl;
	}
	catch (EProductoNoExiste) {
		cout << "ERROR" << endl;
	}
}

void venta(SistemaVentas& ventas) {
	tProducto producto;
	int num_unidades;
	cin >> producto;
	cin >> num_unidades;
	try {
		ventas.venta(producto,num_unidades);
		cout << "OK" << endl;
	}
	catch (EErrorVenta) {
		cout << "ERROR" << endl;
	}
}


void primero_en_espera(const SistemaVentas& ventas) {
	tProducto producto;
	cin >> producto;
	try {

		cout << ventas.primero_en_espera(producto) << endl;
	}
	catch (EErrorAccesoListaEspera) {
		cout << "ERROR" << endl;
	}
}

void lista_ventas(const SistemaVentas& ventas) {
	Lista<Venta> vs = ventas.lista_ventas();   
	Lista<Venta>::ConstIterator iventas = vs.cbegin();
	cout << "/";
	while (iventas != vs.cend()) {
	  	cout << iventas.elem()._producto << ":" << iventas.elem()._unidades_vendidas << "/";
		iventas.next();
	 }
	cout << endl;
  }




int main() {
	SistemaVentas ventas;
	string comando;
	while (cin >> comando) {
		if (comando == "an_oferta") an_oferta(ventas);
		else if (comando == "pon_en_espera") pon_en_espera(ventas);
		else if (comando == "cancela_espera") cancela_espera(ventas);
		else if (comando == "num_en_espera") num_en_espera(ventas);
		else if (comando == "venta") venta(ventas);
		else if (comando == "primero_en_espera") primero_en_espera(ventas);
		else if (comando == "lista_ventas") lista_ventas(ventas);
	}
	return 0;
}

