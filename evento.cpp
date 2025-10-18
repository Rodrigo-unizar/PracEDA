/* Razvan Ghita Calangiu 927460, Rodrigo Herce Alonso 935413
*/

#include "evento.hpp"

//Implementacion de las operaciones del TAD evento

void crearEvento(string desc, unsigned prio, evento& e){
    e.desc = desc;
    e.prio = prio;
}

string descripcion(const evento& e){
    return e.desc;
}

void cambiarDescripcion(string nuevaDesc, evento& e){
    e.desc = nuevaDesc;
}

unsigned suPrioridad(const evento& e){
    return e.prio;
}

void cambiarPrioridad(unsigned prio, evento& e){
    e.prio = prio;
}