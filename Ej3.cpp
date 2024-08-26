#include <cstdlib>
#include <iostream>
#include "Lista/Lista.h"

using namespace std;

void intercambiar(Lista<int>* li1, Lista<int>* li2) {
    Lista<int> aux1, aux2;

    for (int i = 0; i < li1->getTamanio(); i++) {
        aux1.insertarUltimo(li1->getDato(i));
    }

    for (int i = 0; i < li2->getTamanio(); i++) {
        aux2.insertarUltimo(li2->getDato(i));
    }

    li1->vaciar();
    li2->vaciar();

    for (int i = 0; i < aux1.getTamanio(); i++) {
        li2->insertarUltimo(aux1.getDato(i));
    }

    for (int i = 0; i < aux2.getTamanio(); i++) {
        li1->insertarUltimo(aux2.getDato(i));
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " ITERACIONES..." << endl;
        return 1;
    }
    srand(time(NULL));

    Lista<int>* li1 = new Lista<int>();
    Lista<int>* li2 = new Lista<int>();

    for (int i = 0; i < atoi(argv[1]); i++) {
        if (rand()%2) li1->insertarPrimero(rand()%100);
        if (rand()%2) li2->insertarPrimero(rand()%100);
    }

    cout << "Lista 1: " << endl;
    li1->print();
    cout << "Lista 2: " << endl;
    li2->print();

    cout << "INTERCAMBIANDO..." << endl;
    intercambiar(li1, li2);

    cout << "Lista 1: " << endl;
    li1->print();
    cout << "Lista 2: " << endl;
    li2->print();
}
