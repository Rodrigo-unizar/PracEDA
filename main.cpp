/*Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

/* NO SE PUEDE LLAMAR A EXISTIR ANTES DE LLAMAR A LA FUNCION*/

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
    f.open("pruebas.txt");  
    g.open("salia.txt");
    while (f >> instruccion){
        getline(f, salto);
        
        if(instruccion == "A"){         //coste O(1N)
            getline(f, nombre_e);
            getline(f, descripcion_e);
            getline(f, prioridad);
            getline(f, dependencia);
            getline(f, padre);

            crearEvento(descripcion_e, stoi(prioridad), e);
            tam_antes = tamanio(c);
            if(dependencia == "INDependiente"){    
                aniadirIndependiente(c, nombre_e, e);
                tam_dsps = tamanio(c);
                if(tam_antes != tam_dsps){
                    g << "INTRODUCIDO: [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "NO INTRODUCIDO: [ " << nombre_e << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }
            }else{
                aniadirDependiente(c, nombre_e, e, padre);
                tam_dsps = tamanio(c);                              
                if(tam_antes != tam_dsps){              
                    g << "INTRODUCIDO: [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "NO INTRODUCIDO: [ " << nombre_e << " -de-> " << padre << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }  
            }
        } else if (instruccion == "C"){   //no se puede hacer menor que 2N
            getline(f, nombre_e);
            getline(f, descripcion_e);
            getline(f, prioridad);

            crearEvento(descripcion_e, stoi(prioridad), e);

            if(actualizarVal(c, nombre_e, e) && obtenerDatos(nombre_e, numDep, padre, e, c)){   //obtenerDatos(nombre_e, numDep, padre, c)
                if(padre != "-.-.-.-.-"){  //if padre != "vacio"
                    g << "CAMBIADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                } else {
                    g << "CAMBIADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion_e << " --- ( " << prioridad << " )" << endl;
                }
            } else {
                g << "NO CAMBIADO: " << nombre_e << endl;
            }

        } else if (instruccion == "D"){     //coste O(3N)
            getline(f, nombre_e);
            getline(f, padre);

            //primero llamar a hacer dependiente, si el padre y el nombre existen podrá hacerDependiente al elemento, sino no
            hacerDependiente(c, nombre_e, padre);
            if(existe(padre, c) && existe(nombre_e, c)){   
                g << "INTENTANDO hacer depend.: " << nombre_e << " -de-> " << padre << endl;
            } else {
                g << "IMPOSIBLE hacer depend.: " << nombre_e << " -de-> " << padre << endl;
            }
        } else if (instruccion == "O"){     //coste O(1N)
            getline(f, nombre_e);

            if(obtenerDatos(nombre_e, numDep, padre, e, c)){   //obtenerDatos(nombre_e, numDep, padre, valor)
                if(padre != "-.-.-.-.-"){               //if padre != "vacio"
                    g << "LOCALIZADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                } else {
                    g << "LOCALIZADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                }
            } else {
                g << "NO LOCALIZADO: " << nombre_e << endl;
            }
        } else if (instruccion == "E"){         //Coste 1N
            getline(f, nombre_e);
            if(obtenerDatos(nombre_e, numDep, padre, e, c)){        //if obtenerDatos(.., padre, ...)
                if(padre != "-.-.-.-.-"){                               // if padre != "vacio"
                    g << "DEPendiente: " << nombre_e << endl;                 // es dependiente de "padre"
                } else {                    
                    g << "INDEPendiente: " << nombre_e << endl;         // else es independendiente
                }
            } else {
                g << "DESCONOCIDO: " << nombre_e << endl;           // else no existe
            }                                                      
            
        } else if (instruccion == "I"){  //no se hacerlo menos costoso
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

        } else if (instruccion == "B"){     //coste O(N) por la llamada a borrar
            getline(f, nombre_e);
            tam_antes = tamanio(c);
            borrar(nombre_e, c);
            tam_dsps = tamanio(c);
            if(tam_antes != tam_dsps){  
                g << "BORRADO: " << nombre_e << endl;
            } else {
                g << "NO BORRADO: " << nombre_e << endl;
            }
        } else if (instruccion == "LD"){
            getline(f, nombre_e);
            g << "****DEPENDIENTES: " << nombre_e << endl;

            if(obtenerDatos(nombre_e, numDep, padre, e, c)){      //obtenerDatos(...)
                if(padre != "-.-.-.-.-"){                        //if padre != "vacio"
                    g << "[ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                } else {
                    g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                }
                
                iniciarIterador(c);
                i = 1;                                  //cada vez que llamamos a "LD" tiene que volver al inicio
                while(existeSiguiente(c)){
                    if(siguienteDependiente(c) && siguienteIdent(c, nombre_dep) && siguienteSuperior(c, supDep)){
                        if(supDep == nombre_e && obtenerNumDependientes(nombre_dep, c, numDepDP) && obtenerVal(nombre_dep, c, eDP)){             //si su superior es igual al nombre del evento, es que depende de él
                            
                            if(existeIndependiente(nombre_dep, c)){ //aqui esta condicion nunca se cumple en verdad
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
