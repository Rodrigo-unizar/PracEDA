/* Razvan Ghita calangiu 927460, Rodrigo Herce Alonso 935413
*/

//So ordena de manor a mayor
#include <iostream>

using namespace std;


#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP


// PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)
template <typename T> struct colecIndep;

template <typename T> void crear(colecIndep<T>& c);

template <typename T> int tamanio(colecIndep<T>& c);

template <typename T> bool esVacia(colecIndep<T>& c);

template <typename T> void aniadirIndependiente(colecIndep<T>& c, string id,T v );

template <typename T> bool existe(string id, colecIndep<T>& c);

template <typename T> bool existeIndependiente(string id,colecIndep<T>& c);

template <typename T> bool existeDependiente(string id, colecIndep<T>& c);

//Operaciones iterador

template <typename T> void iniciarIterador(colecIndep<T>& c);

template <typename T> bool existeSiguiente(colecIndep<T>& c);

template <typename T> string siguienteIdent(colecIndep<T>& c);

template <typename T> T siguienteVal(colecIndep<T>& c);

template <typename T> void avanza(colecIndep<T>& c);



template<typename T>
struct colecIndep{
    friend void crear<T>(colecIndep<T>& c);
    friend int tamanio<T>(colecIndep<T>& c);
    friend bool esVacia<T>(colecIndep<T>& c);
    friend void aniadirIndependiente<T>(colecIndep<T>& c, string id,T v );
    friend bool existe<T>(string id, colecIndep<T>& c);
    friend bool existeIndependiente<T>(string id,colecIndep<T>& c);
    friend bool existeDependiente<T>(string id, colecIndep<T>& c);

    //Operaciones iterador

    friend void iniciarIterador<T>(colecIndep<T>& c);
    friend bool existeSiguiente<T>(colecIndep<T>& c);
    friend string siguienteIdent<T>(colecIndep<T>& c);
    friend string siguienteVal<T>(colecIndep<T>& c);
    friend void avanza<T>(colecIndep<T>& c);
    
  private: 
    
    struct celdaColec{
        string ident;
        T valor;
        string sup;
        int numDep;
        celdaColec* sig;
    };

    int tamanio;
    celdaColec* iter, primero;

};

template <typename T>
void crear(colecIndep<T>& c){
    c.primero = nullptr;
    c.tamanio = 0;
    return;
}

template <typename T> 
int tamanio(colecIndep<T>& c){
    return c.tamanio;
}

template <typename T> 
bool esVacia(colecIndep<T>& c){
    return c.tamanio == 0;
}

template <typename T> 
void aniadirIndependiente(colecIndep<T>& c, string id,T v ){
    
    if(esVacia(c)){
        c.primero = new typename colecIndep<T> :: celdaColec;

        c.primero->ident = id;
        c.primero->valor = v;
        c.primero->sig = nullptr;
        c.primero->sup = "-";
        c.primero->numDep = 0;

        c.tamanio ++;
        return;
    }

    if(existe(id, c)){
        return;
    }else{

        typename colecIndep<T>::celdaColec* aux = new typename colecIndep<T>::celdaColec;

        aux->ident = id;
        aux->valor = v;
        aux->sig = c.iter->sig; //Hago que apunte al siguiente elemento
        aux->sup = "-";
        aux->numDep = 0;

        c.iter->sig = aux; //Hago que el anterior apunte a el nuevo
    }

    return;
}

template <typename T> 
bool existe(string id, colecIndep<T>& c){
    
    iniciarIterador(c);

    while(existeSiguiente(c)){
        if(siguienteIdent(c, id) > id){
            return false;
        }else if(siguienteIdent(c, id) == id){
            return true;
        }else{
            avanza(c);
        }
    }
    return false;
}

template <typename T> bool existeIndependiente(string id,colecIndep<T>& c);

template <typename T> bool existeDependiente(string id, colecIndep<T>& c);

//Operaciones iterador

template <typename T> void iniciarIterador(colecIndep<T>& c){
    c.iter = c.primero;
    return;
}

template <typename T> bool existeSiguiente(colecIndep<T>& c){
    return c.iter != nullptr;
}

template <typename T> 
string siguienteIdent(colecIndep<T>& c){
    if(existeSiguiente(c)){   
        typename colecIndep<T>::celdaColec* aux = c.iter->sig;
        return aux->ident;
    }
}

template <typename T> 
T siguienteVal(colecIndep<T>& c){
    if(existeSiguiente(c)){
        typename colecIndep<T>::celdaColec* aux = c.iter->sig;
        return aux->valor;
    }
}

template <typename T> void avanza(colecIndep<T>& c){
    if(existeSiguiente(c)){
        c.iter = c.iter->sig;
    }
    return;
}

#endif