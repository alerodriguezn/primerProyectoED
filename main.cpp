#include <iostream>
#include <ctime>  //Libreria utilizada para el manejo de las fechas
#include <vector> //Libreria utilizada para el manejo de las fechas.
#include <string> //Libreria utilizada para la funcion "to_string"

using namespace std;

// Se crea un vector que almacenara los meses
vector<string> mes;
void llenarVectorMeses()
{
    mes.push_back("Enero");
    mes.push_back("Febrero");
    mes.push_back("Marzo");
    mes.push_back("Abril");
    mes.push_back("Mayo");
    mes.push_back("Junio");
    mes.push_back("Julio");
    mes.push_back("Agosto");
    mes.push_back("Septiembre");
    mes.push_back("Octubre");
    mes.push_back("Noviembre");
    mes.push_back("Diciembre");
}

/*  ESTRUCTURAS   */

// Estructura que relaciona Tiempo y Lugar
struct relTiempoLugar
{
    relTiempoLugar *sig;
    struct tiempo *enlace;
    relTiempoLugar()
    {
    }
};

// Estructura que relaciona Tiempo y Personas
struct relTiempoPersona
{
    relTiempoPersona *sig;
    struct tiempo *enlace;
    relTiempoPersona()
    {
    }
};

struct relRegionLugar
{
    relRegionLugar *sig;
    struct lugar *enlace;
    relRegionLugar()
    {
    }
};

struct relTiempoLluvia
{
    relTiempoLluvia *sig;
    struct lluvia *enlace;
    relTiempoLluvia()
    {
    }
};

// Estructura de Personas
struct personas
{
    string nombre;
    int cedula;
    string lugarResidencia;
    string agnoResidencia;
    struct relTiempoPersona *sublistasTiempos;

    personas *sig;
    personas *ant;

    personas(string nombre, int cedula, string lugarResidencia, string agnoResidencia)
    {
        this->nombre = nombre;
        this->cedula = cedula;
        this->lugarResidencia = lugarResidencia;
        this->agnoResidencia = agnoResidencia;
        sig = NULL;
        ant = NULL;
        sublistasTiempos = NULL;
    }

} * listaPersonas;
personas *loginPersona;

// Estructura de lluvia
struct lluvia
{
    string codigo;
    string nombre;
    int rangoPromedioEn_mm;
    lluvia *sig;

    lluvia(string cod, string nom, int rPm)
    {
        codigo = cod;
        nombre = nom;
        rangoPromedioEn_mm = rPm;
        sig = NULL;
    }
} * listaLluvia;

// Estructura de Region
struct region
{
    int id;
    string nombre;
    string ubicacion;
    struct relRegionLugar *sublistasLugares;

    region *sig;

    region(int id, string nombre, string ubicacion)
    {
        this->id = id;
        this->nombre = nombre;
        this->ubicacion = ubicacion;
        sig = NULL;
        sublistasLugares = NULL;
    }

    void agregarLugar(struct lugar *nuevoLugar)
    {
        // Aqui iria la funcion de agregar lugar
        cout << "Agregando nuevo lugar";
    }
} * listaRegion;

// Estructura de lugar
struct lugar
{
    string nombre;
    int poblacion;
    double metrosCuadrados;
    struct relTiempoLugar *sublistasTiempos;

    lugar *sig;

    lugar(string nombre, int poblacion, double metrosCuadrados)
    {
        this->nombre = nombre;
        this->poblacion = poblacion;
        this->metrosCuadrados = metrosCuadrados;
        sig = NULL;
        sublistasTiempos = NULL;
    }

} * listaLugar;

// Estructura de Efimeridad
struct efimeridad
{
    string nombre;
    tm *fecha;
    tm *horaSalida;
    tm *horaOcultamiento;

    efimeridad *sig;
    efimeridad *ant;

    efimeridad(string nombre, tm *fecha, tm *horaSalida, tm *horaOcultamiento)
    {
        this->nombre = nombre;
        this->fecha = fecha;
        this->horaSalida = horaSalida;
        this->horaOcultamiento = horaOcultamiento;
        sig = NULL;
        ant = NULL;
    }
} * listaEfimeridades;

// Estructura de Tiempo
struct tiempo
{
    tm *fecha;
    int precipitacion;
    int tempMaxima;
    int tempMinima;
    int velocidadViento;
    int direccionViento;
    int humedadRelativa;
    bool siLlovio;
    relTiempoLluvia *sublistasLluvias;
    tiempo *sig;

    tiempo(tm *fecha, int precipitacion, int tempMaxima, int tempMinima, int velocidadViento, int direccionViento, int humedadRelativa, bool siLlovio)
    {
        this->fecha = fecha;
        this->precipitacion = precipitacion;
        this->tempMaxima = tempMaxima;
        this->tempMinima = tempMinima;
        this->velocidadViento = velocidadViento;
        this->direccionViento = direccionViento;
        this->humedadRelativa = humedadRelativa;
        this->siLlovio = siLlovio;
        sig = NULL;
        sublistasLluvias = NULL;
    }

} * listaTiempo;

/*  INSERTAR DE CADA UNA DE LAS ESTRUCTURAS */

lluvia *insertarLluvia(string codigo, string nombre, int rangoPromedioEn_mm, lluvia *lista)
{
    lluvia *nuevoDato = new lluvia(codigo, nombre, rangoPromedioEn_mm);
    nuevoDato->sig = lista;
    lista = nuevoDato;
    return lista;
}

region *insertarRegion(int id, string nom, string ubi, region *lista)
{
    region *nuevoDato = new region(id, nom, ubi);
    nuevoDato->sig = lista;
    lista = nuevoDato;
    return lista;
}

lugar *insertarLugar(string nom, int pob, double met, lugar *lista)
{
    lugar *nuevoDato = new lugar(nom, pob, met);
    if (lista == NULL)
    {
        lista = nuevoDato;
        nuevoDato->sig = lista;
    }
    else
    {
        nuevoDato->sig = lista;
        // BUSCAR AL ULTIMO PARA QUE APUNTE AL NUEVO NODO.
        lugar *temp = lista;
        while (temp->sig != lista)
        {
            temp = temp->sig;
        }
        temp->sig = nuevoDato;
        lista = nuevoDato;
    }
    return lista;
}

personas *insertarPersona(string nombre, int cedula, string lugarResidencia, string agnoResidencia)
{

    personas *nuevaPersona = new personas(nombre, cedula, lugarResidencia, agnoResidencia);
    if (listaPersonas == NULL)
    {
        listaPersonas = nuevaPersona;
    }

    else if (nombre[0] < listaPersonas->nombre[0])
    {
        listaPersonas->ant = nuevaPersona;
        listaPersonas = nuevaPersona;
    }

    else
    {
        personas *temp = listaPersonas;
        personas *te = listaPersonas;
        while ((temp != NULL) && (nombre[0] >= temp->nombre[0]))
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
    }
    return listaPersonas;
}

// Me dice si la fecha 1 es mayor que la fecha 2
bool calcularFechaMayor(tm *fecha1, tm *fecha2)
{
    if (fecha1->tm_year > fecha2->tm_year)
        return true;
    if ((fecha1->tm_year == fecha2->tm_year) && (fecha1->tm_mon > fecha2->tm_mon))
        return true;
    if ((fecha1->tm_year == fecha2->tm_year) && (fecha1->tm_mon >= fecha2->tm_mon) && (fecha1->tm_mday >= fecha2->tm_mday))
        return true;
    return false;
}

// TERMINAR EL INSERTAR TIEMPO
tiempo *insertarTiempo(tm *fecha, int precipitacion, int tempMaxima, int tempMinima, int velocidadViento, int direccionViento, int humedadRelativa, bool siLlovio)
{

    tiempo *nuevoTiempo = new tiempo(fecha, precipitacion, tempMaxima, tempMinima, velocidadViento, direccionViento, humedadRelativa, siLlovio);
    if (listaTiempo == NULL)
    {
        listaTiempo = nuevoTiempo;
    }
    else if (calcularFechaMayor(listaTiempo->fecha, fecha))
    {
        nuevoTiempo->sig = listaTiempo;
        listaTiempo = nuevoTiempo;
    }
    else
    {
        tiempo *temp = listaTiempo;
        tiempo *ant = listaTiempo;

        while ((temp != NULL) && calcularFechaMayor(fecha, temp->fecha))
        {
            ant = temp;
            temp = temp->sig;
        }

        ant->sig = nuevoTiempo;
        if (temp != NULL)
        {
            nuevoTiempo->sig = temp;
        }
    }
    return listaTiempo;
}

// Inserta la efimeridad ordenada por fecha
efimeridad *insertarEfimeridad(string nombre, tm *fecha, tm *horaSalida, tm *horaOcultamiento)
{

    efimeridad *nuevaEfimeridad = new efimeridad(nombre, fecha, horaSalida, horaOcultamiento);

    if (listaEfimeridades == NULL)
    {
        listaEfimeridades = nuevaEfimeridad;
    }

    else if (calcularFechaMayor(listaEfimeridades->fecha, fecha))
    {

        nuevaEfimeridad->sig = listaEfimeridades;
        listaEfimeridades->ant = nuevaEfimeridad;
        listaEfimeridades = nuevaEfimeridad;
    }
    else
    {
        efimeridad *temp = listaEfimeridades;
        efimeridad *te = listaEfimeridades;

        while ((temp != NULL) && (calcularFechaMayor(fecha, temp->fecha)))
        {
            te = temp;
            temp = temp->sig;
        }
        nuevaEfimeridad->ant = te;
        te->sig = nuevaEfimeridad;
        if (temp != NULL)
        {
            nuevaEfimeridad->sig = temp;
            temp->ant = nuevaEfimeridad;
        }
    }
    return listaEfimeridades;
}

// Se encarga de pedir una fecha y la valida. Ademas crea y retorna una nueva instancia de tipo tm para manipular la fecha mas facil.

tm *pedirFecha()
{
    int dia, mes, agno;
    while (true)
    {
        cout << "\nDia del mes: ";
        cin >> dia;
        if ((dia > 0) && (dia <= 31))
        {
            break;
        }
        cout << "\nError: El dia del mes debe ser un numero del 1 al 31\n";
    }
    while (true)
    {
        cout << "\nMes: ";
        cin >> mes;
        if ((mes > 0) && (mes) <= 12)
        {
            mes--; // Para la instancia de tm se necesitara dar el numero desde 0 a 11
            break;
        }
        cout << "\nError: El mes debe ser un numero del 1 al 12\n";
    }
    while (true)
    {
        cout << "\nAgno: ";
        cin >> agno;
        if (to_string(agno).length() == 4)
            break;
        cout << "\nError: El anio debe tener 4 digitos. Ej: 2022\n";
    }
    tm *nuevaFecha = new tm();
    nuevaFecha->tm_mday = dia;
    nuevaFecha->tm_mon = mes;
    nuevaFecha->tm_year = agno;

    return nuevaFecha;
}

// Se encarga de pedir una hora y la valida. Ademas crea y retorna una nueva instancia de tipo tm para manipular la hora mas facil.

tm *pedirHora()
{
    int hora, minutos, abreviatura;
    while (true)
    {
        cout << "\nHora: ";
        cin >> hora;
        if ((hora > 0) && (hora <= 12))
            break;
        cout << "\nError: La hora debe ser un numero del 1 al 12 unicamente\n";
    }
    while (true)
    {
        cout << "\nMinutos: ";
        cin >> minutos;
        if ((minutos >= 0) && (minutos <= 59))
            break;
        cout << "\nError: Los minutos deben ser un numero del 00 al 59\n";
    }
    while (true)
    {
        cout << "\nSelecciona la abreviatura correcta: \n1. am\n2. pm\n-> ";
        cin >> abreviatura;
        if ((abreviatura == 1) || (abreviatura == 2))
        {
            if (abreviatura == 2)
                hora += 12; // La convierte en formato de 24 horas para el objeto tm.
            break;
        }
        cout << "\nError: Debes seleccionar la opcion 1 o 2";
    }

    tm *nuevaHora = new tm();
    nuevaHora->tm_hour = hora;
    nuevaHora->tm_min = minutos;

    return nuevaHora;
}

// Devuelve la fecha de la instancia tm dada en los parametros. La retorna asi: "25 de Septiembre del 2022"
string devolverFecha(tm *fecha)
{
    return to_string(fecha->tm_mday) + " de " + mes[fecha->tm_mon] + " del " + to_string(fecha->tm_year);
}

// Devuelve la hora de la instancia tm dada en los parametros. La retorna asi: "4:00 p.m"
string devolverHora(tm *hora)
{
    string minutos = to_string(hora->tm_min);
    if (minutos.length() == 1)
        minutos = "0" + minutos;
    if (hora->tm_hour > 12)
        return to_string(hora->tm_hour - 12) + ":" + minutos + " p.m";
    else
        return to_string(hora->tm_hour) + ":" + minutos + " a.m";
}

// =========== Metodos de Buscar ================

personas *buscarPersona(int cedula)
{
    // cout << "Buscando Persona...";
    if (listaPersonas == NULL)
    {
        cout << "Lista Vacia";
    }

    personas *temp = listaPersonas;
    while (temp != NULL)
    {
        if (temp->cedula == cedula)
        {
            cout << "\nPersonas Encontrada" << endl;
            return temp;
        }
        temp = temp->sig;
    }

    // cout << "\nPersona No Encontrada" << endl;

    return NULL;
}

efimeridad *buscarEfemeridad(tm *fecha)
{
    cout << "Buscando Efimeridad...";
    if (listaEfimeridades == NULL)
    {
        cout << "Lista Vacia";
    }

    efimeridad *temp = listaEfimeridades;
    while (temp != NULL)
    {
        if (temp->fecha == fecha)
        {
            cout << "\nEfimeridad Encontrada" << endl;
            return temp;
        }
        temp = temp->sig;
    }

    cout << "\nEfimeridad No Encontrada" << endl;

    return NULL;
}

lluvia *buscarLluvia(string codigo)
{
    cout << "Buscando Lluvia...";
    if (listaLluvia == NULL)
    {
        cout << "Lista Vacia";
    }

    lluvia *temp = listaLluvia;
    while (temp != NULL)
    {
        if (temp->codigo == codigo)
        {
            cout << "\nLluvia Encontrada" << endl;
            return temp;
        }
        temp = temp->sig;
    }

    cout << "\nLluvia No Encontrada" << endl;

    return NULL;
}

region *buscarRegion(int id)
{
    cout << "Buscando Region...";
    if (listaRegion == NULL)
    {
        cout << "Lista Vacia";
    }

    region *temp = listaRegion;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            cout << "\nRegion Encontrada" << endl;
            return temp;
        }
        temp = temp->sig;
    }

    cout << "\nRegion No Encontrada" << endl;

    return NULL;
}

lugar *buscarLugar(string n)
{
    cout << "Buscando Lugar ..." << endl;
    if (listaLugar == NULL)
    {
        cout << "\n Lista Vacia" << endl;
    }
    else
    {
        lugar *temp = listaLugar;
        if (temp->nombre == n)
        {
            cout << "Lugar Encontrado" << endl;
            return temp;
        }
        while (temp->sig != listaLugar)
        {
            if (temp->nombre == n)
            {
                return temp;
            }
            temp = temp->sig;
        }
        if (temp->nombre == n)
        {
            return temp;
        }
    }
    cout << "Lugar no encontrado " << endl;
    return NULL;
}

tiempo *buscarTiempo(int anio, int mes, int dia)
{
    cout << "\nBuscando el tiempo por fecha..." << endl;

    if (listaTiempo == NULL)
    {
        cout << "\nLa lista esta vacia" << endl;
    }
    else
    {
        tiempo *temp = listaTiempo;
        while (temp->sig != NULL)
        {
            if ((temp->fecha->tm_year == anio) && (temp->fecha->tm_mon == mes) && (temp->fecha->tm_mday == dia))
            {
                cout << "\nTiempo Encontrado" << endl;
                return temp;
            }
            temp = temp->sig;
        }
    }
    // cout << "\nNo se encontro el lugar" << endl;
    return NULL;
}

/*IMPRIMIR DE CADA UNO DE LOS INSERTAR*/

void imprimirLluvia(lluvia *lista)
{
    if (lista == NULL)
    {
        cout << "\nLa lista se encuentra vacia..." << endl;
    }
    else
    {
        lluvia *temp = lista;
        while (temp != NULL)
        {
            cout << "\nCodigo: " << temp->codigo << "\nNombre: " << temp->nombre << "\nPromedio en milimetros: " << temp->rangoPromedioEn_mm << endl;
            temp = temp->sig;
        }
        cout << endl;
    }
}

void imprimirRegion(region *lista)
{
    if (lista == NULL)
    {
        cout << "\nLa lista se encuentra vacia..." << endl;
    }
    else
    {
        region *temp = lista;
        while (temp != NULL)
        {
            cout << "\nId: " << temp->id << "\nNombre: " << temp->nombre << "\nUbicacion: " << temp->ubicacion << endl;
            temp = temp->sig;
        }
        cout << endl;
    }
}

void imprimirLugar(lugar *lista)
{
    if (lista == NULL)
    {
        cout << "\nLa lista esta vacia";
    }
    else
    {
        lugar *temp = lista;
        do
        {
            cout << "\nNombre: " << temp->nombre << "\nPoblacion: " << temp->poblacion << "\nMetros Cuadrados: " << temp->metrosCuadrados << endl;
            temp = temp->sig;
        } while (temp != lista);
    }
}

void imprimirPersonas(personas *lista)
{
    if (lista == NULL)
        cout << "\nLA LISTA ESTA VACIA\n";
    else
    {
        personas *temp = lista;
        cout << "\nIMPRIMIENTO HACIA ADELANTE... \n";
        while (temp->sig != NULL)
        {
            cout << "Nombre: " << temp->nombre << endl;
            temp = temp->sig;
        }
        cout << "Nombre: " << temp->nombre << endl;
        // AHORA IMPRIMO HACIA ATRAS
        cout << "\nIMPRIMIENTO HACIA ATRAS... \n";
        while (temp != NULL)
        {
            cout << "Nombre: " << temp->nombre << endl;
            temp = temp->ant;
        }
    }
}

void imprimirEfimeridades(efimeridad *lista)
{
    if (lista == NULL)
        cout << "\nLA LISTA ESTA VACIA\n";
    else
    {
        efimeridad *temp = lista;

        while (temp->sig != NULL)
        {
            cout << "Nombre: " << temp->nombre << endl;
            cout << "Fecha: " << devolverFecha(temp->fecha) << endl;
            cout << "Hora Salida: " << devolverHora(temp->horaSalida) << endl;
            cout << "Hora Ocultamiento: " << devolverHora(temp->horaOcultamiento) << endl;
            temp = temp->sig;
        }
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Fecha: " << devolverFecha(temp->fecha) << endl;
        cout << "Hora Salida: " << devolverHora(temp->horaSalida) << endl;
        cout << "Hora Ocultamiento: " << devolverHora(temp->horaOcultamiento) << endl;
    }
}

void imprimirTiempoPorLugar(string nombre)
{
    // Funcion que se encarga de imprimir el tiempo
    lugar *lugar = buscarLugar(nombre);
    if (lugar->sublistasTiempos == NULL)
    {
        cout << "\nEsta lista esta vacia" << endl;
    }
    else
    {
        int contador = 1;
        relTiempoLugar *temp = lugar->sublistasTiempos;
        do
        {
            cout << "=================================" << endl;

            cout << "Tiempo numero " << contador << endl;
            cout << "Fecha: " << devolverFecha(temp->enlace->fecha) << endl;
            cout << "Precipitacion: " << temp->enlace->precipitacion << endl;
            cout << "Temperatura maxima: " << temp->enlace->tempMaxima << endl;
            cout << "Temperatura minima: " << temp->enlace->tempMinima << endl;
            cout << "Velocidad del viento: " << temp->enlace->velocidadViento << endl;
            cout << "Direccion del viento: " << temp->enlace->direccionViento << endl;
            cout << "Lluvia: " << temp->enlace->siLlovio << endl;
            cout << "Lista de lluvias: " << temp->enlace->tempMinima << endl;
            if (temp->enlace->sublistasLluvias == NULL)
            {
                cout << "No tiene sublistas de lluvia" << endl;
                cout << "=================================" << endl;
            }
            else
            {
                relTiempoLluvia *tempLluvia = temp->enlace->sublistasLluvias;
                do
                {
                    cout << "\t LLuvia: " << tempLluvia->enlace->codigo << endl;
                    tempLluvia = tempLluvia->sig;
                } while (tempLluvia != NULL);
            }
            contador = contador + 1;
            temp = temp->sig;
        } while (temp != NULL);
    }
}

void imprimirTimepoPorPersona(int cedula)
{
    personas *personaElegida = buscarPersona(cedula);
    if (personaElegida == NULL)
    {
        cout << "\nLo sentimos, intente de nuevo" << endl;
    }
    else if (personaElegida->sublistasTiempos == NULL)
    {
        cout << "\nEsta lista esta vacia" << endl;
    }
    else
    {
        int contador = 1;
        relTiempoPersona *temp = personaElegida->sublistasTiempos;
        do
        {
            cout << "=================================" << endl;

            cout << "Tiempo numero " << contador << endl;
            cout << "Fecha: " << devolverFecha(temp->enlace->fecha) << endl;
            cout << "Precipitacion: " << temp->enlace->precipitacion << endl;
            cout << "Temperatura maxima: " << temp->enlace->tempMaxima << endl;
            cout << "Temperatura minima: " << temp->enlace->tempMinima << endl;
            cout << "Velocidad del viento: " << temp->enlace->velocidadViento << endl;
            cout << "Direccion del viento: " << temp->enlace->direccionViento << endl;
            cout << "Lluvia: " << temp->enlace->siLlovio << endl;
            cout << "Lista de lluvias: " << temp->enlace->tempMinima << endl;
            if (temp->enlace->sublistasLluvias == NULL)
            {
                cout << "No tiene sublistas de lluvia" << endl;
                cout << "=================================" << endl;
            }
            else
            {
                relTiempoLluvia *l = temp->enlace->sublistasLluvias;
                do
                {
                    cout << "\t LLuvia: " << l->enlace->codigo << endl;
                    l = l->sig;
                } while (l != NULL);
            }
            contador = contador + 1;
            temp = temp->sig;
        } while (temp != NULL);
    }
}

void imprimirLugaresPorRegion(int id)
{
    region *regionElegida = buscarRegion(id);
    if (regionElegida == NULL)
    {
        cout << "\nLo sentimos, intente de nuevo" << endl;
    }
    else if (regionElegida->sublistasLugares == NULL)
    {
        cout << "\nEsta lista esta vacia" << endl;
    }
    else
    {
        int contador = 1;
        relRegionLugar *temp = regionElegida->sublistasLugares;
        do
        {
            cout << "=================================" << endl;
            cout << "Lugar numero: " << contador;
            cout << "Nombre: " << temp->enlace->nombre << endl;
            cout << "Poblacion: " << temp->enlace->poblacion << endl;
            cout << "Metros Cuadrados : " << temp->enlace->metrosCuadrados << endl;
            cout << "=================================" << endl;

            contador = contador + 1;
            temp = temp->sig;
        } while (temp != NULL);
    }
}

void imprimirLluviasPorTiempo(tm *fecha)
{
    tiempo *tiempoElegido = buscarTiempo(fecha->tm_year, fecha->tm_mon, fecha->tm_mday);
    if (tiempoElegido == NULL)
    {
        cout << "\nLo sentimos, intente de nuevo" << endl;
    }
    else if (tiempoElegido->sublistasLluvias == NULL)
    {
        cout << "\nEsta lista esta vacia" << endl;
    }
    else
    {
        int contador = 1;
        relTiempoLluvia *temp = tiempoElegido->sublistasLluvias;
        do
        {
            cout << "=================================" << endl;
            cout << "Lluvia numero: " << contador;
            cout << "Codigo: " << temp->enlace->codigo << endl;
            cout << "Nombre: " << temp->enlace->nombre << endl;
            cout << "Rango Promedio en MM : " << temp->enlace->rangoPromedioEn_mm << endl;
            cout << "=================================" << endl;

            contador = contador + 1;
            temp = temp->sig;
        } while (temp != NULL);
    }
}

void imprimirListaTiempo(tiempo *listaTiempoParametro)
{
    if (listaTiempoParametro == NULL)
    {
        cout << "\nEsta lista esta vacia" << endl;
    }
    else
    {
        int contador = 1;
        tiempo *temp = listaTiempoParametro;
        do
        {
            cout << "Tiempo numero " << contador;
            cout << "Fecha: " << devolverFecha(temp->fecha) << endl;
            cout << "Precipitacion: " << temp->precipitacion << endl;
            cout << "Temperatura maxima: " << temp->tempMaxima << endl;
            cout << "Temperatura minima: " << temp->tempMinima << endl;
            cout << "Velocidad del viento: " << temp->velocidadViento << endl;
            cout << "Direccion del viento: " << temp->direccionViento << endl;
            cout << "Lluvia: " << temp->siLlovio << endl;
            cout << "Lista de lluvias: " << temp->tempMinima << endl;
            if (temp->sublistasLluvias == NULL)
            {
                cout << "No tiene sublistas de lluvia" << endl;
            }
            else
            {
                relTiempoLluvia *l = temp->sublistasLluvias;
                do
                {
                    cout << "\t LLuvia: " << l->enlace->codigo << endl;
                    l = l->sig;
                } while (l != NULL);
            }
            contador = contador + 1;
            temp = temp->sig;
        } while (temp != NULL);
    }
}

// Metodos de borrado en la listas

void borrarPersona(int cedula)
{
    personas *buscado = buscarPersona(cedula);
    if (buscado == NULL)
    {
        cout << "No se puede borrar";
        return;
    }
    else
    {
        if (buscado == listaPersonas)
        {
            listaPersonas = listaPersonas->sig;
            if (listaPersonas != NULL)
            {
                listaPersonas->ant = NULL;
            }
        }
        else
        { // Borra medio o al final
            buscado->ant->sig = buscado->sig;
            if (buscado->sig != NULL)
            {
                buscado->sig->ant = buscado->ant;
            }
        }
    }
}

void borrarEfimeridad(tm *fecha)
{
    efimeridad *buscado = buscarEfemeridad(fecha);
    if (buscado == NULL)
    {
        cout << "No se puede borrar";
        return;
    }
    else
    {
        if (buscado == listaEfimeridades)
        {
            listaEfimeridades = listaEfimeridades->sig;
            if (listaEfimeridades != NULL)
            {
                listaEfimeridades->ant = NULL;
            }
        }
        else
        { // Borra medio o al final
            buscado->ant->sig = buscado->sig;
            if (buscado->sig != NULL)
            {
                buscado->sig->ant = buscado->ant;
            }
        }
    }
}

void borrarLluvia(string codigo)
{
    lluvia *temp = listaLluvia;
    lluvia *prev = NULL;
    if (temp != NULL && temp->codigo == codigo)
    {
        listaLluvia = temp->sig;
        return;
    }
    else
    {
        while (temp != NULL && temp->codigo != codigo)
        {
            prev = temp;
            temp = temp->sig;
        }
        if (temp == NULL)
        {
            return;
        }
        prev->sig = temp->sig;
    }
}

void borrarRegion(int id)
{
    region *temp = listaRegion;
    region *prev = NULL;
    if (temp != NULL && temp->id == id)
    {
        listaRegion = temp->sig;
        return;
    }
    else
    {
        while (temp != NULL && temp->id != id)
        {
            prev = temp;
            temp = temp->sig;
        }
        if (temp == NULL)
        {
            return;
        }
        prev->sig = temp->sig;
    }
}

void borrarTiempo(tm *fecha)
{
    tiempo *temp = listaTiempo;
    tiempo *prev = NULL;
    if ((temp != NULL) && (temp->fecha->tm_year == fecha->tm_year) && (temp->fecha->tm_mon == fecha->tm_mon) && (temp->fecha->tm_mday == fecha->tm_mday))
    {
        listaTiempo = temp->sig;
        return;
    }
    else
    {
        while ((temp != NULL) && (temp->fecha->tm_year != fecha->tm_year) && (temp->fecha->tm_mon != fecha->tm_mon) && (temp->fecha->tm_mday != fecha->tm_mday))
        {
            prev = temp;
            temp = temp->sig;
        }
        if (temp == NULL)
        {
            return;
        }
        prev->sig = temp->sig;
    }
}

void borrarLugar(string nombre)
{

    if (listaLugar == NULL)
        return;

    // Si solo hay un dato la lista pasa a ser NULL
    if (listaLugar->nombre == nombre && listaLugar->sig == listaLugar)
    {
        listaLugar = NULL;
        return;
    }
    lugar *ultimo = listaLugar, *d;
    if (listaLugar->nombre == nombre)
    {

        while (ultimo->sig != listaLugar)
        {
            ultimo = ultimo->sig;
        }

        ultimo->sig = listaLugar->sig;

        listaLugar = ultimo->sig;
        return;
    }
    while (ultimo->sig != listaLugar && ultimo->sig->nombre != nombre)
    {
        ultimo = ultimo->sig;
    }

    if (ultimo->sig->nombre == nombre)
    {
        d = ultimo->sig;
        ultimo->sig = d->sig;
    }
    else
        cout << "No se encontro el lugar";
}

// Metodos para modificaar en la lista

// Modifica una persona, recibiendo la cedula
void modificarPersona(int cedula, int cedulaN, string nombreN, string lugarResidenciaN, string agnoResidenciaN)
{

    personas *aux = buscarPersona(cedula);
    if (aux != NULL)
    {
        aux->nombre = nombreN;
        aux->cedula = cedulaN;
        aux->lugarResidencia = lugarResidenciaN;
        aux->agnoResidencia = agnoResidenciaN;
        // Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }
    else
    {
        cout << "No se encontro a la Persona";
    }
}

// Modifica una lluvia, recibiendo el codigo
void modificarLluvia(string codigo, string codigoN, string nombreN, int rangoPromedioEn_mmN)
{

    lluvia *aux = buscarLluvia(codigo);
    if (aux != NULL)
    {
        aux->codigo = codigoN;
        aux->nombre = nombreN;
        aux->rangoPromedioEn_mm = rangoPromedioEn_mmN;
        // Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }
    else
    {
        cout << "No se encontro la lluvia";
    }
}

// Modifica una Efimeridad, recibiendo la fecha
void modificarEfimeridad(string nombreN, tm *fecha, tm *fechaN, tm *horaSalidaN, tm *horaOcultamientoN)
{

    efimeridad *aux = buscarEfemeridad(fecha);
    if (aux != NULL)
    {
        aux->nombre = nombreN;
        aux->fecha = fechaN;
        aux->horaSalida = horaSalidaN;
        aux->horaOcultamiento = horaOcultamientoN;

        // Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }
    else
    {
        cout << "No se encontro la lluvia";
    }
}
// Modifica una region, recibiendo el ID
void modificarRegion(int id, int idN, string nombreN, string ubicacionN)
{

    region *aux = buscarRegion(id);
    if (aux != NULL)
    {
        aux->id = idN;
        aux->nombre = nombreN;
        aux->ubicacion = ubicacionN;
        // Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }
    else
    {
        cout << "No se encontro la region";
    }
}

// Modifica un lugar, recibiendo el nombre
void modificarLugar(string nombre, string nombreN, int poblacionN, double metrosCuadradosN)
{

    lugar *aux = buscarLugar(nombre);
    if (aux != NULL)
    {
        aux->nombre = nombreN;
        aux->poblacion = poblacionN;
        aux->metrosCuadrados = metrosCuadradosN;
        // Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }
    else
    {
        cout << "No se encontro el lugar";
    }
}

// Modifica un tiempo, recibiendo la fecha
void modificarTiempo(tm *fecha, tm *fechaN, int precipitacionN, int tempMaximaN, int tempMinimaN, int velocidadVientoN, int direccionVientoN, int humedadRelativaN, bool siLlovioN)
{

    tiempo *aux = buscarTiempo(fecha->tm_year, fecha->tm_mon, fecha->tm_mday);
    if (aux != NULL)
    {
        aux->fecha = fechaN;
        aux->precipitacion = precipitacionN;
        aux->tempMaxima = tempMaximaN;
        aux->tempMinima = tempMinimaN;
        aux->velocidadViento = velocidadVientoN;
        aux->direccionViento = direccionVientoN;
        aux->siLlovio = siLlovioN;

        // Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }
    else
    {
        cout << "No se encontro el tiempo";
    }
}

// Metodos que permiten guardar las fechas y las horas de los datos quemados
tm *crearFecha(int y, int m, int d)
{
    tm *fecha = new tm();
    fecha->tm_year = y;
    fecha->tm_mon = m - 1;
    fecha->tm_mday = d;
    return fecha;
}
//
tm *crearHora(int h, int m)
{
    tm *hora = new tm();
    hora->tm_hour = h;
    hora->tm_min = m;
    return hora;
}

// Retorna la fecha apartir de un string
tm *obtenerFechadeString(string fecha)
{

    int agno = (fecha[0] - 48) * 1000 + (fecha[1] - 48) * 100 + (fecha[2] - 48) * 10 + fecha[3] - 48;
    int mes = (fecha[5] - 48) * 10 + fecha[6] - 48;
    int dia = (fecha[8] - 48) * 10 + fecha[9] - 48;

    return crearFecha(agno, mes, dia);
}
// Retorna la hora apartir de un string
tm *obtenerHoradeString(string hora)
{
    int h = hora[0] - 48 + hora[1] - 48;
    int m = hora[3] - 48 + hora[4] - 48;

    return crearHora(h, m);
}

// Metodo que relacion Tiempo y Lugar
void relacionarTiempoLugar(tm *fecha, string nombre)
{
    lugar *l = buscarLugar(nombre);
    tiempo *t = buscarTiempo(fecha->tm_year, fecha->tm_mon, fecha->tm_mday);

    if (l == NULL)
    {
        cout << "Lugar no valido";
        return;
    }
    if (t == NULL)
    {
        cout << "Tiempo no valido";
        return;
    }

    relTiempoLugar *nuevo = new relTiempoLugar;
    nuevo->enlace = t;
    nuevo->sig = l->sublistasTiempos;
    l->sublistasTiempos = nuevo;
    cout << "====================";
    cout << "Relacion Completada";
    cout << "====================";
}

// Metodo que relacion Tiempo y Persona
void relacionarTiempoPersona(tm *fecha, int cedula)
{
    personas *p = buscarPersona(cedula);
    tiempo *t = buscarTiempo(fecha->tm_year, fecha->tm_mon, fecha->tm_mday);
    if (p == NULL)
    {
        cout << "Personas no valida";
        return;
    }
    if (t == NULL)
    {
        cout << "Tiempo no valido";
        return;
    }

    relTiempoPersona *nuevo = new relTiempoPersona;
    nuevo->enlace = t;
    nuevo->sig = p->sublistasTiempos;
    p->sublistasTiempos = nuevo;
    cout << "====================";
    cout << "Relacion Completada";
    cout << "====================";
}

void relacionarTiempoLluvia(tm *fecha, string codigo)
{
    tiempo *t = buscarTiempo(fecha->tm_year, fecha->tm_mon, fecha->tm_mday);
    lluvia *l = buscarLluvia(codigo);
    if (t == NULL)
    {
        cout << "Tiempo no valida";
        return;
    }
    if (l == NULL)
    {
        cout << "LLuvia no valida";
        return;
    }

    relTiempoLluvia *nuevo = new relTiempoLluvia;
    nuevo->enlace = l;
    nuevo->sig = t->sublistasLluvias;
    t->sublistasLluvias = nuevo;
    cout << "====================";
    cout << "Relacion Completada";
    cout << "====================";
}

void relacionarLugarRegion(string nombre, int id)
{
    region *r = buscarRegion(id);
    lugar *l = buscarLugar(nombre);
    if (l == NULL)
    {
        cout << "Lugar no valida";
        return;
    }
    if (r == NULL)
    {
        cout << "Region no valida";
        return;
    }

    relRegionLugar *nuevo = new relRegionLugar;
    nuevo->enlace = l;
    nuevo->sig = r->sublistasLugares;
    r->sublistasLugares = nuevo;
    cout << "====================";
    cout << "Relacion Completada";
    cout << "====================";
}

/*  OTROS METODOS   */
void cargarDatos()
{
    /**
     * 1. Con 0 mm/h no hay nada de lluvia.                                    EXTREMO SECO
     * 2. De 1 a 2 mm/h diremos lluvias debiles.                               SECO
     * 3. De 2 a 15 mm/h sera lluvia.                                          NORMAL
     * 4. De 15 a 30 saltaremos a lluvias fuertes.                             LLUVIOSO
     * 5. De 30 a 60 lluvias muy fuertes.                                      EXTREMO LLUVIOSO
     * 6. Finalmente mas de 60 mm/h se describiran como lluvias torrenciales.  EXTREMO LLUVIOSO
     */
    listaLluvia = insertarLluvia("COD-5-55", "Lluvia muy fuerte", 55, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-16", "Lluvia fuerte", 16, listaLluvia);
    listaLluvia = insertarLluvia("COD-3-03", "Lluvia normal", 3, listaLluvia);
    listaLluvia = insertarLluvia("COD-6-60", "Lluvia torrencial", 60, listaLluvia);
    listaLluvia = insertarLluvia("COD-2-10", "Lluvia debil", 10, listaLluvia);
    listaLluvia = insertarLluvia("COD-2-06", "Lluvia debil", 6, listaLluvia);
    listaLluvia = insertarLluvia("COD-3-09", "Lluvia normal", 9, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-20", "Lluvia fuerte", 20, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-27", "Lluvia fuerte", 27, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-22", "Lluvia fuerte", 22, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-17", "Lluvia fuerte", 22, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-18", "Lluvia fuerte", 21, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-19", "Lluvia fuerte", 23, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-14", "Lluvia fuerte", 23, listaLluvia);
    listaLluvia = insertarLluvia("COD-4-20", "Lluvia fuerte", 22, listaLluvia);

    listaRegion = insertarRegion(12, "Quesada", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(14, "Florencia", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(3, "Buenavista", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "Aguas Zarcas", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "Venecia", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "Pital", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "La Fortuna", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "La Tigra", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "La Palmera", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "Pocosol", "San Carlos, provincia de Alajuela, de Costa Rica", listaRegion);

    listaLugar = insertarLugar("Santa Rosa", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Buenos Aires", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Santa Clara", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Barrio Baltazar", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("San Juan", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Santa Rita", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Florencia", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Cuestillas", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Platanar", 100, 2.5, listaLugar);

    listaRegion = insertarRegion(1, "San Jose", "Provincia de San Jose, Costa Rica", listaRegion);
    listaRegion = insertarRegion(2, "Escazu", "Provincia de San Jose, Costa Rica", listaRegion);
    listaRegion = insertarRegion(3, "San Carlos", "Provincia de Alajuela, Costa Rica", listaRegion);
    listaRegion = insertarRegion(4, "Palmares", "Provincia de Alajuela, Costa Rica", listaRegion);
    listaRegion = insertarRegion(5, "Paraiso", "Provincia de Cartago, Costa Rica", listaRegion);
    listaRegion = insertarRegion(6, "La union", "Provincia de Cartago, Costa Rica", listaRegion);
    listaRegion = insertarRegion(7, "Belen", "Provincia de Heredia, Costa Rica", listaRegion);
    listaRegion = insertarRegion(8, "Puntarenas", "Provincia de Puntarenas, Costa Rica", listaRegion);
    listaRegion = insertarRegion(9, "Nicoya", "Provincia de Guanacaste, de Costa Rica", listaRegion);
    listaRegion = insertarRegion(10, "Talamanca", "Provincia de Limon, de Costa Rica", listaRegion);

    listaLugar = insertarLugar("Carmen", 370, 1.47, listaLugar); // San jose
    listaLugar = insertarLugar("Merced", 446, 2.17, listaLugar);

    listaLugar = insertarLugar("Pocosol", 164, 1.54, listaLugar); // san carlos
    listaLugar = insertarLugar("Aguas Zarcas", 474, 1.18, listaLugar);

    listaLugar = insertarLugar("Zaragoza", 386, 3.76, listaLugar); // Palmares
    listaLugar = insertarLugar("Buenos Aires", 154, 2.5, listaLugar);

    listaLugar = insertarLugar("San Antonio", 300, 4.91, listaLugar); // Belen
    listaLugar = insertarLugar("La Ribera", 389, 3.9, listaLugar);
    listaLugar = insertarLugar("La Asuncion", 433, 4.47, listaLugar);

    listaLugar = insertarLugar("Quebrada Honda", 287, 3.31, listaLugar); // Nicoya

    listaPersonas = insertarPersona("Alejandro Rodriguez", 208360735, "El Tanque", "2018");
    listaPersonas = insertarPersona("Persona Prueba", 123, "Santa Clara", "2020");
    listaPersonas = insertarPersona("Juan Ca", 2081230735, "La Fortuna", "2013");
    listaPersonas = insertarPersona("Beto Beto", 1011230735, "San Rafael", "2022");
    listaPersonas = insertarPersona("Roberto Jimenez", 3011230735, "Florencia", "2021");
    listaPersonas = insertarPersona("Alondra", 4011230735, "Santa Clara", "2024");
    listaPersonas = insertarPersona("Carlos Ruiz", 3011230735, "Florencia", "2021");
    listaPersonas = insertarPersona("Bianca Ruiz", 1234, "Florencia", "2022");

    listaTiempo = insertarTiempo(crearFecha(2020, 9, 23), 1, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2018, 11, 7), 2, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2018, 8, 12), 3, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2018, 3, 21), 4, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2021, 7, 15), 5, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2021, 8, 8), 6, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2019, 8, 21), 7, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2019, 2, 7), 8, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2019, 11, 15), 9, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2018, 11, 18), 10, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 6, 11), 10, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2021, 5, 10), 10, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2022, 2, 27), 10, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2022, 9, 18), 10, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2022, 1, 2), 10, 30, 24, 14, -45, -3, true);
    // OK
    relacionarTiempoPersona(crearFecha(2020, 9, 23), 208360735);
    relacionarTiempoPersona(crearFecha(2018, 11, 7), 208360735);
    relacionarTiempoPersona(crearFecha(2018, 8, 12), 2081230735);
    relacionarTiempoPersona(crearFecha(2018, 3, 21), 2081230735);
    relacionarTiempoPersona(crearFecha(2021, 7, 15), 2081230735);
    relacionarTiempoPersona(crearFecha(2021, 8, 8), 1011230735);
    relacionarTiempoPersona(crearFecha(2019, 8, 21), 1011230735);
    relacionarTiempoPersona(crearFecha(2019, 2, 7), 4011230735);
    relacionarTiempoPersona(crearFecha(2019, 11, 15), 3011230735);
    relacionarTiempoPersona(crearFecha(2018, 11, 18), 3011230735);

    relacionarTiempoLugar(crearFecha(2020, 9, 23), "Carmen");
    relacionarTiempoLugar(crearFecha(2018, 11, 7), "Carmen");
    relacionarTiempoLugar(crearFecha(2018, 8, 12), "Pocosol");
    relacionarTiempoLugar(crearFecha(2018, 3, 21), "Pocosol");
    relacionarTiempoLugar(crearFecha(2021, 7, 15), "Pocosol");
    relacionarTiempoLugar(crearFecha(2021, 8, 8), "Buenos Aires");
    relacionarTiempoLugar(crearFecha(2019, 8, 21), "San Antonio");
    relacionarTiempoLugar(crearFecha(2020, 6, 11), "Santa Clara");
    relacionarTiempoLugar(crearFecha(2021, 5, 10), "Florencia");
    relacionarTiempoLugar(crearFecha(2022, 2, 27), "Santa Rita");
    relacionarTiempoLugar(crearFecha(2022, 9, 18), "Cuestillas");
    relacionarTiempoLugar(crearFecha(2022, 1, 2), "Platanar");
    relacionarTiempoLugar(crearFecha(2019, 2, 7), "Quebrada Honda");
    relacionarTiempoLugar(crearFecha(2019, 11, 15), "La Ribera");
    relacionarTiempoLugar(crearFecha(2018, 11, 18), "Aguas Zarcas");

    relacionarLugarRegion("Carmen", 1);
    relacionarLugarRegion("Pocosol", 1);
    relacionarLugarRegion("Buenos Aires", 2);
    relacionarLugarRegion("San Antonio", 3);
    relacionarLugarRegion("Santa Clara", 3);
    relacionarLugarRegion("Florencia", 3);
    relacionarLugarRegion("Platanar", 3);
    relacionarLugarRegion("Cuestillas", 3);
    relacionarLugarRegion("Santa Rita", 3);
    relacionarLugarRegion("Quebrada Honda", 4);
    relacionarLugarRegion("La Ribera", 5);
    relacionarLugarRegion("Aguas Zarcas", 6);
    relacionarLugarRegion("Merced", 6);
    relacionarLugarRegion("Zaragoza", 7);
    relacionarLugarRegion("La Asuncion", 7);

    relacionarTiempoLluvia(crearFecha(2020, 9, 23), "COD-5-55");
    relacionarTiempoLluvia(crearFecha(2018, 11, 7), "COD-4-16");
    relacionarTiempoLluvia(crearFecha(2018, 8, 12), "COD-3-03");
    relacionarTiempoLluvia(crearFecha(2018, 3, 21), "COD-6-60");
    relacionarTiempoLluvia(crearFecha(2021, 7, 15), "COD-2-10");
    relacionarTiempoLluvia(crearFecha(2021, 8, 8), "COD-2-06");
    relacionarTiempoLluvia(crearFecha(2019, 8, 21), "COD-3-09");
    relacionarTiempoLluvia(crearFecha(2019, 2, 7), "COD-4-20");
    relacionarTiempoLluvia(crearFecha(2019, 11, 15), "COD-4-27");
    relacionarTiempoLluvia(crearFecha(2018, 11, 18), "COD-4-22");
    relacionarTiempoLluvia(crearFecha(2020, 6, 11), "COD-4-16");
    relacionarTiempoLluvia(crearFecha(2021, 5, 10), "COD-4-17");
    relacionarTiempoLluvia(crearFecha(2022, 2, 27), "COD-4-18");
    relacionarTiempoLluvia(crearFecha(2022, 2, 27), "COD-4-19");
    relacionarTiempoLluvia(crearFecha(2022, 9, 18), "COD-4-14");
    relacionarTiempoLluvia(crearFecha(2022, 1, 2), "COD-4-20");

    listaEfimeridades = insertarEfimeridad("Sol", crearFecha(2020, 9, 23), crearHora(7, 25), crearHora(17, 9));
    listaEfimeridades = insertarEfimeridad("Efimeridad 2", crearFecha(2018, 11, 7), crearHora(5, 37), crearHora(17, 20));
    listaEfimeridades = insertarEfimeridad("Efimeridad 3", crearFecha(2018, 8, 12), crearHora(6, 12), crearHora(20, 12));
    listaEfimeridades = insertarEfimeridad("Efimeridad 4", crearFecha(2018, 3, 21), crearHora(6, 12), crearHora(20, 12));
    listaEfimeridades = insertarEfimeridad("Efimeridad 5", crearFecha(2021, 7, 15), crearHora(6, 12), crearHora(20, 12));
    listaEfimeridades = insertarEfimeridad("Efimeridad 6", crearFecha(2021, 8, 8), crearHora(6, 12), crearHora(20, 12));
    listaEfimeridades = insertarEfimeridad("Sol", crearFecha(2019, 8, 21), crearHora(6, 12), crearHora(20, 12)); // Este
    listaEfimeridades = insertarEfimeridad("Sol", crearFecha(2019, 8, 7), crearHora(6, 12), crearHora(20, 12));
    listaEfimeridades = insertarEfimeridad("Sol", crearFecha(2019, 11, 15), crearHora(6, 12), crearHora(20, 12));
    listaEfimeridades = insertarEfimeridad("Efimeridad 10", crearFecha(2018, 11, 18), crearHora(6, 12), crearHora(20, 12));
}


void imprimirDiasLluvias(int anio, string nombre){
    
    if (listaLugar == NULL)
    {
        cout << "\nLa lista est?? vac??a";
    }
    else
    {
        lugar *temp = buscarLugar(nombre);
        
        int contador[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
        
        relTiempoLugar*tempTiempo = temp->sublistasTiempos;
        while (tempTiempo != NULL)
        {
            if (tempTiempo->enlace->fecha->tm_year == anio && tempTiempo->enlace->siLlovio == true)
            {
                contador[tempTiempo->enlace->fecha->tm_mon] += 1;
            }
             tempTiempo = tempTiempo->sig;
        }
        int totalResultados = 0;
        for (int x = 0; x < 12; x++)
        {
            totalResultados += contador[x];
        }
        if (totalResultados != 0)
        {
            cout<<"\n============== Dias de lluvia Por Mes En Anio Especifico ============"<<endl;
            cout<<"Lugar: "<<temp->nombre<<" Anio: "<<anio<<endl;
            for (int i = 0; i < 12; i++)
            {
                if (contador[i] != 0)
                {
                    cout<<"Mes de "<<mes[i]<<"| Dias de lluvia "<<contador[i]<<endl ;
                }
            }
            cout<<"=========================================================";
        }
    
       
    }
}



int determinarTipoLluvia(string n ){
    if (n == "Lluvia torrencial")
    {
        return 4;
    }else if ( n == "Lluvia muy fuerte")
    {
        return 3;
        
    }else if (n == "Lluvia fuerte")
    {
        return 2;
        
    }else if (n == "Lluvia normal")
    {
        return 1;
        
    }else if (n == "Lluvia debil")
    {
        return 0;

    }

}

void reporteCambiodeLLuvia(int anio){
    
    if (listaTiempo == NULL)
    {
        cout << "\nLa lista est?? vac??a";
    }
    else
    {
        tiempo *temp = listaTiempo;
        
        
        tm* fechasIncial[5] ;
        tm* fechaFinal[5] ;
        int contadores[5] = {0,0,0,0,0};

        string tipoAnterior = "";
        while (temp != NULL ){
            

            if (temp->fecha->tm_year == anio && temp->sublistasLluvias != NULL)
            {   
                if(tipoAnterior != temp->sublistasLluvias->enlace->nombre){
                    contadores[determinarTipoLluvia(temp->sublistasLluvias->enlace->nombre)] = 0;
                    fechasIncial[determinarTipoLluvia(temp->sublistasLluvias->enlace->nombre)] = temp->fecha;
                    fechaFinal[determinarTipoLluvia(temp->sublistasLluvias->enlace->nombre)] = NULL;
                    tipoAnterior = temp->sublistasLluvias->enlace->nombre;
                }
                else{
                    fechaFinal[determinarTipoLluvia(temp->sublistasLluvias->enlace->nombre)] = temp->fecha;
                    contadores[determinarTipoLluvia(temp->sublistasLluvias->enlace->nombre)]++;
                }
            }
            temp = temp->sig;
        } 
        cout<<"-----------------"<<endl;
        cout<<"Anio: "<< anio<<endl;
        if (contadores[4] >= 6)
        {
            cout<<"Lluvia Torrencial Desde: "<<mes[fechasIncial[4]->tm_mon]<<" "<<fechasIncial[4]->tm_mday<<" Hasta "<<mes[fechaFinal[4]->tm_mon]<<" "<<fechaFinal[4]->tm_mday;
        }else if (contadores[3] >= 6)
        {
            cout<<"Lluvia muy fuerte Desde: "<<mes[fechasIncial[3]->tm_mon]<<" "<<fechasIncial[3]->tm_mday<<" Hasta "<<mes[fechaFinal[3]->tm_mon]<<" "<<fechaFinal[3]->tm_mday<<endl;
        }else if (contadores[2] >= 6)
        {
            cout<<"Lluvia fuerte Desde: "<<mes[fechasIncial[2]->tm_mon]<<" "<<fechasIncial[2]->tm_mday<<" Hasta "<<mes[fechaFinal[2]->tm_mon]<<" "<<fechaFinal[2]->tm_mday;

        }else if (contadores[1] >= 6)
        {
            cout<<"Lluvia normal Desde: "<<mes[fechasIncial[1]->tm_mon]<<" "<<fechasIncial[1]->tm_mday<<" Hasta "<<mes[fechaFinal[1]->tm_mon]<<" "<<fechaFinal[1]->tm_mday;

        }else if (contadores[0] >= 6)
        {
            cout<<"Lluvia Debil Desde:  "<<mes[fechasIncial[0]->tm_mon]<<" "<<fechasIncial[0]->tm_mday<<" Hasta "<<mes[fechaFinal[0]->tm_mon]<<" "<<fechaFinal[0]->tm_mday;
        }
        
        
    }
}

void imprimirClasificacionLluvia(int a, lugar *l)
{

    string nombres[5] = {"Nada de lluvia", "Lluvia debil", "Lluvia normal", "Lluvia fuerte", "Lluvia muy fuerte"};
    int cantidades[5] = {0, 0, 0, 0, 0};

    if (l == NULL)
    {
        cout << "\nLa lista esta vacia";
    }
    else
    {
        lugar *temp = l;
        do
        {
            relTiempoLluvia *lista = l->sublistasTiempos->enlace->sublistasLluvias;
            if (temp->sublistasTiempos != NULL)
            {
                if (temp->sublistasTiempos->enlace->fecha->tm_year == a)
                {
                    if (lista == NULL)
                    {
                        cout << "\nLa lista se encuentra vacia..." << endl;
                    }
                    else
                    {
                        relTiempoLluvia *temp2 = lista;
                        int indice;

                        do
                        {
                            for (int x = 0; x < 5; x++)
                            {
                                if (temp2->enlace->nombre == nombres[x])
                                {
                                    cantidades[x]++;
                                }
                            }
                            temp2 = temp2->sig;
                        } while (temp2 != NULL);
                    }
                }
            }
            temp = temp->sig;
        } while (temp != l);
        cout << "\n *** Porcentajes de Lluvias en " << l->nombre << " en el anio " << a << " ***"<< endl;

        int total = 0;

        if(l->sublistasTiempos != NULL)
        {
           cout << "Mes: " << mes[l->sublistasTiempos->enlace->fecha->tm_mon]<<endl; 
        }
         for (int x = 0; x < 5; x++)
        {
            total += cantidades[x];
        }

        for (int x = 0; x < 5; x++)
        {
            cout << nombres[x]<< " -> " << (cantidades[x] * 100 / total) << "%" << endl;
        }

    }
}


void impReporteVariablesClimaticas(region *r, int anio1, int anio2)
{
    relRegionLugar *lugares = r->sublistasLugares;
    string nombreRegion = "";

    int promedioPrecipitaciones = 0;
    int promedioDiasLluviosos = 0;
    int promedioTemperaturaMayor = 0;
    int promedioTemperaturaMenor = 0;
    int cantidadValidos = 0;

    if (lugares == NULL)
    {
        cout << "\nNo hay lugares registrados en esta region";
    }
    else
    {
        relRegionLugar *temp = lugares;
        int cont = 0;
        do
        {
            if (temp->enlace->sublistasTiempos != NULL)
            {
                int anioTemp = temp->enlace->sublistasTiempos->enlace->fecha->tm_year;
                if ((anioTemp >= anio1) && (anioTemp <= anio2))
                {
                    if (nombreRegion == "")
                    {
                        nombreRegion = r->nombre;
                        cout << "\nREGION: [ " << nombreRegion << " ]" << endl;
                        cont++;
                    }
                    cout << "\n\nLUGAR: " << temp->enlace->nombre << endl;
                    cout << "Precipitacion: " << temp->enlace->sublistasTiempos->enlace->precipitacion << endl;
                    promedioPrecipitaciones+=temp->enlace->sublistasTiempos->enlace->precipitacion;
                    cantidadValidos++;
                    int diasLluviosos = 0;
                    if (temp->enlace->sublistasTiempos->enlace->sublistasLluvias != NULL)
                    {
                        relTiempoLluvia *tempLluvia = temp->enlace->sublistasTiempos->enlace->sublistasLluvias;
                        do
                        {
                            diasLluviosos++;
                            tempLluvia = tempLluvia->sig;
                        } while (tempLluvia != NULL);
                    }
                    cout << "Dias con lluvia: " << diasLluviosos << endl;
                    promedioDiasLluviosos+=diasLluviosos;
                    cout << "Temperatura Maxima: " << temp->enlace->sublistasTiempos->enlace->tempMaxima << endl;
                    promedioTemperaturaMayor+=temp->enlace->sublistasTiempos->enlace->tempMaxima;
                    cout << "Temperatura Minima: " << temp->enlace->sublistasTiempos->enlace->tempMinima << endl;
                    promedioTemperaturaMenor+=temp->enlace->sublistasTiempos->enlace->tempMinima;
                }
            }
            temp = temp->sig;
        } while (temp != NULL);
        if (cont == 0)
            cout << "NO SE A ENCONTRADO NINGUN REGISTRO VALIDO";
        else
        {
            // revisar que esto no sirve
            cout << "\n\n- Promedios de la Region " << r->nombre << " -" << endl;
            
            cout << "Precipitaciones: "
                 << (promedioPrecipitaciones/cantidadValidos) << endl;
            cout << "Dias Lluviosos: "
                 << (promedioDiasLluviosos/cantidadValidos) << endl;
            cout << "Temperatura Maxima: "
                 << (promedioTemperaturaMayor/cantidadValidos) << endl;
            cout << "Temperatura Minima: "
                 << (promedioTemperaturaMenor/cantidadValidos) << endl;
        }
    }

}

void reporteVariablesClimaticas()
{
    region *r;
    int id;
    int anio1, anio2;

    while (true)
    {
        cout << "Ingrese el ID de la region: ";
        cin >> id;
        r = buscarRegion(id);
        if (r != NULL)
            break;
        cout << "Id no valido, vuelve a intentarlo!: " << endl;
    }

    cout << "\n* PERIODO A CONSULTAR *\n";
    cout << "Ingrese el primer anio del periodo: ";
    cin >> anio1;
    cout << "Ingrese el segundo anio del periodo: ";
    cin >> anio2;

    impReporteVariablesClimaticas(r, anio1, anio2);
}


void impReporteEfimeridadAnio(int anio, string nombreEfimeridad)
{
    cout << "\n\n\t** REPORTES HORARIOS DE SALIDA DE '" << nombreEfimeridad << "' EN EL ANIO " << anio << " ** " << endl
         << endl;
    efimeridad *lista = listaEfimeridades;
    if (lista == NULL)
        cout << "\nNO EXISTEN EFIMERIDADES EN ESTE MOMENTO\n";
    else
    {
        efimeridad *temp = lista;
        int mesActual = 0;

        while (temp->sig != NULL)
        {
            if ((temp->nombre == nombreEfimeridad) && (temp->fecha->tm_year == anio))
            {
                if(mesActual != temp->fecha->tm_mon){
                    mesActual = temp->fecha->tm_mon;
                    cout << "\n-------------\n[" << mes[temp->fecha->tm_mon] << "]\n-------------" << endl;
                }
                cout << "Fecha: " << devolverFecha(temp->fecha) << endl;
                cout << "Hora Salida: " << devolverHora(temp->horaSalida) << endl;
                cout << "Hora Ocultamiento: " << devolverHora(temp->horaOcultamiento) << endl;
            }
            temp = temp->sig;
        }
    }
}

void reporteEfimeridadAnio()
{
    int anio;
    string nombre;
    cout << "\nIngrese el anio que desea consultar: ";
    cin >> anio;
    cout << "\nIngrese el nombre de la efimeridad que desea consultar: ";
    getline(cin >> ws, nombre);
    impReporteEfimeridadAnio(anio, nombre);
}

void reportesPromedioMensualLugaresAnioX(int anio){
    
    if (listaLugar == NULL)
    {
        cout << "\nLa lista est?? vac??a";
    }
    else
    {
        lugar *temp = listaLugar;
        do
        {
            int meses[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            int contador[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            relTiempoLugar*tempTiempo = temp->sublistasTiempos;
            while (tempTiempo != NULL)
            {
                if (tempTiempo->enlace->fecha->tm_year == anio)
                {
                    meses[tempTiempo->enlace->fecha->tm_mon] += tempTiempo->enlace->precipitacion;
                    contador[tempTiempo->enlace->fecha->tm_mon] += 1;
                }

                 tempTiempo = tempTiempo->sig;
            }
            int totalResultados = 0;
            for (int x = 0; x < 12; x++)
            {
                totalResultados += contador[x];
            }
            if (totalResultados != 0)
            {
                cout<<"\n============== PROMEDIO MENSUAL DE UN ANIO ============"<<endl;
                cout<<"Lugar: "<<temp->nombre<<endl;

                for (int i = 0; i < 12; i++)
                {
                    if (contador[i] != 0)
                    {
                        cout<<"Promedio Mes de "<<mes[i]<<": ( "<<meses[i]/contador[i]<<" )"<<endl ;
                    }
                }
                cout<<"=========================================================";
            }
            temp = temp->sig;
            
            
        } while (temp != listaLugar);
    }
}

void impPrecipitacionRegio (int anio) {
    if (listaRegion == NULL)
    {
        cout << "\nLa lista est?? vac??a";
    }
    else
    {
        region *tempRegion = listaRegion;
        while (tempRegion != NULL)
        {
            cout << "\nDENTRO DEL WHILE REGION" << endl;
            int meses[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            int contador[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            if (tempRegion->sublistasLugares != NULL)
            {
                relRegionLugar* tempLugar = tempRegion->sublistasLugares;
                while (tempLugar->sig != tempRegion->sublistasLugares);
                {
                    cout << "\nDENTRO DEL WHILE LUGAR" << endl;
                    while (tempLugar->enlace->sublistasTiempos != NULL)
                    {
                        cout << "\nDENTRO DEL WHILE TIEMPO" << endl;
                        if (tempLugar->enlace->sublistasTiempos->enlace->fecha->tm_year == anio)
                        {
                            cout << "\nDENTRO DEL IF A??O" << endl;
                            meses[tempLugar->enlace->sublistasTiempos->enlace->fecha->tm_mon] += tempLugar->enlace->sublistasTiempos->enlace->precipitacion;
                            contador[tempLugar->enlace->sublistasTiempos->enlace->fecha->tm_mon] += 1;
                        }
                        tempLugar->enlace->sublistasTiempos = tempLugar->enlace->sublistasTiempos->sig;
                    }
                    cout << "\nSAL?? DEL WHILE TIEMPO" << endl;
                    tempLugar = tempLugar->sig;
                }
                cout << "\nSAL?? DEL WHILE LUGAR" << endl;

                int totalResultados = 0;
                for (int x = 0; x < 12; x++)
                {
                    cout << "\nDENTRO DEL PRIMER FOR" << endl;
                    totalResultados = totalResultados + contador[x];
                }
                {
                    cout<<"\n============== PROMEDIO MENSUAL DE UN ANIO ============"<<endl;
                    cout<<"Regi??n: "<<tempRegion->nombre <<endl;

                    for (int i = 0; i < 12; i++)
                    {
                        if (contador[i] != 0)
                        {
                            cout<<"Promedio Mes de "<<mes[i]<<": ( "<<meses[i]/contador[i]<<" )"<<endl ;
                        }
                    }
                    cout<<"=========================================================";
                }
            }
            tempRegion = tempRegion->sig;
        }
    }
}

void reporteExtremosAnioLugar(int anioE, string lugarE)
{
    lugar *lugarEscogido = buscarLugar(lugarE);
    if (lugarEscogido == NULL)
    {
        cout << "\nLo sentimos, no hemos encontrado el lugar." << endl;
    }
    else if (lugarEscogido->sublistasTiempos != NULL)
    {
        int mesesMinimo[12] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        int mesesMaximo[12] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        relTiempoLugar *tempTiempo = lugarEscogido->sublistasTiempos;
        do
        {
            if (tempTiempo->enlace->fecha->tm_year == anioE)
            {
                if (mesesMaximo[tempTiempo->enlace->fecha->tm_mon] == NULL)
                {
                    mesesMaximo[tempTiempo->enlace->fecha->tm_mon] = tempTiempo->enlace->tempMaxima;
                }
                if (mesesMinimo[tempTiempo->enlace->fecha->tm_mon] == NULL)
                {
                    mesesMinimo[tempTiempo->enlace->fecha->tm_mon] = tempTiempo->enlace->tempMinima;
                }
                if (mesesMinimo[tempTiempo->enlace->fecha->tm_mon] < tempTiempo->enlace->tempMinima)
                {
                    mesesMinimo[tempTiempo->enlace->fecha->tm_mon] = tempTiempo->enlace->tempMinima;
                }
                if (mesesMaximo[tempTiempo->enlace->fecha->tm_mon] > tempTiempo->enlace->tempMaxima)
                {
                    mesesMaximo[tempTiempo->enlace->fecha->tm_mon] = tempTiempo->enlace->tempMaxima;
                }
            }
            tempTiempo = tempTiempo->sig;
        } while (tempTiempo->sig != NULL);

        for (int i = 0; i < 12; i++)
        {
            cout << "\nPara el mes " << mes[i] << endl;
            if ((mesesMaximo[i] != NULL) && (mesesMinimo[i] != NULL))
            {
                cout << "\nLa temperatura Minima es " << mesesMinimo[i] << endl;
                cout << "\nLa temperatura M??xima es " << mesesMaximo[i] << endl;
            }
        }
    }
}

void impOcultamientoSalidaSol()
{
    /*
    Determinar e imprimir el dia(fecha completa)con la salida de ???sol???mas temprano de un a??o Y,
    y el ocultamientomastardio del ???sol???en el a??o Y.
    */
    tm *horaTempranoOcultamiento = new tm;
    tm *horaTardioSalida = new tm;

    if (listaEfimeridades == NULL)
    {
        cout << "\nLa lista esta vacia" << endl;
    }
    else
    {
        efimeridad *temp = listaEfimeridades;
        horaTempranoOcultamiento = temp->horaOcultamiento;
        horaTardioSalida = temp->horaSalida;
        while (temp->sig != NULL)
        {
            temp = temp->sig;
            // Comparando las horas para determinar el ocultamiento mas temprano
            if (temp->horaOcultamiento->tm_hour < horaTempranoOcultamiento->tm_hour)
            {
                horaTempranoOcultamiento = temp->horaOcultamiento;
            }
            else if ((temp->horaOcultamiento->tm_hour == horaTempranoOcultamiento->tm_hour) && (temp->horaOcultamiento->tm_min < horaTempranoOcultamiento->tm_min))
            {
                horaTempranoOcultamiento = temp->horaOcultamiento;
            }
            // Comparando las horas para determinar la salida del sol mas tranquila
            if (temp->horaSalida->tm_hour > horaTardioSalida->tm_hour)
            {
                horaTardioSalida = temp->horaSalida;
            }
            else if ((temp->horaSalida->tm_hour == horaTardioSalida->tm_hour) && (temp->horaSalida->tm_min > horaTardioSalida->tm_min))
            {
                horaTardioSalida = temp->horaSalida;
            }
        }
    }
    cout << "\nLa hora de ocultamiento del sol mas temprano es: " << devolverHora(horaTempranoOcultamiento);
    cout << "\nLa hora de salida del sol mas tardia es: " << devolverHora(horaTardioSalida) << endl;
}

int obtenerDiferencia(tm *horaTemprano, tm *horaTarde)
{
    /*
    Obtiene la diferencia en minutos de las horas que se envian por parametro
    Este metodo se complementa con el segundo metodo de las consultas

    Ejemplo/guia para sacar la diferencia:
        Hora temprana:  1:53
        Hora Tardia:    4:23

        4-1 = 3*60 = 180 minutos
        180-53 = 127 (la primera hora no estuvo completa)
        127+23 = 150 (los minutos que sobraron)
    */
    int diferencia = horaTarde->tm_hour - horaTemprano->tm_hour; // Saco la diferencia de horas
    diferencia = diferencia * 60;                                // Convierto la diferencia a minutos
    diferencia = diferencia - horaTemprano->tm_min;
    diferencia = diferencia + horaTarde->tm_min;
    return diferencia;
}
/*
    Determinar e imprimir las fechas que generan la mayor diferencia en minutos de la salidadel sol,
    indicar las dos fechas que producen la mayor diferencia, para un a??o Y.
*/
void diferenciaSalidaSol()
{

    int anio;
    tm *horaTemprano;
    tm *horaTarde;
    cout << "\nDigite el a??o en el que desea buscar las fechas: ";
    cin >> anio;
    efimeridad *temp = listaEfimeridades;
    horaTarde = temp->horaSalida;
    horaTemprano = temp->horaSalida;
    while (temp->sig != NULL)
    {
        if (temp->fecha->tm_year == anio)
        {
            // Compara con las horas tempranas
            if (temp->horaSalida->tm_hour < horaTemprano->tm_hour)
            {
                horaTemprano = temp->horaSalida;
            }
            else if ((temp->horaSalida->tm_hour == horaTemprano->tm_hour) && (temp->horaSalida->tm_min < horaTemprano->tm_min))
            {
                horaTemprano = temp->horaSalida;
            }
            // Compara con las horas tardias
            if (temp->horaSalida->tm_hour > horaTarde->tm_hour)
            {
                horaTarde = temp->horaSalida;
            }
            else if ((temp->horaSalida->tm_hour == horaTarde->tm_hour) && (temp->horaSalida->tm_min > horaTarde->tm_min))
            {
                horaTarde = temp->horaSalida;
            }
        }
        temp = temp->sig;
    }
    int diferencia = obtenerDiferencia(horaTemprano, horaTarde);
    cout << "\nLa diferencia de la salida del sol en  mas temprana y mas tarde en el anio " << anio;
    cout << " es de: " << diferencia << " minutos";
}

void imprimirExtremos()
{
    /*
    Determinar e imprimir el mes que mas extremos de lluvia tiene de un a??o X para un lugar Z.
    Debe imprimir ambos:extremo seco y extremo lluvioso. En caso de empate imprimir todos los
    meses que tiene el empate maximo.
    */
    string lugarParaBuscar;
    int anioParaBuscar;
    cout << "\nDigite el lugar en el que desea buscar: ";
    getline(cin >> ws, lugarParaBuscar);
    lugar *lugarEscogido = buscarLugar(lugarParaBuscar);
    if (lugarEscogido == NULL)
    {
        cout << "\nLo sentimos, no hemos encontrado el lugar." << endl;
    }
    else if (lugarEscogido->sublistasTiempos != NULL)
    {
        relTiempoLugar *tempTiempo = lugarEscogido->sublistasTiempos;
        int extLluvioso = NULL;
        int extSeco = NULL;
        int conAnterioLluvioso = 0;
        int conAnteriorSeco = 0;
        int contadorLluvioso = 0;
        int contadorSeco = 0;
        cout << "\nDigite el a??o en el que desea revisar los extremos: ";
        cin >> anioParaBuscar;
        do
        {
            if (tempTiempo->enlace->fecha->tm_year == anioParaBuscar)
            {
                relTiempoLluvia *tempLluvia = tempTiempo->enlace->sublistasLluvias;
                while (tempLluvia != NULL)
                {
                    if (tempLluvia->enlace->rangoPromedioEn_mm <= 0)
                    {
                        contadorSeco = contadorSeco + 1;
                    }
                    else if (tempLluvia->enlace->rangoPromedioEn_mm >= 60)
                    {
                        contadorLluvioso = contadorLluvioso + 1;
                    }
                    tempLluvia = tempLluvia->sig;
                }
                if (contadorLluvioso > conAnterioLluvioso)
                {
                    extLluvioso = tempTiempo->enlace->fecha->tm_mon;
                    conAnterioLluvioso = contadorLluvioso;
                }
                if (contadorSeco > conAnteriorSeco)
                {
                    extSeco = tempTiempo->enlace->fecha->tm_mon;
                    conAnteriorSeco = contadorSeco;
                }
            }
            tempTiempo = tempTiempo->sig;
        } while (tempTiempo->sig != NULL);

        if (extSeco == NULL)
        {
            cout << "\nEn este a??o no tenemos extremos secos";
        }
        else
        {
            cout << "\nEl mes con mayor extremos secos es: " << mes[extSeco];
        }

        if (extLluvioso == NULL)
        {
            cout << "\nEn este a??o no tenemos extremos lluviosos";
        }
        else
        {
            cout << "\nEl mes con mayor extremos lluvioso es: " << mes[extLluvioso];
        }
    }
}

/*Determinar e imprimir la persona que mas registros del tiempo tiene.*/
void personaMayorRegistrosTiempo()
{
    personas *tempPersona = listaPersonas;
    personas *masRegistros;
    int registrosAnterior = 0;
    int contadorRegistros = 0;
    do
    {
        relTiempoPersona *tempRegistro = tempPersona->sublistasTiempos;
        if (tempRegistro != NULL)
        {
            do
            {
                contadorRegistros = contadorRegistros + 1;
                tempRegistro = tempRegistro->sig;
            } while (tempRegistro != NULL);
            if (contadorRegistros > registrosAnterior)
            {
                masRegistros = tempPersona;
                registrosAnterior = contadorRegistros;
            }
            contadorRegistros = 0;
        }
        tempPersona = tempPersona->sig;
    } while (tempPersona->sig != NULL);

    cout << "La persona con mas registros de tiempo es " << masRegistros->nombre;
}

// Menu de Borrado
void menuBorrado()
{
    cout << "\n--------------------BIENVENIDO AL MENU DE BORRADO------------------------" << endl;
    int opcion;
    cout << "\n1. Borrar Personas";
    cout << "\n2. Borrar Lluvia";
    cout << "\n3. Borrar Region";
    cout << "\n4. Borrar tiempo";
    cout << "\n5. Borrar lugar";
    cout << "\n6. Borrar efimeridad" << endl;

    cout << "\nDigite su opcion a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        int cedula;
        cout << "==== Borrando Persona ===" << endl;
        cout << "\nCedula: ";
        cin >> cedula;
        cout << endl;
        borrarPersona(cedula);
        cout << "=== Se ha borrado la persona ===";
    }
    else if (opcion == 2)
    {
        string codigo;
        cout << "==== Borrando Lluvia ===" << endl;
        cout << "\nCodigo: ";
        cin >> codigo;
        cout << endl;
        borrarLluvia(codigo);
        cout << "=== Se ha borrado la lluvia ===";
    }
    else if (opcion == 3)
    {
        int id;
        cout << "==== Borrando Region ===" << endl;
        cout << "\n ID: ";
        cin >> id;
        cout << endl;
        borrarRegion(id);
        cout << "=== Se ha borrado la region ===";
    }
    else if (opcion == 4)
    {
        string fecha;
        cout << "==== Borrando Tiempo ===" << endl;
        cout << "\n Fecha(YYYY/MM/DD): ";
        cin >> fecha;
        cout << endl;
        borrarTiempo(obtenerFechadeString(fecha));
        cout << "=== Se ha borrado el Tiempo ===";
    }
    else if (opcion == 5)
    {
        string nombre;
        cout << "==== Borrando Lugar ===" << endl;
        cout << "\nNombre: ";
        cin >> nombre;
        cout << endl;
        borrarLugar(nombre);
        cout << "=== Se ha borrado el lugar ===";
    }
    else if (opcion == 6)
    {
        string fechaE;
        cout << "==== Borrando Efimeridad ===" << endl;
        cout << "\n Fecha(YYYY/MM/DD): ";
        cin >> fechaE;
        cout << endl;
        borrarTiempo(obtenerFechadeString(fechaE));
        cout << "=== Se ha borrado la Efimeridad ===";
    }
}

// Menu de Modificado
void menuModificar()
{
    cout << "\n--------------------BIENVENIDO AL MENU DE MODIFICAR------------------------" << endl;
    int opcion;
    cout << "\n1. Modificar Persona";
    cout << "\n2. Modificar luvia";
    cout << "\n3. Modificar Region";
    cout << "\n4. Modifcar Lugar";
    cout << "\n5. Modificar Efimeridad";
    cout << "\n6. Modificar Tiempo" << endl;

    cout << "\nDigite su opcion a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        string nombre, lugarResidencia, agnoResidencia;
        int cedula, cedulaN;

        cout << "==== Modificando Persona ===" << endl;
        cout << "\nCedula de la persona a modificar: ";
        cin >> cedula;
        cout << endl;
        cout << "\nNuevo Nombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nNueva Cedula: ";
        cin >> cedulaN;
        cout << endl;
        cout << "\nNuevo Lugar Residencia: ";
        getline(cin >> ws, lugarResidencia);
        cout << endl;
        cout << "\nNuevo A??o Residencia: ";
        cin >> agnoResidencia;
        cout << endl;

        if (buscarPersona(cedula) != NULL)
        {
            modificarPersona(cedula, cedulaN, nombre, lugarResidencia, agnoResidencia);
            cout << "Personas Modificada Correctamente";
        }
        else
        {
            cout << "No se puede modificar a la persona, al parecer no existe";
        }
    }
    else if (opcion == 2)
    {

        string codigo, codigoN, nombre;
        int rangoPromedioEn_MM;
        cout << "==== Modificando Lluvia ===" << endl;
        cout << "\nCodigo de la lluvia a modificar: ";
        cin >> codigo;
        cout << endl;
        cout << "\nNuevo Codigo: ";
        cin >> codigoN;
        cout << endl;
        cout << "\nNuevo Nombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nNuevo Rango en Promedio(en MM): ";
        cin >> rangoPromedioEn_MM;
        cout << endl;

        if (buscarLluvia(codigo) != NULL)
        {
            modificarLluvia(codigo, codigoN, nombre, rangoPromedioEn_MM);
            cout << "Lluvia Modificada Correctamente";
        }
        else
        {
            cout << "No se pudo modificar la lluvia";
        }
    }
    else if (opcion == 3)
    {
        string nombre, ubicacion;
        int id, idN;
        cout << "==== Modificando Region ===" << endl;
        cout << "\nID de la region a modificar: ";
        cin >> id;
        cout << endl;
        cout << "\nNuevo ID: ";
        cin >> idN;
        cout << endl;
        cout << "\nNuevo Nombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nNueva Ubicacion: ";
        getline(cin >> ws, ubicacion);
        cout << endl;

        if (buscarRegion(id) != NULL)
        {
            modificarRegion(id, idN, nombre, ubicacion);
            cout << "Region Modificada Correctamente";
        }
        else
        {
            cout << "No se pudo modificar la region";
        }
    }
    else if (opcion == 4)
    {
        string nombre, nombreN;
        int poblacion;
        double metrosCuadrados;
        cout << "==== Modificando Lugar ===" << endl;
        cout << "\nNombre del lugar a modificar: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nNuevo Nombre: ";
        getline(cin >> ws, nombreN);
        cout << endl;
        cout << "\nNueva Poblacion: ";
        cin >> poblacion;
        cout << endl;
        cout << "\nNuevo Metros Cuadrados: ";
        cin >> metrosCuadrados;
        cout << endl;

        if (buscarLugar(nombre) != NULL)
        {
            modificarLugar(nombre, nombreN, poblacion, metrosCuadrados);
            cout << "Lugar Modificado Correctamente";
        }
        else
        {
            cout << "No se pudo modificar el lugar";
        }
    }
    else if (opcion == 5)
    {
        string nombre, fecha, fechaN, horaSalida, horaOcultamiento;
        cout << "==== Modificando Efimeridad ===" << endl;
        cout << "\nFecha de efimeridad a modificar: ";
        cin >> fecha;
        cout << endl;
        cout << "\nNuevo Nombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nNueva Fecha(YYYY/MM/DD): ";
        cin >> fechaN;
        cout << endl;
        cout << "\nNueva Hora Salida(HH:MM): ";
        cin >> horaSalida;
        cout << endl;
        cout << "\nNueva Hora Ocultamieto(HH:MM): ";
        cin >> horaOcultamiento;
        cout << endl;
        tm *fechaB = obtenerFechadeString(fecha);
        tm *fechaNN = obtenerFechadeString(fechaN);
        tm *horaS = obtenerHoradeString(horaSalida);
        tm *horaO = obtenerHoradeString(horaOcultamiento);

        if (buscarEfemeridad(fechaB) != NULL)
        {
            modificarEfimeridad(nombre, fechaB, fechaNN, horaS, horaO);
            cout << "Efimeridad Modificada Correctamente";
        }
        else
        {
            cout << "No se pudo modificar la Efimeridad";
        }
    }
    else if (opcion == 6)
    {
        string fecha, fechaN;
        bool siLlovio = false;
        int precipitacion, tempMaxima, tempMinima, velocidadViento, direccionViento, humedadRelativa;
        string lluvia;
        cout << "==== Insertando Tiempo ===" << endl;
        cout << "\nFecha del tiempo a modificar(YYYY/MM/DD): ";
        cin >> fecha;
        cout << endl;
        cout << "\nNueva Fecha(YYYY/MM/DD): ";
        cin >> fechaN;
        cout << endl;
        cout << "\nNueva Precipitacion: ";
        cin >> precipitacion;
        cout << endl;
        cout << "\nNueva Temperatura Maxima: ";
        cin >> tempMaxima;
        cout << endl;
        cout << "\nNueva Temperatura Minima: ";
        cin >> tempMinima;
        cout << endl;
        cout << "\nNueva Velocidad del viento: ";
        cin >> velocidadViento;
        cout << endl;
        cout << "\nNueva Direccion del viento: ";
        cin >> direccionViento;
        cout << endl;
        cout << "\nNueva Humedad del viento: ";
        cin >> humedadRelativa;
        cout << endl;
        cout << "\nNuevo Llovio(s/n): ";
        cin >> lluvia;
        cout << endl;
        if (siLlovio == 's')
        {
            siLlovio = true;
        }
        tm *fB = obtenerFechadeString(fecha);
        tm *fN = obtenerFechadeString(fecha);
        int agno = fB->tm_year;
        int mes = fB->tm_mon;
        int dia = fB->tm_mday;

        if (buscarTiempo(agno, mes, dia) != NULL)
        {
            modificarTiempo(fB, fN, precipitacion, tempMaxima, tempMinima, velocidadViento, direccionViento, humedadRelativa, siLlovio);
            cout << "Tiempo Modificado Correctamente";
        }
        else
        {
            cout << "No se pudo modificar el tiempo";
        }
    }
}

// Menu de Inserciones
void menuInserciones(personas *personaLogeada)
{

    cout << "\n--------------------BIENVENIDO AL MENU DE INSERCIONES------------------------" << endl;
    int opcion;
    cout << "\n1. Insertar en lista de personas";
    cout << "\n2. Insertar en lista de lluvia";
    cout << "\n3. Insertar en lista de region";
    cout << "\n4. Insertar en lista de lugar";
    cout << "\n5. Insertar en lista de efimeridad";
    cout << "\n6. Insertar en lista tiempo";
    cout << "\n7. Insertar en sublista tiempo (Lugar)";
    cout << "\n8. Insertar en sublista tiempo (Personas)";
    cout << "\n9. Insertar en sublista Lugar (Region)" << endl;

    cout << "\nDigite su opcion a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        string nombre, lugarResidencia, agnoResidencia;
        int cedula;

        cout << "==== Insertando Persona ===" << endl;
        cout << "\nNombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nCedula: ";
        cin >> cedula;
        cout << endl;
        cout << "\nLugar Residencia: ";
        getline(cin >> ws, lugarResidencia);
        cout << endl;
        cout << "\nA??o Residencia: ";
        cin >> agnoResidencia;
        cout << endl;

        if (buscarPersona(cedula) == NULL)
        {
            listaPersonas = insertarPersona(nombre, cedula, lugarResidencia, agnoResidencia);
            cout << "Personas Insertada Correctamente";
        }
        else
        {
            cout << "No se pudo inserta a la persona, al parecer YA EXISTE";
        }
    }
    else if (opcion == 2)
    {

        string codigo, nombre;
        int rangoPromedioEn_MM;
        cout << "==== Insertando Lluvia ===" << endl;
        cout << "\nCodigo: ";
        cin >> codigo;
        cout << endl;
        cout << "\nNombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nRango en Promedio(en MM): ";
        cin >> rangoPromedioEn_MM;
        cout << endl;

        if (buscarLluvia(codigo) == NULL)
        {
            listaLluvia = insertarLluvia(codigo, nombre, rangoPromedioEn_MM, listaLluvia);
            cout << "Lluvia Insertada Correctamente";
        }
        else
        {
            cout << "No se pudo inserta la lluvia, al parecer YA EXISTE";
        }
    }
    else if (opcion == 3)
    {
        string nombre, ubicacion;
        int id;
        cout << "==== Insertando Region ===" << endl;
        cout << "\nID: ";
        cin >> id;
        cout << endl;
        cout << "\nNombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nUbicacion: ";
        getline(cin >> ws, ubicacion);
        cout << endl;

        if (buscarRegion(id) == NULL)
        {
            listaRegion = insertarRegion(id, nombre, ubicacion, listaRegion);
            cout << "Region Insertada Correctamente";
        }
        else
        {
            cout << "No se pudo inserta la region, al parecer YA EXISTE";
        }
    }
    else if (opcion == 4)
    {
        string nombre;
        int poblacion;
        double metrosCuadrados;
        cout << "==== Insertando Lugar ===" << endl;
        cout << "\nNombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nPoblacion: ";
        cin >> poblacion;
        cout << endl;
        cout << "\nMetros Cuadrados: ";
        cin >> metrosCuadrados;
        cout << endl;

        if (buscarLugar(nombre) == NULL)
        {
            listaLugar = insertarLugar(nombre, poblacion, metrosCuadrados, listaLugar);
            cout << "Lugar Insertado Correctamente";
        }
        else
        {
            cout << "No se pudo inserta el lugar, al parecer YA EXISTE";
        }
    }
    else if (opcion == 5)
    {
        string nombre, fecha, horaSalida, horaOcultamiento;

        cout << "==== Insertando Efimeridad ===" << endl;
        cout << "\nNombre: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nFecha(YYYY/MM/DD): ";
        cin >> fecha;
        cout << endl;
        cout << "\nHora Salida(HH:MM): ";
        cin >> horaSalida;
        cout << endl;
        cout << "\nHora Ocultamieto(HH:MM): ";
        cin >> horaOcultamiento;
        cout << endl;
        tm *f = obtenerFechadeString(fecha);
        tm *horaS = obtenerHoradeString(horaSalida);
        tm *horaO = obtenerHoradeString(horaOcultamiento);

        if (buscarEfemeridad(f) == NULL)
        {
            listaEfimeridades = insertarEfimeridad(nombre, f, horaS, horaO);
            cout << "Efimeridad Insertada Correctamente";
        }
        else
        {
            cout << "No se pudo inserta la Efimeridad, al parecer YA EXISTE";
        }
    }
    else if (opcion == 6)
    {
        string fecha;
        bool siLlovio = false;
        int precipitacion, tempMaxima, tempMinima, velocidadViento, direccionViento, humedadRelativa;
        string lluvia;
        cout << "==== Insertando Tiempo ===" << endl;
        cout << "\nFecha(YYYY/MM/DD): ";
        cin >> fecha;
        cout << endl;
        cout << "\nPrecipitacion: ";
        cin >> precipitacion;
        cout << endl;
        cout << "\nTemperatura Maxima: ";
        cin >> tempMaxima;
        cout << endl;
        cout << "\nTemperatura Minima: ";
        cin >> tempMinima;
        cout << endl;
        cout << "\nVelocidad del viento: ";
        cin >> velocidadViento;
        cout << endl;
        cout << "\nDireccion del viento: ";
        cin >> direccionViento;
        cout << endl;
        cout << "\nHumedad del viento: ";
        cin >> humedadRelativa;
        cout << endl;
        cout << "\nLlovio(s/n): ";
        cin >> lluvia;
        cout << endl;
        if (siLlovio == 's')
        {
            siLlovio = true;
        }

        tm *f = obtenerFechadeString(fecha);
        int agno = f->tm_year;
        int mes = f->tm_mon;
        int dia = f->tm_mday;

        if (buscarTiempo(agno, mes, dia) == NULL)
        {
            listaTiempo = insertarTiempo(f, precipitacion, tempMaxima, tempMinima, velocidadViento, direccionViento, humedadRelativa, siLlovio);
            cout << "Tiempo insertado Correctamente";
        }
        else
        {
            cout << "No se pudo inserta el tiempo, al parecer YA EXISTE";
        }
    }
    else if (opcion == 7)
    {
        string nombreLugar, fecha;

        cout << "==== Insertando en Sublista de Tiempo(Lugar) ===" << endl;
        cout << "\nFecha del tiempo(YYYY/MM/DD):";
        cin >> fecha;
        cout << endl;
        cout << "\nNombre del lugar: ";
        getline(cin >> ws, nombreLugar);
        cout << endl;

        tm *f = obtenerFechadeString(fecha);

        relacionarTiempoLugar(f, nombreLugar);
    }
    else if (opcion == 8)
    {
        string fecha;
        int cedula;

        cout << "==== Insertando en Sublista de Tiempo(Persona) ===" << endl;
        cout << "\nFecha del tiempo(YYYY/MM/DD): ";
        cin >> fecha;
        cout << endl;

        tm *f = obtenerFechadeString(fecha);

        relacionarTiempoPersona(f, personaLogeada->cedula);
    }
    else if (opcion == 9)
    {
        string nombre;
        int id;

        cout << "==== Insertando en Sublista de Lugar(Region) ===" << endl;
        cout << "\nNombre del Lugar: ";
        getline(cin >> ws, nombre);
        cout << endl;
        cout << "\nID de la Region: ";
        cin >> id;
        cout << endl;

        relacionarLugarRegion(nombre, id);
    }
    else
    {
        cout << "La opcion digitada es invalida";
    }
}
// Menu impresiones
void menuImprimir()
{

    cout << "\n--------------------BIENVENIDO AL MENU DE IMPRESIONES------------------------" << endl;
    int opcion;
    cout << "\n1. Imprimir lista de personas";
    cout << "\n2. Imprimir lista de lluvia";
    cout << "\n3. Imprimir lista de region";
    cout << "\n4. Imprimir lista de lugar";
    cout << "\n5. Imprimir lista de efimeridad";
    cout << "\n6. Imprimir lista tiempo";
    cout << "\n7. Imprimir sublista tiempo (Lugar)";
    cout << "\n8. Imprimir sublista tiempo (Personas)";
    cout << "\n9. Imprimir sublista Lugar (Region)";
    cout << "\n10. Imprimir sublista lluvia (Tiempo)" << endl;

    cout << "\nDigite su opcion a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        imprimirPersonas(listaPersonas);
    }
    else if (opcion == 2)
    {
        imprimirLluvia(listaLluvia);
    }
    else if (opcion == 3)
    {
        imprimirRegion(listaRegion);
    }
    else if (opcion == 4)
    {
        imprimirLugar(listaLugar);
    }
    else if (opcion == 5)
    {
        imprimirEfimeridades(listaEfimeridades);
    }
    else if (opcion == 6)
    {
        imprimirListaTiempo(listaTiempo);
    }
    else if (opcion == 7)
    {
        string nombre;
        cout << "\n\nEscriba el nombre del lugar: ";
        getline(cin >> ws, nombre);
        imprimirTiempoPorLugar(nombre);
    }
    else if (opcion == 8)
    {
        int cedula;
        cout << "\n\nEscriba la cedula de la persona: ";
        cin >> cedula;
        imprimirTimepoPorPersona(cedula);
    }
    else if (opcion == 9)
    {
        int id;
        cout << "\n\nEscriba el ID de de la region : ";
        cin >> id;
        imprimirLugaresPorRegion(id);
    }
    else if (opcion == 10)
    {
        string fecha;
        cout << "\n\nEscriba la fecha del tiempo(YYYY/MM/DD) : ";
        cin >> fecha;
        tm *fechaB = obtenerFechadeString(fecha);
        imprimirLluviasPorTiempo(fechaB);
    }
    else
    {
        cout << "La opcion digitada es invalida";
        // main();
    }
}
// Menu Consultas
void menuConsultas()
{
    cout << "\n--------------------BIENVENIDO AL MENU DE CONSULTAS------------------------" << endl;
    int opcion;
    cout << "\n1. Imprimir el dia en el sol sale mas temprano y el dia en el que el sol se oculta mas temprano.";
    cout << "\n2. Imprimir las horas con mayor diferencia de salida del sol en un anio.";
    cout << "\n3. Imprimir los extremos (seco/lluvioso) de un lugar en un determinado anio.";
    cout << "\n4. Imprimir la persona que ha hecho mayor caantidad de registros de tiempo." << endl;
    cout << "\nDigite su opcion a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        impOcultamientoSalidaSol();
    }
    else if (opcion == 2)
    {
        diferenciaSalidaSol();
    }
    else if (opcion == 3)
    {
        imprimirExtremos();
    }
    else if (opcion == 4)
    {
        personaMayorRegistrosTiempo();
    }
    else
    {
        cout << "La opcion digitada es invalida";
        // main();
    }
}

void menuReportes()
{
    cout << "\n--------------------BIENVENIDO AL MENU DE REPORTES------------------------" << endl;
    int opcion;
    cout << "\n1. Imprimir la informacion de todas las listas.";
    cout << "\n2. Imprimir de los horarios de la salida de X y de la puesta de X por mes separado por anio.";
    cout << "\n3. Imprimir la precipitaci??n mensual promedio de cada lugar en un a??o X";
    cout << "\n4. Imprimir la precipitaci??n mensual promedio de cada regi??n en un a??o X"; 
    cout << "\n5. Imprimir las variables climatol??gicas de una region X y un periodo Y";
    cout << "\n6. imprimir si hay periodos en un a??o X de cambios en tipos de d??as de lluvia";
    cout << "\n7. imprimir si hay periodos en un a??o X de cambios en tipos de d??as de lluvia";
    cout << "\n8. Imprimir los d??as de lluvia de cada mes de un a??o X para un lugar Z";
    cout << "\n9. Obtenga e imprima los extremos de temperatura de cada mes de un a??o X para un lugar Z" <<endl;




    cout << "\nDigite su opcion a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        menuImprimir();
    }
    else if (opcion == 2)
    {
        reporteEfimeridadAnio();
    }
    else if (opcion == 3)
    {
        int anioRep;
        cout << "\nDigite el anio: ";
        cin >> anioRep;
        reportesPromedioMensualLugaresAnioX(anioRep);
    }
    else if (opcion == 4)
    {
        int anioPR;
        cout << "\n Digite el a??o en que desea buscar: ";
        cin >> anioPR;
        impPrecipitacionRegio(anioPR);
    }
    else if (opcion == 5)
    {
        reporteVariablesClimaticas();
    }else if (opcion == 6)
    {
        int anioP;
        cout << "\n Digite el a??o: ";
        cin >> anioP;
        reporteCambiodeLLuvia(anioP);

    }
    else if (opcion == 7)
    {
        int a; // A??o X
        string nombreLugar;
        lugar *l; // lugar Z
        cout << "\n Digite el anio: ";
        cin >> a;
        while (true)
        {
            cout << "\n Digite el nombre del lugar: ";
            getline(cin >> ws, nombreLugar);
            if (buscarLugar(nombreLugar) != NULL)
            {
                l = buscarLugar(nombreLugar);
                break;
            }
        }
        imprimirClasificacionLluvia(a, l);
    }
    else if (opcion == 8)
    {
        int a;
        string nombre;
        cout << "\n Digite el a??o: ";
        cin >> a;
        cout << "\n Digite el nombre: ";
        getline(cin >> ws, nombre);
        imprimirDiasLluvias(a,nombre);
    }
    else if (opcion == 9)
    {
        string lugarE;
        int anioE;
        cout << "\n Digite el a??o en que desea buscar: ";
        cin >> anioE;
        cout << endl;
        cout << "\n Digite el lugar en el que desea buscar: ";
        cin >> lugarE;
        reporteExtremosAnioLugar(anioE, lugarE);
    }
    else
    {
        cout << "La opcion digitada es invalida";
        // main();
    }
}

int main()
{

    llenarVectorMeses();

    cargarDatos();

    /* Pruebas
    tm *fecha = obtenerFechadeString("2020/10/02");
    relacionarTiempoLugar(fecha,"San Jose");
    lugar * listaLugarPrueba = listaLugar;
    relacionarTiempoPersona(fecha,208360735);*/

    cout << "\n--------------------BIENVENIDO AL SISTEMA------------------------" << endl;

    while (true)
    {
        cout << "\n------------ESCRIBA SU NUMERO DE CEDULA PARA INGRESAR -------------" << endl;
        int cedula;
        cout << "\nCedula: ";
        cin >> cedula;
        cout << endl;
        loginPersona = buscarPersona(cedula);
        if (loginPersona == NULL)
        {
            cout << "\nLo sentimos, intente de nuevo" << endl;
        }
        else
        {
            while (true)
            {
                int opcion;
                cout << "\n========================";
                cout << "\n1. Menu de Inserciones.";
                cout << "\n2. Menu de Imprimir.";
                cout << "\n3. Menu de Borrar.";
                cout << "\n4. Menu de Modificar.";
                cout << "\n5. Menu de consultas.";
                cout << "\n6. Menu de reportes.";
                cout << "\n0. Salir" << endl;
                cout << "\n========================";
                cout << "\nDigite su opcion: ";
                cin >> opcion;
                cout << endl;

                if (opcion == 1)
                    menuInserciones(loginPersona);

                else if (opcion == 2)
                    menuImprimir();

                else if (opcion == 3)
                    menuBorrado();

                else if (opcion == 4)
                    menuModificar();

                else if (opcion == 5)
                    menuConsultas();

                else if (opcion == 6)
                    menuReportes();

                else if (opcion == 0)
                    break;
            }
        }
    }

    // cambios

    return 0;
}