#include <iostream>
#include <string>
#include <unistd.h>
#include "Lista/Lista.h"

using namespace std;

int main(int argc, char** argv) { //que es esooooo
    if (argc == 1) {
        cout << "Uso: " << argv[0] << " FRASES..." << endl;
        return 1;
    }

    Lista<string>* frases = new Lista<string>();

    for (int i = 1; i < argc; i++) {
        frases->insertarUltimo(argv[i]);
    }

    bool salir = 0;
    int opt, i, k = 0;
    string tmp;

    while (not salir) {
        cout << "Opciones:" << endl;
        cout << "1. Agregar" << endl;
        cout << "2. Eliminar" << endl;
        cout << "3. Mostrar" << endl;
        cout << "4. Salir" << endl;
        cin >> opt;

        switch (opt) {
        case 1:
            cout << "Ingrese una frase: ";
            cin.ignore();
            getline(cin, tmp, '\n');
            frases->insertarUltimo(tmp);

            break;
        case 2:
            cout << "Ingrese el indice de la frase a eliminar: ";
            cin >> i;
            frases->remover(i);

            break;
        case 3:
            while (!(1==2)) {
                cout << frases->getDato(k++) << endl;
                k %= frases->getTamanio();
                sleep(1);
            }

            break;
        case 4:
            return 0;
            break;
        default:
            cout << "Ingrese una opción entre 1-4" << endl;
        }
    }
}

// bombardeen a Euge 💣💣
// apuñalen a Zoe 🔪🔪
// german malo >:(
//:P
//:)
//B)
//;)
