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
template<typename I, typename V> struct colecInterdep;

/*
* Crea un colección vacía, sin elementos.
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
* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.
*/
template<typename I, typename V> bool existe(I id, colecInterdep<I,V>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id, es
* decir un elemento (id, v, idSup, NumDep).
*/
template<typename I, typename V> bool existeDependiente(I id, colecInterdep<I,V>& c);

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id, es
* decir un elemento (id, v, -, NumDep).
*/
template<typename I, typename V> bool existeIndependiente(I id, colecInterdep<I,V>& c);

/*
* Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
* independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.
*/
template<typename I, typename V> void aniadirIndependiente(colecInterdep<I,V>& c, I id, V v);

/*
* Si no existe?(id,c) y existe?(super,c) devuelve una colección igual a la resultante de:
* incrementar en 1 el número de elementos dependientes del elemento con identificador super en c, y
* de añadir el elemento (id,v,super,0) a la colección c. En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> void aniadirDependiente(colecInterdep<I,V>& c, I id, V v, I sup);


template<typename I, typename V> void hacerDependiente(colecInterdep<I,V>& c, I id, I sup);


template<typename I, typename V> void hacerIndependiente(colecInterdep<I,V>& c, I id);
/*
template<typename I, typename V> void actualizarVal(colecInterdep<I,V>& c, I id, V v);

template<typename I, typename V> void obtenerVal(colecInterdep<I,V>& c, I id, V v);
*/


//Operaciones iterador

/*
* Inicializa el iterador para recorrer los elementos de la colección c, de forma que el siguiente
* elemento a visitar sea el que tiene un ident anterior a los de todos los demás elementos de la
* colección (situación de no haber visitado ningún elemento). 
*/
template<typename I, typename V> void iniciarIterador(colecInterdep<I,V>& c);

/*
* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección c, devuelve
* falso si ya se ha visitado el último elemento.
*/
template<typename I, typename V> bool existeSiguiente(colecInterdep<I,V>& c);

/*
* Si existeSiguiente(c), devuelve el ident del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> I siguienteIdent(colecInterdep<I,V>& c);

/*
* Si existeSiguiente(c), devuelve el valor del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> V siguienteVal(colecInterdep<I,V>& c);

/*
* Si existeSiguiente(c), si el siguiente elemento a visitar con el iterador de la colección,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados,
* es de la forma (ident, val, -, numDep) devuelve falso, pero si es de la forma (ident, val, identSup, numDep) devuelve verdad. 
*/
template<typename I, typename V> bool siguienteDependiente(colecInterdep<I,V>& c);

/*
* Si existeSiguiente(c) y siguienteDependiente(c), si el siguiente elemento a visitar con el iterador
* de la colección, que será el elemento no visitado con ident anterior a los de todos los demás aún
* no visitados, es de la forma (ident, val, identSup, numDep), devuelve su identSup.
*/
template<typename I, typename V> I siguienteSuperior(colecInterdep<I,V>& c);

/*
* Si existeSiguiente(c), devuelve el NumDep del siguiente elemento a visitar con el iterador de la colección c, que
* será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V> unsigned siguienteNumDependientes(colecInterdep<I,V>& c);

/*
* Si existeSiguiente?(c), avanza el iterador de la colección c para que se pueda visitar otro elemento.
*/
template<typename I, typename V> void avanza(colecInterdep<I,V>& c);

// FIN predeclaracion del TAD GENERICO agrupacion (Fin INTERFAZ)


// DECLARACION DEL TAD GENERICO agrupacion

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

    //Operaciones iterador

    friend void iniciarIterador<I,V>(colecInterdep<I,V>& c);
    friend bool existeSiguiente<I,V>(colecInterdep<I,V>& c);
    friend I siguienteIdent<I,V>(colecInterdep<I,V>& c);
    friend V siguienteVal<I,V>(colecInterdep<I,V>& c);
    friend bool siguienteDependiente<I,V>(colecInterdep<I,V>& c);
    friend I siguienteSuperior<I,V>(colecInterdep<I,V>& c);
    friend unsigned siguienteNumDependientes<I,V>(colecInterdep<I,V>& c);
    friend void avanza<I,V>(colecInterdep<I,V>& c);
    
  private: //declaracion de la representacion interna del tipo
    
    struct celdaColec{  //{cada elemento de la colección se almacena en una celda}
        I ident;            //ident contiene la cadena correspondiente al nombre del evento 
        V valor;            //valor es de tipo genérico, en este caso lo utilizaremos con el TAD evento
        I sup;              //sup contiene la cadena correspodiente al nombre del evento superior (del que depende este), si no depende (-) 
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
template<typename I, typename V>
void crear(colecInterdep<I,V>& c){
    c.primero = nullptr;
    c.tamanio = 0;
    //c.iter = nullptr; podriamos ponerlo por seguridad pero lo q veas
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
* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.
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
* Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id, es
* decir un elemento (id, v, idSup, NumDep).
*/
template<typename I, typename V>
bool existeDependiente(I id, colecInterdep<I,V>& c){
    typename colecInterdep<I,V>::celdaColec* aux = c.primero;
    if(existe(id,c)){
        while(aux != nullptr && aux->ident != id){
            aux = aux->sig;
        }
        if(aux != nullptr && aux->sup == "-"){
            return false;
        }else{
            return true;
        }
    }
    return false;
}

/*
* Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id, es
* decir un elemento (id, v, -, NumDep).
*/
template<typename I, typename V>
bool existeIndependiente(I id, colecInterdep<I,V>& c){
    typename colecInterdep<I,V>::celdaColec* aux = c.primero;
    if(existe(id,c)){
        while(aux != nullptr && aux->ident != id){
            aux = aux->sig;
        }
        if(aux != nullptr && aux->sup == "-"){
            return true;
        }
    }
    return false;
}

/*
* Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
* independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.
*/
template<typename I, typename V> 
void aniadirIndependiente(colecInterdep<I,V>& c, I id, V v){
    // Puntero al nodo ANTERIOR al punto de inserción
    typename colecInterdep<I,V>::celdaColec* prev = nullptr; 
    // Puntero al nodo ACTUAL
    typename colecInterdep<I,V>::celdaColec* actual = c.primero;
    // Puntero al nodo que irá DESPUÉS del nuevo nodo
    typename colecInterdep<I,V>::celdaColec* siguiente = nullptr;

    while(actual != nullptr && actual->ident < id){
        prev = actual;    // 'prev' se actualiza al nodo actual
        actual = actual->sig; // 'actual' avanza
    }

    if(actual != nullptr && id < actual->ident){
       siguiente = actual;                          //guardo el puntero al siguiente que tiene que apuntar el nuevo nodo
    }

    while(actual != nullptr && actual->ident != id){
        actual = actual->sig;
    }

    if(actual == nullptr){
        typename colecInterdep<I,V>::celdaColec* nuevoNodo;
        nuevoNodo = new typename colecInterdep<I,V>::celdaColec;
        nuevoNodo->ident = id;
        nuevoNodo->valor = v;
        nuevoNodo->sup = "-";
        nuevoNodo->numDep = 0;
        c.tamanio++;

        if(prev == nullptr){        //si el nuevo 'id' es menor que c.primero->ident hay que añadirlo el primero de la lsita
            nuevoNodo->sig = c.primero; 
            c.primero = nuevoNodo;      
        } else {                    //si no, se inserta entre el previo y el actual
            nuevoNodo->sig = siguiente;
            prev->sig = nuevoNodo;    
        }
    }
}

/*
* Si no existe?(id,c) y existe?(super,c) devuelve una colección igual a la resultante de:
* incrementar en 1 el número de elementos dependientes del elemento con identificador super en c, y
* de añadir el elemento (id,v,super,0) a la colección c. En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename I, typename V> 
void aniadirDependiente(colecInterdep<I,V>& c, I id, V v, I sup){
    
    // Puntero al nodo ANTERIOR al punto de inserción
    typename colecInterdep<I,V>::celdaColec* prev = nullptr; 
    // Puntero al nodo ACTUAL
    typename colecInterdep<I,V>::celdaColec* actual = c.primero;
    // Puntero para guardar el nodo 'sup' SI lo encontramos
    typename colecInterdep<I,V>::celdaColec* nodoSup = nullptr;
    
    while(actual != nullptr && actual->ident < id){    //avanzamos 'actual' hasta encontrar el punto de inserción
        
        if(actual->ident == sup){     //comprobamos por el camino si alguno de los nodos es 'sup'
            nodoSup = actual; 
        }

        prev = actual;    // 'prev' se actualiza al nodo actual
        actual = actual->sig; // 'actual' avanza
    }

    /*
    * Salimos del bucle. Ahora tenemos dos posibilidades:
    * 1. actual == nullptr (llegamos al final de la lista)
    * 2. actual->ident >= id (encontramos el punto de inserción)
    */

    // AHORA: 'actual' apunta al nodo que debe ir DESPUÉS del nuevo.
    // 'prev' apunta al nodo que debe ir ANTES.
    // PERO, 'sup' podría estar MÁS ADELANTE en la lista.
    // Debemos continuar el recorrido (desde 'actual') hasta el final, 
    // solo para asegurarnos de encontrar 'sup' si aún no ha aparecido.
    
    typename colecInterdep<I,V>::celdaColec* buscadorSup = actual;
    while(buscadorSup != nullptr && buscadorSup->ident != id){    //hay que encontar primero 'sup' antes de añadir
        
        if(buscadorSup->ident == sup){
            nodoSup = buscadorSup;                                //encontramos 'sup'
        }

        buscadorSup = buscadorSup->sig;
    }
    

    if(nodoSup != nullptr && buscadorSup == nullptr){  //solo añadimos el elemento si existe 'sup' y 'buscadorSup' ha recorrido todos los nodos

        nodoSup->numDep++;          //incrementamos su contador
        c.tamanio++;

        typename colecInterdep<I,V>::celdaColec* nuevoNodo;
        nuevoNodo = new typename colecInterdep<I,V>::celdaColec;
        nuevoNodo->ident = id;
        nuevoNodo->valor = v;
        nuevoNodo->sup = sup;
        nuevoNodo->numDep = 0;

        if(prev == nullptr){        //si el nuevo 'id' es menor que c.primero->ident hay que añadirlo el primero de la lsita
            nuevoNodo->sig = c.primero; 
            c.primero = nuevoNodo;      
        } else {                    //si no, se inserta entre el previo y el actual
            nuevoNodo->sig = actual;    
            prev->sig = nuevoNodo;    
        }
    }
}

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

    if(aux1 != nullptr && aux1->ident == sup){ //si encuentra al padre nuevo lo guarda en aux2 y busca el "hijo" 
        typename colecInterdep<I,V>::celdaColec* aux2 = aux1; //nuevo padre en aux2

        while(aux1 != nullptr && id != aux1->ident){
            aux1 = aux1->sig;
        }

        if(aux1 == nullptr){
            //si entra aqui es que no hay hijo por lo que no tine que hacer nada
        }else{
            //Antes era independiente
            if(aux1->sup == "-"){
                aux1->sup = sup;
                aux2->numDep++;
            }else{//antes era dependiente
                typename colecInterdep<I,V>::celdaColec* aux3 = aux1; //aux3 alamcena el hijo 
                if(aux3->sup < sup){//si el padre anterior esta antes de encontrar al nuevo padre
                    aux1 = c.primero; //iteras desde el principio hasta el nuevo padre
                }else if(aux3->sup < id){ //esta entre el padre nuevo y el hijo 
                    aux1 = aux2;//iteras desde el nuevo padre
                }//sino iteras desde el hijo hasta el final
                //como ya era padre asumiendo que no estan mal las operaciones anteriores ==> existe
                
                while(aux1 != nullptr && aux1->ident != aux3->sup){
                    aux1 = aux1->sig;
                }
                aux1->numDep--;//padre antiguo
                aux2->numDep++;//nuevo padre
                aux3->sup = sup;//hijo

            }
        }

    } else if(aux1 != nullptr && aux1->ident == id){
        if(aux1->sup == "-"){//el hijo es independiente?
            typename colecInterdep<I,V>::celdaColec* aux2 = aux1;  //aux2 hijo
            //busca al nuevo padre padres 
            while(aux1 != nullptr && sup != aux1->ident){
                aux1 = aux1->sig;
            }
            if(aux1 != nullptr && aux1->ident == sup){//ha encontrado al nuevo padre
                aux2->sup = sup;
                aux1->numDep++;
            }else{
                //no hay nuevo padre entonces no hace nada 
            }
        }else{
            typename colecInterdep<I,V>::celdaColec* aux2 = aux1;//aux2 hijo
            //busca cualquiera de los padres (se podria quitar de aqui el nullptr ya que el padre antigua tiene que existir)
            if(aux1->sup < sup){//si el padre anterior esta antes se vuelve a empezasr 
                aux1 = c.primero;
            }
            while(aux1 != nullptr && sup != aux1->ident && aux2->sup != aux1->ident){
                aux1 = aux1->sig;
            }

            if(aux1 == nullptr){
                //aqui no hace nada ya que no existe el nuevo padre por lo que no modifica nada
            }else if(aux1->ident == sup){//ha encontrado al nuevo padre
                typename colecInterdep<I,V>::celdaColec* aux3 = aux1; //aux3 alamcena al nuevo padre
                while(aux1 != nullptr && aux1->ident != aux2->sup){//busca al padre viejo no hay que poner nullptr ya que tiene que existir(si quieres ponlo tu)
                    aux1 = aux1->sig;
                }
                aux1->numDep--;//padre antiguo
                aux3->numDep++;//nuevo padre
                aux2->sup = sup;//hijo
            }else if(aux2->sup == aux1->ident){//
                typename colecInterdep<I,V>::celdaColec* aux3 = aux1; //aux3 alamcena al padre viejo
                while(aux1 != nullptr && sup != aux1->ident){//busca al padre nuevo
                    aux1 = aux1->sig;
                }
                if(aux1 ==nullptr){
                    //aqui no hace nada ya que no existe el nuevo padre por lo que no modifica nada
                }else{
                    aux3->numDep--;//padre antiguo
                    aux1->numDep++;//nuevo padre
                    aux2->sup = sup;//hijo
                }
            }
        }
    }
}


template<typename I, typename V> 
void hacerIndependiente(colecInterdep<I,V>& c, I id){
    //Buscas o padre o hijo
    if(!esVacia(c)){
        typename colecInterdep<I,V>::celdaColec* aux1 = c.primero;
        while(aux1 != nullptr && aux1->ident != id){
            aux1 = aux1->sig;
        }//localizas al que quieres hacer independiente
        if(aux1 != nullptr){
            typename colecInterdep<I,V>::celdaColec* aux2 = aux1;
            if(aux2->sup == "-"){
                //ya es independiente ==> no hace nada
            }else{
                if(aux2->sup < id){
                    aux1 = c.primero;
                }
                while(aux1 != nullptr && aux1->ident != aux2->sup){
                    aux1 = aux1->sig;
                }//llegas al antiguo padre
                aux1->numDep--;
                aux2->sup = "-";
            }
        }
    }
}

//OPERACIONES ITERADOR

/*
* Inicializa el iterador para recorrer los elementos de la colección c, de forma que el siguiente
* elemento a visitar sea el que tiene un ident anterior a los de todos los demás elementos de la
* colección (situación de no haber visitado ningún elemento). 
*/
template<typename I, typename V>
void iniciarIterador(colecInterdep<I,V>& c){
    c.iter = c.primero;
    return;
}

/*
* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección c, devuelve
* falso si ya se ha visitado el último elemento.
*/
template<typename I, typename V>
bool existeSiguiente(colecInterdep<I,V>& c){
    return c.iter != nullptr;
}

/*
* Si existeSiguiente(c), devuelve el ident del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V>
I siguienteIdent(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){   
        //typename colecInterdep<I>::celdaColec* aux = c.iter->sig;
        return c.iter->ident;
    }
}

/*
* Si existeSiguiente(c), devuelve el valor del siguiente elemento a visitar con el iterador de la colección c,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V>
V siguienteVal(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        //typename colecInterdep<I>::celdaColec* aux = c.iter->sig;
        return c.iter->valor;
    }
}

/*
* Si existeSiguiente(c), si el siguiente elemento a visitar con el iterador de la colección,
* que será el elemento no visitado con ident anterior a los de todos los demás aún no visitados,
* es de la forma (ident, val, -, numDep) devuelve falso, pero si es de la forma (ident, val, identSup, numDep) devuelve verdad. 
*/
template<typename I, typename V> 
bool siguienteDependiente(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        return c.iter->sup != "-";
    }
    return false;
}

/*
* Si existeSiguiente(c) y siguienteDependiente(c), si el siguiente elemento a visitar con el iterador
* de la colección, que será el elemento no visitado con ident anterior a los de todos los demás aún
* no visitados, es de la forma (ident, val, identSup, numDep), devuelve su identSup.
*/
template<typename I, typename V>
I siguienteSuperior(colecInterdep<I,V>& c){
    if(siguienteDependiente(c)){
        return c.iter->sup;
    }
    return "";
}

/*
* Si existeSiguiente(c), devuelve el NumDep del siguiente elemento a visitar con el iterador de la colección c, que
* será el elemento no visitado con ident anterior a los de todos los demás aún no visitados.
*/
template<typename I, typename V>
unsigned siguienteNumDependientes(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        return c.iter->numDep;
    }
}

/*
* Si existeSiguiente?(c), avanza el iterador de la colección c para que se pueda visitar otro elemento.
*/
template<typename I, typename V>
void avanza(colecInterdep<I,V>& c){
    if(existeSiguiente(c)){
        c.iter = c.iter->sig;
    }
    return;
}

#endif