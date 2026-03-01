#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H
#include <string>
using namespace std;

struct Cancion {
    string nombreCancion;
    string compositor;
    string duracion;
    string letra;

    Cancion* siguiente;
    Cancion* anterior;
};

extern Cancion* cabeza;
extern Cancion* actual;

bool listaVacia();
bool camposValidos(string nombre, string compositor, string duracion);
bool duracionValida(string dur);
bool existeCancion(string nombre);
void agregarCancion(string nombre, string comp, string dur, string rutaLetra);
void mostrarPlaylist();
bool buscarCancion(string nombre);
void eliminarCancion(string nombre);
string cargarLetra(string ruta);
void guardarCancionArchivo(string nombre, string comp, string dur, string rutaLetra);
void cargarCancionesDesdeArchivo();
void reproducirActual();
void siguienteCancion();
void anteriorCancion();

#endif