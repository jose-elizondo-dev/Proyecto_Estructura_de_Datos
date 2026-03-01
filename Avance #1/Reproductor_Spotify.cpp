#include <iostream>
#include <fstream>
#include <sstream> //para separar textos 
#include <cctype> //validar numeros
using namespace std;
#include "reproductor.h"

Cancion* cabeza = nullptr;  // inicio de la lista
Cancion* actual = nullptr;  // canción en reproducción


bool listaVacia() {
    return cabeza == nullptr;
}

bool camposValidos(string nombre, string compositor, string duracion) {

    if (nombre.empty() || compositor.empty() || duracion.empty()) {
        cout << "Error: No se permiten campos vacios.\n";
        return false;
    }
    return true;
}

bool duracionValida(string dur) {

    int contador = 0;

    for (char c : dur) {
        if (c == ':') contador++;
        else if (!isdigit(c)) return false;
    }

    return (contador == 1 || contador == 2);
}

bool existeCancion(string nombre) {

    if (listaVacia()) return false;

    Cancion* temp = cabeza;

    do {
        if (temp->nombreCancion == nombre)
            return true;

        temp = temp->siguiente;

    } while (temp != cabeza);

    return false;
}

void agregarCancion(string nombre, string comp, string dur, string rutaLetra) {

    if (!camposValidos(nombre, comp, dur)) return;

    if (!duracionValida(dur)) {
        cout << "Duracion invalida.\n";
        return;
    }

    if (existeCancion(nombre)) {
        cout << "La cancion ya existe.\n";
        return;
    }

    Cancion* nueva = new Cancion;
    nueva->nombreCancion = nombre;
    nueva->compositor = comp;
    nueva->duracion = dur;

    nueva->letra = cargarLetra(rutaLetra);

    if (cabeza == nullptr) {
        cabeza = nueva;
        nueva->siguiente = nueva;
        nueva->anterior = nueva;
        actual = nueva;
    } else {
        Cancion* ultimo = cabeza->anterior;

        ultimo->siguiente = nueva;
        nueva->anterior = ultimo;

        nueva->siguiente = cabeza;
        cabeza->anterior = nueva;
    }

    guardarCancionArchivo(nombre, comp, dur, rutaLetra); //guardar en archivo

    cout << "Cancion agregada correctamente.\n";

}

void mostrarPlaylist() {

    if (listaVacia()) {
    cout << "No hay canciones en la playlist.\n";
    return;
    }

    Cancion* temp = cabeza;
    do {
        if (temp == actual)
            cout << "▶ ";
        else
            cout << "  ";

        cout << temp->nombreCancion << " - "
            << temp->compositor << endl;

        temp = temp->siguiente;
    } while (temp != cabeza);
}

bool buscarCancion(string nombre) {

    if (listaVacia()) {
        cout << "Playlist vacia.\n";
        return false;
    }

    Cancion* temp = cabeza;

    do {
        if (temp->nombreCancion == nombre) {
            actual = temp;
            cout << "Cancion encontrada.\n";
            return true;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);

    cout << "Cancion no encontrada.\n";
    return false;
}


void eliminarCancion(string nombre) {
    
    if (listaVacia()) {
    cout << "No hay canciones para eliminar.\n";
    return;
    }
    Cancion* temp = cabeza;

    do {
        if (temp->nombreCancion == nombre) {

            if (temp->siguiente == temp) {
                cabeza = nullptr;
                actual = nullptr;
            } else {
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;

                if (temp == cabeza)
                    cabeza = temp->siguiente;

                if (temp == actual)
                    actual = temp->siguiente;
            }

            delete temp;
            cout << "Cancion eliminada.\n";
            return;
        }

        temp = temp->siguiente;
    } while (temp != cabeza);

    cout << "No encontrada.\n";
}

string cargarLetra(string ruta){

    ifstream archivo(ruta);            //abrir el archivo
    string linea;                     //guarda la linea que se va leyendo 
    string textoCompleto = "";      // se acumula todo el texto

    if (archivo.is_open()){ //veriifca que se abra bien
        while (getline(archivo, linea)) { //leer linea por linea
            textoCompleto += linea + "\n";
        }
        archivo.close(); 
    }else{
        textoCompleto =  "Letra no disponible";
    }
    return textoCompleto;
}
void guardarCancionArchivo(string nombre, string comp, string dur, string rutaLetra) {

    ofstream archivo("canciones.txt", ios::app);

    if (archivo.is_open()) {
        archivo << nombre << "|"
                << comp << "|"
                << dur << "|"
                << rutaLetra << endl;

        archivo.close();
    } else {
        cout << "Error al guardar la canción en archivo.\n";
    }
}

void cargarCancionesDesdeArchivo() {

    ifstream archivo("canciones.txt");

    if (!archivo.is_open())
        return;

    string linea;

    while (getline(archivo, linea)) {

        string nombre, comp, dur, ruta;
        stringstream ss(linea);

        getline(ss, nombre, '|');
        getline(ss, comp, '|');
        getline(ss, dur, '|');
        getline(ss, ruta, '|');

        Cancion* nueva = new Cancion;
        nueva->nombreCancion = nombre;
        nueva->compositor = comp;
        nueva->duracion = dur;
        nueva->letra = cargarLetra(ruta);

        if (cabeza == nullptr) {
            cabeza = nueva;
            nueva->siguiente = nueva;
            nueva->anterior = nueva;
            actual = nueva;
        } else {
            Cancion* ultimo = cabeza->anterior;

            ultimo->siguiente = nueva;
            nueva->anterior = ultimo;

            nueva->siguiente = cabeza;
            cabeza->anterior = nueva;
        }
    }

    archivo.close();
}
void reproducirActual() {

    if (listaVacia()) {
        cout << "No hay canciones en la playlist.\n";
        return;
    }

    cout << "\n=== REPRODUCIENDO ===\n";
    cout << "Nombre: " << actual->nombreCancion << endl;
    cout << "Compositor: " << actual->compositor << endl;
    cout << "Duracion: " << actual->duracion << endl;

    if (!actual->letra.empty()) {
        cout << "\nFragmento de la letra:\n";
        cout << actual->letra.substr(0, 100) << "...\n";  
    }
}

void siguienteCancion() {

    if (listaVacia()) {
        cout << "No hay canciones en la playlist.\n";
        return;
    }

    actual = actual->siguiente;
    cout << "Pasando a la siguiente cancion...\n";
    reproducirActual();
}

void anteriorCancion() {

    if (listaVacia()) {
        cout << "No hay canciones en la playlist.\n";
        return;
    }

    actual = actual->anterior;
    cout << "Regresando a la cancion anterior...\n";
    reproducirActual();
}
int main() {

    int opcion;
    string nombre, compositor, duracion, ruta;
    cargarCancionesDesdeArchivo();

    do {
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
        cin >> opcion;
        cin.ignore();

        switch (opcion) {

        case 1:
            cout << "Nombre de la cancion: ";
            getline(cin, nombre);

            cout << "Compositor: ";
            getline(cin, compositor);

            cout << "Duracion (mm:ss): ";
            getline(cin, duracion);

            cout << "Ruta del archivo de letra: ";
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

            if (confirmacion == 's' || confirmacion == 'S') {
                eliminarCancion(nombre);
            }
            else {
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

    return 0;
}