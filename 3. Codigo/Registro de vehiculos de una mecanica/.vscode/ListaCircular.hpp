#pragma once
#include "Vehiculo.hpp"
#include "menuInteractivo.cpp"
#include <iostream>
#include <string.h>
#include <fstream>

class ListaCircular {
private:
    Vehiculo *raiz=NULL;
public:
    ListaCircular();
    void agregar();
    bool vacia();
    void consultarPrimero();
    void consultarUltimo();
    void borrar();
    void buscar();
};