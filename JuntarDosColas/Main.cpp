#include <iostream>
#include "cola.h"

using namespace std;

bool resuelveCaso() {
    Cola<int> cola1, cola2;
    int numCasos, tam1, tam2, aux;
    cin >> numCasos;
    if (!cin) { return false; }
    for (int i = 0; i < numCasos; i++) {
        cin >> tam1;
        for (int j = 0; j < tam1; ++j) {
            cin >> aux;
            cola1.pon(aux);
        }
        cin >> tam2;
        for (int k = 0; k < tam2; k++) {
            cin >> aux;
            cola2.pon(aux);
        }
        cola1.entremezclar(cola2, tam1, tam2);
        cola1.imprimir();
    }
    return true;
}
int main() {
    while (resuelveCaso());
    return 0;
}
