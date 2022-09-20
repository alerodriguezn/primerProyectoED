#include <iostream>

using namespace std;

/*  ESTRUCTURAS   */
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
}*listaPersonas;

struct lluvia{
    string codigo;
    string nombre;
    int rangoPromedioEn_mm;
    lluvia* sig;

    lluvia(string cod, string nom, int rPm){
        codigo = cod;
        nombre = nom;
        rangoPromedioEn_mm = rPm;
        sig = NULL;
    }
} *listaLluvia;

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
} *listaRegion;

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
    
} *listaLugar;

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

/*  INSERTAR DE CADA UNA DE LAS ESTRUCTURAS */

lluvia * insertarLluvia(string codigo, string nombre, int rangoPromedioEn_mm, lluvia * lista)
{
    lluvia * nuevoDato = new lluvia(codigo, nombre, rangoPromedioEn_mm);
    nuevoDato->sig = lista;
    lista = nuevoDato;
    return lista;
}

region * insertarRegion(int id, string nom, string ubi, region * lista)
{
    region* nuevoDato = new region(id, nom, ubi);
    nuevoDato->sig = lista;
    lista = nuevoDato;
    return lista;
}

lugar * insertarLugar(string nom, int pob, double met, lugar * lista){
    lugar * nuevoDato = new lugar(nom, pob, met);
    if (lista == NULL){
        lista = nuevoDato;
        nuevoDato->sig = lista;
    }
    else{
        nuevoDato->sig = lista;
        //BUSCAR AL ÚLTIMO PARA QUE APUNTE AL NUEVO NODO.
        lugar * temp = lista;
        while (temp->sig != lista){
            temp = temp->sig;
        }
        temp->sig = nuevoDato;
        lista = nuevoDato;
    }
    return lista;
}

personas *insertarPersona(string nombre, int cedula, string lugarResidencia, string agnoResidencia){

    personas * nuevaPersona = new personas(nombre, cedula, lugarResidencia,agnoResidencia);
    if (listaPersonas == NULL)
    {
        listaPersonas = nuevaPersona;
    }

    else if (nombre[0] < listaPersonas->nombre[0])
    {               
        listaPersonas->ant = nuevaPersona;
        listaPersonas = nuevaPersona;
    }

    else{
        personas* temp = listaPersonas;
        personas* te = listaPersonas;
        while ((temp != NULL) &&(nombre[0] >= temp->nombre[0]))
        {
            te = temp;
            temp = temp->sig;
        }
        nuevaPersona->ant = te;
        te->sig = nuevaPersona;
        if (temp != NULL)
        {
            nuevaPersona->sig = temp;
            temp->ant = nuevaPersona;
        }
        return listaPersonas;
        
    }
}

/*IMPRIMIR DE CADA UNO DE LOS INSERTAR*/

void imprimirLluvia(lluvia * lista)
{
    if (lista == NULL){
        cout << "\nLa lista se encuentra vacia..." << endl;
    } else{
        lluvia * temp = lista;
        while (temp != NULL){
            cout << temp->codigo << "\t" << temp->nombre << "\t" << temp->rangoPromedioEn_mm << endl;
            temp = temp->sig;
        }
        cout << endl;
    }
}

void imprimirRegion(region * lista)
{
    if (lista == NULL){
        cout << "\nLa lista se encuentra vacia..." << endl;
    } else{
        region * temp = lista;
        while (temp != NULL){
            cout << temp->id << "\t" << temp->nombre << "\t" << temp->ubicacion << endl;
            temp = temp->sig;
        }
        cout << endl;
    }
}

void imprimirLugar(lugar * lista){
    if(lista == NULL){
        cout << "\nLa lista está vacía";
    }
    else{
        lugar * temp = lista;
        do{
            cout << temp->nombre << "\t" << temp->poblacion << "\t" << temp->metrosCuadrados << endl;
            temp = temp->sig;
        }while(temp != lista);
    }
}

void imprimirPersonas(personas* lista){
    if(lista == NULL)
        cout << "\nLA LISTA ESTA VACIA\n";
    else{
        personas * temp = lista;
        cout << "\nIMPRIMIENTO HACIA ADELANTE... \n";
        while(temp->sig!=NULL){
            cout<<"Nombre: "<<temp->nombre<<endl;
            temp = temp->sig;
        }
        cout<<"Nombre: "<<temp->nombre<<endl;
        //AHORA IMPRIMO HACIA ATRAS
        cout << "\nIMPRIMIENTO HACIA ATRAS... \n";
        while(temp!=NULL){
            cout<<"Nombre: "<<temp->nombre<<endl;
            temp = temp->ant;
        }
    }

}



/*  OTROS MÉTODOS   */
void cargarDatos()
{
    listaLluvia = insertarLluvia("COD#1", "NombreL#1", 01, listaLluvia);
    listaLluvia = insertarLluvia("COD#2", "NombreL#2", 02, listaLluvia);
    listaLluvia = insertarLluvia("COD#3", "NombreL#3", 03, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 04, listaLluvia);

    listaRegion = insertarRegion(01, "Region#1", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(02, "Region#2", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(03, "Region#3", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(04, "Region#4", "Ubicaicacio1", listaRegion);

    listaLugar = insertarLugar("Lugar#1", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Lugar#2", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Lugar#3", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Lugar#4", 100, 2.5, listaLugar);


    listaPersonas = insertarPersona("Alejandro Rodriguez", 208360735, "El Tanque","2018");
    listaPersonas = insertarPersona("Juan Ca", 2081230735, "La Fortuna","2013");
    listaPersonas = insertarPersona("Beto Beto", 1011230735, "San Rafael","2022");
    listaPersonas = insertarPersona("Roberto Jimenez", 3011230735, "Florencia","2021");
    listaPersonas = insertarPersona("Alondra", 4011230735, "Santa Clara","2024");
    listaPersonas = insertarPersona("Carlos Ruiz", 3011230735, "Florencia","2021");
    listaPersonas = insertarPersona("Bianca Ruiz", 4011230735, "Florencia","2022");
}

int main()
{
    cargarDatos();

    imprimirLluvia(listaLluvia);
    imprimirRegion(listaRegion);
    imprimirLugar(listaLugar);
    imprimirPersonas(listaPersonas);

    return 0;
}