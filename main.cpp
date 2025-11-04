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
    evento e, eDP;

    crear(c);

    string instruccion, salto;
    string nombre_e, descripcion_e, dependencia, padre, prioridad, nombre_dep, supDep;
    unsigned numDep, numDepDP;
    int i = 1;
    bool error = false;
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
                    g << "INTRODUCIDO: [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "NO INTRODUCIDO: [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }
                
            }else{                              
                if(existe(padre, c)){   //esto creo que con 1 llamada vale
                    aniadirDependiente(c, nombre_e, e, padre);             
                    g << "INTRODUCIDO: [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "NO INTRODUCIDO: [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }  
            }
        } else if (instruccion == "C"){
            getline(f, nombre_e);
            getline(f, descripcion_e);
            getline(f, prioridad);

            crearEvento(descripcion_e, stoi(prioridad), e);

            if(actualizarVal(c, nombre_e, e)){
                numDep = obtenerNumDependientes(nombre_e, c, error);
                if(existeIndependiente(nombre_e, c) && !error){
                    g << "CAMBIADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    if(!error){
                        padre = obtenerSupervisor(nombre_e, c, error);
                        if(!error){
                            g << "CAMBIADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                        }
                    }
                }
            } else {
                g << "NO CAMBIADO: " << nombre_e << endl;
            }

        } else if (instruccion == "D"){
            getline(f, nombre_e);
            getline(f, padre);

            if(existe(nombre_e, c) && existe(padre,c)){
                hacerDependiente(c, nombre_e, padre);
                g << "INTENTANDO hacer depend.: " << nombre_e << " -de-> " << padre << endl;
            } else {
                g << "IMPOSIBLE hacer depend.: " << nombre_e << " -de-> " << padre << endl;
            }
        } else if (instruccion == "O"){
            getline(f, nombre_e);

            if(existe(nombre_e, c)){            //si existe el "id" en la coleccion no hay que preocuparse por los errores
                numDep = obtenerNumDependientes(nombre_e, c, error);
                e = obtenerVal(nombre_e, c, error);
                if(existeIndependiente(nombre_e, c)){
                    g << "LOCALIZADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                } else {
                    descripcion_e = obtenerSupervisor(nombre_e, c, error);
                    g << "LOCALIZADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                }
            } else {
                g << "NO LOCALIZADO: " << nombre_e << endl;
            }
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
            getline(f, nombre_e);
            if(existe(nombre_e,c)){
                if(!existeIndependiente(nombre_e, c)){
                    hacerIndependiente(c, nombre_e);
                    g << "INDEPENDIZADO: " << nombre_e << endl;
                } else {
                    g << "YA ERA INDepend.: " << nombre_e << endl;
                }
            } else {
                g << "NO INDEPENDIZADO: " << nombre_e << endl;
            }
        } else if (instruccion == "B"){
            getline(f, nombre_e);
            if(existe(nombre_e, c)){
                borrar(nombre_e, c);
                if(!existe(nombre_e, c)){  //realmente no hace falta ver si existe ya que lo mira el borrar
                    g << "BORRADO: " << nombre_e << endl;
                } else {
                    g << "NO BORRADO: " << nombre_e << endl;
                }
            }else{
                g << "NO BORRADO: " << nombre_e << endl;
            }
        } else if (instruccion == "LD"){
            getline(f, nombre_e);
            g << "****DEPENDIENTES: " << nombre_e << endl;

            if(existe(nombre_e, c)){
                numDep = obtenerNumDependientes(nombre_e, c, error);
                e = obtenerVal(nombre_e, c, error);

                if(existeIndependiente(nombre_e, c) && !error){
                    g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                } else {
                    padre = obtenerSupervisor(nombre_e, c, error);
                    g << "[ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                }

                iniciarIterador(c);
                i = 1;                                  //cada vez que llamamos a "LD" tiene que volver al inicio
                while(existeSiguiente(c)){
                    nombre_dep = siguienteIdent(c);  
                    supDep = siguienteSuperior(c);
                    if(siguienteDependiente(c) && supDep == nombre_e){             //si su superior es igual al nombre del evento, es que depende de él
                        numDepDP = obtenerNumDependientes(nombre_dep, c, error);
                        eDP = obtenerVal(nombre_dep, c, error);

                        if(existeIndependiente(nombre_dep, c)){
                            g << "[" << i << " -> " << nombre_dep << " --- " << numDepDP << " ] --- " << descripcion(eDP) << " --- ( " << suPrioridad(eDP) << " ) ;;;;" << endl;
                            i++;
                        } else {
                            g << "[" << i << " -> " << nombre_dep << " -de-> " << supDep << " ;;;  " << numDepDP << " ] --- " << descripcion(eDP) << " --- ( " << suPrioridad(eDP) << " ) ;;;;" << endl;
                            i++;
                        }
                    }
                    avanza(c);
                }

                g << "****FINAL dependientes -de-> " << nombre_e << endl;

            } else {
                g << "****DESCONOCIDO" << endl;
            }

        } else if(instruccion == "LT"){
            g << "-----LISTADO: " << tamanio(c) <<endl;  
            iniciarIterador(c);
            while(existeSiguiente(c)){
                nombre_e = siguienteIdent(c);
                e = siguienteVal(c);
                numDep = siguienteNumDependientes(c);
                if(siguienteDependiente(c)){
                    g << "[ " << nombre_e <<  " -de-> " << siguienteSuperior(c) << " ;;;  " << numDep << " ] --- " << descripcion(e) << " --- " << "( " << suPrioridad(e) << " )" << endl;
                } else {
                    g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                }  
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