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
* los llamaremos en general ‘elementos dependientes’. En las tuplas que representan elementos dependientes,
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

/*
*/
template<typename I, typename V> bool borrarAux(typename colecInterdep<I,V>::celdaColec*& abb, I id);

/*
*/
template<typename I, typename V> typename colecInterdep<I,V>::celdaColec* borrarMax(typename colecInterdep<I,V>::celdaColec*& abb);

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
  * La implementación de este TAD genérico se hace a partir de un diccionario pero cuya implementación interna está basada en un abb.
  * Dicho diccionario estáa formado por los pares <ident, valor>, siendo ident la clave única y permanente
  * (no se puede modificar ni duplicar) y siendo valor el valor (contando con funciones para consultarlo y modificarlo).
  * Situándonos en la raíz del árbol, todos los identificadores que están en su subarbol izquierdo son esctrictamente menores que su 
  * propio identificador, además todos los que estén en su subarbol derecho serán estrictamente mayores. Esta lógica también se aplica 
  * para todos los subárboles hijos y sus respectivos hijos. 
  * El diccionario está implementado en memoria dinámica utilizando un árbol binario de búsqueda formado por celdas del tipo celdaColec. 
  * Dicho diccionario ocupa en memoria O(n), siendo n el número total de celdas que tiene. Además, el coste de todas las operaciones también
  * tiene coste O(n), siendo n el número total de celdas. Cada celda del diccionario contendrá una clave de tipo I, un valor de tipo V,
  * un puntero al elemento del que es dependiente (si no depende de nadie este puntero apuntará a nullptr), un natural correspondiente
  * al número de elementos dependientes que tiene este elemento y 2 punteros izq y der que apuntarán respectivamente a los hijos/subarboles
  * izquierdos y derechos respectivamente que a su vez, también seráan árboles binarios de búsqueda.
  * 
  * Además, el diccionario cuenta con un entero llamado tamanio que registra el número de celdas que tiene actualmente el árbol,
  * un puntero llamado primero que como su nombre indica apunta al primer elemento del árbol, la raiz (si no hay ningún elemento apunta a nullptr) y
  * un puntero llamado iter que se utilizará únicamente para mantener el estado del iterador y *solo* será usado por las operaciones del iterador.
  */
    
    struct celdaColec{  //{cada elemento de la colección se almacena en una celda}
        I ident;            //ident es de tipo genérico y en este caso contiene la cadena correspondiente al nombre del evento 
        V valor;            //valor es de tipo genérico, en este caso lo utilizaremos con el TAD evento
        celdaColec* sup;    //sup es un puntero de tipo celdaColec que apunta al evento del que depende, si es independiente apunta a nullptr 
        unsigned numDep;    //numDep contiene el natural correspondiente el numero de eventos dependientes de este
        celdaColec* izq;    //izq es un puntero de tipo celdaColec que apunta al subarbol izquierdo 
        celdaColec* der;    //der es un puntero de tipo celdaColec que apunta al subarbol derecho
    };

    int tamanio;                    //tamanio contiene el entero correspodiente al número de celdas del árbol
    celdaColec* raiz;               //raíz es un puntero a la primera celda del árbol
    Pila<celdaColec*> iter;         //iter es una pila que almacena punteros para realizar las operaciones del iterador
    /* Queremos resaltar que la implementación de la pilaDianmica ha sido realizada por los profesores de la asignatura de EDA 
    * y que nosotros únicamente la hemos copiado del material proporcionado por ellos mismos del moodle de la asignatura. */

    //Operaciones privadas
    friend bool existe2<I,V>(I id, typename colecInterdep<I,V>::celdaColec* abb);
    friend typename colecInterdep<I,V>::celdaColec* buscar<I,V>(I id, typename colecInterdep<I,V>::celdaColec* abb);
    friend void introducirIndep<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c);
    friend void introducirDep<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup);
    friend bool borrarAux<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, I id);
    friend typename colecInterdep<I,V>::celdaColec* borrarMax<I,V>(typename colecInterdep<I,V>::celdaColec*& abb);
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
* Crea un colección vacía, sin elementos. Todos los punteros a nullptr, el tamaño a 0 y por seguridad creamos la pila del iterador vacía.
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
* Devuelve verdad si y solo si la colección c no contiene ningún elemento.
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
* 
*/
template<typename I, typename V>
bool existe(I id, colecInterdep<I,V>& c){
    return existe2<I,V>(id, c.raiz);
}



/*
* Buscamos el nodo correspondiente al identificador especificado dentro de la colección utilizando la función 
* auxiliar buscar. Dicha función devuelve un puntero al nodo que tiene como identificador id (si existe), si no existe
* en la colección devuelve nullptr. Si el elemento no existe en el árbol (el puntero es nullptr) o si, aún existiendo, 
* su puntero al nodo superior es nulo (significa que no depende de nadie), la función devuelve false. 
* En caso contrario, si el nodo existe y tiene un superior diferente a nullptr (válido), devuelve true.
*
* Recibe como parametros: id el identificador a buscar y c la propia colección.
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
* Buscamos el nodo correspondiente al identificador especificado dentro de la colección utilizando la función 
* auxiliar buscar. Dicha función devuelve un puntero al nodo que tiene como identificador id (si existe), si no existe
* en la colección devuelve nullptr. Si el elemento no existe en el árbol (el puntero es nullptr) o si, aún existiendo, 
* su puntero al nodo superior no es nulo (significa que depende de alguiem), la función devuelve false. 
* En caso contrario, si el nodo existe y tiene un superior igual a nullptr (válido), devuelve true.
*
* Recibe como parametros: id el identificador a buscar y c la propia colección.
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
* Recorremos el árbol de tal forma que si el identificador que estamos buscando es menor que el que estamos visitando en la llamada
* actual, llamamos de forma recursiva a la función con el el subárbol izquierdo. En caso contrario, si el identificador que estamos 
* buscando es mayor que el de la llamada actual, continuamos buscandolode forma recursiva en el subarbol derecho. Repetimos el proceso
* hasta llegar a un subárbol (izquierdo o derecho) que será nullptr y lo insertaremos allí como una hoja. De este modo, no se alterará
* la estructura interna y seguirá siendo un abb que cumple todas las demás características.
*
* Recibe como parametros: abb puntero a un nodo del árbol, id el identificador a buscar/añadir,
* v el valor de dicho elemento v y la colección c.
*/
template<typename I, typename V>
void introducirIndep(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c){
    if(abb == nullptr){     // posicion en la que hay que hay que añadir la nueva celda como hoja
        abb = new typename colecInterdep<I,V>::celdaColec;      //asignas un nuevo nodo
        abb->der = nullptr;         //como es una hoja no tiene subarboles
        abb->izq = nullptr;
        abb->ident = id;            //asignamos la información correspondiente
        abb->valor = v;
        abb->numDep = 0;            //como se acaba de crear no puede tener elementos dependientes de él
        abb->sup = nullptr;         //hemos añadido un elemento independiente
        c.tamanio++;                //aumentamos el tamaño de la colección tras añadir un nodo
    } else if(id < abb->ident){
        introducirIndep<I,V>(abb->izq, id, v, c);  //seguimos buscando la posición por el árbol izquierdo
    } else if(id > abb->ident){
        introducirIndep<I,V>(abb->der, id, v, c);   //seguimos buscando la posición por el árbol derecho
    } 
    //else no hace nada porque no puede haber claves repetidas
}

/*
* Llama a la funcion auxiliar introducirIndep, encargada de añadir el elemento, la cual recibe como parametros un puntero a la raiz del arbol,
* el identificador del elemento que queremos añadir, el valor que tendrá dicho elemento y la propia colección c 
* en la que hay que añadir el nuevo elemento. Si no existe un nodo con identificador id, añade el nuevo elemento
* como independiente a la coleccion de forma recursiva donde el nuevo elemento es un nodo hoja. Por el contrario, si 
* ya existe un elemento con identificador id devuelve una colección idéntica sin modificar nada. 
*/
template<typename I, typename V> 
void aniadirIndependiente(colecInterdep<I,V>& c, I id, V v){

    introducirIndep<I,V>(c.raiz, id, v, c);
    
}

/*
* Recorremos el árbol de tal forma que si el identificador que queremos introducir es menor que el del nodo
* que estamos visitando, llamamos de forma recursiva a la función con el subárbol izquierdo. En caso contrario, 
* si el identificador es mayor, continuamos buscando la posición de inserción de forma recursiva en el subárbol 
* derecho. Repetimos el proceso hasta llegar a un puntero que sea nulo (nullptr), donde insertamos la nueva celda.
* Al crear el nodo, además de guardar el id y el valor, tambíen lo hacemos dependiente con su nodo superior (sup), 
* se incrementa el contador de dependendientes de dicho superior (sup->numDep++) y se incrementa el tamaño de la colección.
*
* Recibe como parametros: abb puntero por referencia al nodo actual del recorrido, id el identificador a buscar/añadir,
* v el valor asociado, c la proopia colección y sup el puntero al nodo del cual depende el nuevo elemento.
*/
template<typename I, typename V>
void introducirDep(typename colecInterdep<I,V>::celdaColec*& abb, I id, V v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup){
    if(abb == nullptr){     //posicion en la que hay que hay que añadir la nueva celda como hoja
        abb = new typename colecInterdep<I,V>::celdaColec;      //asignamos un nuevo nodo
        abb->der = nullptr;     //como es hoja no tiene hijos
        abb->izq = nullptr;
        abb->ident = id;        //añadimos toda la información
        abb->valor = v;
        abb->numDep = 0;        //como se acaba de añadir no puede tener dependientes
        abb->sup = sup;         //sup apunta al elemento superior (del que es dependiente)
        abb->sup->numDep++;     //incrementamos el numero de dependientes del superior
        c.tamanio++;            //incrementamos el tamaño de la colección
    } else if(id < abb->ident){
        introducirDep<I,V>(abb->izq, id, v, c, sup);    //seguimos buscando la posición por el árbol izquierdo
    } else if(id > abb->ident){
        introducirDep<I,V>(abb->der, id, v, c, sup);    //seguimos buscando la posición por el árbol derecho
    } 
    //else no hace nada porque no puede haber claves repetidas
}

/*
* Si el nodo superior (del que depende id) existe, la función buscar nos devuelve un puntero que apunta a dicho elemento, si no devuelve nullptr.
* Por tanto, si el puntero superior es distinto de nullptr significa que exite el superior en la colección, por ello podemos llamar
* a la funcion introducirDep, encargada de añadir el elemento, la cual recibe como parametros un puntero a la raiz del arbol,
* el identificador del elemento que queremos añadir, el valor que tendrá dicho elemento, la propia colección c en la que hay que añadir
* el nuevo elemento y el puntero al elemento superior. Si no existe un nodo con identificador id, añade el nuevo elemento como elemento
* dependiente del elemento apuntado por superior a la coleccion de forma recursiva, donde el nuevo elemento es un nodo hoja.
* Por el contrario, si ya existe un elemento con identificador id o el elemento superior no existe devuelve una colección sin cambios. 
*/
template<typename I, typename V> 
void aniadirDependiente(colecInterdep<I,V>& c, I id, V v, I sup){
    typename colecInterdep<I,V>::celdaColec* superior = buscar<I,V>(sup, c.raiz);
    if(superior != nullptr){introducirDep<I,V>(c.raiz, id, v, c, superior);}
}

/*
* Primero comprobamos que el id del elemento que queremos añadir no es igual al de su nuevo padre para evitar hacer dependiente 
* un elemento de sí mismo...
*/
template<typename I, typename V> 
void hacerDependiente(colecInterdep<I,V>& c, I id, I sup){
    if(id != sup){
        typename colecInterdep<I,V>::celdaColec* superior = buscar<I,V>(sup, c.raiz);
        if(superior != nullptr){
            typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz); 
            if(nodo != nullptr){
                if(nodo->sup != nullptr){   //si era dependiente hay que restarle los numDep al supervisor antiguo
                    nodo->sup->numDep--;
                }
                nodo->sup = superior;
                superior->numDep++;
            }
        } 
    }
       
}

/*
* Recorre la lista en busca de id. Si lo encuentra decrementa numDep de sup en uno y pone sup de id en null, sino 
* lo encuentra devuelve la coleccion original. 
*/
template<typename I, typename V> 
void hacerIndependiente(colecInterdep<I,V>& c, I id){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(nodo != nullptr && nodo->sup != nullptr){        //significa que era dependiente por tanto lo hacemos independiente
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
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(nodo != nullptr){
        nodo->valor = v;
        return true;
    }
    return false;
}

/*
* Si la colección c no es vacía:
* Recorre la lista en busca de id. Si lo encuentra pone el valor de id en la variable val la cual esta pasada
* por referencia para posteriormente poder recuperar el valor y devuelve true, sino devuelve false.
* Es una operación parcial porque si no existe id no puede obtener su valor.
*/
template<typename I, typename V> 
bool obtenerVal(I id, colecInterdep<I,V>& c, V& val){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(nodo != nullptr){
        val = nodo->valor;
        return true;
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
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(nodo != nullptr && nodo->sup != nullptr){
        sup = nodo->sup->ident;
        return true;
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
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(nodo != nullptr){
        numDep = nodo->numDep;
        return true;
    }
    return false;
}

/*
*/
template<typename I, typename V>
typename colecInterdep<I,V>::celdaColec* borrarMax(typename colecInterdep<I,V>::celdaColec*& abb){
    if(abb->der == nullptr){
        typename colecInterdep<I,V>::celdaColec* aux = abb;
        abb = abb->izq;
        aux->izq = nullptr;
        return aux;
    } else {
        return borrarMax<I,V>(abb->der);
    }
}

/*
*/
template<typename I, typename V>
bool borrarAux(typename colecInterdep<I,V>::celdaColec*& abb, I id){
    if(abb != nullptr){
        if(id < abb->ident){
           return borrarAux<I,V>(abb->izq, id);
        } else if(id > abb->ident){
           return borrarAux<I,V>(abb->der, id);
        } else if(abb->numDep == 0){
            if(abb->sup != nullptr){
                abb->sup->numDep--;
            }
            typename colecInterdep<I,V>::celdaColec* aux = abb;

            if(abb->izq == nullptr){
                abb = abb->der;
                delete(aux);
                return true;
            } else if(abb->der == nullptr){
                abb = abb->izq;
                delete(aux);
                return true;
            } else {
                
                typename colecInterdep<I,V>::celdaColec* nodoMAX = borrarMax<I,V>(abb->izq);
                
                nodoMAX->izq = abb->izq;
                nodoMAX->der = abb->der;

                abb = nodoMAX;
                delete(aux);
                return true;
            }
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
    if(borrarAux<I,V>(c.raiz, id)){ c.tamanio--;}
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
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(nodo != nullptr){
        v = nodo->valor;
        numDep = nodo->numDep;
        if(nodo->sup != nullptr){       //significa que es dependiente
            esDep = true;
            sup = nodo->sup->ident;
        } else {                        //significa que es independiente
            esDep = false;
        }
        return true;
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