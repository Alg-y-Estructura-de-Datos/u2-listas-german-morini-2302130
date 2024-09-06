#include <cstdio>
#include <iostream>
#include "Lista/Lista.h"

using namespace std;

struct Contacto {
    string nombre;
    int numero;
};

void imprimir(Lista<Contacto>& l) {
    for (int i = 0; i < l.getTamanio(); i++) {
        cout << "---------------------------" << endl;
        cout << l.getDato(i).nombre << endl;
        cout << l.getDato(i).numero << endl;
    }
}

void aniadir_contactos(Lista<Contacto>& l, int n = 5) {
    Contacto c;

    for (int i = 0; i < n; i++) {
        cout << "--- CONTACTO " << i+1 << " ---" << endl;
        
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, c.nombre, '\n');

        cout << "Numero: "; 
        cin >> c.numero;

        l.insertarUltimo(c);
    }
}

Contacto buscar(Lista<Contacto>& l, string nom) {
    // hacer
}

void eliminar(Lista<Contacto>& l, string nom) {
    // hacer
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " CANTIDAD" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    Lista<Contacto>* contactos = new Lista<Contacto>;

    aniadir_contactos(*contactos, n);

    int opt;
    string nom;

    while (1==1) {
        cout << endl;
        cout << "--- MENU ---" << endl;
        cout << "1. Agregar contacto" << endl;
        cout << "2. Mostrar contactos" << endl;
        cout << "3. Buscar por nombre" << endl;
        cout << "4. Eliminar por nombre" << endl;
        cout << "5. Contar contactos" << endl;
        cout << "6. Salir" << endl << "> ";
        cin >> opt;
        
        cout << "\033[H\033[2J";
        switch (opt) {
        case 1:
            cout << "¿Cuantos deseas agregar?: ";
            cin >> n;

            aniadir_contactos(*contactos, n);
            break;
        case 2:
            imprimir(*contactos);
            break;
        case 3:
            cout << "Ingrese el nombre a buscar: ";
            cin.ignore();
            getline(cin, nom, '\n');

            buscar(*contactos, nom);
            break;
        case 4:
            cout << "Ingrese el nombre a elimiar: ";
            cin.ignore();
            getline(cin, nom, '\n');

            eliminar(*contactos, nom);
            break;
        case 5:
            cout << "Tenés " << contactos->getTamanio() << " contactos agendados" << endl;
            break;
        case 6:
            return 0;
        default:
            cout << "Ingrese una opción valida!" << endl;
        }
    }
}
