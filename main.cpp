#include <iostream>

using namespace std;

struct personas{
    string nombre;
    int cedula;
    string lugarResidencia;
    string añoResidencia;

    personas* sig;
    personas* ant;

};

struct lluvia{
    string codigo;
    string nombre;
    int rangoPromedioEn_mm;

    lluvia* sig;
};

struct region{
    int id;
    string nombre;
    string ubicacion;
    struct lugar*sublistasLugares;

    region* sig;

};

struct lugar{
    string nombre;
    int poblacion;
    double metrosCuadrados;

    lugar* sig;
};

struct efimeridad{
    string nombre;
    string fecha;
    string horaSalida;
    string horaOcultamiento;

    efimeridad* sig;
    efimeridad* ant;

};



int main()
{
    return 0;
}
