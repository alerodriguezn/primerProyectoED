#include <iostream>

using namespace std;

struct personas{
    string nombre;
    int cedula;
    string lugarResidencia;
    string agnoResidencia;

    personas* sig;
    personas* ant;

    personas(string n, int c, string lr, string ar){
        nombre = n;
        cedula = c;
        lugarResidencia = lr;
        agnoResidencia = ar;
    }

};

struct lluvia{
    string codigo;
    string nombre;
    int rangoPromedioEn_mm;

    lluvia* sig;

    lluvia(string c, string n, int rp){
        codigo = c;
        nombre = n;
        rangoPromedioEn_mm = rp;
    }
};

struct region{
    int id;
    string nombre;
    string ubicacion;
    struct lugar*sublistasLugares;

    region* sig;

    region(int i, string n, string u){
        id = i;
        nombre = n; 
        ubicacion = u;
    }

    void agregarLugar(struct lugar*sublistasLugares){
        //Aqui iria la funcion de agregar lugar 
        cout << "Agregando nuevo lugar";
    }
};

struct lugar{
    string nombre;
    int poblacion;
    double metrosCuadrados;

    lugar* sig;

    lugar(string n, int p, double mc){
        nombre = n;
        poblacion = p;
        metrosCuadrados = mc;
    }
};

struct efimeridad{
    string nombre;
    string fecha;
    string horaSalida;
    string horaOcultamiento;

    efimeridad* sig;
    efimeridad* ant;

    efimeridad(string n, string f, string hs, string ho){
        nombre = n;
        fecha = f;
        horaSalida = hs;
        horaOcultamiento = ho;
    }
};



int main()
{
    return 0;
}
