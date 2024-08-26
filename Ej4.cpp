#include <cctype>
#include <iostream>
#include <cstring>
#include "Lista/Lista.h"

using namespace std;

bool esVocal(char v) {
    return v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u';
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " PALABRA" << endl;
        return 1;
    }

    Lista<char>* palabra = new Lista<char>();
    string frase = argv[1];

    for (char c : frase) {
        palabra->insertarUltimo(c);
    }

    if (palabra->esVacia()) return 2;
    
    char v;
    int contador = 0;
    while (not esVocal(v)) {
        cout << "Ingrese una vocal para buscar: "; cin >> v;
    }

    for (int i = 0; i < palabra->getTamanio(); i++) {
        contador += tolower(palabra->getDato(i)) == tolower(v);
    }

    palabra->print();
    cout << "Veces que aparece: " << contador << endl;
}
