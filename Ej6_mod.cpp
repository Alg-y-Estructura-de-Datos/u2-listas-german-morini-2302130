#include <cstdio>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include "Lista/CircList.h"

using namespace std;

class Contacto {
    private:
        string nombre;
        int numero;
    public:
        Contacto() {};
        Contacto(string nom, int num) : nombre(nom), numero(num) {}

        // sobreescribe el operador de salida de datos
        // 'friend' indica que se puede acceder a los campos privados de la clase
        friend ostream& operator<<(ostream& os, const Contacto& c) {
            os << c.nombre << " " << c.numero;
            return os;
        }

        // lo mismo pero para el operador de ingreso de datos
        // esto permite definir como se van a leer los datos desde un archivo
        friend istream& operator>>(istream& is, Contacto& c) {
            is >> c.nombre >> c.numero;
            return is;
        }

        bool operator==(const Contacto& otro) {
            return nombre == otro.nombre;
        }
};

void cargar_contactos(CircList<Contacto>& l, string archivo) {
    ifstream file(archivo);

    if (!file) exit(2);

    Contacto c;

    while (file >> c) {
        l.insertarUltimo(c);
    }

    file.close();
}

void guardar_contactos(CircList<Contacto>& l, string archivo) {
    ofstream file(archivo);

    if (!file) exit(2);

    for (int i = 0; i < l.getTamanio(); i++) {
        try {
            file << l.getDato(i) << endl;
            // no se, no anda, no quiero saberlo
        } catch (int e) {}
    }

    file.close();
}

void aniadir_contactos(CircList<Contacto>& l, int n = 5) {
    string nom;
    int num;

    for (int i = 0; i < n; i++) {
        cout << "--- CONTACTO " << i+1 << " ---" << endl;
        
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nom, '\n');

        cout << "Numero: ";
        cin >> num;

        l.insertarUltimo(Contacto(nom, num));
    }
}

Contacto buscar(CircList<Contacto>& l, string nom) {
    // hacer
}

void eliminar(CircList<Contacto>& l, string nom) {
    // hacer
}

int main() {
    CircList<Contacto>* contactos = new CircList<Contacto>;

    cargar_contactos(*contactos, "contactos.txt");
    int opt, n;
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

        switch (opt) {
        case 1:
            cout << "¿Cuantos deseas agregar?: ";
            cin >> n;

            aniadir_contactos(*contactos, n);
            break;
        case 2:
            contactos->imprimir();
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
            guardar_contactos(*contactos, "contactos.txt");
            return 0;
        default:
            cout << "Ingrese una opción valida!" << endl;
        }
    }
}
