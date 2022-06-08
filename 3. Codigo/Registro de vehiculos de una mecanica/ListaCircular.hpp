#pragma once
#include "Vehiculo.hpp"

class ListaCircular {
private:
    Vehiculo *raiz;
public:
    ListaCircular();
    void agregar();
    bool vacia();
    void consultarPrimero();
    void consultarUltimo();
    void borrar();
    void buscar();
};