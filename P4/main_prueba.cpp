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
    descripcion_e = "esto es la desc tranquila";
    unsigned pri = 3;
    crearEvento(descripcion_e, pri, e);
    nombre_dep = "Manolo";

    if(existe(nombre_e, c)){g << "Hola" << endl;} 
    else{g << "Funciona " << endl;}
    if(!existeDependiente(nombre_e, c)){g << "ASDASD" << endl;}
    if(!existeIndependiente(nombre_e, c)){g << "PERICOOOO" << endl;}
    tam_antes = tamanio(c);
    aniadirIndependiente(c, nombre_e, e);
    aniadirIndependiente(c, nombre_e, e);
    if(existeIndependiente(nombre_e, c)){g << "Tus huevos pal lao primo" << endl;} 
    else{g << "mal" << endl;}
    aniadirDependiente(c, nombre_dep, e, nombre_e);
    aniadirDependiente(c, nombre_e, e, nombre_e);
    if(existeDependiente(nombre_dep, c)){g << "Se ha añadido correcto un dependiente" << endl;} else {g << "Me voy al baño" << endl;}
    tam_dsps = tamanio(c);
    g << tam_antes << tam_dsps << endl; 
    hacerDependiente(c, nombre_e, nombre_dep);
    hacerIndependiente(c, nombre_dep);

    g << endl << endl << endl;

    g << "-----LISTADO: " << tamanio(c) <<endl;  
            iniciarIterador(c);
            while(existeSiguiente(c)){
                if(siguienteIdent(c, nombre_e) && siguienteVal(c, e) && siguienteNumDependientes(c, numDep)){
                    if(siguienteSuperior(c, supDep)){
                        g << "[ " << nombre_e <<  " -de-> " << supDep << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- " << "( " << suPrioridad(e) << " )" << endl;
                    } else {
                        g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                    } 
            }
            avanza(c);

            }    
            g << "-----" << endl;
}