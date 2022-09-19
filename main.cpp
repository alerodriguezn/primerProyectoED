#include <iostream>

using namespace std;

struct personas{
    string nombre;
    int cedula;
    string lugarResidencia;
    string agnoResidencia;
    struct tiempo* sublistasTiempos;


    personas* sig;
    personas* ant;

    personas(string nombre, int cedula, string lugarResidencia, string agnoResidencia){
        this->nombre = nombre;
        this->cedula = cedula;
        this->lugarResidencia = lugarResidencia;
        this->agnoResidencia = agnoResidencia;
        sig = NULL;
        ant = NULL;
    }

    void agregarTiempo (tiempo* nuevoTiempo){
        //Aquí iría el metodo de agregar un tiempo a la sublista de tiempos o directamente mandar una lista de tiempos
        cout << "Agregando nuevo registro de tiempo";
    }
};

struct lluvia{
    string codigo;
    string nombre;
    int rangoPromedioEn_mm;

    lluvia* sig;

    lluvia(string codigo, string nombre, int rangoPromedioEn_mm){
        codigo = codigo;
        nombre = nombre;
        rangoPromedioEn_mm = rangoPromedioEn_mm;
        sig = NULL;
    }
};

struct region{
    int id;
    string nombre;
    string ubicacion;
    struct lugar*sublistasLugares;

    region* sig;

    region(int id, string nombre, string ubicacion){
        this->id = id;
        this->nombre = nombre; 
        this->ubicacion = ubicacion;
        sig = NULL;
    }

    void agregarLugar(struct lugar*nuevoLugar){
        //Aqui iria la funcion de agregar lugar 
        cout << "Agregando nuevo lugar";
    }
};

struct lugar{
    string nombre;
    int poblacion;
    double metrosCuadrados;
    struct tiempo* sublistasTiempos;

    lugar* sig;

    lugar(string nombre, int poblacion, double metrosCuadrados){
        this->nombre = nombre;
        this->poblacion = poblacion;
        this->metrosCuadrados = metrosCuadrados;
        sig = NULL;
    }

    void agregarTiempo (tiempo* nuevoTiempo){
        //Aquí iría el metodo de agregar un tiempo a la sublista de tiempos o directamente mandar una lista de tiempos
        cout << "Agregando nuevo registro de tiempo";
    }
    
};



struct efimeridad{
    string nombre;
    string fecha;
    string horaSalida;
    string horaOcultamiento;

    efimeridad* sig;
    efimeridad* ant;

    efimeridad(string nombre, string fecha, string horaSalida, string horaOcultamiento){
        this->nombre = nombre;
        this->fecha = fecha;
        this->horaSalida = horaSalida;
        this->horaOcultamiento = horaOcultamiento;
        sig = NULL;
        ant = NULL;
    }
};

struct  tiempo
{
    int precipitacion;
    int tempMaxima;
    int tempMinima;
    int velocidadViento;
    int direccionViento;
    int humedadRelativa;
    bool siLlovio;
    lluvia*sublistasLluvias;

    tiempo* sig;

    tiempo(int precipitacion, int tempMaxima, int tempMinima, int velocidadViento, int direccionViento, int humedadRelativa, bool siLlovio){
        this->precipitacion = precipitacion;
        this->tempMaxima = tempMaxima;
        this->tempMinima = tempMinima;
        this->velocidadViento = velocidadViento;
        this->direccionViento = direccionViento;
        this->humedadRelativa = humedadRelativa;
        this->siLlovio = siLlovio;
        sig = NULL;
    }

    void agregarLluvia (lluvia* nuevaLluvia){
        //Aquí iría el metodo de agregar la lluvia a la sublista de lluvias o directamente mandar una lista de lluvias
        cout << "Agregando nuevo registro de lluvia";
    }

};


int main()
{
    return 0;
}
