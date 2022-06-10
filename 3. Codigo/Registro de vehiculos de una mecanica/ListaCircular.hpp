#pragma once
#include "Vehiculo.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fstream>

class ListaCircular {
private:
    Vehiculo *raiz = NULL;
public:
    ListaCircular();
    void agregar();
    bool vacia();
    void consultarPrimero();
    void consultarUltimo();
    void borrar();
    void buscar();
};