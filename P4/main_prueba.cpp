#include <iostream>
#include <fstream>
#include "colecInterdep.hpp" 
#include "evento.hpp"

int main(){
    ifstream f;
    ofstream g;
    colecInterdep<string, evento> c;
    evento e, eDP;

    crear(c);

    string instruccion, salto;
    string nombre_e, descripcion_e, dependencia, padre, prioridad, nombre_dep, supDep;
    unsigned numDep, numDepDP;
    int i = 1;
    int tam_antes = 0;
    int tam_dsps = 0;
    bool esDep = false;
    f.open("entrada.txt");  
    g.open("salida.txt");
    nombre_e = "perico";
    if(existe(nombre_e, c)){g << "Hola" << endl;} 
    else{g << "Funciona ";}
}