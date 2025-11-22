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
*   bool menorque(I e1, I e2) devuelve verdadero si y solo si el elemento e1 es menor (anterior) que el elemento e2.
*
*/
template<typename I, typename V> struct colecInterdep;

/*
* Recibe una colección c y la crea vacía, sin elementos.
*/
template<typename I, typename V> void crear(colecInterdep<I,V>& c);

/*
* Recibe una colección c. Devuelve el número de elementos que hay en la colección c.
*/
template<typename I, typename V> int tamanio(const colecInterdep<I,V>& c);

/*
* Recibe una colección c. Devuelve verdad si y solo si la colección c no contiene ningún elemento.
*/
template<typename I, typename V> bool esVacia(const colecInterdep<I,V>& c);

/*
* Recibe una colección c y un identificador id. Devuelve verdad si y solo si en c hay algún elemento con un identificador igual a id.
*/
template<typename I, typename V> bool existe(const I& id, const colecInterdep<I,V>& c);

/*
* Recibe un identificador id y una colección c. Devuelve verdad si y solo si en c hay algún elemento 
* dependiente cuya clave sea igual a id, es decir un elemento de la forma (id, v, sup, numDep).
*/
template<typename I, typename V> bool existeDependiente(const I& id, const colecInterdep<I,V>& c);

/*
* Recibe un identificador id y una colección c. Devuelve verdad si y solo si en c hay algún elemento independiente
* cuyo identificador sea igual a id, es decir un elemento de la forma (id, v, -, numDep).
*/
template<typename I, typename V> bool existeIndependiente(const I& id, const colecInterdep<I,V>& c);

/*
* Recibe una colección c, un identificador id y un valor v. Si el identificador id no existe en la colección c,
* devuelve una colección igual a la resultante de añadir a la colección c el elemento independiente de la forma (id,v,-,0),
* siendo id su identificador y v su valor. En caso contrario, devuelve una colección igual a c.
*/
template<typename I, typename V> void aniadirIndependiente(colecInterdep<I,V>& c, const I& id, const V& v);

/*
* Recibe una colección c, un identificador id, un valor v y otro identificador sup del que dependerá el elemento.
* Si el identificador id no existe en la colección c y el identificador sup sí que existe en la colección c,
* devuelve una colección igual a la resultante de:
* incrementar en 1 el número de elementos dependientes del elemento con identificador sup en c y
* añadir el elemento de la forma (id,v,sup,0) a la colección c. En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void aniadirDependiente(colecInterdep<I,V>& c, const I& id, const V& v, const I& sup);

/*
* Recibe una colección c, un identificador id y otro identificador sup del que dependerá el elemento.
* Si el identificador id es diferente al identificador sup, existe el identificador sup en la colección c y además el elemento
* con identificador id es dependiente de forma (id, v, superAnt, numDep), devuelve una colección igual a la resultante de:
*   - incrementar en 1 el número de elementos dependientes del elemento con identificador sup en c
*   - decrementar en 1 el número de elementos dependientes del elemento con identificador superAnt en c
*   - sustituir el elemento (id, v, superAnt, numDep) por el elemento (id, v, sup, numDep) en c.
*
* Si el identificador id es diferente al identificador sup, existe el identificador sup en la colección c y además el elemento
* con identificador id es independendiente de forma (id, v, -, numDep), devuelve una colección igual a la resultante de:
*   - incrementar en 1 el número de elementos dependientes del elemento con identificador sup en c
*   - sustituir en c el elemento (id, v, -, numDep) por el elemento (id, v, sup, numDep).
*
* En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void hacerDependiente(colecInterdep<I,V>& c, const I& id, const I& sup);

/*
* Recibe una colección c y un identificador id.
* Si el elemento con identificador id existe en la colección c y además dicho elemento es dependiente, de la forma (id, v, sup, numDep),
* devuelve una colección igual a la resultante de:
*   - establecer el identificador del supervisor (sup) del elemento con identificador id como vacío (‘-’),
*   - decrementar en 1 el número de dependientes del antiguo supervisor (sup) del elemento con identificador id.
* En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void hacerIndependiente(colecInterdep<I,V>& c, const I& id);

/*
* Recibe una colección c, un identificador id y un valor v.
* Operación parcial -> la operación no está definida si el elemento con identificador id no existe en la colección c.
* Si el elemento con identificador id existe en la colección c, modifica la colección actual de tal manera que actualiza
* el valor del elemento con identificador id en la colección c con el valor v y devuelve verdadero.
* En caso contrario, no se modifica la colección c, se mantiene igual que antes y devuelve falso.
*/
template<typename I, typename V> bool actualizarVal(colecInterdep<I,V>& c, const I& id, const V& v);


/*
* Recibe un identificador id y una colección c.
* Si existe el elemento con identificador id en la colección c y dicho elemento es dependiente de la forma (id, v, sup, numDep),
* tal que numDep es el número de elementos dependientes del elemento con identificador id y es igual a 0, entonces
* modifica la colección de tal forma que tenemos una colección igual a la resultante de: 
*   - decrementar en 1 el número de elementos dependientes (numDep) del elemento con identificador sup.
*   - eliminar el elemento (id, v, sup, numDep), en la colección c.
*
* Si existe el elemento con identificador id en la colección c y dicho elemento es independiente de la forma (id, v, -, numDep),
* tal que numDep es el número de elementos dependientes del elemento con identificador id y es igual a 0, entonces:
* modifica la colección de tal forma que tenemos una colección igual a la resultante de:
*   - eliminar el elemento (id, v, sup, numDep), en la colección c.
*
* En cualquier otro caso, mantiene una colección igual a c.
*/
template<typename I, typename V> void borrar(const I& id, colecInterdep<I,V>& c);

//Operacion auxiliar que agrupa las funciones de obtenerNumDependientes, obtenerSupervisor y obtenerVal
/*
* Recibe un identificador id, un natural numDep, otro identificador sup, un valor v, una colección c y un booleano esDep.
* Si existe el elemento con identificador id en la colección c, asigna los valores correspondientes a los parámetros 
* (si el elemento con identificador id es dependiente el booleano esDep será verdadero, si es independiente valdrá falso) y
* devuelve verdadero si y solo si ha podido obtener todos los datos relacionados al elemento con identificador id.
* Si el elemento no existe en la colección, es que no puede obtener sus datos entonces devuelve falso y no modifica nada. 
*/
template<typename I, typename V> bool obtenerDatos(const I& id, unsigned& numDep, I& sup, V& v, const colecInterdep<I,V>& c, bool &esDep);


//Operaciones iterador

/*
* Recibe una coleción c.
* Inicializa el iterador para recorrer los elementos de la colección c, de forma que el siguiente
* elemento a visitar sea el que tiene un identificador anterior a los de todos los demás elementos de la
* colección, que se corresponde con la situación de no haber visitado ningún elemento. 
*/
template<typename I, typename V> void iniciarIterador(colecInterdep<I,V>& c);

/*
* Recibe una coleción c.
* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección c, devuelve
* falso si ya se ha visitado el último elemento.
*/
template<typename I, typename V> bool existeSiguiente(colecInterdep<I,V>& c);

//Operación auxiliar que engloba siguienteIdent, siguienteVal, siguienteDependiente?, siguienteSuperior, siguienteNumDependeintes.
/* 
* Recibe una colección c, un identificador id, un valor v, otro identificador sup, un natural numDep y un booleano esDep.
* Si existe el siguiente elemento del iterador con identificador id en la colección c, asigna los valores correspondientes a los parámetros 
* (si el siguiente elemento del iterador con identificador id es dependiente el booleano esDep será verdadero, si es independiente valdrá falso) y
* devuelve verdadero si y solo si ha podido obtener todos los datos relacionados al elemento con identificador id.
* Si el elemento no existe en la colección, es que no puede obtener sus datos entonces devuelve falso y no modifica nada. 
*/
template<typename I, typename V> bool siguienteDatos(colecInterdep<I,V>& c, I &id, V &valor, I &sup, unsigned &numDep, bool &esDep);

/*
* Recibe una colección c.
* Si aún queda algun elemento por visitar, avanza el iterador de la colección c para que se pueda visitar otro elemento.
*/
template<typename I, typename V> void avanza(colecInterdep<I,V>& c);

// FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)

//COMIENZA LA PARTE PRIVADA A PARTIR DE ESTE PUNTO

//Predeclaración de las operaciones privadas  (es necesario para que compile correctamente)

/* Busca recursivamente un nodo por su identificador. */
template<typename I, typename V> typename colecInterdep<I,V>::celdaColec* buscar(const I& id, typename colecInterdep<I,V>::celdaColec* abb);

/* Inserta un nuevo nodo de forma recursiva manteniendo el orden establecido. */
template<typename I, typename V> void introducir(typename colecInterdep<I,V>::celdaColec*& abb, const I& id, const V& v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup);

/* Busca y elimina un nodo, garantizando el orden establecido. */
template<typename I, typename V> bool borrarAux(typename colecInterdep<I,V>::celdaColec*& abb, const I& id);

/* Encuentra y desvincula el nodo máximo del subárbol izquierdo (auxiliar de borrarAux). */
template<typename I, typename V> typename colecInterdep<I,V>::celdaColec* borrarMax(typename colecInterdep<I,V>::celdaColec*& abb);

// DECLARACION DEL TAD GENERICO colecInterdep

template<typename I, typename V>
struct colecInterdep{
    friend void crear<I,V>(colecInterdep<I,V>& c);
    friend int tamanio<I,V>(const colecInterdep<I,V>& c);
    friend bool esVacia<I,V>(const colecInterdep<I,V>& c);
    friend bool existe<I,V>(const I& id, const colecInterdep<I,V>& c);
    friend bool existeDependiente<I,V>(const I& id, const colecInterdep<I,V>& c);
    friend bool existeIndependiente<I,V>(const I& id,const colecInterdep<I,V>& c);
    friend void aniadirIndependiente<I,V>(colecInterdep<I,V>& c, const I& id, const V& v);
    friend void aniadirDependiente<I,V>(colecInterdep<I,V>& c, const I& id,const V& v, const I& sup);
    friend void hacerDependiente<I,V>(colecInterdep<I,V>& c, const I& id, const I& sup);
    friend void hacerIndependiente<I,V>(colecInterdep<I,V>& c, const I& id);
    friend bool actualizarVal<I,V>(colecInterdep<I,V>& c, const I& id, const V& v);
    friend void borrar<I,V>(const I& id, colecInterdep<I,V>& c);
    //Operacion auxiliar
    friend bool obtenerDatos<I,V>(const I& id, unsigned& numDep, I& sup, V& v, const colecInterdep<I,V>& c, bool &esDep);
    
    /* Operaciones iterador */
    friend void iniciarIterador<I,V>(colecInterdep<I,V>& c);
    friend bool existeSiguiente<I,V>(colecInterdep<I,V>& c);
    friend bool siguienteDatos<I,V>(colecInterdep<I,V>& c, I &id, V &valor, I &sup, unsigned &numDep, bool &esDep);
    friend void avanza<I,V>(colecInterdep<I,V>& c);
    
    
  private: //declaracion de la representacion interna del tipo

  /*
  * La implementación de este TAD genérico se hace a partir de un diccionario pero cuya implementación interna está basada en un abb.
  * Dicho diccionario está formado por los pares <ident, valor>, siendo ident la clave única y permanente
  * (no se puede modificar ni duplicar) y siendo valor el valor (contando con funciones para consultarlo y modificarlo).
  * Situándonos en la raíz del árbol, todos los identificadores que están en su subarbol izquierdo son esctrictamente menores que su 
  * propio identificador, además todos los que estén en su subarbol derecho serán estrictamente mayores. Esta lógica también se aplica 
  * para todos los subárboles hijos y sus respectivos hijos. 
  * El diccionario está implementado en memoria dinámica utilizando un árbol binario de búsqueda formado por celdas del tipo celdaColec. 
  * Dicho diccionario ocupa en memoria O(n), siendo n el número total de celdas que tiene. Cada celda del diccionario contendrá una clave de tipo I, un valor de tipo V,
  * un puntero al elemento del que es dependiente (si no depende de nadie este puntero apuntará a nullptr), un natural correspondiente
  * al número de elementos dependientes que tiene este elemento y 2 punteros izq y der que apuntarán respectivamente a los hijos/subarboles
  * izquierdos y derechos respectivamente que a su vez, también serán árboles binarios de búsqueda.
  * 
  * Además, el diccionario cuenta con un entero llamado tamanio que registra el número de celdas que tiene actualmente el árbol,
  * un puntero llamado raiz que apunta al primer elemento del árbol (si no hay ningún elemento apunta a nullptr) y un TAD Pila implementado
  * por los profesores de la asignatura de EDA que se utilizará únicamente para mantener el estado del iterador y *solo* será usado por las operaciones del iterador.
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
    /* Queremos resaltar que la implementación de la pilaDinámica ha sido realizada por los profesores de la asignatura de EDA 
    * y que nosotros únicamente la hemos copiado del material proporcionado por ellos mismos del moodle de la asignatura. */

    //Operaciones privadas
    friend typename colecInterdep<I,V>::celdaColec* buscar<I,V>(const I& id, typename colecInterdep<I,V>::celdaColec* abb);
    friend void introducir<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, const I& id, const V& v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup);
    friend bool borrarAux<I,V>(typename colecInterdep<I,V>::celdaColec*& abb, const I& id);
    friend typename colecInterdep<I,V>::celdaColec* borrarMax<I,V>(typename colecInterdep<I,V>::celdaColec*& abb);
};

//Implementación de operaciones privadas auxiliares
/*
* Recibe como parámetros un identificador id y un puntero abb de tipo celdaColec.
* Si el puntero abb que pasamos como parámetro apunta a nullptr, devolvemos dicho valor. En caso contrario, buscamos de forma recursiva 
* el identificador id a lo largo del árbol. Si el id que buscamos es menor que el id apuntado por abb, seguimos buscando por el subarbol 
* izquierdo, pero si es mayor que el id apuntado por abb buscamos en el subarbol derecho y si no se cumple ninguna de las 2 es que coinciden
* por tanto devolvemos el puntero que apunta a esa celda. 
*/
template<typename I, typename V>
typename colecInterdep<I,V>::celdaColec* buscar(const I& id, typename colecInterdep<I,V>::celdaColec* abb){
    if(abb == nullptr){
        return nullptr;
    } else {
        if(id < abb->ident){
            return buscar<I,V>(id, abb->izq);
        } else if(abb->ident < id){
            return buscar<I,V>(id, abb->der);
        } else {
            return abb;
        }
    }
}

/*
* Recibe como parametros un puntero abb al nodo actual, el identificador id a buscar/añadir,
* v el valor asociado, c la propia colección y sup el puntero al nodo del cual depende el nuevo elemento.
*
* Recorremos el árbol de tal forma que si el identificador que queremos introducir es menor que el del nodo
* que estamos visitando, llamamos de forma recursiva a la función con el subárbol izquierdo. En caso contrario, 
* si el identificador es mayor, continuamos buscando la posición de inserción de forma recursiva en el subárbol 
* derecho. Repetimos el proceso hasta llegar a un puntero que sea nulo (nullptr), donde insertamos la nueva celda.
* Al crear el nodo, además de guardar el id y el valor, tambien lo hacemos dependiente de su nodo superior (sup), 
* se incrementa el contador de dependientes de dicho superior y se incrementa el tamaño de la colección.
*/
template<typename I, typename V>
void introducir(typename colecInterdep<I,V>::celdaColec*& abb, const I& id, const V& v, colecInterdep<I,V>& c, typename colecInterdep<I,V>::celdaColec* sup){
    if(abb == nullptr){     //posicion en la que hay que hay que añadir la nueva celda como hoja
        abb = new typename colecInterdep<I,V>::celdaColec;      //asignamos un nuevo nodo
        abb->der = nullptr;     //como es hoja no tiene hijos
        abb->izq = nullptr;
        abb->ident = id;        //añadimos toda la información
        abb->valor = v;
        abb->numDep = 0;        //como se acaba de añadir no puede tener dependientes
        abb->sup = sup;        //sup apunta al elemento superior (del que es dependiente)
        if(!(sup == nullptr)){
            abb->sup->numDep++;     //incrementamos el numero de dependientes del superior
        }
        c.tamanio++;            //incrementamos el tamaño de la colección
    } else if(id < abb->ident){
        introducir<I,V>(abb->izq, id, v, c, sup);    //seguimos buscando la posición por el árbol izquierdo
    } else if(abb->ident < id){
        introducir<I,V>(abb->der, id, v, c, sup);    //seguimos buscando la posición por el árbol derecho
    } 
    //else no hace nada porque no puede haber claves repetidas
}

/*
* Recibe como parametros abb puntero por referencia al nodo actual del recorrido y id el identificador a borrar.
*
* Bajamos por el arbol buscando el maximo valor de la izquierda (el mayor de los menores) para sustituir el nodo que 
* queremos borrar (raiz) por él (mayor de los menores). Para ello, como queremos encontrar el maximo del subarbol izquierdo,
* nos desplazamos hacia la derecha hasta encontrar un nodo que no tenga hijo derecho. Cuando lo encontramos, ese nodo
* es el mayor de los menores. Una vez encontrado, lo devolvemos y hacemos que el puntero al
* hijo derecho del padre apunte al hijo izquierdo del nodo encontrado (que puede ser nullptr si no tiene hijo izquierdo).
* De esta forma, eliminamos el nodo mayor de los menores del árbol original y lo devolvemos para sustituir la raiz.
*/
template<typename I, typename V>
typename colecInterdep<I,V>::celdaColec* borrarMax(typename colecInterdep<I,V>::celdaColec*& abb){
    if(abb->der == nullptr){   //hemos llegado al maximo de la rama izquierda
        typename colecInterdep<I,V>::celdaColec* aux = abb;
        abb = abb->izq; 
        aux->izq = nullptr; 
        return aux;
    } else {
        return borrarMax<I,V>(abb->der); //seguimos buscando el maximo de la rama 
    }
}

/*
* Recibe como parametros: abb puntero por referencia al nodo actual del recorrido y id el identificador a borrar.
*
* Buscamos el nodo con identificador id de forma recursiva. Cuando lo encontramos, comprobamos si su número de dependientes
* es 0, en ese caso procedemos a borrarlo. Si el nodo a borrar no tiene hijos, simplemente lo eliminamos y en caso de que 
* tenga padre, decrementamos en 1 el número de dependientes de su padre. Si el nodo tiene solo un hijo, hacemos que el puntero 
* del padre apunte a ese hijo y eliminamos el nodo. Si tiene dos hijos, llamamos a la función borrarMax que nos devolverá un puntero al
* máximo elemento del subarbol izquierdo y arreglamos el orden para que el árbol siga siendo un abb. 
*/
template<typename I, typename V>
bool borrarAux(typename colecInterdep<I,V>::celdaColec*& abb, const I& id){
    if(!(abb == nullptr)){ //si el árbol no es vacío
        if(id < abb->ident){  //buscamos en el subárbol izquierdo   
           return borrarAux<I,V>(abb->izq, id);
        } else if(abb->ident < id){ //buscamos en el subárbol derecho
           return borrarAux<I,V>(abb->der, id);
        } else if(abb->numDep == 0){ //lo encontramos y comprobamos que su numDep es 0 para poder borrarlo
            if(!(abb->sup == nullptr)){
                abb->sup->numDep--; //decrementamos en 1 el numero de dependientes de su superior (si tiene)
            }
            typename colecInterdep<I,V>::celdaColec* aux = abb;

            if(abb->izq == nullptr){ //si no tiene hijo izquierdo
                abb = abb->der; 
                delete(aux);
                return true;
            } else if(abb->der == nullptr){ //si no tiene hijo derecho
                abb = abb->izq;
                delete(aux);
                return true;
            } else { //si tiene los 2 hijos
                
                typename colecInterdep<I,V>::celdaColec* nodoMAX = borrarMax<I,V>(abb->izq); //buscamos el maximo de la izquierda para sustituir la raiz
                
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

// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colecInterdep

/*
* Recibe como parámetros una colección c.
* Crea un colección vacía, sin elementos. Todos los punteros a nullptr, el tamaño a 0 y por seguridad creamos la pila del iterador vacía.
*/
template<typename I, typename V>
void crear(colecInterdep<I,V>& c){
    c.raiz = nullptr;
    c.tamanio = 0;
    crearVacia(c.iter); //por seguridad
}

/*
* Recibe como parámetros una colección c y devuelve el número de elementos que hay en la colección c.
*/
template<typename I, typename V>
int tamanio(const colecInterdep<I,V>& c){
    return c.tamanio;
}

/*
* Recibe como parámetros una colección c y devuelve verdad si y solo si la colección c no contiene ningún elemento.
*/
template<typename I, typename V> 
bool esVacia(const colecInterdep<I,V>& c){
    return c.tamanio == 0;
}

/*
* Recibe como parametros: id el identificador a buscar y c la propia colección.
*
* Buscamos el nodo correspondiente al identificador id dentro de la colección utilizando la función 
* auxiliar buscar. Dicha función devuelve un puntero al nodo que tiene como identificador id (si existe), si no existe
* en la colección devuelve nullptr. Si el puntero es distinto de nullptr significa que el elemento existe, por tanto devolvemos true,
* en caso contrario devolvemos false.
*/
template<typename I, typename V>
bool existe(const I& id, const colecInterdep<I,V>& c){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    return !(nodo == nullptr);
}

/*
* Recibe como parametros: id el identificador a buscar y c la propia colección.
*
* Buscamos el nodo correspondiente al identificador id dentro de la colección utilizando la función 
* auxiliar buscar. Dicha función devuelve un puntero al nodo que tiene como identificador id (si existe), si no existe
* en la colección devuelve nullptr. Si el elemento no existe en el árbol (el puntero es nullptr) o si, aún existiendo, 
* su puntero al nodo superior es nulo (significa que no depende de nadie), la función devuelve false. 
* En caso contrario, si el nodo existe y tiene un superior diferente a nullptr (válido), devuelve true.
*/
template<typename I, typename V>
bool existeDependiente(const I& id, const colecInterdep<I,V>& c){
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
* Recibe como parametros: id el identificador a buscar y c la propia colección.
*
* Buscamos el nodo correspondiente al identificador id dentro de la colección utilizando la función 
* auxiliar buscar. Dicha función devuelve un puntero al nodo que tiene como identificador id (si existe), si no existe
* en la colección devuelve nullptr. Si el elemento no existe en el árbol (el puntero es nullptr) o si, aún existiendo, 
* su puntero al nodo superior no es nulo (significa que depende de alguien), la función devuelve false. 
* En caso contrario, si el nodo existe y tiene un superior igual a nullptr (válido), devuelve true.
*/
template<typename I, typename V>
bool existeIndependiente(const I& id, const colecInterdep<I,V>& c){
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
* Recibe como parametros: c la propia colección, id el identificador del elemento a introducir y v el valor que deberá tener nuestro elemento.
*
* Llama a la funcion auxiliar introducir, encargada de añadir el elemento, la cual recibe como parametros un puntero a la raiz del arbol,
* el identificador del elemento que queremos añadir, el valor que tendrá dicho elemento, la propia colección c en la que hay que añadir el 
* nuevo elemento y un puntero a su superior, en este caso nullptr porque es independiente. Si no existe un nodo con identificador id, 
* añade el nuevo elemento como independiente a la colección de forma recursiva donde el nuevo elemento es un nodo hoja. Por el contrario, si 
* ya existe un elemento con identificador id devuelve una colección idéntica sin modificar nada. 
*/
template<typename I, typename V> 
void aniadirIndependiente(colecInterdep<I,V>& c, const I& id, const V& v){
    introducir<I,V>(c.raiz, id, v, c, nullptr);   
}

/*
* Recibe como parametros: c la propia colección, id el identificador del elemento a introducir, v el valor que deberá tener nuestro elemento
* y sup el identificador del superior (elemento del que dependerá el nuevo).
*
* Si el nodo superior (del que depende id) existe, la función buscar nos devuelve un puntero que apunta a dicho elemento, si no devuelve nullptr.
* Por tanto, si el puntero superior es distinto de nullptr significa que existe el superior en la colección, por ello podemos llamar
* a la funcion introducir, encargada de añadir el elemento, la cual recibe como parametros un puntero a la raiz del arbol,
* el identificador del elemento que queremos añadir, el valor que tendrá dicho elemento, la propia colección c en la que hay que añadir
* el nuevo elemento y el puntero al elemento superior. Si no existe un nodo con identificador id, añade el nuevo elemento como elemento
* dependiente del elemento apuntado por superior a la colección de forma recursiva, donde el nuevo elemento es un nodo hoja.
* Por el contrario, si ya existe un elemento con identificador id o el elemento superior no existe devuelve una colección sin cambios. 
*/
template<typename I, typename V> 
void aniadirDependiente(colecInterdep<I,V>& c, const I& id, const V& v, const I& sup){
    typename colecInterdep<I,V>::celdaColec* superior = buscar<I,V>(sup, c.raiz);
    if(!(superior == nullptr)){introducir<I,V>(c.raiz, id, v, c, superior);}
}

/*
* Recibe como parámetros: c la propia colección, id el identificador del elemento a modificar y sup el identificador del nuevo superior.
* Primero verifica que el elemento a modificar no sea el mismo que el superior, ya que no puede depender de sí mismo.
* Busca el elemento con identificador sup en la colección. Si existe, busca el elemento con identificador id.
* Si ambos elementos existen, comprueba si id era dependiente anteriormente y si lo era, decrementa el contador de dependientes
* de su antiguo superior. Luego, actualiza el puntero superior de id para que apunte al nuevo sup y aumenta el contador de
* dependientes de este nuevo superior. Si alguno de los elementos no existe, no realiza ningún cambio.
*/
template<typename I, typename V> 
void hacerDependiente(colecInterdep<I,V>& c, const I& id, const I& sup){
    if(!(id == sup)){
        typename colecInterdep<I,V>::celdaColec* superior = buscar<I,V>(sup, c.raiz);
        if(!(superior == nullptr)){
            typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz); 
            if(!(nodo == nullptr)){
                if(!(nodo->sup == nullptr)){   //si era dependiente hay que restarle los numDep al supervisor antiguo
                    nodo->sup->numDep--;
                }
                nodo->sup = superior;
                superior->numDep++;
            }
        } 
    }
       
}

/*
* Recibe una colección c y un identificador id.
* Si el elemento con identificador id existe en la colección c y además dicho elemento es dependiente,
* entonces lo hacemos independiente restando en 1 el número de dependientes de su antiguo superior y poniendo su puntero 
* sup a nullptr. En cualquier otro caso, no se modifica la colección c.
*/
template<typename I, typename V> 
void hacerIndependiente(colecInterdep<I,V>& c, const I& id){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(!(nodo == nullptr) && !(nodo->sup == nullptr)){        //significa que era dependiente por tanto lo hacemos independiente
        nodo->sup->numDep--;
        nodo->sup = nullptr;
    }
}

/*
* Recibe como parametros: c la propia colección, id el identificador del elemento a modificar y v el nuevo valor que deberá tener nuestro elemento.
* Buscamos el nodo correspondiente al identificador especificado dentro de la colección utilizando la función 
* auxiliar buscar. Dicha función devuelve un puntero al nodo que tiene como identificador id (si existe), si no existe
* en la colección devuelve nullptr. Si el puntero es distinto de nullptr significa que el elemento existe, por tanto actualizamos su valor
* con el nuevo valor v y devolvemos true. En caso contrario devolvemos false.
*/
template<typename I, typename V> 
bool actualizarVal(colecInterdep<I,V>& c, const I& id, const V& v){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(!(nodo == nullptr)){
        nodo->valor = v;
        return true;
    }
    return false;
}

/*
* Recibe como parametros: id el identificador a borrar y c la propia colección.
* Llama a la función auxiliar borrarAux, encargada de borrar el elemento, la cual recibe como parametros un puntero
* a la raiz del arbol y el identificador del elemento que queremos borrar. Si existe el nodo con identificador id y su número de dependientes es 0,
* borra el elemento de la colección y devuelve true, en caso contrario devuelve false. Si la función borrarAux devuelve true, decrementamos en 1 el tamaño de la colección. 
*/
template<typename I, typename V> 
void borrar(const I& id, colecInterdep<I,V>& c){
    if(borrarAux<I,V>(c.raiz, id)){ c.tamanio--;}
}


//Operacion Auxiliar que engloba obtenerVal, obtenerSupervisor, obtenerNumDependientes    
/*
* Recibe como parámetros un identificador id, un natural numDep, un identificador sup, un valor v, una colección c y un booleano esDep.
*
* Buscamos el nodo correspondiente al identificador id dentro de la colección utilizando la función auxiliar buscar. Si el nodo no existe me
* devuelve nullptr, si existe me devuelve el puntero que apunta a dicho nodo. Si existe el nodo que tiene a id como identificador,
* modificamos las variables de tal forma que: numDep ahora contiene el numero de elementos dependientes de nuestro elemento
* con identificador id, v contiene el valor de nuestro elemento con identificador id y sup, si el elemento con ident id es dependiente, contiene
* el identificador del elemento del que depende (su superior) además de que esDep se vuelve verdadero y si es independiente, 
* se devuelve en esDep falso y no hace falta modificar nada mas.
* Devuelve verdadero si y solo si ha podido obtener todos los datos, en caso contrario devuelve falso.
*/
template<typename I, typename V> 
bool obtenerDatos(const I& id, unsigned& numDep, I& sup, V& v, const colecInterdep<I,V>& c, bool &esDep){
    typename colecInterdep<I,V>::celdaColec* nodo = buscar<I,V>(id, c.raiz);
    if(!(nodo == nullptr)){
        v = nodo->valor;
        numDep = nodo->numDep;
        if(!(nodo->sup == nullptr)){       //significa que es dependiente
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
* Recibe como parametro la colección c y la prepara para iniciar la iteracion.
* Para ello, liberamos la pila del iterador por si ya tenía elementos de una iteración anterior.
* A continuación, partiendo de la raíz del árbol, vamos bajando por la izquierda apilando
* todos los nodos que vamos encontrando hasta llegar a un puntero nulo (nullptr).
* De esta forma, el siguiente elemento a visitar será el que tiene un identificador
* anterior a los de todos los demás elementos de la colección.
*/
template<typename I, typename V>
void iniciarIterador(colecInterdep<I,V>& c){
    liberar(c.iter);
    typename colecInterdep<I,V>::celdaColec* nodo = c.raiz;
    while(!(nodo == nullptr)){
        apilar(c.iter, nodo);
        nodo = nodo->izq;
    }

}

/*
* Recibe como parametro la colección c y devuelve verdadero si y solo si existe un siguiente elemento a visitar.
* Para ello, comprobamos si la pila del iterador está vacía o no. Si no está vacía, significa que quedan elementos por visitar,
* por tanto devolvemos verdadero. En caso contrario, devolvemos falso.
*/
template<typename I, typename V>
bool existeSiguiente(colecInterdep<I,V>& c){
    return !(esVacia(c.iter));
}

/*
* Recibe como parametro la colección c y devuelve verdadero si y solo si existe un siguiente elemento a visitar.
* Además, devuelve en los parámetros id, valor, sup, numDep y esDep los datos del siguiente elemento a visitar.
* En caso de que no exista siguiente elemento, no modifica los parámetros y devuelve falso.
*/
template<typename I, typename V>
bool siguienteDatos(colecInterdep<I,V>& c, I &id, V &valor, I &sup, unsigned &numDep, bool &esDep){
    bool error = false;
    esDep = false;
    if(existeSiguiente(c)){   
        typename colecInterdep<I,V>::celdaColec* nodo;
        cima(c.iter, nodo, error);
        if(!error){             //por seguridad porque si existeSiguiente(c) seguro que habrá cima
            id = nodo->ident;
            valor = nodo->valor;
            numDep = nodo->numDep;
            if(!(nodo->sup == nullptr)){
                sup = nodo->sup->ident;
                esDep = true;
            }
           
        }
        return true;
    }
    return false;
}

/*
* Recibe como parametro la colección c y avanza el iterador para que el siguiente elemento a visitar sea el siguiente elemento con menor
* identificador aun no visitado. Para ello, si existe un siguiente elemento, desapilamos el nodo que estamos visitando actualmente y 
* nos movemos al subárbol derecho de dicho nodo. A continuación, bajamos por la izquierda de ese subárbol derecho apilando
* todos los nodos que vamos encontrando hasta llegar a un puntero nulo (nullptr).
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

            while(!(nodo == nullptr)){
                apilar(c.iter, nodo);
                nodo = nodo->izq;
            }
        }
    }
}

#endif
