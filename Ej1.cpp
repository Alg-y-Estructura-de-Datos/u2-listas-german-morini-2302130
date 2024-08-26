#include <iostream>
#include "Lista/Lista.h"

using namespace std;

template<class T>
void printLista(Lista<T>* li, int p) {
    for (int i = p; i < li->getTamanio(); i++) {
        cout << li->getDato(i) << "->";
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cout << "Uso: " << argv[0] << " PALABRAS..." << endl;
        return 1;
    }

    Lista<string>* li = new Lista<string>();

    for (int i = 1; i < argc; i++) {
        li->insertarUltimo(argv[i]);
    }

    int p;
    cout << "Ingrese la posición de la cual empezar a imprimir: " << endl;
    cin >> p;

    printLista(li, p);
}
