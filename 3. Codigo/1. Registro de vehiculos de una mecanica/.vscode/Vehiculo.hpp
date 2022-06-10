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