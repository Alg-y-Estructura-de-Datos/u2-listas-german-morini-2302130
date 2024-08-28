#include <iostream>
#include <cstdlib>
#include "Lista/Lista.h"

using namespace std;

template<class T>
Lista<T>* repetidos(Lista<T>* li) {
    Lista<T>* rep = new Lista<T>;

    for (int i = 0; i < li->getTamanio()-1; i++) {
        if (li->getDato(i) == li->getDato(i+1)) {
            rep->insertarUltimo(li->getDato(i));

            while (i < li->getTamanio()-1 && !rep->esVacia() && li->getDato(i+1) == rep->getDato(rep->getTamanio()-1)) {
                i++;
            }
        }       
    }

    return rep;
}

template<class T>
void ordenar(Lista<T>* li) {
    T elem;
    int j;

    for (int i = 1; i < li->getTamanio(); i++) {
        elem = li->getDato(i);
        j = i - 1;

        while (j >= 0 && li->getDato(j) > elem) {
            li->reemplazar(j+1, li->getDato(j));
            j--;
        }
        li->reemplazar(j+1, elem);
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "Uso: " << argv[0] << " NUMEROS..." << endl;
        return 1;
    }

    Lista<int>* li = new Lista<int>;
    Lista<int>* rep;

    for (int i = 1; i < argc; i++) {
        li->insertarUltimo(atoi(argv[i]));
    }

    ordenar(li);
    li->print();
    rep = repetidos(li);
    
    if (rep->esVacia()) {
        cout << "No hay elementos repetidos" << endl;
    } else {
        cout << "Los elementos repetidos son: " << endl;
        rep->print();
    }
}
