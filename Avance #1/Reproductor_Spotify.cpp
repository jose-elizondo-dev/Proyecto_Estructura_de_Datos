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

string cargarLetra(string ruta){

    ifstream archivo(ruta);            //abrir el archivo
    string linea;                     //guarda la linea que se va leyendo 
    string textoCompleto = " ";      // se acumula todo el texto

    if (archivo.is_open()){
        
    }
    

}