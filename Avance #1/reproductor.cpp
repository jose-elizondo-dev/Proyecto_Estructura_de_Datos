#include <iostream>
#include <fstream>
#include <sstream> //para separar textos 
#include <cctype> //validar numeros
using namespace std;
#include "reproductor.h"

Cancion* cabeza = nullptr;  // inicio de la lista
Cancion* actual = nullptr;  // canción en reproducción


bool listaVacia(){
    return cabeza == nullptr;
}
bool camposValidos(string nombre, string compositor, string duracion) {

    if (nombre.empty() || compositor.empty() || duracion.empty()){
        cout << "Error: No se permiten campos vacios.\n";
        return false;
    }
    return true;
}

bool duracionValida(string dur) {
    int contador = 0;
    for (char c : dur){
        if (c == ':') contador++;
        else if (!isdigit(c)) return false;
    }
    return (contador == 1 || contador == 2);
}

bool existeCancion(string nombre) {
    if (listaVacia()) return false;
    Cancion* temp = cabeza;
    do{
        if (temp->nombreCancion == nombre)
            return true;

        temp = temp->siguiente;

    }while (temp != cabeza);
    return false;
}

void agregarCancion(string nombre, string comp, string dur, string rutaLetra) {
    if (!camposValidos(nombre, comp, dur)) return;

    if (rutaLetra.empty()){
        cout << "Error: Debe ingresar el nombre del archivo de la letra.\n";
        return;
    }
    if (!duracionValida(dur)){
        cout << "Error: La duracion debe tener formato mm:ss o hh:mm:ss.\n";
        return;
    }

    if (existeCancion(nombre)){
        cout << "La cancion ya existe.\n";
        return;
    }
    string rutaCompleta = "letras/" + rutaLetra;
    Cancion* nueva = new Cancion;
    nueva->nombreCancion = nombre;
    nueva->compositor = comp;
    nueva->duracion = dur;

     nueva->letra = cargarLetra(rutaCompleta);

    if (cabeza == nullptr){
        cabeza = nueva;
        nueva->siguiente = nueva;
        nueva->anterior = nueva;
        actual = nueva;
    }else{
        Cancion* ultimo = cabeza->anterior;

        ultimo->siguiente = nueva;
        nueva->anterior = ultimo;

        nueva->siguiente = cabeza;
        cabeza->anterior = nueva;
    }
    guardarCancionArchivo(nombre, comp, dur, rutaCompleta); //guardar en archivo
    cout << "Cancion agregada correctamente.\n";
}

void mostrarPlaylist(){
    if (listaVacia()) {
    cout << "Por el momento no hay canciones en la playlist..\n";
    return;
    }
    Cancion* temp = cabeza;
    do{
        if (temp == actual)
            cout << "> ";
        else
            cout << "  ";

        cout << temp->nombreCancion << " - "
            << temp->compositor << endl;

        temp = temp->siguiente;
    } while (temp != cabeza);
}

bool buscarCancion(string nombre){
    if (listaVacia()) {
        cout << "Por el momento no hay canciones en la playlist..\n";
        return false;
    }
    Cancion* temp = cabeza;
    do{
        if (temp->nombreCancion == nombre){
            actual = temp;
            cout << "Cancion encontrada y lista para reproducir.\n";
            return true;
        }
        temp = temp->siguiente;
    } while (temp != cabeza);
    cout << "La cancion ingresada no existe en la playlist....\n";
    return false;
}

void eliminarCancion(string nombre){ 
    if (listaVacia()){
    cout << "No hay canciones para eliminar.\n";
    return;
    }
    Cancion* temp = cabeza;
    do{
        if(temp->nombreCancion == nombre){

            if (temp->siguiente == temp){
                cabeza = nullptr;
                actual = nullptr;
            }else{
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;

                if (temp == cabeza)
                    cabeza = temp->siguiente;

                if (temp == actual)
                    actual = temp->siguiente;
            }

            delete temp;
            cout << "La cancion fue eliminada correctamente de la playlist.\n";
            return;
        }

        temp = temp->siguiente;
    } while(temp != cabeza);

    cout << "La cancion ingresada no existe en la playlist.\n";
}

string cargarLetra(string ruta){
    ifstream archivo(ruta);            //abrir el archivo
    string linea;                     //guarda la linea que se va leyendo 
    string textoCompleto = "";      // se acumula todo el texto

    if(archivo.is_open()){ //veriifca que se abra bien
        while(getline(archivo, linea)){ //leer linea por linea
            textoCompleto += linea + "\n";
        }
        archivo.close(); 
    }else{
       cout << "Advertencia: No se pudo abrir el archivo de la letra.\n";
        textoCompleto = "Letra no disponible";
    }
    return textoCompleto;
}
void guardarCancionArchivo(string nombre, string comp, string dur, string rutaLetra){
   //crea el archivo
    ofstream archivo("canciones.txt", ios::app); //ios::app agrega al final sin necesidad de borrar
    if (archivo.is_open()){
        archivo << nombre << "|"
                << comp << "|"
                << dur << "|"
                << rutaLetra << endl;

        archivo.close();
    }else{
        cout << "Error: No se pudo guardar la canción en el archivo.\n";
    }
}

void cargarCancionesDesdeArchivo(){
    ifstream archivo("canciones.txt"); //abre el archivo para leer
    if (!archivo.is_open())
        return;
    string linea;

    while(getline(archivo, linea)){ //lee cada linea
        string nombre, comp, dur, ruta;
        stringstream ss(linea); // Convertir la línea en un "stream" para separar por '|'
   
        getline(ss, nombre, '|');
        getline(ss, comp, '|'); 
        getline(ss, dur, '|');
        getline(ss, ruta, '|');

        Cancion* nueva = new Cancion;
        nueva->nombreCancion = nombre;
        nueva->compositor = comp;
        nueva->duracion = dur;
        nueva->letra = cargarLetra(ruta);

        if(cabeza == nullptr){   //si la lista esta vacia
            cabeza = nueva;    
            nueva->siguiente = nueva; 
            nueva->anterior = nueva; 
            actual = nueva;
        }else{
            Cancion* ultimo = cabeza->anterior;

            ultimo->siguiente = nueva;
            nueva->anterior = ultimo;

            nueva->siguiente = cabeza;
            cabeza->anterior = nueva;
        }
    }
    archivo.close();
}
void reproducirActual(){
    if (listaVacia()) {
        cout << "Lo sentimos, aun no hay canciones en la playlist.\n";
        return;
    }
    cout << "\n=== REPRODUCIENDO ===\n";
    cout << "Nombre: " << actual->nombreCancion << endl;
    cout << "Compositor: " << actual->compositor << endl;
    cout << "Duracion: " << actual->duracion << endl;

    if (!actual->letra.empty()){
        cout << "\nFragmento de la letra:\n";
        cout << actual->letra.substr(0, 100) << "...\n";  
    }
}

void siguienteCancion(){
    if(listaVacia()){
        cout << "Por el momento no hay canciones en la playlist.\n";
        return;
    }

    actual = actual->siguiente;
    cout << "Pasando a la siguiente cancion...\n";
    reproducirActual();
}

void anteriorCancion(){
    if (listaVacia()){
        cout << "Por el momento no hay canciones en la playlist..\n";
        return;
    }
    actual = actual->anterior;
    cout << "Regresando a la cancion anterior...\n";
    reproducirActual();
}