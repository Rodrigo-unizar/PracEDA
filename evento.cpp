/* Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

#include "evento.hpp"

//Implementacion de las operaciones del TAD evento

/* Devuelve un evento compuesto por una descripción desc y con una prioridad prio.*/
void crearEvento(string desc, unsigned prio, evento& e){
    e.desc = desc;
    e.prio = prio;
}

/* 
* Dado un evento formado por la tupla (D,P) devuelve la cadena 
* correspondiente a la descripcion del evento e.
*/
string descripcion(const evento& e){
    return e.desc;
}

/* 
* Dado un evento formado por la tupla (D,P) devuelve un evento
* igual al compuesto formado por la tupla (nuevaDesc, P).
*/
void cambiarDescripcion(string nuevaDesc, evento& e){
    e.desc = nuevaDesc;
}

/* 
* Dado un evento formado por la tupla (D,P) devuelve el natural
* correspondiente a la prioridad del evento e.
*/
unsigned suPrioridad(const evento& e){
    return e.prio;
}


/*
* Dado un evento formado por la tupla (D,P) devuelve un evento
* igual al compuesto formado por la tupla (D, prio).
*/
void cambiarPrioridad(unsigned prio, evento& e){
    e.prio = prio;
}