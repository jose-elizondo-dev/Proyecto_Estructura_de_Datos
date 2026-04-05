#include <iostream>
using namespace std;
#include "reproductor.h"
#include "gestor.h"

void menuReproductor();
void menuArchivos();

int main() {
    int opcion;
    do {
        cout << "\n====== MENU PRINCIPAL ======\n";
        cout << "1. Reproductor de musica\n";
        cout << "2. Gestor de archivos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        // Validacion de entrada
        if (!(cin >> opcion)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Ingrese un numero valido.\n";
            continue;
        }
        cin.ignore();
        switch(opcion) {
            case 1:
                menuReproductor();  //llama al menu de reproductor
                break;
            case 2:
                menuArchivos();
                break;
            case 0:
            cout<< "Saliendo......\n";
            break;
            default:
                cout << "Error: Opcion invalida.\n";
        }

    } while(opcion != 0);

    return 0;
}