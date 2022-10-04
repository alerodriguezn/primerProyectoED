#include <iostream>
#include <ctime>  //Libreria utilizada para el manejo de las fechas
#include <vector> //Libreria utilizada para el manejo de las fechas.
#include <string> //Librería utilizada para la función "to_string"

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
struct personas
{
    string nombre;
    int cedula;
    string lugarResidencia;
    string agnoResidencia;
    struct tiempo *sublistasTiempos;

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
    }

    void agregarTiempo(tiempo *nuevoTiempo)
    {
        // Aquí iría el metodo de agregar un tiempo a la sublista de tiempos o directamente mandar una lista de tiempos
        cout << "Agregando nuevo registro de tiempo";
    }
} * listaPersonas;

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

struct region
{
    int id;
    string nombre;
    string ubicacion;
    struct lugar *sublistasLugares;

    region *sig;

    region(int id, string nombre, string ubicacion)
    {
        this->id = id;
        this->nombre = nombre;
        this->ubicacion = ubicacion;
        sig = NULL;
    }

    void agregarLugar(struct lugar *nuevoLugar)
    {
        // Aqui iria la funcion de agregar lugar
        cout << "Agregando nuevo lugar";
    }
} * listaRegion;

struct lugar
{
    string nombre;
    int poblacion;
    double metrosCuadrados;
    struct tiempo *sublistasTiempos;

    lugar *sig;

    lugar(string nombre, int poblacion, double metrosCuadrados)
    {
        this->nombre = nombre;
        this->poblacion = poblacion;
        this->metrosCuadrados = metrosCuadrados;
        sig = NULL;
    }

    void agregarTiempo(tiempo *nuevoTiempo)
    {
        // Aquí iría el metodo de agregar un tiempo a la sublista de tiempos o directamente mandar una lista de tiempos
        cout << "Agregando nuevo registro de tiempo";
    }

} * listaLugar;

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
    lluvia *sublistasLluvias;

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
    }

    void agregarLluvia(lluvia *nuevaLluvia)
    {
        // Aquí iría el metodo de agregar la lluvia a la sublista de lluvias o directamente mandar una lista de lluvias
        cout << "Agregando nuevo registro de lluvia";
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
        // BUSCAR AL ÚLTIMO PARA QUE APUNTE AL NUEVO NODO.
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

// TERMINAR EL INSERTAR TIEMPO
tiempo *insertarTiempo(tm *fecha, int precipitacion, int tempMaxima, int tempMinima, int velocidadViento, int direccionViento, int humedadRelativa, bool siLlovio)
{
    tiempo *nuevoTiempo = new tiempo(fecha, precipitacion, tempMaxima, tempMinima, velocidadViento, direccionViento, humedadRelativa, siLlovio);
    if (listaTiempo == NULL)
    {
        listaTiempo = nuevoTiempo;
    }
    else if ((fecha->tm_year <= listaTiempo->fecha->tm_year) && (fecha->tm_mon <= listaTiempo->fecha->tm_mon) && (fecha->tm_mday <= listaTiempo->fecha->tm_mday))
    {
        nuevoTiempo->sig = listaTiempo;
        listaTiempo = nuevoTiempo;
    }
    else
    {
        tiempo *temp = listaTiempo;
        tiempo *te = listaTiempo;

        while ((fecha->tm_year > listaTiempo->fecha->tm_year) || ((fecha->tm_year == listaTiempo->fecha->tm_year) && (fecha->tm_mon > listaTiempo->fecha->tm_mon)) || ((fecha->tm_year == listaTiempo->fecha->tm_year) && (fecha->tm_mon == listaTiempo->fecha->tm_mon) && ((fecha->tm_mday > listaTiempo->fecha->tm_mday))))
        {
            if (temp->sig != NULL)
            {
                temp = temp->sig;
            }
            if (temp->sig == NULL)
            {
                temp->sig = nuevoTiempo;
                break;
            }
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

    else if ((fecha->tm_year <= listaEfimeridades->fecha->tm_year) && (fecha->tm_mon <= listaEfimeridades->fecha->tm_mon) && (fecha->tm_mday <= listaEfimeridades->fecha->tm_mday))
    {
        nuevaEfimeridad->sig = listaEfimeridades;
        listaEfimeridades->ant = nuevaEfimeridad;
        listaEfimeridades = nuevaEfimeridad;
    }
    else
    {
        efimeridad *temp = listaEfimeridades;
        efimeridad *te = listaEfimeridades;

        /*
        Analisis del siguiente while
        Datos del Elemento nuevo:          x1=2022 x2=12 x3=16
        Datos del Elemento en la lista:    y1=2022 y2=11 y3=17

        Así se representaría para validar que sea mayor :
        (   (x1>y1) || (  (x1 == y1) && (x2 > y2)  ) || (  (x1 == y1) && (x2 == y2) && (x3 > y3)  )  )
        */
        while ((fecha->tm_year > listaEfimeridades->fecha->tm_year) || ((fecha->tm_year == listaEfimeridades->fecha->tm_year) && (fecha->tm_mon > listaEfimeridades->fecha->tm_mon)) || ((fecha->tm_year == listaEfimeridades->fecha->tm_year) && (fecha->tm_mon == listaEfimeridades->fecha->tm_mon) && ((fecha->tm_mday > listaEfimeridades->fecha->tm_mday))))
        {
            te = temp;
            if (temp->sig != NULL)
            {
                temp = temp->sig;
            }
            if (temp->sig == NULL)
            {
                temp->sig = nuevaEfimeridad;
                nuevaEfimeridad->ant = temp;
                break;
            }
        }
        // nuevaEfimeridad->ant = te;
        // te->sig = nuevaEfimeridad;
        // if (temp != NULL)
        // {
        //     nuevaEfimeridad->sig = temp;
        //     temp->ant = nuevaEfimeridad;
        // }
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
        cout << "\nError: El año debe tener 4 digitos. Ej: 2022\n";
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

// Devuelve la fecha de la instancia tm dada en los parametros. La retorna así: "25 de Septiembre del 2022"
string devolverFecha(tm *fecha)
{
    return to_string(fecha->tm_mday) + " de " + mes[fecha->tm_mon] + " del " + to_string(fecha->tm_year);
}

// Devuelve la hora de la instancia tm dada en los parametros. La retorna así: "4:00 p.m"
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
            cout << temp->codigo << "\t" << temp->nombre << "\t" << temp->rangoPromedioEn_mm << endl;
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
            cout << temp->id << "\t" << temp->nombre << "\t" << temp->ubicacion << endl;
            temp = temp->sig;
        }
        cout << endl;
    }
}

void imprimirLugar(lugar *lista)
{
    if (lista == NULL)
    {
        cout << "\nLa lista está vacía";
    }
    else
    {
        lugar *temp = lista;
        do
        {
            cout << temp->nombre << "\t" << temp->poblacion << "\t" << temp->metrosCuadrados << endl;
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
        cout << "\nIMPRIMIENTO HACIA ADELANTE... \n";
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
        // AHORA IMPRIMO HACIA ATRAS
        cout << "\nIMPRIMIENTO HACIA ATRAS... \n";
        while (temp != NULL)
        {
            cout << "Nombre: " << temp->nombre << endl;
            cout << "Fecha: " << devolverFecha(temp->fecha) << endl;
            cout << "Hora Salida: " << devolverHora(temp->horaSalida) << endl;
            cout << "Hora Ocultamiento: " << devolverHora(temp->horaOcultamiento) << endl;
            temp = temp->ant;
        }
    }
}

// =========== Metodos de Buscar ================

personas *buscarPersona(int cedula)
{
    cout << "Buscando Persona...";
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

    cout << "\nPersona No Encontrada" << endl;

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
    }
    cout << "Lugar no encontrado " << endl;
    return NULL;
}

tiempo *buscarTiempo(int anio, int mes, int dia)
{
    cout << "\nBuscando el tiempo por fecha..." << endl;

    if (listaTiempo == NULL)
    {
        cout << "\nLa lista está vacía" << endl;
    }
    else
    {
        tiempo *temp = listaTiempo;
        while (temp->sig != NULL)
        {
            if ((temp->fecha->tm_year == anio) && (temp->fecha->tm_mon == mes) && (temp->fecha->tm_mday == dia))
            {
                cout << "\nTiempo ENcontrado" << endl;
                return temp;
            }
            temp = temp->sig;
        }
    }
    cout << "\nNo se encontró el lugar" << endl;
    return NULL;
}

// Métodos que permiten guardar las fechas y las horas de los datos quemados
tm *crearFecha(int y, int m, int d)
{
    tm *fecha = new tm();
    fecha->tm_year = y;
    fecha->tm_mon = m;
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

/*  OTROS MÉTODOS   */
void cargarDatos()
{
    listaLluvia = insertarLluvia("COD#1", "NombreL#1", 01, listaLluvia);
    listaLluvia = insertarLluvia("COD#2", "NombreL#2", 02, listaLluvia);
    // listaLluvia = insertarLluvia("COD#3", "NombreL#3", 03, listaLluvia);
    // listaLluvia = insertarLluvia("COD#4", "NombreL#4", 04, listaLluvia);

    listaRegion = insertarRegion(12, "Region#1", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(14, "Region#2", "Ubicaicacio1", listaRegion);
    // listaRegion = insertarRegion(03, "Region#3", "Ubicaicacio1", listaRegion);
    // listaRegion = insertarRegion(04, "Region#4", "Ubicaicacio1", listaRegion);

    listaLugar = insertarLugar("San Juan", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("San Carlos", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Santa Clara", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("San Jose", 100, 2.5, listaLugar);

    listaPersonas = insertarPersona("Alejandro Rodriguez", 208360735, "El Tanque", "2018");
    listaPersonas = insertarPersona("Juan Ca", 2081230735, "La Fortuna", "2013");
    // listaPersonas = insertarPersona("Beto Beto", 1011230735, "San Rafael","2022");
    // listaPersonas = insertarPersona("Roberto Jimenez", 3011230735, "Florencia","2021");
    // listaPersonas = insertarPersona("Alondra", 4011230735, "Santa Clara","2024");
    // listaPersonas = insertarPersona("Carlos Ruiz", 3011230735, "Florencia","2021");
    // listaPersonas = insertarPersona("Bianca Ruiz", 4011230735, "Florencia","2022");

    // Forma para pedir la fecha y hora en variables y insertarlas despues
    //  cout << "\nIngresa la fecha\n";
    //  tm * fecha1 = pedirFecha();
    //  cout << "\nIngresa la hora de salida\n";
    //  tm * hora1 = pedirHora();
    //  cout << "\nIngresa la hora de ocultamiento\n";
    //  tm * hora2 = pedirHora();

    // cout << "\nIngresa la fecha\n";
    // tm * fecha2 = pedirFecha();
    // cout << "\nIngresa la hora de salida\n";
    // tm * hora3 = pedirHora();
    // cout << "\nIngresa la hora de ocultamiento\n";
    // tm * hora4 = pedirHora();

    // listaEfimeridades = insertarEfimeridad("Efimeridad 1",fecha1, hora1, hora2);
    // listaEfimeridades = insertarEfimeridad("Efimeridad 2",fecha2, hora3, hora4);

    // Otra forma de meterlos pero sin pedir los datos al usuario

    // cout << "\nIngresa la fecha\n";
    tm *fecha1 = new tm();
    fecha1->tm_year = 2020;
    fecha1->tm_mon = 3;
    fecha1->tm_mday = 16;

    // cout << "\nIngresa la hora de salida\n";
    tm *hora1 = new tm();
    hora1->tm_hour = 7;
    hora1->tm_min = 25;

    // cout << "\nIngresa la hora de ocultamiento\n";
    tm *hora2 = new tm();
    hora2->tm_hour = 17;
    hora2->tm_min = 9;
    //---------------------------
    // cout << "\nIngresa la fecha\n";
    tm *fecha2 = new tm();
    fecha2->tm_year = 2020;
    fecha2->tm_mon = 2;
    fecha2->tm_mday = 12;

    // cout << "\nIngresa la hora de salida\n";
    tm *hora3 = new tm();
    hora3->tm_hour = 7;
    hora3->tm_min = 25;

    // cout << "\nIngresa la hora de ocultamiento\n";
    tm *hora4 = new tm();
    hora4->tm_hour = 17;
    hora4->tm_min = 20;
    //---------------------------
    // cout << "\nIngresa la fecha\n";
    tm *fechaX = new tm();
    fechaX->tm_year = 2020;
    fechaX->tm_mon = 6;
    fechaX->tm_mday = 11;

    // cout << "\nIngresa la hora de salida\n";
    tm *horaX = new tm();
    horaX->tm_hour = 7;
    horaX->tm_min = 25;

    // cout << "\nIngresa la hora de ocultamiento\n";
    tm *horaX2 = new tm();
    horaX2->tm_hour = 12;
    horaX2->tm_hour = 20;

    listaEfimeridades = insertarEfimeridad("Efimeridad 1", fecha1, hora1, hora2);
    listaEfimeridades = insertarEfimeridad("Efimeridad 2", fecha2, hora3, hora4);
    listaEfimeridades = insertarEfimeridad("Efimeridad 3", fechaX, horaX, horaX2);

    listaTiempo = insertarTiempo(crearFecha(2020, 9, 28), 04, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 9, 30), 04, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 10, 2), 04, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 10, 4), 04, 30, 24, 14, -45, -3, true);
}

void impOcultamientoSalidaSol() 
{
    tm * horaTempranoOcultamiento = new tm;
    tm * horaTardioSalida = new tm;

    if (listaEfimeridades == NULL) 
    {
        cout << "\nLa lista está vacía" << endl;
    }
    else
    {
        efimeridad *temp = listaEfimeridades;
        horaTempranoOcultamiento = temp->horaOcultamiento;
        horaTardioSalida = temp->horaSalida;
        while (temp->sig != NULL)
        {
            temp = temp->sig;
            //Comparando las horas para determinar el ocultamiento más temprano
            if (temp->horaOcultamiento->tm_hour < horaTempranoOcultamiento->tm_hour) {
                horaTempranoOcultamiento = temp->horaOcultamiento;
            }
            else if ((temp->horaOcultamiento->tm_hour == horaTempranoOcultamiento->tm_hour) && (temp->horaOcultamiento->tm_min < horaTempranoOcultamiento->tm_min))
            {
                horaTempranoOcultamiento = temp->horaOcultamiento;
            }
            //Comparando las horas para determinar la salida del sol más tranquila
            if (temp->horaSalida->tm_hour > horaTardioSalida->tm_hour) {
                horaTardioSalida = temp->horaSalida;
            }
            else if ((temp->horaSalida->tm_hour == horaTardioSalida->tm_hour) && (temp->horaSalida->tm_min > horaTardioSalida->tm_min))
            {
                horaTardioSalida = temp->horaSalida;
            }
        }
    }
    cout << "\nLa hora de ocultamiento del sol más temprano es: " << devolverHora(horaTempranoOcultamiento);
    cout << "\nLa hora de salida del sol más tardía es: " << devolverHora(horaTardioSalida) << endl;
}

void menuConsultas()
{
    cout << "--------------------BIENVENIDO AL MENU DE CONSULTAS------------------------" << endl;
    int opcion;
    cout << "\n1. Imprimir el día en el sol sale más temprano y el día en el que el sol se oculta más temprano." << endl;
    
    cout << "\nDigite su opción a ejecutar: "; cin >> opcion; cout << endl;

    if (opcion == 1)
    {
        impOcultamientoSalidaSol();
    }
}

int main()
{

    cout << "--------------------BIENVENIDO AL SISTEMA------------------------" << endl;
    llenarVectorMeses();
    cargarDatos();

    buscarLugar("San Jose");
    buscarLugar("d");
    buscarPersona(208360735);

    buscarLluvia("COD#1");
    buscarLluvia("123#1");

    buscarRegion(12);
    buscarRegion(1234);

    buscarTiempo(2020, 10, 4);


    int opcion;
    cout << "\n1. Para ingresar al menu de consultas.";
    cout << "\n2. Para ingresar al menu de reportes." << endl;
    cout << "\nDigite su opción: "; cin >> opcion; cout << endl;

    if (opcion == 1)
    {
        menuConsultas();
    }

    return 0;
}