/**
 * @file ListaCircular.hpp
 * @authors Cadena Jeremy - Dylan Tipan
 * @brief Clase Lista Circular
 * @version 0.4
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
    /**
     * @brief Construye un nuevo objeto de la ListaCircular
     * 
     */
    ListaCircular();

    /**
     * @brief Agrega nuevo Nodos de Vehiculos a la lista
     * 
     */
    void agregar();

    /**
     * @brief Verifica si nuestra lista esta vacia
     * 
     * @return true 
     * @return false 
     */
    bool vacia();

    /**
     * @brief Muestra el primer vehiculo ingresado en la lista y sus sucesivos
     * 
     */
    void consultarPrimero();

    /**
     * @brief Muestra el ultimo vehiculo ingresado en la lista hasta el primero
     * 
     */
    void consultarUltimo();

    /**
     * @brief Elimina un vehiculo de la lista
     * 
     */
    void borrar();

    /**
     * @brief Busca un vehiculo ingresado anteriormente
     * 
     */
    void buscar();
};