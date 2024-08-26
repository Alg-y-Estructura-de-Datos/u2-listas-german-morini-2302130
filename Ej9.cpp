#include <iostream>
#include <string>
#include "Lista/ListaDoble.h"

using namespace std;

void aniadir(ListaDoble<string>* urls) {
    string u;
    cout << "Ingrese el sitio a añadir: ";
    cin.ignore();
    getline(cin, u, '\n');
    urls->insertarUltimo(u);
}

void historial(ListaDoble<string>* urls) {
    urls->imprimir();
}

void retroceder(ListaDoble<string>* urls, int& cursor) {
    if (cursor > 0 and cursor < urls->getTamanio()) {
        cursor--;
    } else {
        cout << "Estas en la pagina inicial" << endl;
    }
}

void avanzar(ListaDoble<string>* urls, int& cursor) {
    if (cursor >= 0 and cursor < urls->getTamanio()-1) {
        cursor++;
    } else {
        cout << "No hay mas paginas para mostrar" << endl;
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "Uso: " << argv[0] << " URL's..." << endl;
        return 1;
    }

    ListaDoble<string>* urls = new ListaDoble<string>();
    for (int i = 1; i < argc; i++) {
        urls->insertarUltimo(argv[i]);
    }

    bool salir = 0;
    int opt, cursor = 0;

    while(!salir) {
        cout << endl << "Sitio: " << urls->getDato(cursor) << endl << endl;;

        cout << "Opciones: " << endl;
        cout << "1. Añadir sitio" << endl;
        cout << "2. Mostrar todas" << endl;
        cout << "3. Retroceder" << endl;
        cout << "4. Avanzar" << endl;
        cout << "5. Salir" << endl;
        cin >> opt;

        switch (opt) {
        case 1:
            aniadir(urls);
            break;
        case 2:
            historial(urls);
            break;
        case 3:
            retroceder(urls, cursor);
            break;
        case 4:
            avanzar(urls, cursor);
            break;
        case 5:
            cout << "Saliendo ..." << endl << endl;
            salir = 1;
            break;
        default:
            cout << "Opción incorrecta, vuelva a ingresarla!" << endl << endl;
            break;
        }
    }

    return 0;
}
