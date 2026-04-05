#include <iostream>
#include <string>
using namespace std;
#include "arbol.h"

//navegacion 
string rutaActual = "/raiz";
void entrarCarpeta(string nombre){
if (nombre.empty()){
        cout << "Error: nombre vacio.\n";
        return;
    }
    rutaActual += "/" + nombre;
    cout << "Entraste a: " << rutaActual << endl;
}
void volver(){
   if (rutaActual == "/raiz"){
        cout << "Ya estas en la raiz.\n";
        return;
    }
    int pos = rutaActual.find_last_of('/');
    rutaActual = rutaActual.substr(0, pos);

    cout << "Regresaste a: " << rutaActual << endl;  
}
void mostrarRuta(){
    cout << "Ruta actual: " << rutaActual << endl;
}