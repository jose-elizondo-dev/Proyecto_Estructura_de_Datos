#include <iostream>
#include <fstream>
using namespace std;

struct Cancion
{
    string nombreCancion;
    string compositor;
    string duracion;
    string letra;

    Cancion *siguiente;
    Cancion *anterior;
};

Cancion* cabeza = nullptr;  // inicio de la lista
Cancion* actual = nullptr;  // canción en reproducción


bool listaVacia() {
    return cabeza == nullptr;
}

bool camposValidos(string nombre, string compositor, string duracion) {

    if (nombre.empty() || compositor.empty() || duracion.empty()) {
        cout << "Error: No se permiten campos vacíos.\n";
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
        cout << "Duración inválida.\n";
        return;
    }

    if (existeCancion(nombre)) {
        cout << "La canción ya existe.\n";
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

    cout << "Canción agregada correctamente.\n";

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
        cout << "Playlist vacía.\n";
        return false;
    }

    Cancion* temp = cabeza;

    do {
        if (temp->nombreCancion == nombre) {
            actual = temp;
            cout << "Canción encontrada.\n";
            return true;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);

    cout << "Canción no encontrada.\n";
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
            cout << "Canción eliminada.\n";
            return;
        }

        temp = temp->siguiente;
    } while (temp != cabeza);

    cout << "No encontrada.\n";
}

string cargarLetra(string ruta){

    ifstream archivo(ruta);            //abrir el archivo
    string linea;                     //guarda la linea que se va leyendo 
    string textoCompleto = " ";      // se acumula todo el texto

    if (archivo.is_open()){
        while (getline(archivo, linea)) {
            textoCompleto += linea + "\n";
        }
        archivo.close();
    }else{
        textoCompleto =  "Letra no disponible";
    }
    return textoCompleto;
}


int main() {

    int opcion;
    string nombre, compositor, duracion, ruta;

    do {
        cout << "\n====== REPRODUCTOR DE MUSICA ======\n";
        cout << "1. Agregar canción\n";
        cout << "2. Mostrar playlist\n";
        cout << "3. Reproducir canción actual\n";
        cout << "4. Siguiente canción\n";
        cout << "5. Canción anterior\n";
        cout << "6. Buscar canción por nombre\n";
        cout << "7. Eliminar canción\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {

        case 1:
            cout << "Nombre de la canción: ";
            getline(cin, nombre);

            cout << "Compositor: ";
            getline(cin, compositor);

            cout << "Duración (mm:ss): ";
            getline(cin, duracion);

            cout << "Ruta del archivo de letra: ";
            getline(cin, ruta);

            agregarCancion(nombre, compositor, duracion, ruta);
            break;

        case 2:
            mostrarPlaylist();
            break;

        case 3:
            //usar para la reproduccion y la navegacion
            break;

        case 4:
            //usar para la reproduccion y la navegacion
            break;

        case 5:
            //usar para la reproduccion y la navegacion
            break;

        case 6:
            cout << "Nombre de la canción a buscar: ";
            getline(cin, nombre);
            buscarCancion(nombre);
            break;

        case 7:
            cout << "Nombre de la canción a eliminar: ";
            getline(cin, nombre);

            char confirmacion;
            cout << "¿Seguro que desea eliminarla? (s/n): ";
            cin >> confirmacion;
            cin.ignore();

            if (confirmacion == 's' || confirmacion == 'S') {
                eliminarCancion(nombre);
            }
            else {
                cout << "Eliminación cancelada.\n";
            }
            break;

        case 8:
            cout << "Saliendo del reproductor...\n";
            break;

        default:
            cout << "Opción inválida.\n";
        }

    } while (opcion != 8);

    return 0;
}