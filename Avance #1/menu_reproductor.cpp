#include <iostream>
#include <string>
using namespace std;

#include "reproductor.h"

void menuReproductor() {

    int opcion;
    string nombre, compositor, duracion, ruta;
    cargarCancionesDesdeArchivo();

    do{
     cout << "\n====== REPRODUCTOR DE MUSICA ======\n";
     cout << "1. Agregar cancion\n";
     cout << "2. Mostrar playlist\n";
     cout << "3. Reproducir cancion actual\n";
     cout << "4. Siguiente cancion\n";
     cout << "5. Cancion anterior\n";
     cout << "6. Buscar cancion por nombre\n";
     cout << "7. Eliminar cancion\n";
     cout << "8. Salir\n";
     cout << "Seleccione una opcion: ";
        if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Ingrese un numero valido.\n";
        continue; // vuelve al inicio del menú
    }
    cin.ignore();
        switch (opcion){
        case 1:
            cout << "Nombre de la cancion: ";
            getline(cin, nombre);

            cout << "Compositor: ";
            getline(cin, compositor);

            cout << "Duracion (mm:ss): ";
            getline(cin, duracion);

            cout << "Nombre y extension del archivo de letra: ";
            getline(cin, ruta);

            agregarCancion(nombre, compositor, duracion, ruta);
            break;
        case 2:
            mostrarPlaylist();
            break;
        case 3:
            reproducirActual(); 
            break;
        case 4:
            siguienteCancion();
            break;
        case 5:
            anteriorCancion();
            break;
        case 6:
            cout << "Nombre de la cancion a buscar: ";
            getline(cin, nombre);
            buscarCancion(nombre);
            break;
        case 7:
            cout << "Nombre de la cancion a eliminar: ";
            getline(cin, nombre);

            char confirmacion;
            cout << "¿Seguro que desea eliminarla? (s/n): ";
            cin >> confirmacion;
            cin.ignore();

            if (confirmacion == 's' || confirmacion == 'S'){
                eliminarCancion(nombre);
            }
            else{
                cout << "Eliminacion cancelada.\n";
            }
            break;
        case 8:
            cout << "Saliendo del reproductor...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 8);
}