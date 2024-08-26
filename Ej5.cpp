#include <cstdlib>
#include <iostream>
#include "Lista/Lista.h"

using namespace std;

template<class T>
Lista<T>* reepetidos(Lista<T>* li) {
    Lista<T>* repetidos = new Lista<T>();
    int indx = 0;
    int contador = 0;

    while (indx < li->getTamanio()) {
        for (int i = indx+1; i < li->getTamanio(); i++) {
            if (li->getDato(indx) == li->getDato(i)) contador++;
        }

        if (contador != 0) {
            contador = 0;
            repetidos->insertarUltimo(li->getDato(indx));
        }
        indx++;
    }

    return repetidos;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cout << "Uso: " << argv[0] << " NUMEROS..." << endl;
        return 1;
    }

    Lista<int>* li = new Lista<int>();
    Lista<int>* repetidos;

    for (int i = 1; i < argc; i++) {
        li->insertarUltimo(atoi(argv[i]));
    }

    repetidos = reepetidos(li);
    
    if (repetidos->getTamanio() == 0) {
        cout << "No hay elementos repetidos" << endl;
    } else {
        cout << "Los elementos repetidos son: " << endl;
        repetidos->print();
    }
}
