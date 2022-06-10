/**
 * @file Vehiculo.hpp
 * @authors Cadena Jeremy - Tipan Dylan 
 * @brief Clase Vehiculo
 * @version 0.1
 * @date 2022-06-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
class Vehiculo {

public:
       
private:

    char marca[12];
    char placaVehicular[10];
    char nombrePropietario[40];
    Vehiculo *siguiente;
    Vehiculo *anterior;
    friend class ListaCircular;
};