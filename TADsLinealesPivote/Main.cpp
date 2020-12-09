#include <iostream>
#include "dcola.h"

using namespace std;

bool resuelveCaso() {
    DCola<int> cola;
    int n, piv, aux;
    cin >> n;
    cin >> piv;
    if (!cin) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        cin >> aux;
        cola.pon_final(aux);
    }

    cola.particion(piv, n);
    cola.imprime();

    return true;
}
int main() {
    while (resuelveCaso());
    return 0;
}