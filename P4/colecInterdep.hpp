/* Razvan Ghita calangiu 927460, Rodrigo Herce Alonso 935413
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

#include <iostream>
using namespace std;
#include "pilaDinamica.hpp"

// PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)


/*
* Los valores del TAD genérico colecInterdep representan colecciones de elementos formados como tuplas
* de la forma (id, v, -, numDep) o bien (id, v, sup, numDep), de tal forma que 
* no podrá haber 2 elementos con el mismo identificador id. A los elementos con forma (id, v, -, numDep)
* los llamaremos en general ‘elementos independientes’, mientras que a los elementos con forma (id, v, sup, numDep),
* los llamaremos en general ‘elementos dependientes’. Todas las operaciones tendrán coste O(N), siendo N el número de elementos. 
* Equivalentemente, el coste en memoria tambien sera O(N). En las tuplas que representan elementos dependientes,
* la información sup será la identificación del elemento del que es directamente dependiente el elemento con identificación
* id. Ningún elemento de la colección podrá ser directamente dependiente de sí mismo, y todo
* elemento dependiente debe serlo de otro elemento que exista en la colección (que a su vez puede
* ser un elemento independiente o dependiente). En cada elemento, la información numDep de su tupla representará
* el número total de elementos en la colección que son directamente dependientes del elemento con identificador id, y que
* será 0 si ningún elemento de la colección depende de dicho elemento. 
* 
* El parámetro formal I es necesario que tenga definidas las operaciones igual y anterior, que definen una relación de orden total.
* Por ejemplo, permiten organizar los datos de la colección en forma de secuencia ordenada.
*
*   bool igual(I e1, I e2) devuelve verdadero si y solo si el elemento e1 es igual al elemento e2.
*   bool anterior(I e1, I e2) devuelve verdadero si y solo si el elemento e1 es anterior (menor) que el elemento e2.
*
*/
template<typename I, typename V> struct colecInterdep;

/*
* Crea un colección c vacía, sin elementos.
*/
template<typename I, typename V> void crear(colecInterdep<I,V>& c);

/*
* Devuelve el número de elementos que hay en la colección c.
*/
template<typename I, typename V> int tamanio(colecInterdep<I,V>& c);

/*
* Devuelve verdad si y solo si la colección c no contiene ningún elemento.
*/
template<typename I, typename V> bool esVacia(colecInterdep<I,V>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento con un identificador igual a id.
*/
template<typename I, typename V> bool existe(I id, colecInterdep<I,V>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo identificador sea igual a id,
* es decir un elemento de la forma (id, v, sup, numDep).
*/
template<typename I, typename V> bool existeDependiente(I id, colecInterdep<I,V>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo identificador sea igual a id, 
* es decir un elemento de la forma (id, v, -, numDep).
*/
template<typename I, typename V> bool existeIndependiente(I id, colecInterdep<I,V>& c);

/*
* Si el identificador id no existe en la coleccion c, devuelve una colección igual a la resultante de añadir a la colección c 
* el elemento independiente de la forma (id,v,-,0), siendo id su identificacion y v su valor.
* En caso contrario, devuelve una colección igual a c.
*/
template<typename I, typename V> void aniadirIndependiente(colecInterdep<I,V>& c, I id, V v);

/*
* Si el identificador id no existe en la coleccion c y el identificador sup sí que existe en la coleccion c,
* devuelve una colección igual a la resultante de:
* incrementar en 1 el número de elementos dependientes del elemento con identificador sup en c y
* añadir el elemento de la forma (id,v,sup,0) a la colección c. En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void aniadirDependiente(colecInterdep<I,V>& c, I id, V v, I sup);

/*
* Si el identficador id es diferente al identificador sup, existe el identificador sup en la colección c y además el elemento
* con identificador id es dependiente de forma (id, v, superAnt, numDep), devuelve una colección igual a la resultante de:
*   - incrementar en 1 el número de elementos dependientes del elemento con identificador sup en c,
*   - decrementar en 1 el número de elementos dependientes del elemento con identificador superAnt en c,
*   - sustituir el elemento (id, v, superAnt, numDep) por el elemento (id, v, sup, numDep) en c.
*
* Si el identficador id es diferente al identificador sup, existe el identificador sup en la colección c y además el elemento
* con identificador id es independendiente de forma (id, v, -, numDep), devuelve una colección igual a la resultante de:
*   - incrementar en 1 el número de elementos dependientes del elemento con identificador sup en c,
*   - sustituir en c el elemento (id, v, -, numDep) por el elemento (id, v, sup, numDep).
*
* En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void hacerDependiente(colecInterdep<I,V>& c, I id, I sup);

/*
* Si el elemento con identificador id existe en la coleccion c y además dicho elemento es dependiente, de la forma (id, v, sup, numDep).
* devuelve una colección igual a la resultante de:
*   - establecer el identificador del supervisor (sup) del elemento con identificador id como vacío (‘-’),
*   - decrementar en 1 el número de dependientes del antiguo supervisor (sup) del elemento con identificador id.
* En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void hacerIndependiente(colecInterdep<I,V>& c, I id);

/*
*Operación parcial -> la operación no está definida si no el elemento con identificador id no existe en la coleccion c.
* Si el elemento con identificador id existe en la coleccion c, modifica la coleccion actual de tal manera que actualiza
* el valor del elemento con identificador id en la coleccion c con el valor v.
* En caso contrario, no se modifica la coleccion c y se mantiene igual que antes.
* Devuelve verdadero si la actualización se ha realizado con éxito y falso en caso contrario.
*/
template<typename I, typename V> bool actualizarVal(colecInterdep<I,V>& c, I id, V v);

/*
*Operación parcial -> la operación no está definida si no el elemento con identificador id no existe en la coleccion c.
* Si el elemento con identificador id existe en la coleccion c, guarda en val el valor asociado al elemento con identificador id
* en la coleccion c y devuelve verdadero.
* En caso contrario, no se modifica nada y devuelve falso.
*/
template<typename I, typename V> bool obtenerVal(I id, colecInterdep<I,V>& c, V& val);

/*
*Operación parcial -> la operación no está definida si el elemento con identificador id no es dependiente de la forma (id, v, sup, numDep).
* Si el elemento con identificador id existe en la coleccion c y además dicho elemento es dependiente de la forma (id, v, sup, numDep),
* modifica sup para que contenga el identificador de su supervisor y devuelve verdadero.
* En cualquier otro caso (si no existe o es independiente), no modifica nada y devuelve falso.
*/
template<typename I, typename V> bool obtenerSupervisor(I id, colecInterdep<I,V>& c, I& sup);

/*
*Operación parcial -> la operación no está definida si no el elemento con identificador id no existe en la coleccion c.
* Si el elemento con identificador id existe en la coleccion c, modifica numDep con el número de elementos dependientes del elemento
* con identificador id en la coleccion c y devuelve verdadero.
* En caso contrario, no modifica nada y devuelve falso.
*/
template<typename I, typename V> bool obtenerNumDependientes(I id, colecInterdep<I,V>& c, unsigned& numDep);

/*
* Si existe el elemento con identificador id en la colección c y dicho elemento es dependiente de la forma (id, v, sup, numDep),
* tal que numDep es el número de elementos dependientes del elemento con identificador id y es igual a 0, entonces:
* modifica la colección de tal forma que tenemos una colección igual a la resultante de: 
*   - decrementar en 1 el número de elementos dependientes (numDep) del elemento con identificador sup.
*   - eliminar el elemento (id, v, sup, numDep), en la colección c.
*
* Si existe el elemento con identificador id en la colección c y dicho elemento es independiente de la forma (id, v, -, numDep),
* tal que numDep es el número de elementos dependientes del elemento con identificador id y es igual a 0, entonces:
* modifica la colección de tal forma que tenemos una colección igual a la resultante de:
*   - eliminar el elemento (id, v, sup, numDep), en la colección c.
*
* En cualquier otro caso, mantiene una coleccion igual a c.
*/
template<typename I, typename V> void borrar(I id, colecInterdep<I,V>& c);

//Operacion auxiliar que agrupa las funciones de obtenerNumDependientes, obtenerSupervisor y obtenerVal
/*
* Si existe el elemento con identificador id en la coleccion c, devuelve verdadero si y solo si ha podido obtener
* todos los datos relacionados al elemento con identificador id. Si el elemento no existe en la colección, es que no 
* puede obtener sus datos entonces devuelve falso y no modifica nada. 
*/
template<typename I, typename V> bool obtenerDatos(I id, unsigned& numDep, I& sup, V& v, colecInterdep<I,V>& c, bool &esDep);

//Operaciones privadas

/*
*/
template<typename I, typename V> bool existe2(I id, typename colecInterdep<I,V>::celdaColec* abb);

/*
*/
template<typename I, typename V> typename colecInterdep<I,V>::celdaColec* buscar(I id, typename colecInterdep<I,V>::celdaColec* abb);

/*
*/
template<typename I, typename V> void introducirIndep(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c);
/*
*/
template<typename I, typename V> void introducirDep(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup);


//Operaciones iterador

/*
* Inicializa el iterador para recorrer los elementos de la colección c, de forma que el siguiente
* elemento a visitar sea el que tiene un identificador anterior a los de todos los demás elementos de la
* colección, que se corresponde con la situación de no haber visitado ningún elemento. 
*/
template<typename I, typename V> void iniciarIterador(colecInterdep<I,V>& c);

/*
* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección c, devuelve
* falso si ya se ha visitado el último elemento.
*/
template<typename I, typename V> bool existeSiguiente(colecInterdep<I,V>& c);

/*
* Si aún queda algun elemento por visitar, devuelve el identificador del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con identificador anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> bool siguienteIdent(colecInterdep<I,V>& c, I &id);

/*
* Si aún queda algun elemento por visitar, devuelve el valor del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con identificador anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> bool siguienteVal(colecInterdep<I,V>& c, V &valor);

/*
* Si aún queda algun elemento por visitar, si el siguiente elemento a visitar con el iterador de la colección,
* que será el elemento no visitado con identificador anterior a los de todos los demás aún no visitados,
* es independiente de la forma (id, v, -, numDep) devuelve falso, 
* pero si dependiente es de la forma (id, v, sup, numDep) devuelve verdad. 
*/
template<typename I, typename V> bool siguienteDependiente(colecInterdep<I,V>& c);

/*
* Si aún queda algun elemento por visitar y dicho elemento es dependiente de la forma (id, v, sup, numDep),
* si el siguiente elemento a visitar con el iterador de la colección, que será el elemento no visitado con identificador anterior
* a los de todos los demás aún no visitados, es dependiente de la forma (id, v, sup, numDep), devuelve el identificador de sup.
*/
template<typename I, typename V> bool siguienteSuperior(colecInterdep<I,V>& c, I &sup);

/*
* Si aún queda algun elemento por visitar, devuelve el numero de elementos dependientes del elemento con identificador id (numDep)
* del siguiente elemento a visitar con el iterador de la colección c, que será el elemento no visitado con
* identificador anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> bool siguienteNumDependientes(colecInterdep<I,V>& c, unsigned &numDep);

/*
* Si aún queda algun elemento por visitar, avanza el iterador de la colección c para que se pueda visitar otro elemento.
*/
template<typename I, typename V> void avanza(colecInterdep<I,V>& c);

// FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)


// DECLARACION DEL TAD GENERICO colecInterdep

template<typename I, typename V>
struct colecInterdep{
    friend void crear<I,V>(colecInterdep<I,V>& c);
    friend int tamanio<I,V>(colecInterdep<I,V>& c);
    friend bool esVacia<I,V>(colecInterdep<I,V>& c);
    friend bool existe<I,V>(I id, colecInterdep<I,V>& c);
    friend bool existeDependiente<I,V>(I id, colecInterdep<I,V>& c);
    friend bool existeIndependiente<I,V>(I id,colecInterdep<I,V>& c);
    friend void aniadirIndependiente<I,V>(colecInterdep<I,V>& c, I id, V v);
    friend void aniadirDependiente<I,V>(colecInterdep<I,V>& c, I id,V v, I sup);
    friend void hacerDependiente<I,V>(colecInterdep<I,V>& c, I id, I sup);
    friend void hacerIndependiente<I,V>(colecInterdep<I,V>& c, I id);
    friend bool actualizarVal<I,V>(colecInterdep<I,V>& c, I id, V v);
    friend bool obtenerVal<I,V>(I id, colecInterdep<I,V>& c, V& val);
    friend bool obtenerSupervisor<I,V>(I id, colecInterdep<I,V>& c, I& sup);
    friend bool obtenerNumDependientes<I,V>(I id, colecInterdep<I,V>& c, unsigned& numDep);
    friend void borrar<I,V>(I id, colecInterdep<I,V>& c);
    //Operacion auxiliar
    friend bool obtenerDatos<I,V>(I id, unsigned& numDep, I& sup, V& v, colecInterdep<I,V>& c, bool &esDep);
    //Operaciones privadas
    /* Operaciones iterador */

    friend void iniciarIterador<I,V>(colecInterdep<I,V>& c);
    friend bool existeSiguiente<I,V>(colecInterdep<I,V>& c);
    friend bool siguienteIdent<I,V>(colecInterdep<I,V>& c, I &id);
    friend bool siguienteVal<I,V>(colecInterdep<I,V>& c, V &valor);
    friend bool siguienteDependiente<I,V>(colecInterdep<I,V>& c);
    friend bool siguienteSuperior<I,V>(colecInterdep<I,V>& c, I &sup);
    friend bool siguienteNumDependientes<I,V>(colecInterdep<I,V>& c, unsigned &numDep);
    friend void avanza<I,V>(colecInterdep<I,V>& c);
    
  private: //declaracion de la representacion interna del tipo

  /*
  * La implementación de este TAD genérico se hace a partir de un diccionario formado por los pares <ident, valor>, siendo ident la clave
  * única y permanente (no se puede modificar ni duplicar) y siendo valor el valor (contando con funciones para consultarlo y modificarlo).
  * El diccionario está implementado en memoria dinámica utilizando una lista enlazada simple de celdas del tipo celdaColec. Dicho 
  * diccionario ocupa en memoria O(n), siendo n el número total de celdas que tiene. Además, el coste de todas las operaciones también
  * tiene coste O(n), siendo n el número total de celdas. Cada celda del diccionario contendrá una clave de tipo I, un valor de tipo V,
  * un puntero al elemento del que es dependiente (si no depende de nadie este puntero apuntará a nullptr), un natural correspondiente
  * al número de elementos dependientes que tiene este elemento y un puntero a la siguiente celda para encadenar la lista (si es el último apunta a nullptr).
  * 
  * Además, el diccionario cuenta con un entero llamado tamanio que registra el número de celdas que tiene actualmente el diccionario,
  * un puntero llamado primero que como su nombre indica apunta al primer elemento de la lista (si n hay ningún elemento apunta a nullptr) y
  * un puntero llamado iter que se utilizará únicamente para mantener el estado del iterador y *solo* será usado por las operaciones del iterador.
  */
    
    struct celdaColec{  //{cada elemento de la colección se almacena en una celda}
        I ident;            //ident es de tipo genérico y en este caso contiene la cadena correspondiente al nombre del evento 
        V valor;            //valor es de tipo genérico, en este caso lo utilizaremos con el TAD evento
        celdaColec* sup;    //sup es un puntero de tipo celdaColec que apunta al evento del que depende, si es independientes apunta a nullptr 
        unsigned numDep;    //numDep contiene el natural correspondiente el numero de eventos dependientes de este
        celdaColec* izq;
        celdaColec* der;   //izq y der son punteros de tipo celdaColec que apuntan a los hijos de un nodo
    };

    int tamanio;                    //tamanio contiene el entero correspodiente al número de celdas del árbol
    celdaColec* raiz;               //raíz es un puntero a la primera celda del árbol
    Pila<celdaColec*> iter;         //iter es una pila que almacena punteros para realizar las operaciones del iterador

    friend bool existe2<I,V>(I id, typename colecInterdep<I,V>::celdaColec* abb);
    friend typename colecInterdep<I,V>::celdaColec* buscar<I,V>(I id, typename colecInterdep<I,V>::celdaColec* abb);
    friend void introducirIndep<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c);
    friend void introducirDep<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup);

};

//Operaciones auxiliares
/*
*/
template<typename I, typename V>
typename colecInterdep<I,V>::celdaColec* buscar(I id, typename colecInterdep<I,V>::celdaColec* abb){
    if(abb == nullptr){
        return nullptr;
    } else {
        if(id < abb->ident){
            return buscar<I,V>(id, abb->izq);
        } else if(id > abb->ident){
            return buscar<I,V>(id, abb->der);
        } else {
            return abb;
        }
    }
}

// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colecInterdep

/*
* Crea un colección vacía, sin elementos. Todos los punteros a nullptr y el tamaño a 0.
*/
template<typename I, typename V>
void crear(colecInterdep<I,V>& c){
    c.raiz = nullptr;
    c.tamanio = 0;
    crearVacia(c.iter); //por seguridad
}

/*
* Devuelve el número de elementos que hay en la colección c.
*/
template<typename I, typename V>
int tamanio(colecInterdep<I,V>& c){
    return c.tamanio;
}

/*
* Devuelve verdad si y solo la colección si c no contiene ningún elemento.
*/
template<typename I, typename V> 
bool esVacia(colecInterdep<I,V>& c){
    return c.tamanio == 0;
}

/*
*/
template<typename I, typename V>
bool existe2(I id, typename colecInterdep<I,V>::celdaColec* abb){
    if(abb == nullptr){
        return false;
    } else {
        if(id < abb->ident){
            return existe2<I,V>(id, abb->izq);
        } else if(id > abb->ident){
            return existe2<I,V>(id, abb->der);
        } else {
            return true;
        }
    }
}

/*
* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id. Si la coleccion c es vacía es imposible que exista,
* si no es vacía, avanzamos hasta que encontremos la celda que tenga su identificador igual a id o lleguemos al final.
*/
template<typename I, typename V>
bool existe(I id, colecInterdep<I,V>& c){
    return existe2<I,V>(id, c.raiz);
}



/*
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id. Si la colleción es vacia
* es imposible que exista, si no es vacía, avanzamos hasta encontrar la celda con ident igual a id o llegar al final.
* Si el puntero a sup de la celda encontrada es distinto de nullptr, es que es dependiente de alguien y devolvemos true 
* sino devolvemos false.
*/
template<typename I, typename V>
bool existeDependiente(I id, colecInterdep<I,V>& c){
    typename colecInterdep<I,V>::celdaColec* pDep = buscar<I,V>(id, c.raiz);
    if(pDep == nullptr){
        return false;
    } else if(pDep->sup == nullptr){
        return false;
    } else {
        return true;
    }
    
}

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id. Si la colleción es vacia
* es imposible que exista, si no es vacía, avanzamos hasta encontrar la celda con ident igual a id o llegar al final.
* Si el puntero a sup de la celda encontrada es nullptr, es que es independiente y devolvemos true sino devolvemos false.
*/
template<typename I, typename V>
bool existeIndependiente(I id, colecInterdep<I,V>& c){
    typename colecInterdep<I,V>::celdaColec* pIDep = buscar<I,V>(id, c.raiz);
    if(pIDep == nullptr){
        return false;
    } else if(pIDep->sup == nullptr){
        return true;
    } else {
        return false;
    }
}

/*
*/
template<typename I, typename V>
void introducirIndep(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c){
    if(abb == nullptr){
        abb = new typename colecInterdep<I,V>::celdaColec;
        abb->der = nullptr;
        abb->izq = nullptr;
        abb->ident = id;
        abb->valor = v;
        abb->numDep = 0;
        abb->sup = nullptr;
        c.tamanio++;
    } else if(id < abb->ident){
        introducirIndep<I,V>(abb->izq, id, v, c);
    } else if(id > abb->ident){
        introducirIndep<I,V>(abb->der, id, v, c);
    } 
    //else no hace nada porque no puede haber claves repetidas
}

/*
* Bucamos la posicion en la que tenemos que añadir el nuevo elemento y guardamos tambien la posicion anterior, 
* una vez encontrado se pone el puntero siguiente apuntando a la siguiente celda. Posteriormente creamos la nueva 
* celda y ponemos como puntero de la anterior a esta nueva y de la nueva celda de puntero ponemos siguiente.
*  Finalmente sumamos 1 a tamanio.
*/
template<typename I, typename V> 
void aniadirIndependiente(colecInterdep<I,V>& c, I id, V v){

    introducirIndep<I,V>(c.raiz, id, v, c);
    
}

/*
*/
template<typename I, typename V>
void introducirDep(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup){
    if(abb == nullptr){
        abb = new typename colecInterdep<I,V>::celdaColec;
        abb->der = nullptr;
        abb->izq = nullptr;
        abb->ident = id;
        abb->valor = v;
        abb->numDep = 0;
        abb->sup = sup;
        abb->sup->numDep++;
        c.tamanio++;
    } else if(id < abb->ident){
        introducirDep<I,V>(abb->izq, id, v, c, sup);
    } else if(id > abb->ident){
        introducirDep<I,V>(abb->der, id, v, c, sup);
    } 
    //else no hace nada porque no puede haber claves repetidas
}

/*
* Bucamos la posicion en la que tenemos que añadir el nuevo elemento a la vez comprobamos si pasamos por el padre
* en caso de encontrar el padre simplemente lo gusrdamos y seguimos buscando al hijo, sino al encontrar el hijo 
* seguimos iterando en busca del padre. Si encontramos al padre entonces creamos la nueva celda con sus valores y 
* en el puntero sup ponemos un puntero al padre. Finalmente sumamos 1 a tamanio.
*/
template<typename I, typename V> 
void aniadirDependiente(colecInterdep<I,V>& c, I id, V v, I sup){
    typename colecInterdep<I,V>::celdaColec* superior = buscar<I,V>(sup, c.raiz);
    if(superior != nullptr){introducirDep<I,V>(c.raiz, id, v, c, superior);}
}

/*
* Primero comprobamos que el id del elemento que queremos añadir no es igual al de su nuevo padre para evitar 
* posibles fallos. Posteriormente recorremos la lista en busca de id o de el nuevo sup. En caso de encontar primero
* id seguimos recorriendo en busca del id, sino seguimos recorriendo en busca de sup. Una vez terminada de recorrer
* la lista compruebas si es porque encuentra ambos o por si no existe alguno, en caso de que no existe devuelve la
* colección original. Posteriormente si id era independiente se pone sup como padre y se suma a sup numDep y sino 
* hace lo mismo pero antes resta a el antiguo sup (accediendo desde el puntero) numDep en uno.
*/
template<typename I, typename V> 
void hacerDependiente(colecInterdep<I,V>& c, I id, I sup){
    typename colecInterdep<I,V>::celdaColec* superior = buscar<I,V>(sup, c.raiz);
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);

    if(nodo->sup == nullptr){   //significa que era independiente antes por tanto si que podemos hacerlo dependiente
        nodo->sup = superior;
        superior->numDep++;
    }
}

/*
* Recorre la lista en busca de id. Si lo encuentra decrementa numDep de sup en uno y pone sup de id en null, sino 
* lo encuentra devuelve la coleccion original. 
*/
template<typename I, typename V> 
void hacerIndependiente(colecInterdep<I,V>& c, I id){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);

    if(nodo->sup != nullptr){   //significa que era dependiente por tanto lo hacemos independiente
        nodo->sup->numDep--;
        nodo->sup = nullptr;
    }
}

/*
* Si la colección c no es vacía:
* Recorre la lista en busca de id. Si lo encuentra actualiza el valor v y devuelve true, sino devuelve false.
* Es una operación parcial porque si no existe id no puede actualizar su valor.
*/
template<typename I, typename V> 
bool actualizarVal(colecInterdep<I,V>& c, I id, V v){
    ;
}

/*
* Si la colección c no es vacía:
* Recorre la lista en busca de id. Si lo encuentra pone el valor de id en la variable val la cual esta pasada
* por referencia para posteriormente poder recuperar el valor y devuelve true, sino devuelve false.
* Es una operación parcial porque si no existe id no puede obtener su valor.
*/
template<typename I, typename V> 
bool obtenerVal(I id, colecInterdep<I,V>& c, V& val){
    if(esVacia(c)){
        return false;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){        //si llegamos hasta el final significa que no existe (se puede optimizar este bucle con 1 solo if en verdad)
            return false;
        } else if(aux1 != nullptr && aux1->ident == id){    //comprobamos que realmente estamos en el caso que queremos estar
            val = aux1->valor;     //devolvemos el valor y actualizamos error a falso
            return true;
        } else {
            return false;
        }
    }
    return false;
}

/*
* Si la colección c no es vacía:
* Recorre la lista en busca de id. Si lo encuentra y es dependiente pone el identificador de su sup en la variable sup
* la cual esta pasada por referencia para posteriormente poder recuperar el valor y devuelve true, sino devuelve false.
* Es una operación parcial porque si no existe id o no es dependiente no puede obtener su supervisor.
*/
template<typename I, typename V> 
bool obtenerSupervisor(I id, colecInterdep<I,V>& c, I& sup){
    if(esVacia(c)){
        return false;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){       //si llegamos hasta el final significa que no existe (se puede optimizar este bucle con 1 solo if en verdad)
            return false;
        } else if(aux1 != nullptr && aux1->ident == id && aux1->sup != nullptr){ //comprobamos que la celda existe y es dependiente
            sup = aux1->sup->ident;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

/*
* Si la colección c no es vacía:
* Recorre la lista en busca de id. Si lo encuentra pone el valor de numDep en la variable numDep la cual esta pasada
* por referencia para posteriormente poder recuperar en valor y devuelve true, sino devuelve false.
* Es una operación parcial porque si no existe id no puede obtener su número de dependientes.
*/
template<typename I, typename V> 
bool obtenerNumDependientes(I id, colecInterdep<I,V>& c, unsigned& numDep){
    if(esVacia(c)){
        return false;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){       //si llegamos hasta el final significa que no existe (se puede optimizar este bucle con 1 solo if en verdad)
            return false;
        } else if(aux1 != nullptr && aux1->ident == id){ //comprobamos que la celda existe y es dependiente
            numDep = aux1->numDep;
            return true;
        } else {
            return false;
        }

    }
    return false;
}

/*
* Recorre la lista en busca de id con un puntero una celda por detras. Cuando encuentra id si es dependiente 
* resta numDep de sup en uno. A la celda anterior le ponemos como sig a el nodo al que apunta id, finalmente 
* borramos id y decrementamos tamanio en uno.
*/
template<typename I, typename V> 
void borrar(I id, colecInterdep<I,V>& c){
    if(!esVacia(c)){
        typename colecInterdep<I,V>::celdaColec* ante = nullptr; 
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;

        while(aux1 != nullptr && aux1->ident < id){
            ante = aux1;    
            aux1 = aux1->sig; 
        }

        if(aux1 != nullptr && aux1->ident == id && aux1->numDep == 0){ //si lo encontramos
            
            if(aux1->sup != nullptr){   //si es dependiente decrementamos en 1 los numDep del superior ANTES DE BORRAR MIRA EL ENUNCIADO
                aux1->sup->numDep--;
            }
            
            //es el que queremos borrar
            if(ante == nullptr){ //es el primero
                c.primero = aux1->sig;
            }else{
                ante->sig =  aux1->sig;
            }
        
            delete aux1;
            c.tamanio--;
        } 
    }
}


//Auxiliar
/*
* Si la lista contiene al menos 1 elemento, recorremos la lista hasta encontrar el elemento con identificador igual a id. Una vez
* encontrado, modificamos las variables de tal forma que: numDep ahora contiene el numero de elementos dependientes de nuestro elemento
* con identificador id, v contiene el valor de nuestro elemento con identificador id y sup, si el elemento con ident id es dependiente, contiene
* el identificador del elemento del que depende (su padre) además de que esDep se vuelve verdadero y si es independiente, 
* se devuelve en esDep falso y no hace falta modificar nada mas.
* Devuelve verdadero si y solo si ha podido obtener todos los datos, en caso contrario devuelve falso.
*/
template<typename I, typename V> 
bool obtenerDatos(I id, unsigned& numDep, I& sup, V& v, colecInterdep<I,V>& c, bool &esDep){
    if(esVacia(c)){
        return false;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident < id){
            aux1 = aux1->sig; 
        }

        if(aux1 != nullptr && aux1->ident == id){
            numDep = aux1->numDep;
            v = aux1->valor;
            if(aux1->sup == nullptr){
                esDep = false;
            } else {
                sup = aux1->sup->ident;
                esDep = true;
            }
            return true;
        }
    }
    return false;
}

//OPERACIONES ITERADOR

/*
* Inicializa el iterador haciendo que apunte a la primera celda.
*/
template<typename I, typename V>
void iniciarIterador(colecInterdep<I,V>& c){
    liberar(c.iter);
    typename colecInterdep<I,V>::celdaColec* nodo = c.raiz;
    while(nodo != nullptr){
        apilar(c.iter, nodo);
        nodo = nodo->izq;
    }

}

/*
* Devuelve verdad si el siguiente a el nodo al que apunta el iterador es distinto de nullptr.
*/
template<typename I, typename V>
bool existeSiguiente(colecInterdep<I,V>& c){
    return !(esVacia(c.iter));
}

/*
* Nos devuelve true si y solo si el siguiente nodo al que apunta el iterador existe y puede asignar a id su identificador.
*/
template<typename I, typename V>
bool siguienteIdent(colecInterdep<I,V>& c, I &id){
    bool error = false;
    if(existeSiguiente(c)){   
        typename colecInterdep<I,V>::celdaColec* nodo;
        cima(c.iter, nodo, error);
        if(!error){             //por seguridad porque si existeSiguiente(c) seguro que habrá cima
            id = nodo->ident;
        }
        return true;
    }
    return false;
}

/*
* Nos devuelve true si y solo si el siguiente nodo al que apunta el iterador existe y puede asignar a valor su valor.
*/
template<typename I, typename V>
bool siguienteVal(colecInterdep<I,V>& c, V &valor){
    bool error = false;
    if(existeSiguiente(c)){   
        typename colecInterdep<I,V>::celdaColec* nodo;
        cima(c.iter, nodo, error);
        if(!error){             //por seguridad porque si existeSiguiente(c) seguro que habrá cima
            valor = nodo->valor;
        }
        return true;
    }
    return false;
}

/*
* Nos devuelve true si y solo si el siguiente nodo al que apunta el iterador es dependiente.
*/
template<typename I, typename V> 
bool siguienteDependiente(colecInterdep<I,V>& c){
    bool error = false;
    if(existeSiguiente(c)){   
        typename colecInterdep<I,V>::celdaColec* nodo;
        cima(c.iter, nodo, error);
        if(!error && nodo->sup != nullptr){             //por seguridad porque si existeSiguiente(c) seguro que habrá cima
            return true;    
        }
    }
    return false;
}

/*
* Devuelve verdadero si y solo si el elemento apuntado por el iterador es dependiente y ha copiado en sup el identificador del superior.
*/
template<typename I, typename V>
bool siguienteSuperior(colecInterdep<I,V>& c, I &sup){
    bool error = false;
    if(existeSiguiente(c)){   
        typename colecInterdep<I,V>::celdaColec* nodo;
        cima(c.iter, nodo, error);
        if(!error && nodo->sup != nullptr){             //por seguridad porque si existeSiguiente(c) seguro que habrá cima
            sup = nodo->sup->ident;
            return true;    
        }
    }
    return false;
}

/*
* Devuelve verdadero si y solo si el nodo al que apunta el iterador existe y puede copiar en numDep el número de elementos
* dependientes del elemento apuntado por el iterador.
*/
template<typename I, typename V>
bool siguienteNumDependientes(colecInterdep<I,V>& c, unsigned &numDep){
    bool error = false;
    if(existeSiguiente(c)){   
        typename colecInterdep<I,V>::celdaColec* nodo;
        cima(c.iter, nodo, error);
        if(!error){             //por seguridad porque si existeSiguiente(c) seguro que habrá cima
            numDep = nodo->numDep;
            return true;    
        }
    }
    return false;
}

/*
* Si el siguiente nodo al que apunta el iterador existe, avanza el iterador al siguente nodo.
*/
template<typename I, typename V>
void avanza(colecInterdep<I,V>& c){

    if(existeSiguiente(c)){    
        typename colecInterdep<I,V>::celdaColec* nodo;
        bool error = false;

        cima(c.iter, nodo, error);
        if(!error){
            desapilar(c.iter);
            nodo = nodo->der;

            while(nodo != nullptr){
                apilar(c.iter, nodo);
                nodo = nodo->izq;
            }
        }
        
    }
}

#endif