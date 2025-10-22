/*Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

#include <iostream>
#include <fstream>
#include "colecInterdep.hpp" 
#include "evento.hpp"

int main(){
    ifstream f;
    ofstream g;
    colecInterdep<string, evento> c;
    evento e;

    crear(c);     //antes de hacer cosas con una coleccion primero hay que crearla o que :)

    string instruccion, salto;
    string nombre_e, descripcion_e, dependencia, padre, prioridad;
    unsigned numDep;
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

            crearEvento(descripcion_e, stoi(prioridad), e);
                
           if(dependencia == "INDependiente"){    
                if(!existeIndependiente(nombre_e, c)){
                    aniadirIndependiente(c, nombre_e, e);
                    g << "INTRODUCIDO [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } 
                
            }else{                              
                if(existe(padre, c)){
                    aniadirDependiente(c, nombre_e, e, padre);             
                    g << "INTRODUCIDO [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "NO INTRODUCIDO [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }  
            }
        } else if (instruccion == "C"){
            ;
        } else if (instruccion == "D"){
            ;
        } else if (instruccion == "O"){
            ;
        } else if (instruccion == "E"){
            getline(f, nombre_e);
            if(existeIndependiente(nombre_e, c)){
                g << "INDEPendiente: " << nombre_e << endl;
            } else if(existeDependiente(nombre_e, c)){
                g << "DEPendiente: " << nombre_e << endl;
            } else {
                g << "DESCONOCIDO: " << nombre_e << endl;
            }
        } else if (instruccion == "I"){
            ;
        } else if (instruccion == "B"){
            ;
        } else if (instruccion == "LD"){
            ;
        } else if (instruccion == "LT"){
            g << "-----LISTADO: " << tamanio(c) <<endl;  
            iniciarIterador(c);
            while(existeSiguiente(c)){
                nombre_e = siguienteIdent(c);
                e = siguienteVal(c);
                numDep = siguienteNumDependientes(c);
               // if(siguienteDependiente(c)) {g << "perico" << endl;}
                g << siguienteSuperior(c);  
                g << "[ " << nombre_e << " --- " << numDep << " ]  --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                avanza(c);
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