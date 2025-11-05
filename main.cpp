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
                if(!existe(nombre_e, c)){
                    aniadirIndependiente(c, nombre_e, e);
                    g << "INTRODUCIDO: [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "NO INTRODUCIDO: [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }
                
            }else{                              
                if(existe(padre, c) && !existe(nombre_e, c)){   
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

            if(actualizarVal(c, nombre_e, e) && obtenerNumDependientes(nombre_e, c, numDep)){
                if(obtenerSupervisor(nombre_e, c, padre)){
                    g << "CAMBIADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "CAMBIADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
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

            if(obtenerNumDependientes(nombre_e, c, numDep) && obtenerVal(nombre_e, c, e)){   
                if(obtenerSupervisor(nombre_e, c, padre)){
                    g << "LOCALIZADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                } else {
                    g << "LOCALIZADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
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
                if(!existe(nombre_e, c)){  
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

            if(obtenerNumDependientes(nombre_e, c, numDep) && obtenerVal(nombre_e, c, e)){
                if(obtenerSupervisor(nombre_e, c, padre)){
                    g << "[ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                } else {
                    g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                }
                
                iniciarIterador(c);
                i = 1;                                  //cada vez que llamamos a "LD" tiene que volver al inicio
                while(existeSiguiente(c)){
                    if(siguienteIdent(c, nombre_dep) && siguienteSuperior(c, supDep)){
                        if(siguienteDependiente(c) && supDep == nombre_e
                        && obtenerNumDependientes(nombre_dep, c, numDepDP) && obtenerVal(nombre_dep, c, eDP)){             //si su superior es igual al nombre del evento, es que depende de él
                            
                            if(existeIndependiente(nombre_dep, c)){
                                g << "[" << i << " -> " << nombre_dep << " --- " << numDepDP << " ] --- " << descripcion(eDP) << " --- ( " << suPrioridad(eDP) << " ) ;;;;" << endl;
                                i++;
                            } else {
                                g << "[" << i << " -> " << nombre_dep << " -de-> " << supDep << " ;;;  " << numDepDP << " ] --- " << descripcion(eDP) << " --- ( " << suPrioridad(eDP) << " ) ;;;;" << endl;
                                i++;
                            }
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
                if(siguienteIdent(c, nombre_e) && siguienteVal(c, e) && siguienteNumDependientes(c, numDep)){
                    if(siguienteSuperior(c, supDep)){
                        g << "[ " << nombre_e <<  " -de-> " << supDep << " ;;;  " << numDep << " ] --- " << descripcion(e) << " --- " << "( " << suPrioridad(e) << " )" << endl;
                    } else {
                        g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                    } 
            }
            avanza(c);

            }    
            g << "-----" << endl;
        }
    } 
    f.close();
    g.close();

    return 0;
}
