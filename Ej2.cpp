#include <iostream>
#include "Lista/Lista.h"

using namespace std;

void eliminar(Lista<int>* li, int n) {
    for (int i = 0; i < li->getTamanio(); i++) {
        if (li->getDato(i) == n) li->remover(i);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cout << "Uso: " << argv[0] << " NUMEROS..." << endl;
        return 1;
    }

    Lista<int>* li = new Lista<int>();

    for (int i = 1; i < argc; i++) {
        li->insertarUltimo(atoi(argv[i]));
    }

    int n;
    cout << "Ingrese el numero a borrar: "; cin >> n;

    cout << "--- LISTA ANTES DE BORRAR ---" << endl;
    li->print();
    eliminar(li, n);

    cout << "--- LISTA DESPUES DE BORRAR ---" << endl;
    li->print();
}
