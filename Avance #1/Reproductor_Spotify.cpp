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