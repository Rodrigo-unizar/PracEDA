/* Razvan Ghita calangiu 927460, Rodrigo Herce Alonso 935413
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

#include <iostream>
using namespace std;


// PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)


/*
* Los valores del TAD colecInterdep representan colecciones de elementos formados como tuplas
* de la forma (ident, val, -, NumDepend) o bien (ident, val, identSup, NumDepend). A los elementos
* con forma (ident, val, -, NumDepend) los llamaremos en general ‘elementos independientes’,
* mientras que a los elementos con forma (ident, val, identSup, NumDepend), los llamaremos en
* general ‘elementos dependientes’.
* En la colección no podrá haber dos elementos con el mismo ident. Además, se requiere que 
* el género ident tenga definidas las operaciones igual y anterior, que definen una relación de orden total.
* Por ejemplo, permiten organizar los datos de la colección en forma de secuencia ordenada.
* En las tuplas que representan elementos dependientes, la información identSup será la 
* identificación del elemento del que es directamente dependiente el elemento con identificación
* ident. Ningún elemento de la colección podrá ser directamente dependiente de sí mismo, y todo
* elemento dependiente debe serlo de otro elemento que exista en la colección (que a su vez puede
* ser un elemento independiente o dependiente).
* En cada elemento, la información NumDepend de su tupla representará el número total de elementos
* en la colección que son directamente dependientes del elemento con identificador ident, y que
* será 0 si ningún elemento de la colección depende de dicho elemento. 
*/
template <typename T> struct colecInterdep;

/*
* Crea un colección vacía, sin elementos.
*/
template<typename T> void crear(colecInterdep<T>& c);

/*
* Devuelve el número de elementos que hay en la colección c.
*/
template<typename T> int tamanio(colecInterdep<T>& c);

/*
* Devuelve verdad si y solo si la colección c no contiene ningún elemento.
*/
template<typename T> bool esVacia(colecInterdep<T>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.
*/
template<typename T> bool existe(string id, colecInterdep<T>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id, es
* decir un elemento (id, v, idSup, NumDep).
*/
template<typename T> bool existeDependiente(string id, colecInterdep<T>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id, es
* decir un elemento (id, v, -, NumDep).
*/
template<typename T> bool existeIndependiente(string id, colecInterdep<T>& c);

/*
* Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
* independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.
*/
template<typename T> void aniadirIndependiente(colecInterdep<T>& c, string id, T v);


//Operaciones iterador

/*
* Inicializa el iterador para recorrer los elementos de la colección c, de forma que el siguiente
* elemento a visitar sea el que tiene un ident anterior a los de todos los demás elementos de la
* colección (situación de no haber visitado ningún elemento). 
*/
template<typename T> void iniciarIterador(colecInterdep<T>& c);

/*
* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección c, devuelve
* falso si ya se ha visitado el último elemento.
*/
template<typename T> bool existeSiguiente(colecInterdep<T>& c);

/*
* Si existeSiguiente(c), devuelve el ident del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename T> string siguienteIdent(colecInterdep<T>& c);

/*
* Si existeSiguiente(c), devuelve el valor del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename T> T siguienteVal(colecInterdep<T>& c);

/*
* Si existeSiguiente(c), si el siguiente elemento a visitar con el iterador de la colección,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados,
* es de la forma (ident, val, -, numDep) devuelve falso, pero si es de la forma (ident, val, identSup, numDep) devuelve verdad. 
*/
template<typename T> bool siguienteDependiente(colecInterdep<T>& c);

/*
* Si existeSiguiente(c) y siguienteDependiente(c), si el siguiente elemento a visitar con el iterador
* de la colección, que será el elemento no visitado con ident anterior a los de todos los demás aún
* no visitados, es de la forma (ident, val, identSup, numDep), devuelve su identSup.
*/
template<typename T> string siguienteSuperior(colecInterdep<T>& c);

/*
* Si existeSiguiente(c), devuelve el NumDep del siguiente elemento a visitar con el iterador de la colección c, que
* será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename T> unsigned siguienteNumDependientes(colecInterdep<T>& c);

/*
* Si existeSiguiente?(c), avanza el iterador de la colección c para que se pueda visitar otro elemento.
*/
template<typename T> void avanza(colecInterdep<T>& c);

// FIN predeclaracion del TAD GENERICO agrupacion (Fin INTERFAZ)


// DECLARACION DEL TAD GENERICO agrupacion

template<typename T>
struct colecInterdep{
    friend void crear<T>(colecInterdep<T>& c);
    friend int tamanio<T>(colecInterdep<T>& c);
    friend bool esVacia<T>(colecInterdep<T>& c);
    friend bool existe<T>(string id, colecInterdep<T>& c);
    friend bool existeDependiente<T>(string id, colecInterdep<T>& c);
    friend bool existeIndependiente<T>(string id,colecInterdep<T>& c);
    friend void aniadirIndependiente<T>(colecInterdep<T>& c, string id, T v);

    //Operaciones iterador

    friend void iniciarIterador<T>(colecInterdep<T>& c);
    friend bool existeSiguiente<T>(colecInterdep<T>& c);
    friend string siguienteIdent<T>(colecInterdep<T>& c);
    friend T siguienteVal<T>(colecInterdep<T>& c);
    friend bool siguienteDependiente<T>(colecInterdep<T>& c);
    friend string siguienteSuperior<T>(colecInterdep<T>& c);
    friend unsigned siguienteNumDependientes<T>(colecInterdep<T>& c);
    friend void avanza<T>(colecInterdep<T>& c);
    
  private: //declaracion de la representacion interna del tipo
    
    struct celdaColec{  //{cada elemento de la colección se almacena en una celda}
        string ident;       //ident contiene la cadena correspondiente al nombre del evento 
        T valor;            //valor es de tipo genérico, en este caso lo utilizaremos con el TAD evento
        string sup;         //sup contiene la cadena correspodiente al nombre del evento superior (del que depende este), si no depende (-) 
        unsigned numDep;    //numDep contiene el natural correspondiente el numero de eventos dependientes de este
        celdaColec* sig;    //sig es un puntero dirigido a la siguiente celda de la lista enlazada
    };

    int tamanio;            //tamanio contiene el entero correspodiente al número de celdas de la lsita
    celdaColec* primero;    //primero es un puntero a la primera celda de la lista
    celdaColec* iter;       //iter es un puntero encargado de las operaciones del iterador

};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colecInterdep

/*
* Crea un colección vacía, sin elementos.
*/
template<typename T>
void crear(colecInterdep<T>& c){
    c.primero = nullptr;
    c.tamanio = 0;
    //c.iter = nullptr; podriamos ponerlo por seguridad pero lo q veas
}

/*
* Devuelve el número de elementos que hay en la colección c.
*/
template<typename T> 
int tamanio(colecInterdep<T>& c){
    return c.tamanio;
}

/*
* Devuelve verdad si y solo la colección si c no contiene ningún elemento.
*/
template<typename T> 
bool esVacia(colecInterdep<T>& c){
    return c.tamanio == 0;
}

/*
* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.
*/
template <typename T> 
bool existe(string id, colecInterdep<T>& c){
    if(esVacia(c)){
        return false;
    }else {
        typename colecInterdep<T>::celdaColec* aux = c.primero;
        while(aux != nullptr){
            if(aux->ident == id){
                return true;
            }
            aux = aux->sig;
        }
        return false;
    }
}

/*
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id, es
* decir un elemento (id, v, idSup, NumDep).
*/
template<typename T> 
bool existeDependiente(string id, colecInterdep<T>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id, es
* decir un elemento (id, v, -, NumDep).
*/
template<typename T>
bool existeIndependiente(string id,colecInterdep<T>& c);

/*
* Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
* independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.
*/
template<typename T> 
void aniadirIndependiente(colecInterdep<T>& c, string id, T v){
    if(!existe(id, c)){
        if(esVacia(c)){    //no hay ninguna
            c.primero = new typename colecInterdep<T> :: celdaColec;

            c.primero->ident = id;
            c.primero->valor = v;
            c.primero->sig = nullptr;
            c.primero->sup = "-";
            c.primero->numDep = 0;

            c.tamanio ++;
        } else {
            typename colecInterdep<T>::celdaColec* aux1 = c.primero;

            if(id < aux1->ident){
                //añadir antes del primero
                c.primero = new typename colecInterdep<T> :: celdaColec;
                c.primero->ident = id;
                c.primero->valor = v;
                c.primero->sig = aux1;
                c.primero->sup = "-";
                c.primero->numDep = 0;

            } else {  //añadir despues del primero
                typename colecInterdep<T>::celdaColec* aux2 = aux1->sig;
                while(aux2 !=nullptr && id > aux2->ident){ //primero hay que comprobar que aux2 != nullptr para no acceder si lo fuera
                    aux1 = aux1->sig;
                    aux2 = aux2->sig;
                }
                aux1->sig = new typename colecInterdep<T> :: celdaColec;
                aux1->sig->ident = id;
                aux1->sig->valor = v;
                aux1->sig->sig = aux2;
                aux1->sig->sup = "-";
                aux1->sig->numDep = 0;
            }
            c.tamanio ++;
        }
    }
}

/*
    if(esVacia(c)){
        c.primero = new typename colecInterdep<T> :: celdaColec;

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

        typename colecInterdep<T>::celdaColec* aux = new typename colecInterdep<T>::celdaColec;

        aux->ident = id;
        aux->valor = v;
        aux->sig = c.iter->sig; //Hago que apunte al siguiente elemento
        aux->sup = "-";
        aux->numDep = 0;

        c.iter->sig = aux; //Hago que el anterior apunte a el nuevo
    }

    return;
    */


//OPERACIONES ITERADOR

/*
* Inicializa el iterador para recorrer los elementos de la colección c, de forma que el siguiente
* elemento a visitar sea el que tiene un ident anterior a los de todos los demás elementos de la
* colección (situación de no haber visitado ningún elemento). 
*/
template<typename T> 
void iniciarIterador(colecInterdep<T>& c){
    c.iter = c.primero;
    return;
}

/*
* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección c, devuelve
* falso si ya se ha visitado el último elemento.
*/
template<typename T> 
bool existeSiguiente(colecInterdep<T>& c){
    return c.iter != nullptr;
}

/*
* Si existeSiguiente(c), devuelve el ident del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename T> 
string siguienteIdent(colecInterdep<T>& c){
    if(existeSiguiente(c)){   
        //typename colecInterdep<T>::celdaColec* aux = c.iter->sig;
        return c.iter->ident;
    }
}

/*
* Si existeSiguiente(c), devuelve el valor del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename T> 
T siguienteVal(colecInterdep<T>& c){
    if(existeSiguiente(c)){
        //typename colecInterdep<T>::celdaColec* aux = c.iter->sig;
        return c.iter->valor;
    }
}

/*
* Si existeSiguiente(c), si el siguiente elemento a visitar con el iterador de la colección,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados,
* es de la forma (ident, val, -, numDep) devuelve falso, pero si es de la forma (ident, val, identSup, numDep) devuelve verdad. 
*/
template<typename T> bool siguienteDependiente(colecInterdep<T>& c){
    if(existeSiguiente(c)){
        return c.iter->sup == "-";
    }
}

/*
* Si existeSiguiente(c) y siguienteDependiente(c), si el siguiente elemento a visitar con el iterador
* de la colección, que será el elemento no visitado con ident anterior a los de todos los demás aún
* no visitados, es de la forma (ident, val, identSup, numDep), devuelve su identSup.
*/
template<typename T> string siguienteSuperior(colecInterdep<T>& c){
    if(siguienteDependiente(c)){
        return c.iter->sup;
    }
}

/*
* Si existeSiguiente(c), devuelve el NumDep del siguiente elemento a visitar con el iterador de la colección c, que
* será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename T> unsigned siguienteNumDependientes(colecInterdep<T>& c){
    if(existeSiguiente(c)){
        return c.iter->numDep;
    }
}

/*
* Si existeSiguiente?(c), avanza el iterador de la colección c para que se pueda visitar otro elemento.
*/
template<typename T> 
void avanza(colecInterdep<T>& c){
    if(existeSiguiente(c)){
        c.iter = c.iter->sig;
    }
    return;
}

#endif