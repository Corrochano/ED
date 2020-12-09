/*

NOMBRE Y APELLIDOS:

*/
#include "SistemaVentas.h"

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
SistemaVentas::SistemaVentas() {}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
void SistemaVentas::an_oferta(const tProducto& producto, unsigned int num_unidades) {
	if(num_unidades <= 0 || dicOfertas.contiene(producto)) throw EErrorAltaProducto();
	
	dicUnidades.inserta(producto, num_unidades);
	Lista<tCliente> l;
	dicOfertas.inserta(producto, l);
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Lineal
	 
	*/
void SistemaVentas::pon_en_espera(const tCliente& cliente, const tProducto& producto) {
	if (!dicOfertas.contiene(producto)) throw EProductoNoExiste();
	
	Lista<tCliente> l = dicOfertas.valorPara(producto);

	typename Lista<tCliente>::ConstIterator it = l.cbegin();

	while(it != l.cend() && it.elem() != cliente){
		it.next();
	}

	if (it == l.cend()) {
		l.pon_final(cliente);
		dicOfertas.inserta(producto, l);
	}

}	
	
   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	  Lineal
	 
	*/
void SistemaVentas::cancela_espera(const tCliente& cliente, const tProducto& producto) {
	if (!dicOfertas.contiene(producto)) throw EProductoNoExiste();

	Lista<tCliente> l = dicOfertas.valorPara(producto);

	typename Lista<tCliente>::Iterator it = l.begin();
	
	while (it != l.end() && it.elem() != cliente) {
		it.next();
	}

	if (it != l.end()) {
		l.eliminar(it);
		dicOfertas.inserta(producto, l);
	}

}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
unsigned int SistemaVentas::num_en_espera(const tProducto& producto) const {
	if (!dicOfertas.contiene(producto)) throw EProductoNoExiste();

	return dicOfertas.valorPara(producto).longitud();

}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
void SistemaVentas::venta(const tProducto& producto, unsigned int num_unidades) {
	if(!dicOfertas.contiene(producto) || num_unidades > dicUnidades.valorPara(producto) || 
		dicOfertas.valorPara(producto).esVacia()) throw EErrorVenta();

	int n = dicUnidades.valorPara(producto) - num_unidades;

	if (dicVentas.contiene(producto)) {
		Venta v = Venta(producto, dicVentas.valorPara(producto)._unidades_vendidas + num_unidades);
		dicVentas.inserta(producto, v);
	}
	else {
		Venta v = Venta(producto, num_unidades);
		dicVentas.inserta(producto, v);
	}

	if (n == 0) {
		dicOfertas.borra(producto);
		dicUnidades.borra(producto);
	}
	else {
		Lista<tCliente> l = dicOfertas.valorPara(producto);
		l.quita_ppio();
		dicOfertas.inserta(producto, l);
		dicUnidades.inserta(producto, n);
	}

}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
const string& SistemaVentas::primero_en_espera(const tProducto& producto) const {
	if (!dicOfertas.contiene(producto) || dicOfertas.valorPara(producto).esVacia()) throw EErrorAccesoListaEspera();

	return dicOfertas.valorPara(producto).primero();
}

    /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Lineal
	 
	*/
Lista<Venta> SistemaVentas::lista_ventas() const {
	Lista<Venta> l;

	typename DiccionarioHash<tProducto, Venta>::ConstIterator it = dicVentas.cbegin();

	while (it != dicVentas.cend()) {
		l.pon_ppio(it.valor());
		it.next();
	}

	return l;
}

