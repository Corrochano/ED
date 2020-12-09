#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;

Arbin<int> lee_arbol(istream& in) {
    char c;
    in >> c;
    switch (c) {
    case '#': return Arbin<int>();
    case '[': {
        int raiz;
        in >> raiz;
        in >> c;
        return Arbin<int>(raiz);
    }
    case '(': {
        Arbin<int> iz = lee_arbol(in);
        int raiz;
        in >> raiz;
        Arbin<int> dr = lee_arbol(in);
        in >> c;
        return Arbin<int>(iz, raiz, dr);
    }
    default: return Arbin<int>();
    }
}

bool esHoja(const Arbin<int>& a) {
    return (!a.esVacio() && (a.hijoDer().esVacio() && a.hijoIz().esVacio()));
}

void mejorRentaAux(Arbin<int> a, bool& esRentable, int& renta_maxima, int acum) {
    if (a.esVacio()) return;

    if (acum + a.raiz() <= 0) { esRentable = false; return; }

    esRentable = true;

    int renta = acum + a.raiz();

    bool renDer = false;
    bool renIz = false;

    if (esHoja(a)) {
        if (renta > renta_maxima) renta_maxima = renta;
        return;
    }

    mejorRentaAux(a.hijoIz(), renIz, renta_maxima, renta);
    mejorRentaAux(a.hijoDer(), renDer, renta_maxima, renta);

    if (!renIz && !renDer) esRentable = false;

}


void mejorRenta(Arbin<int> a, bool& esRentable, int& renta_maxima) {
    mejorRentaAux(a, esRentable, renta_maxima, 0);
}

void rentable(const Arbin<int> a) {
    bool b = false;
    int rent = 0;

    mejorRenta(a, b, rent);

    if (b) {
        cout << "Rentable.\n"
            << "Mayor renta: " << rent << endl;
    }
    else {
        cout << "No Rentable.\n";
    }

}


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF) {
        rentable(lee_arbol(cin));
        string resto_linea;
        getline(cin, resto_linea);
        if (cin.peek() != EOF) cout << endl;
    }
    return 0;
}