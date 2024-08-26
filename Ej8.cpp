#include <iostream>
#include <string>
#include "Lista/CircList.h"

using namespace std;

int main(int argc, char** argv) { //que es esooooo
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " CANTIDAD" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    string* frases = new string[n];

    for (int i = 0; i < n; i++) {
        cout << "Ingrese frase " << i+1 << ": ";
        getline(cin, frases[i], '\n');
    }

    bool salir = 0;
    int opt;
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
                getline(cin, frases[frases->length()], '\n');

                break;
            case 2:
                int i;
                cout << "Ingrese el indice de la frase a eliminar: ";
                cin >> i;



                break;
            case 3:
                break;
            case 4:
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
