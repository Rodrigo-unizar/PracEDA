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
    string nombre_e, descripcion_e, dependencia, padre, nombre_dep, supDep;
    unsigned numDep, numDepDP, prioridad;
    int i = 1;
    int tam_antes = 0;
    int tam_dsps = 0;
    bool esDep = false;
    crearEvento(descripcion_e, prioridad, e);   //inicializamos un único evento
    f.open("entrada.txt");  
    g.open("salida.txt");
    while (f >> instruccion){
        getline(f, salto);
        
        if(instruccion == "A"){
            getline(f, nombre_e);
            getline(f, descripcion_e);
            f >> prioridad;
            getline(f, salto);
            getline(f, dependencia);
            getline(f, padre);

            cambiarDescripcion(descripcion_e, e);
            cambiarPrioridad(prioridad, e);
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
        } else if (instruccion == "C"){ 
            getline(f, nombre_e);
            getline(f, descripcion_e);
            f >> prioridad;
            getline(f, salto);

            cambiarDescripcion(descripcion_e, e);
            cambiarPrioridad(prioridad, e);

            if(actualizarVal(c, nombre_e, e) && obtenerDatos(nombre_e, numDep, padre, e, c, esDep)){ 
                if(esDep){  //if padre != "vacio"
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

            hacerDependiente(c, nombre_e, padre);  
            if(existe(padre, c) && existe(nombre_e, c)){        //existe el padre y el hijo 
                g << "INTENTANDO hacer depend.: " << nombre_e << " -de-> " << padre << endl;
            } else {
                g << "IMPOSIBLE hacer depend.: " << nombre_e << " -de-> " << padre << endl;
            }
        } else if (instruccion == "O"){
            getline(f, nombre_e);

            if(obtenerDatos(nombre_e, numDep, padre, e, c, esDep)){   
                if(esDep){               //if padre != "vacio", es decir, es dependiente
                    g << "LOCALIZADO: [ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                } else {
                    g << "LOCALIZADO: " << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                }
            } else {
                g << "NO LOCALIZADO: " << nombre_e << endl;
            }
        } else if (instruccion == "E"){
            getline(f, nombre_e);
            if(obtenerDatos(nombre_e, numDep, padre, e, c, esDep)){        //if obtenerDatos(.., padre, ...)
                if(esDep){                               // if padre != "vacio"
                    g << "DEPendiente: " << nombre_e << endl;                 // es dependiente de "padre"
                } else {                    
                    g << "INDEPendiente: " << nombre_e << endl;         // else es independendiente
                }
            } else {
                g << "DESCONOCIDO: " << nombre_e << endl;           // else no existe
            }                                                      
            
        } else if (instruccion == "I"){  
            getline(f, nombre_e);
            if(obtenerDatos(nombre_e, numDep, padre, e, c, esDep)){
                if(esDep){
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

            if(obtenerDatos(nombre_e, numDep, padre, e, c, esDep)){      //obtenerDatos(...)
                if(esDep){                        //if padre != "vacio"
                    g << "[ " << nombre_e << " -de-> " << padre << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                } else {
                    g << "[ " << nombre_e << " --- " << numDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " ) ****" << endl;
                }
                
                iniciarIterador(c);
                i = 1;                                  //cada vez que llamamos a "LD" tiene que volver al inicio
                while(existeSiguiente(c)){
                    if(siguienteDatos(c, nombre_dep, eDP, supDep, numDepDP, esDep)){
                        if(supDep == nombre_e && esDep){  //si su superior es igual al nombre del evento, es que depende de él
                            g << "[" << i << " -> " << nombre_dep << " -de-> " << supDep << " ;;; " << numDepDP << " ] --- " << descripcion(eDP) << " --- ( " << suPrioridad(eDP) << " ) ;;;;" << endl;
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
                if(siguienteDatos(c, nombre_e, e, supDep, numDep, esDep)){
                    if(esDep){
                        g << "[ " << nombre_e <<  " -de-> " << supDep << " ;;; " << numDep << " ] --- " << descripcion(e) << " --- " << "( " << suPrioridad(e) << " )" << endl;
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
