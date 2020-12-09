/*

NOMBRE Y APELLIDOS: Álvaro Corrochano López

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
	if (num_unidades <= 0 || dicOfertas.contiene(producto)) throw EErrorAltaProducto();

	dicOfertas.inserta(producto, num_unidades);
	dicClientes.inserta(producto, Lista<tCliente>());
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
void SistemaVentas::pon_en_espera(const tCliente& cliente, const tProducto& producto) {
	DiccionarioHash<tProducto, Lista<tCliente>>::Iterator it = dicClientes.busca(producto); // busco si está el producto
	if (it == dicClientes.end()) throw EProductoNoExiste(); // lanzo la excepción si no está
	
	if (!dicIt.contiene(cliente)) dicIt.inserta(cliente, DiccionarioHash<tProducto, Lista<tCliente>::Iterator>()); // si el cliente no está en el diccionario, lo añado
	else if (dicIt.busca(cliente).valor().contiene(producto)) return; // si sí estaba en el diccionario, miro ai está ya en la cola del producto y si está, me salgo

	it.valor().pon_ppio(cliente); // añado al cliente a la lista
	dicIt.busca(cliente).valor().inserta(producto, it.valor().begin()); // me quedo con que donde está en la lista de ese producto
}	
	
   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	  Constante
	 
	*/
void SistemaVentas::cancela_espera(const tCliente& cliente, const tProducto& producto) {
	DiccionarioHash<tProducto, Lista<tCliente>>::Iterator it = dicClientes.busca(producto); // busco si está el producto
	if (it == dicClientes.end()) throw EProductoNoExiste(); // lanzo la excepción si no está

	if (!dicIt.contiene(cliente)) return; // si el cliente no está en el diccionario, me voy
	if (!dicIt.busca(cliente).valor().contiene(producto)) return; // si el cliente no está en la lista del producto, me voy

	dicClientes.busca(cliente).valor().eliminar(dicIt.busca(cliente).valor().busca(producto).valor()); // elimino el cliente de la lista de ese producto
	dicIt.busca(cliente).valor().borra(producto); // elimino que el cliente estuviese en la lista de ese producto
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
unsigned int SistemaVentas::num_en_espera(const tProducto& producto) const {
	DiccionarioHash<tProducto, Lista<tCliente>>::ConstIterator it = dicClientes.cbusca(producto); // busco si está el producto
	if (it == dicClientes.cend()) throw EProductoNoExiste(); // lanzo la excepción si no está

	return it.valor().longitud();
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
void SistemaVentas::venta(const tProducto& producto, unsigned int num_unidades) {
	DiccionarioHash<tProducto, int>::Iterator itOfer = dicOfertas.busca(producto); // busco si está el producto
	DiccionarioHash<tProducto, Lista<tCliente>>::Iterator itListaClientes = dicClientes.busca(producto);
	if (itOfer == dicOfertas.end() || itListaClientes.valor().esVacia() || num_unidades > itOfer.valor()) throw EErrorVenta(); // lanzo la excepción si no está

	DiccionarioHash<tProducto, Lista<Venta>::Iterator>::Iterator itVenta = dicVentas.busca(producto);

	if (itVenta == dicVentas.end()) {
		listaVentas.pon_ppio(Venta(producto, num_unidades));
		dicVentas.inserta(producto, listaVentas.begin());
	}
	else {
		listaVentas.pon_ppio(Venta(producto, num_unidades + dicVentas.busca(producto).valor().elem()._unidades_vendidas));
		dicVentas.inserta(producto, listaVentas.begin());
	}

	dicIt.busca(primero_en_espera(producto)).valor().borra(producto);

	int restantes = itOfer.valor() - num_unidades;

	if (restantes == 0) {
		dicOfertas.borra(producto);
	}
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
const string& SistemaVentas::primero_en_espera(const tProducto& producto) const {
	DiccionarioHash<tProducto, Lista<tCliente>>::ConstIterator it = dicClientes.cbusca(producto); // busco si está el producto
	if (it == dicClientes.cend() || it.valor().esVacia()) throw EErrorAccesoListaEspera(); // lanzo la excepción si no está

	return it.valor().ultimo();
}

    /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 Constante
	 
	*/
Lista<Venta> SistemaVentas::lista_ventas() const {
	return listaVentas;
}

