/*Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

#include <iostream>
#include <fstream>
#include "./colecInterdep.hpp" 

int main(){
    ifstream f;
    ofstream g;

    char instruccion;
    string nombre_e, descripcion_e, dependencia, padre, prioridad;
    int prio;
    f.open("entrada.txt");  
    g.open("salia.txt");
    while (f >> instruccion){
        switch( instruccion){
            case 'A':
                getline(f, nombre_e);
                getline(f, descripcion_e);
                getline(f, prioridad);
                prio = stoi(prioridad);
                getline(f, dependencia);
                getline(f, padre);
                
                if(dependencia == "INDependiente"){
                    aniadirIndependiente(colecIndep<T>& c, nombre_e, v );//falta añador el evento y la coleccion que para eso hay que crear ambos y es tu chamba
                }else{

                }
                g << "introducido [ " << nombre_e << " ]  --- " << descripcion_e << " --- ( " << prio << " )" << endl;
                g << "[ nombre -de-> " << padre << " ]  --- " << " --- ( "   << " )" << endl; //aqui nos faltan funciones para poder terminarlo 

            case 'C':

            case 'D':

            case 'O':

            case 'E':
                getline(f, nombre_e);

            case 'I':

            case 'B':

            case 'LD':

            case 'LT':
                g << "-----LISTADO: " << tamanio(T) <<endl;
                g << "[ " << nombre_e << " --- numdepend"<< " ]  --- " << descripcion_e << " --- ( " << prio << " )" << endl;
                g << "-----";
            default:

        }
    }
    f.close();
    g.close();
}

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
