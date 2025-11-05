/* Razvan Ghita calangiu 927460, Rodrigo Herce Alonso 935413
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

#include <iostream>
using namespace std;


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
*   bool operator==(I e1, I e2) devuelve verdadero si y solo si el elemento e1 es igual al elemento e2.
*   bool operator<(I e1, I e2) devuelve verdadero si y solo si el elemento e1 es anterior (menor) que el elemento e2.
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
* Si el elemento con identificador id existe en la coleccion c y además dicho elementp es dependiente, de la forma (id, v, sup, numDep).
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
* Si el elemento con identificador id existe en la coleccion c, devuelve el valor asociado al elemento con identificador id
* en la coleccion c y asigna a error el valor falso.
* En caso contrario, devuelve un valor indeterminado y asigna a error el valor verdadero.
*/
template<typename I, typename V> V obtenerVal(I id, colecInterdep<I,V>& c, bool& error);

/*
*Operación parcial -> la operación no está definida si el elemento con identificador id no es dependiente de la forma (id, v, sup, numDep).
* Si el elemento con identificador id existe en la coleccion c y además dicho elemento es dependiente de la forma (id, v, sup, numDep),
* devuelve el identificador de su supervisor y asigna a error el valor falso.
* En cualquier otro caso (si no existe o es independiente), devuelve un valor indeterminado y asigna a error el valor verdadero.
*/
template<typename I, typename V> I obtenerSupervisor(I id, colecInterdep<I,V>& c, bool& error);

/*
*Operación parcial -> la operación no está definida si no el elemento con identificador id no existe en la coleccion c.
* Si el elemento con identificador id existe en la coleccion c, devuelve el número de eventos dependientes del elemento
* con identificador id en la coleccion c y asigna a error el valor falso.
* En caso contrario, devuelve un valor indeterminado y asigna a error el valor verdadero.
*/
template<typename I, typename V> unsigned obtenerNumDependientes(I id, colecInterdep<I,V>& c, bool& error);

/*
* Si existe el elemento con identificador id en la colección c y dicho elemento es dependiente de la forma (id, v, sup, numDep),
* tal que numDep es el número de elementos dependientes del elemento con identificador id y es igual a 0, entonces:
* devuelve verdadero y modifica la colección de tal forma que tenemos una colección igual a la resultante de: 
*   - decrementar en 1 el número de elementos dependientes (numDep) del elemento con identificador sup.
*   - eliminar el elemento (id, v, sup, numDep), en la colección c.
*
* Si existe el elemento con identificador id en la colección c y dicho elemento es independiente de la forma (id, v, -, numDep),
* tal que numDep es el número de elementos dependientes del elemento con identificador id y es igual a 0, entonces:
* devuelve verdadero y modifica la colección de tal forma que tenemos una colección igual a la resultante de:
*   - eliminar el elemento (id, v, sup, numDep), en la colección c.
*
* En cualquier otro caso, devuelve falso y mantiene una coleccion igual a c.
*/
template<typename I, typename V> void borrar(I id, colecInterdep<I,V>& c);


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
template<typename I, typename V> I siguienteIdent(colecInterdep<I,V>& c);

/*
* Si aún queda algun elemento por visitar, devuelve el valor del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con identificador anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> V siguienteVal(colecInterdep<I,V>& c);

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
template<typename I, typename V> I siguienteSuperior(colecInterdep<I,V>& c);

/*
* Si aún queda algun elemento por visitar, devuelve el numero de elementos dependientes del elemento con identificador id (numDep)
* del siguiente elemento a visitar con el iterador de la colección c, que será el elemento no visitado con
* identificador anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> unsigned siguienteNumDependientes(colecInterdep<I,V>& c);

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
    friend V obtenerVal<I,V>(I id, colecInterdep<I,V>& c, bool& error);
    friend I obtenerSupervisor<I,V>(I id, colecInterdep<I,V>& c, bool& error);
    friend unsigned obtenerNumDependientes<I,V>(I id, colecInterdep<I,V>& c, bool& error);
    friend void borrar<I,V>(I id, colecInterdep<I,V>& c);

    /* Operaciones iterador */

    friend void iniciarIterador<I,V>(colecInterdep<I,V>& c);
    friend bool existeSiguiente<I,V>(colecInterdep<I,V>& c);
    friend I siguienteIdent<I,V>(colecInterdep<I,V>& c);
    friend V siguienteVal<I,V>(colecInterdep<I,V>& c);
    friend bool siguienteDependiente<I,V>(colecInterdep<I,V>& c);
    friend I siguienteSuperior<I,V>(colecInterdep<I,V>& c);
    friend unsigned siguienteNumDependientes<I,V>(colecInterdep<I,V>& c);
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
        celdaColec* sig;    //sig es un puntero dirigido a la siguiente celda de la lista enlazada
    };

    int tamanio;            //tamanio contiene el entero correspodiente al número de celdas de la lista
    celdaColec* primero;    //primero es un puntero a la primera celda de la lista
    celdaColec* iter;       //iter es un puntero encargado de las operaciones del iterador

};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colecInterdep

/*
* Crea un colección vacía, sin elementos. Todos los punteros a nullptr y el tamaño a 0.
*/
template<typename I, typename V>
void crear(colecInterdep<I,V>& c){
    c.primero = nullptr;
    c.tamanio = 0;
    c.iter = nullptr; //por seguridad
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
* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id. Si la coleccion c es vacía es imposible que exista,
* si no es vacía, avanzamos hasta que encontremos la celda que tenga su identificador igual a id o lleguemos al final.
*/
template<typename I, typename V>
bool existe(I id, colecInterdep<I,V>& c){
    if(esVacia(c)){
        return false;
    }else {
        typename colecInterdep<I,V>::celdaColec* aux = c.primero;
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
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id. Si la colleción es vacia
* es imposible que exista, si no es vacía, avanzamos hasta encontrar la celda con ident igual a id o llegar al final.
* Si el puntero a sup de la celda encontrada es distinto de nullptr, es que es dependiente de alguien y devolvemos true 
* sino devolvemos false.
*/
template<typename I, typename V>
bool existeDependiente(I id, colecInterdep<I,V>& c){
    if(esVacia(c)){
        return false;
    }
    typename colecInterdep<I,V>::celdaColec* aux = c.primero;
    while(aux != nullptr && aux->ident != id){
        aux = aux->sig;
    }
    if(aux != nullptr && aux->sup != nullptr){      //es dependiente de alguien
        return true;
    }
    return false;
}

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id. Si la colleción es vacia
* es imposible que exista, si no es vacía, avanzamos hasta encontrar la celda con ident igual a id o llegar al final.
* Si el puntero a sup de la celda encontrada es nullptr, es que es independiente y devolvemos true sino devolvemos false.
*/
template<typename I, typename V>
bool existeIndependiente(I id, colecInterdep<I,V>& c){
    if(esVacia(c)){
        return false;
    }
    typename colecInterdep<I,V>::celdaColec* aux = c.primero;
    while(aux != nullptr && aux->ident != id){
        aux = aux->sig;
    }
    if(aux != nullptr && aux->sup == nullptr){
        return true;
    }
    
    return false;
}

/*
* Bucamos la posicion en la que tenemos que añadir el nuevo elemento y guardamos tambien la posicion anterior, 
* una vez encontrado se pone el puntero siguiente apuntando a la siguiente celda. Posteriormente creamos la nueva 
* celda y ponemos como puntero de la anterior a esta nueva y de la nueva celda de puntero ponemos siguiente.
*  Finalmente sumamos 1 a tamanio.
*/
template<typename I, typename V> 
void aniadirIndependiente(colecInterdep<I,V>& c, I id, V v){
    typename colecInterdep<I,V>::celdaColec* anterior = nullptr;            //puntero al anterior (de momento nullptr)
    typename colecInterdep<I,V>::celdaColec* actual = c.primero;            //puntero a la celda actual
    typename colecInterdep<I,V>::celdaColec* siguiente = nullptr;           //puntero a la siguiente celda del que vamos a añadir
    
    while(actual != nullptr && actual->ident < id){         //avanzamos a través de la lista hasta encontrar un ident mayor a id
        anterior = actual;                                  //anterior se actualiza a la celda actual
        actual = actual->sig;                               //actual avanza
    }

    if(actual != nullptr && actual->ident > id){            //compruebo que el ident actual efectivamente es mas grande y me lo guardo
       siguiente = actual;                                  //guardo el puntero al siguiente que tiene que apuntar la nueva celda
    }

    while(actual != nullptr && actual->ident != id){        //llego hasta el final de la lista para comprobar que no hay repetidos
        actual = actual->sig;
    }

    if(actual == nullptr){                                  //si actual=nullptr es que he llegado al final por lo que no hay repetidos
        typename colecInterdep<I,V>::celdaColec* nuevaCelda;             
        nuevaCelda = new typename colecInterdep<I,V>::celdaColec;            //añado la nueva celda
        nuevaCelda->ident = id;
        nuevaCelda->valor = v;
        nuevaCelda->sup = nullptr;
        nuevaCelda->numDep = 0;
        c.tamanio++;

        if(anterior == nullptr){        //si el nuevo id es menor que c.primero->ident hay que añadirlo el primero de la lsita
            nuevaCelda->sig = c.primero; 
            c.primero = nuevaCelda;      
        } else {                    //si no, se inserta entre el previo y el actual
            nuevaCelda->sig = siguiente;
            anterior->sig = nuevaCelda;    
        }
    }
}

/*
* Bucamos la posicion en la que tenemos que añadir el nuevo elemento a la vez comprobamos si pasamos por el padre
* en caso de encontrar el padre simplemente lo gusrdamos y seguimos buscando al hijo, sino al encontrar el hijo 
* seguimos iterando en busca del padre. Si encontramos al padre entonces creamos la nueva celda con sus valores y 
* en el puntero sup ponemos un puntero al padre. Finalmente sumamos 1 a tamanio.
*/
template<typename I, typename V> 
void aniadirDependiente(colecInterdep<I,V>& c, I id, V v, I sup){
    typename colecInterdep<I,V>::celdaColec* anterior = nullptr;        //puntero al anterior (de momento nullptr)
    typename colecInterdep<I,V>::celdaColec* actual = c.primero;        //puntero a la celda actual
    typename colecInterdep<I,V>::celdaColec* nodoSup = nullptr;         //puntero a la celda del elemento que es dependiente
    
    while(actual != nullptr && actual->ident < id){                 //avanzamos a través de la lista hasta encontrar un ident mayor a id
        
        if(actual->ident == sup){                   //comprobamos si de casualidad el identificador se corresponde con sup 
            nodoSup = actual;                       //(habríamos encontrado al padre -> elemento del que depende)
        }

        anterior = actual;                          //anterior se actualiza a la celda actual
        actual = actual->sig;                       //actual avanza
    }


    /*
    * Si salimos del bucle while es porque una de las condiciones no se cumple, es decir:
    *   - actual ha recorrido todas las celdas y no ha encontrado ningún identificador mayor a id (se añadirá el último si y solo si se ha encontrado el padre)
    *   - hemos encontrado un identificador mayor a id, por tanto ya tenemos el hueco donde añadirlo si y solo si hemos encontrado / encontramos al padre.
    */
    
    //hay que recorrer lo que nos queda para ver que no se repite el id y que encontramos si o si al padre si no lo hemos encontrado antes
    typename colecInterdep<I,V>::celdaColec* buscadorSup = actual;
    while(buscadorSup != nullptr && buscadorSup->ident != id){    //hay que encontar primero sup (el padre) antes de añadir
        
        if(buscadorSup->ident == sup){
            nodoSup = buscadorSup;                                //encontramos sup (es decir el padre)
        }

        buscadorSup = buscadorSup->sig;
    }
    
    //si buscadorSup no es nullptr significa que la condicion del while no se ha roto por llegar al final, sino por encontrar un duplicado 
    if(nodoSup != nullptr && buscadorSup == nullptr){  //solo añadimos el elemento si hemos encontrado a sup y buscadorSup ha recorrido todos los nodos

        nodoSup->numDep++;          //incrementamos su contador
        c.tamanio++;

        typename colecInterdep<I,V>::celdaColec* nuevaCelda;
        nuevaCelda = new typename colecInterdep<I,V>::celdaColec;
        nuevaCelda->ident = id;
        nuevaCelda->valor = v;
        nuevaCelda->sup = nodoSup;    //el puntero 'sup' apunta al nodo 'sup' encontrado
        nuevaCelda->numDep = 0;

        if(anterior == nullptr){        //si el nuevo 'id' es menor que c.primero->ident hay que añadirlo el primero de la lsita
            nuevaCelda->sig = c.primero; 
            c.primero = nuevaCelda;      
        } else {                    //si no, se inserta entre el previo y el actual
            nuevaCelda->sig = actual;    
            anterior->sig = nuevaCelda;    
        }
    }
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
    if(id == sup){
        return; //son iguales entonces no hace nada
    }
    typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
    //Buscas o padre o hijo
    if(c.tamanio < 2){
        return; //no puede hacer nada
    }
    while(aux1 != nullptr && id != aux1->ident && sup != aux1->ident){
        aux1 = aux1->sig;
    }

    if(aux1 != nullptr){
        typename colecInterdep<I,V>::celdaColec* aux2 = aux1;
        if(aux2->ident == id){
            //es el hijo
            if(aux2->sup == nullptr){//era independiente
                //buscas al padre
                while(aux1 != nullptr && aux1->ident != sup){
                    aux1 = aux1->sig;
                }//llegas al padre
                if(aux1 != nullptr){
                    aux1->numDep++;
                    aux2->sup = aux1;
                }
            }else{
                while(aux1 != nullptr && aux1->ident != sup){
                    aux1 = aux1->sig;
                }//llegas al padre
                if(aux1 != nullptr){
                    aux1->numDep++;
                    aux2->sup->numDep--; 
                    aux2->sup = aux1;
                }
            }
        }else{
            //es el padre
            //buscas al hijo
            while(aux1 != nullptr && aux1->ident != id){
                aux1 = aux1->sig;
            }//llegas al hijo
            if(aux1 != nullptr){
                if(aux1->sup != nullptr){
                    aux1->sup->numDep--; 
                    aux2->numDep++;
                    aux1->sup = aux2;
                }else{//independiente
                    aux2->numDep++;
                    aux1->sup = aux2;
                }
            }
        }
    }
}

/*
* Recorre la lista en busca de id. Si lo encuentra decrementa numDep de sup en nuo y pone sup de id en null, sino 
* lo encuentra devuelve la coleccion original. 
*/
template<typename I, typename V> 
void hacerIndependiente(colecInterdep<I,V>& c, I id){
    //Buscas al hijo
    if(!esVacia(c)){
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){
            aux1 = aux1->sig;
        }//localizas al que quieres hacer independiente
        if(aux1 != nullptr && aux1->sup != nullptr){
            aux1->sup->numDep--; 
            aux1->sup = nullptr;
        }
    }
}

/*
* Recorre la lista en busca de id. Si lo encuentra cambia el valor del valor a V y devuelve true debido a que
* es parcial (si la lista es vacia o id no existe no puede cambiar el valor), sino devuelve false debido a que no 
* ha podido cambiar el valor.
*/
template<typename I, typename V> 
bool actualizarVal(colecInterdep<I,V>& c, I id, V v){
    if(esVacia(c)){     //si la colección es vacía no puede existir un nodo con identificador "id"
        return false;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){        //si llegamos hasta el final significa que no existe
            return false;
        } else if(aux1 != nullptr && aux1->ident == id){    //comprobamos que realmente estamos en el caso que queremos estar
            aux1->valor = v;     //cambiamos el valor sin tener en cuenta si es dep o indep porque no hace falta
            return true;
        } else {
            return false;
        }
    }
}

/*
* Recorre la lista en busca de id. Si lo encuentra devuelve el valor pone error a false debido a que
* es parcial (si la lista es vacia o id no existe no id no puede obtener el valor), sino
* pone error a true debido a que no ha podido obtener el valor.
*/
template<typename I, typename V> 
V obtenerVal(I id, colecInterdep<I,V>& c, bool& error){
    if(esVacia(c)){
        error = true;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){        //si llegamos hasta el final significa que no existe (se puede optimizar este bucle con 1 solo if en verdad)
            error = true;
        } else if(aux1 != nullptr && aux1->ident == id){    //comprobamos que realmente estamos en el caso que queremos estar
            error = false;
            return aux1->valor;     //devolvemos el valor y actualizamos error a falso
        } else {
            error = true;
        }
    }
    return V();
}

/*
* Recorre la lista en busca de id. Si lo encuentra devuelve el id del supervisor y pone error a false debido a que
* es parcial (si la lista es vacia o id no existe no id no puede obtener el id de sup), sino pone error a true.
*/
template<typename I, typename V> 
I obtenerSupervisor(I id, colecInterdep<I,V>& c, bool& error){
    if(esVacia(c)){
        error = true;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){       //si llegamos hasta el final significa que no existe (se puede optimizar este bucle con 1 solo if en verdad)
            error = true;
        } else if(aux1 != nullptr && aux1->ident == id && aux1->sup != nullptr){ //comprobamos que la celda existe y es dependiente
            error = false;
            return aux1->sup->ident;
        } else {
            error = true;
        }
    }
    return I();
}

/*
* Recorre la lista en busca de id. Si lo encuentra devuelve numDep y pone error a false debido a que
* es parcial (si la lista es vacia o id no existe no id no puede obtener el id de sup), sino pone error a true.
*/
template<typename I, typename V> 
unsigned obtenerNumDependientes(I id, colecInterdep<I,V>& c, bool& error){
    if(esVacia(c)){
        error = true;
    } else {
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){          //buscamos la celda con indentificador "id"
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){       //si llegamos hasta el final significa que no existe (se puede optimizar este bucle con 1 solo if en verdad)
            error = true;
        } else if(aux1 != nullptr && aux1->ident == id){ //comprobamos que la celda existe y es dependiente
            error = false;
            return aux1->numDep;
        } else {
            error = true;
        }

    }
    return 0;
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


//OPERACIONES ITERADOR

/*
* Inicializa el iterador.
*/
template<typename I, typename V>
void iniciarIterador(colecInterdep<I,V>& c){
    c.iter = c.primero;
    return;
}

/*
* Devuelve verdad si el siguiente a el nodo al que apunta el iterador es distinto de null
*/
template<typename I, typename V>
bool existeSiguiente(colecInterdep<I,V>& c){
    return c.iter != nullptr;
}

/*
* Nos devuelve el identificador del nodo al que apunta el iterador.
*/
template<typename I, typename V>
I siguienteIdent(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){   
        return c.iter->ident;
    }
    return I();
}

/*
* Nos devuelve el valor del nodo al que apunta el iterador.
*/
template<typename I, typename V>
V siguienteVal(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        return c.iter->valor;
    }
    return V();
}

/*
* Si el nodo al que apunta el iterador es dependiente devuelve true
*/
template<typename I, typename V> 
bool siguienteDependiente(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        return c.iter->sup != nullptr;
    }
    return false;
}

/*
* Nos devuelve el id del sup del nodo al que apunta el iterador.
*/
template<typename I, typename V>
I siguienteSuperior(colecInterdep<I,V>& c){
    if(siguienteDependiente(c)){
        return c.iter->sup->ident;
    }
    return I();
}

/*
* Nos devuelve el numDep de el nodo al que apunta el iterador.
*/
template<typename I, typename V>
unsigned siguienteNumDependientes(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        return c.iter->numDep;
    }
    return 0;
}

/*
* Avanza el iterador al siguente nodo.
*/
template<typename I, typename V>
void avanza(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        c.iter = c.iter->sig;
    }
    return;
}

#endif