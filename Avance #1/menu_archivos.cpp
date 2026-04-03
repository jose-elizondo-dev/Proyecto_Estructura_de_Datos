#include <iostream>
#include <string>
using namespace std;
#include "arbol.h"

void menuArchivos(){
    int op;
    string nombre;

    do{
        cout << "\n====== GESTOR DE ARCHIVOS ======\n";
        cout << "1. Crear carpeta\n";
        cout << "2. Crear archivo\n";
        cout << "3. Eliminar\n";
        cout << "4. Listar contenido\n";
        cout << "5. Entrar a carpeta\n";
        cout << "6. Volver a carpeta anterior\n";
        cout << "7. Mostrar ruta actual\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        //validar entrada
        if(!(cin>>op)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<< "Error: Por Favor ingrese un numero valido.\n";
            continue;
        }cin.ignore();

        switch(op){
        case 1:
            cout <<"Nombre de la carpeta: ";
            getline(cin,nombre);
            break;

        case 2:
        break;

        case 3:
        break;

        case 4:
        break;

        case 5:
        break;

        case 6:
        break;

        case 7:
        break;

        case 0:
        cout<< "Estas saliendo del gestor de archivos...\n";
        break;
        
        default:
            cout << "Error: Opcion invalida.\n";
        }
    }
    while(op !=0);
}