/*Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

#include <iostream>
#include <fstream>
#include "colecInterdep.hpp" 
#include "evento.hpp"

int main(){
    ifstream f;
    ofstream g;
    colecInterdep<evento> c;
    evento e;

    crear(c);     //antes de hacer cosas con una coleccion primero hay que crearla o que :)

    string instruccion, salto;
    string nombre_e, descripcion_e, dependencia, padre, prioridad;
    f.open("entrada.txt");  
    g.open("salia.txt");
    while (f >> instruccion){
        getline(f, salto);
       
        if(instruccion == "A"){
            getline(f, nombre_e);
            getline(f, descripcion_e);
            getline(f, prioridad);
            getline(f, dependencia);
            getline(f, padre);
                
           if(dependencia == "INDependiente"){    
                aniadirIndependiente(c, nombre_e, e);
                g << "INTRODUCIDO [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
            }else{                              //faltan cosillas de logica por aqui, tipo que si su padre no existe poner NO INTRODUCIDO
                //if existe(padre) hacemos lo de abajo
                //aniadirDependiente();             
                g << "INTRODUCIDO [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                //else 
                // g << "NO INTRODUCIDO [ " << nombre_e << " -de-> " << padre << " ] --- " << " --- ( "   << " )" << endl;
            }
        } else if (instruccion == "C"){
            ;
        } else if (instruccion == "D"){
            ;
        } else if (instruccion == "O"){
            ;
        } else if (instruccion == "E"){
            getline(f, nombre_e);
        } else if (instruccion == "I"){
            ;
        } else if (instruccion == "B"){
            ;
        } else if (instruccion == "LD"){
            ;
        } else if (instruccion == "LT"){
            g << "-----LISTADO: " << tamanio(c) <<endl;   //de momento no imprime nada, tamaño(c) = 0
            for(int i = 0; i < tamanio(c); i++){
                g << "[ " << nombre_e << " --- " << "obtenerNumDependientes(nombre_e, c)" << " ]  --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
            } 
            g << "-----" << endl;
        }
    }
    f.close();
    g.close();
}

/*
void casoA(ifstream& f ){

}

void casoC(ifstream& f ){
    
}

void casoD(ifstream& f ){
    
}

void casoO(ifstream& f ){
    
}

void casoE(ifstream& f ){
    
}

void casoI(ifstream& f ){
    
}

void casoB(ifstream& f ){
    
}

void casoLD(ifstream& f ){
    
}

void casoLT(ifstream& f ){
    
}
*/