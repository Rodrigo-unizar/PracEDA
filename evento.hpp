/* Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <iostream>
using namespace std;

// PREDECLARACION DEL TAD contacto (inicio INTERFAZ)

/* Los valores del TAD evento representan tuplas formadas por 2 elementos, tal y como:
* (descripción, prioridad) siendo la descripción una cadena y la prioridad un número natural.
*/
struct evento;

/* Devuelve un evento compuesto por una descripción desc y con una prioridad prio.*/
void crearEvento(string desc, unsigned prio, evento& e);

/* Dado un evento formado por la tupla (D,P) devuelve la cadena 
* correspondiente a la descripcion del evento e.
*/
string descripcion(const evento& e);

/* Dado un evento formado por la tupla (D,P) devuelve un evento
* igual al compuesto formado por la tupla (nuevaDesc, P).
*/
void cambiarDescripcion(string nuevaDesc, evento& e);

/* Dado un evento formado por la tupla (D,P) devuelve el natural
* correspondiente a la prioridad del evento e.
*/
unsigned suPrioridad(const evento& e);

/* Dado un evento formado por la tupla (D,P) devuelve un evento
* igual al compuesto formado por la tupla (D, prio).
*/
void cambiarPrioridad(unsigned prio, evento& e);

// FIN de la PREDECLARACION DEL TAD evento (fin INTERFAZ)

// DECLARACION DEL TAD evento

struct evento{
    friend void crearEvento(string desc, unsigned prio, evento& e);
    friend string descripcion(const evento& e);
    friend void cambiarDescripcion(string nuevaDesc, evento& e);
    friend unsigned suPrioridad(const evento& e);
    friend void cambiarPrioridad(unsigned prio, evento& e);

    private:                //declaracion de la representacion interna del tipo
        string desc;        // desc contiene la cadena que corresponde con la descripción del evento
        unsigned prio;      // prio contiene el natural correspondiente a la prioridad del evento
};

#endif