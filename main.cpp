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


struct relTiempoLugar
{
    relTiempoLugar*sig;
    struct tiempo*enlace;
    relTiempoLugar(){
    }

};


struct relTiempoPersona
{
    relTiempoPersona*sig;
    struct tiempo*enlace;
    relTiempoPersona(){
    }

};

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
personas*loginPersona;

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

// =========== Metodos de Buscar ================

personas *buscarPersona(int cedula)
{
    //cout << "Buscando Persona...";
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

    //cout << "\nPersona No Encontrada" << endl;

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
    //cout << "\nNo se encontró el lugar" << endl;
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
        cout << "\nLa lista está vacía";
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

void imprimirTiempoPorLugar(string nombre) {
    //Función que se encarga de imprimir el tiempo
    lugar *lugar = buscarLugar(nombre);
    if (lugar->sublistasTiempos == NULL) 
    {
        cout << "\nEsta lista está vacía" << endl;
    }
    else
    {
        int contador = 1;
        relTiempoLugar *temp = lugar->sublistasTiempos;
        do        
        {
            cout << "Tiempo número " << contador;
            cout << "Fecha: " << devolverFecha(temp->enlace->fecha) << endl;
            cout << "Precipitación: " << temp->enlace->precipitacion << endl;
            cout << "Temperatura máxima: " << temp->enlace->tempMaxima << endl;
            cout << "Temperatura mínima: " << temp->enlace->tempMinima << endl;
            cout << "Velocidad del viento: " << temp->enlace->velocidadViento << endl;
            cout << "Dirección del viento: " << temp->enlace->direccionViento << endl;
            cout << "Lluvia: " << temp->enlace->siLlovio << endl;
            cout << "Lista de lluvias: " << temp->enlace->tempMinima << endl;
            if (temp->enlace->sublistasLluvias == NULL)
            {
                cout << "No tiene sublistas de lluvia" << endl;
            }
            else
            {
                lluvia *tempLluvia = temp->enlace->sublistasLluvias;
                do
                {
                    cout << "\t LLuvia: " << tempLluvia->codigo << endl;
                } while (tempLluvia->sig != NULL);
                
            }
            contador = contador + 1;
        } while (temp->sig != NULL);
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
        cout << "\nEsta lista está vacía" << endl;
    }
    else
    {
        int contador = 1;
        relTiempoPersona *temp = personaElegida->sublistasTiempos;
        do        
        {
            cout << "Tiempo número " << contador;
            cout << "Fecha: " << devolverFecha(temp->enlace->fecha) << endl;
            cout << "Precipitación: " << temp->enlace->precipitacion << endl;
            cout << "Temperatura máxima: " << temp->enlace->tempMaxima << endl;
            cout << "Temperatura mínima: " << temp->enlace->tempMinima << endl;
            cout << "Velocidad del viento: " << temp->enlace->velocidadViento << endl;
            cout << "Dirección del viento: " << temp->enlace->direccionViento << endl;
            cout << "Lluvia: " << temp->enlace->siLlovio << endl;
            cout << "Lista de lluvias: " << temp->enlace->tempMinima << endl;
            if (temp->enlace->sublistasLluvias == NULL)
            {
                cout << "No tiene sublistas de lluvia" << endl;
            }
            else
            {
                lluvia *tempLluvia = temp->enlace->sublistasLluvias;
                do
                {
                    cout << "\t LLuvia: " << tempLluvia->codigo << endl;
                } while (tempLluvia->sig != NULL);
                
            }
            contador = contador + 1;
        } while (temp->sig != NULL);
    }
}

void imprimirListaTiempo(tiempo *listaTiempoParametro) {
    if (listaTiempoParametro == NULL) 
    {
        cout << "\nEsta lista está vacía" << endl;
    }
    else
    {
        int contador = 1;
        tiempo *temp = listaTiempoParametro;
        do        
        {
            cout << "Tiempo número " << contador;
            cout << "Fecha: " << devolverFecha(temp->fecha) << endl;
            cout << "Precipitación: " << temp->precipitacion << endl;
            cout << "Temperatura máxima: " << temp->tempMaxima << endl;
            cout << "Temperatura mínima: " << temp->tempMinima << endl;
            cout << "Velocidad del viento: " << temp->velocidadViento << endl;
            cout << "Dirección del viento: " << temp->direccionViento << endl;
            cout << "Lluvia: " << temp->siLlovio << endl;
            cout << "Lista de lluvias: " << temp->tempMinima << endl;
            if (temp->sublistasLluvias == NULL)
            {
                cout << "No tiene sublistas de lluvia" << endl;
            }
            else
            {
                lluvia *tempLluvia = temp->sublistasLluvias;
                do
                {
                    cout << "\t LLuvia: " << tempLluvia->codigo << endl;
                } while (tempLluvia->sig != NULL);
                
            }
            contador = contador + 1;
        } while (temp->sig != NULL);
    }
}

// Metodos de borrado en la listas

void borrarPersona(int cedula){
    personas*buscado = buscarPersona(cedula);
    if(buscado == NULL){
        cout<<"No se puede borrar";
        return;
    }else{
        if(buscado == listaPersonas){
            listaPersonas = listaPersonas->sig;
            if (listaPersonas != NULL){
                listaPersonas->ant = NULL;
            }    
        }else{//Borra medio o al final
            buscado->ant->sig = buscado->sig;
            if (buscado->sig != NULL)
            {
                buscado->sig->ant = buscado->ant;
            }
            
        }
    }
}

void borrarEfimeridad(tm* fecha){
    efimeridad*buscado = buscarEfemeridad(fecha);
    if(buscado == NULL){
        cout<<"No se puede borrar";
        return;
    }else{
        if(buscado == listaEfimeridades){
            listaEfimeridades = listaEfimeridades->sig;
            if (listaEfimeridades != NULL){
                listaEfimeridades->ant = NULL;
            }    
        }else{//Borra medio o al final
            buscado->ant->sig = buscado->sig;
            if (buscado->sig != NULL)
            {
                buscado->sig->ant = buscado->ant;
            }
            
        }
    }
}

void borrarLluvia(string codigo){
    lluvia* temp = listaLluvia;
    lluvia* prev = NULL;
    if (temp != NULL && temp->codigo == codigo)
    {
        listaLluvia = temp->sig; 
        return;
    }
    else{
    while (temp != NULL && temp->codigo != codigo){
        prev = temp;
        temp = temp->sig;
    }
    if (temp == NULL){
        return;
    }
    prev->sig = temp->sig;
    }
}

void borrarRegion(int id){
    region* temp = listaRegion;
    region* prev = NULL;
    if (temp != NULL && temp->id == id)
    {
        listaRegion = temp->sig; 
        return;
    }
    else{
    while (temp != NULL && temp->id != id){
        prev = temp;
        temp = temp->sig;
    }
    if (temp == NULL){
        return;
    }
    prev->sig = temp->sig;
    }
}

void borrarTiempo(tm* fecha){
    tiempo* temp = listaTiempo;
    tiempo* prev = NULL;
    if ((temp != NULL) && (temp->fecha->tm_year == fecha->tm_year) && (temp->fecha->tm_mon == fecha->tm_mon)&& (temp->fecha->tm_mday == fecha->tm_mday))
    {
        listaTiempo = temp->sig; 
        return;
    }
    else{
    while ((temp != NULL) && (temp->fecha->tm_year != fecha->tm_year) && (temp->fecha->tm_mon != fecha->tm_mon)&& (temp->fecha->tm_mday != fecha->tm_mday)){
        prev = temp;
        temp = temp->sig;
    }
    if (temp == NULL){
        return;
    }
    prev->sig = temp->sig;
    }
}

void borrarLugar(string nombre){
 
    if (listaLugar == NULL)
        return;
 
    //Si solo hay un dato la lista pasa a ser NULL
    if (listaLugar->nombre == nombre && listaLugar->sig == listaLugar) {
        listaLugar = NULL;
        return;
    }
    lugar *ultimo = listaLugar, *d;
    if (listaLugar->nombre == nombre) {
 
        while (ultimo->sig != listaLugar){
            ultimo = ultimo->sig;
        }

        ultimo->sig = listaLugar->sig;
        
        listaLugar= ultimo->sig;
        return;
    }
    while (ultimo->sig != listaLugar && ultimo->sig->nombre != nombre) {
        ultimo = ultimo->sig;
    }
 
    if (ultimo->sig->nombre == nombre) {
        d = ultimo->sig;
        ultimo->sig = d->sig;
    }
    else
        cout << "No se encontro el lugar";
}

//Metodos para modificaar en la lista


void modificarPersona(int cedula,int cedulaN, string nombreN,string lugarResidenciaN,string agnoResidenciaN){

    personas*aux = buscarPersona(cedula);
    if (aux != NULL)
    {
        aux->nombre = nombreN;
        aux->cedula = cedulaN;
        aux->lugarResidencia = lugarResidenciaN;
        aux->agnoResidencia = agnoResidenciaN;
        //Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }else{
        cout<<"No se encontro a la Persona";
    }

}

void modificarLluvia(string codigo,string codigoN, string nombreN, int rangoPromedioEn_mmN){

    lluvia*aux = buscarLluvia(codigo);
    if (aux != NULL)
    {
        aux->codigo = codigoN;
        aux->nombre = nombreN;
        aux->rangoPromedioEn_mm = rangoPromedioEn_mmN;
        //Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }else{
        cout<<"No se encontro la lluvia";
    }

}
void modificarEfimeridad(string nombreN, tm*fecha,tm*fechaN,tm*horaSalidaN,tm*horaOcultamientoN){

    efimeridad*aux = buscarEfemeridad(fecha);
    if (aux != NULL)
    {
        aux->nombre = nombreN;
        aux->fecha = fechaN;
        aux->horaSalida = horaSalidaN;
        aux->horaOcultamiento = horaOcultamientoN;

        //Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }else{
        cout<<"No se encontro la lluvia";
    }

}

void modificarRegion(int id,int idN, string nombreN, string ubicacionN){

    region*aux = buscarRegion(id);
    if (aux != NULL)
    {
        aux->id = idN;
        aux->nombre = nombreN;
        aux->ubicacion = ubicacionN;
        //Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }else{
        cout<<"No se encontro la region";
    }
}

void modificarLugar(string nombre,string nombreN, int poblacionN, double metrosCuadradosN){

    lugar*aux = buscarLugar(nombre);
    if (aux != NULL)
    {
        aux->nombre = nombreN;
        aux->poblacion = poblacionN;
        aux->metrosCuadrados = metrosCuadradosN;
        //Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }else{
        cout<<"No se encontro el lugar";
    }
}


void modificarTiempo(tm *fecha,tm *fechaN, int precipitacionN, int tempMaximaN, int tempMinimaN, int velocidadVientoN, int direccionVientoN, int humedadRelativaN, bool siLlovioN){

    tiempo*aux = buscarTiempo(fecha->tm_year,fecha->tm_mon,fecha->tm_mday);
    if (aux != NULL)
    {
        aux->fecha = fechaN;
        aux->precipitacion = precipitacionN;
        aux->tempMaxima = tempMaximaN;
        aux->tempMinima = tempMinimaN;
        aux->velocidadViento = velocidadVientoN;
        aux->direccionViento = direccionVientoN;
        aux->siLlovio = siLlovioN;

        //Aqui faltaria ver si le borramos las sublistas(Supongo que es opcional)
    }else{
        cout<<"No se encontro el tiempo";
    }

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

//Retorna la fecha apartir de un string
tm *obtenerFechadeString(string fecha){
    int agno = (fecha[0] -48)*1000 + (fecha[1] -48)*100 + (fecha[2] -48)*10 + fecha[3] -48;
    int mes =  (fecha[5] -48)*10 + fecha[6] -48 ;
    int dia = (fecha[8] -48)*10 + fecha[9] -48 ;

    return crearFecha(agno,mes,dia);

}
//Retorna la hora apartir de un string
tm *obtenerHoradeString(string hora){
    int h = hora[0] -48 + hora[1] -48 ;
    int m = hora[3] -48 + hora[4] -48 ;

    return crearHora(h,m);

}

/*  OTROS MÉTODOS   */
void cargarDatos()
{
    /**
     * Con 0 mm/h no hay nada de lluvia.                                    EXTREMO SECO
     * De 1 a 2 mm/h diremos lluvias débiles.                               SECO                    
     * De 2 a 15 mm/h será lluvia.                                          NORMAL
     * De 15 a 30 saltaremos a lluvias fuertes.                             LLUVIOSO
     * De 30 a 60 lluvias muy fuertes.                                      EXTREMO LLUVIOSO
     * Finalmente más de 60 mm/h se describirán como lluvias torrenciales.  EXTREMO LLUVIOSO
     */
    listaLluvia = insertarLluvia("COD#1", "NombreL#1", 1, listaLluvia);
    listaLluvia = insertarLluvia("COD#2", "NombreL#2", 2, listaLluvia);
    listaLluvia = insertarLluvia("COD#3", "NombreL#3", 3, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);
    listaLluvia = insertarLluvia("COD#4", "NombreL#4", 4, listaLluvia);

    listaRegion = insertarRegion(12, "Region#1", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(14, "Region#2", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(3, "Region#3", "Ubicaicacio1", listaRegion);
    listaRegion = insertarRegion(4, "Region#4", "Ubicaicacio1", listaRegion);

    listaLugar = insertarLugar("San Juan", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("San Carlos", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("Santa Clara", 100, 2.5, listaLugar);
    listaLugar = insertarLugar("San Jose", 100, 2.5, listaLugar);

    listaPersonas = insertarPersona("Alejandro Rodriguez", 208360735, "El Tanque", "2018");
    listaPersonas = insertarPersona("Juan Ca", 2081230735, "La Fortuna", "2013");
    listaPersonas = insertarPersona("Beto Beto", 1011230735, "San Rafael","2022");
    listaPersonas = insertarPersona("Roberto Jimenez", 3011230735, "Florencia","2021");
    listaPersonas = insertarPersona("Alondra", 4011230735, "Santa Clara","2024");
    listaPersonas = insertarPersona("Carlos Ruiz", 3011230735, "Florencia","2021");
    listaPersonas = insertarPersona("Bianca Ruiz", 1234, "Florencia","2022");


    listaEfimeridades = insertarEfimeridad("Efimeridad 1", crearFecha(2020, 3, 16), crearHora(7, 25), crearHora(17, 9));
    listaEfimeridades = insertarEfimeridad("Efimeridad 2", crearFecha(2020, 2, 12), crearHora(5, 37), crearHora(17, 20));
    listaEfimeridades = insertarEfimeridad("Efimeridad 3", crearFecha(2020, 6, 11), crearHora(6, 12), crearHora(20, 12));

    listaTiempo = insertarTiempo(crearFecha(2020, 9, 28), 4, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 9, 30), 4, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 10, 2), 4, 30, 24, 14, -45, -3, true);
    listaTiempo = insertarTiempo(crearFecha(2020, 10, 4), 4, 30, 24, 14, -45, -3, true);
}

void impOcultamientoSalidaSol()
{
    /*
    Determinar e imprimir el día(fecha completa)con la salida de “sol”más temprano de un año Y,
    y el ocultamientomástardío del “sol”en el año Y.
    */
    tm *horaTempranoOcultamiento = new tm;
    tm *horaTardioSalida = new tm;

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
            // Comparando las horas para determinar el ocultamiento más temprano
            if (temp->horaOcultamiento->tm_hour < horaTempranoOcultamiento->tm_hour)
            {
                horaTempranoOcultamiento = temp->horaOcultamiento;
            }
            else if ((temp->horaOcultamiento->tm_hour == horaTempranoOcultamiento->tm_hour) && (temp->horaOcultamiento->tm_min < horaTempranoOcultamiento->tm_min))
            {
                horaTempranoOcultamiento = temp->horaOcultamiento;
            }
            // Comparando las horas para determinar la salida del sol más tranquila
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
    cout << "\nLa hora de ocultamiento del sol más temprano es: " << devolverHora(horaTempranoOcultamiento);
    cout << "\nLa hora de salida del sol más tardía es: " << devolverHora(horaTardioSalida) << endl;
}

int obtenerDiferencia(tm *horaTemprano, tm *horaTarde)
{
    /*
    Obtiene la diferencia en minutos de las horas que se envían por parámetro
    Este método se complementa con el segundo método de las consultas

    Ejemplo/guía para sacar la diferencia:
        Hora temprana:  1:53
        Hora Tardía:    4:23
        
        4-1 = 3*60 = 180 minutos
        180-53 = 127 (la primera hora no estuvo completa)
        127+23 = 150 (los minutos que sobraron)
    */
   int diferencia = horaTarde->tm_hour - horaTemprano->tm_hour; //Saco la diferencia de horas
   diferencia = diferencia * 60; //Convierto la diferencia a minutos
   diferencia = diferencia  - horaTemprano->tm_min;
   diferencia = diferencia  + horaTarde->tm_min;
   return diferencia;
}

void diferenciaSalidaSol()
{
    /*
    Determinar e imprimir las fechas que generan la mayor diferencia en minutos de la salidadel sol,
    indicar las dos fechas que producen la mayor diferencia, para un año Y.
    */
    int anio;
    tm *horaTemprano;
    tm *horaTarde;
    cout << "\nDigite el año en el que desea buscar las fechas: ";
    cin >> anio;
    efimeridad *temp = listaEfimeridades;
    horaTarde = temp->horaSalida;
    horaTemprano = temp->horaSalida;
    while (temp->sig != NULL)
    {
        if (temp->fecha->tm_year == anio)
        {
            //Compara con las horas tempranas
            if (temp->horaSalida->tm_hour < horaTemprano->tm_hour)
            {
                horaTemprano = temp->horaSalida;
            } else if ((temp->horaSalida->tm_hour == horaTemprano->tm_hour) && (temp->horaSalida->tm_min < horaTemprano->tm_min))
            {
                horaTemprano = temp->horaSalida;
            }
            //Compara con las horas tardías
            if (temp->horaSalida->tm_hour > horaTarde->tm_hour)
            {
                horaTarde = temp->horaSalida;
            } else if ((temp->horaSalida->tm_hour == horaTarde->tm_hour) && (temp->horaSalida->tm_min > horaTarde->tm_min))
            {
                horaTarde = temp->horaSalida;
            }
            temp = temp->sig;
        }
    }
    int diferencia = obtenerDiferencia(horaTemprano, horaTarde);
    cout << "\nLa diferencia de la salida del sol en  más temprana y más tarde en el año " << anio;
    cout << " es de: " << diferencia << " minutos";
}

void imprimirExtremos() 
{
    /*
    Determinar e imprimir el mes que más externos de lluvia tiene de un año X para un lugar Z.
    Debe imprimir ambos:extremo seco y extremo lluvioso. En caso de empate imprimir todos los
    meses que tiene el empate máximo.
    */
   string lugarParaBuscar;
    int anioParaBuscar;
    cout << "\nDigite el lugar del que desea imprimir los extremos: ";
    cin >> lugarParaBuscar;
    lugar *lugarEscogido = buscarLugar(lugarParaBuscar);
    if (lugarEscogido == NULL)
    {
        cout << "\nLo sentimos" << endl;
    }
    else if (lugarEscogido != NULL)
    {
        relTiempoLugar *tempTiempo = lugarEscogido->sublistasTiempos;
        tiempo *extLluvioso = tempTiempo->enlace;
        tiempo *extSeco = tempTiempo->enlace;        
    }
}

void personaMayorRegistrosTiempo() 
{
    /*Determinar e imprimir la persona que más registros del tiempo tiene.*/
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
            } while (tempRegistro->sig != NULL);
            if (contadorRegistros > registrosAnterior)
            {
                masRegistros = tempPersona;
                registrosAnterior = contadorRegistros;
                cout << "REGISTROS ANTERIOR " << registrosAnterior <<endl;
                cout << "CONTADOR REGISTROS " << contadorRegistros <<endl;
            }
            contadorRegistros = 0;
        }
        tempPersona = tempPersona->sig;
    } while (tempPersona->sig != NULL);

    cout << "La persona con más registros de tiempo es " << masRegistros->nombre;
}


void relacionarTiempoLugar(tm*fecha,string nombre){
    lugar*l = buscarLugar(nombre);
    tiempo*t = buscarTiempo(fecha->tm_year,fecha->tm_mon,fecha->tm_mday);
    if (l == NULL)
    {
        cout<<"Lugar no valido";
        return;
    }
    if (t == NULL)
    {
        cout<<"Tiempo no valido";
        return;
    }

    relTiempoLugar*nuevo = new relTiempoLugar;
    nuevo->enlace = t;
    nuevo->sig = l->sublistasTiempos;
    l->sublistasTiempos = nuevo;
    cout<<"====================";
    cout<<"Relacion Completada";
    cout<<"====================";
}

void relacionarTiempoPersona(tm*fecha,int cedula){
    personas*p = buscarPersona(cedula);
    tiempo*t = buscarTiempo(fecha->tm_year,fecha->tm_mon,fecha->tm_mday);
    if (p == NULL)
    {
        cout<<"Personas no valida";
        return;
    }
    if (t == NULL)
    {
        cout<<"Tiempo no valido";
        return;
    }

    relTiempoPersona*nuevo = new relTiempoPersona;
    nuevo->enlace = t;
    nuevo->sig = p->sublistasTiempos;
    p->sublistasTiempos = nuevo;
    cout<<"====================";
    cout<<"Relacion Completada";
    cout<<"====================";

}

//Menu de Borrado
void menuBorrado(){
    cout << "\n--------------------BIENVENIDO AL MENU DE BORRADO------------------------" << endl;
    int opcion;
    cout << "\n1. Borrar Personas";
    cout << "\n2. Borrar Lluvia";
    cout << "\n3. Borrar Region";
    cout << "\n4. Borrar tiempo";
    cout << "\n5. Borrar lugar";
    cout << "\n6. Borrar efimeridad"<<endl;
    
    cout << "\nDigite su opción a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1){
        int cedula;
        cout <<"==== Borrando Persona ==="<<endl;
        cout << "\nCedula: "; cin >> cedula; cout << endl;
        borrarPersona(cedula);
        cout<<"=== Se ha borrado la persona ===";

    }else if (opcion == 2){
        string codigo;
        cout <<"==== Borrando Lluvia ==="<<endl;
        cout << "\nCodigo: "; cin >> codigo; cout << endl;
        borrarLluvia(codigo);
        cout<<"=== Se ha borrado la lluvia ===";
        
    }else if (opcion == 3){
        int id;
        cout <<"==== Borrando Region ==="<<endl;
        cout << "\n ID: "; cin >> id; cout << endl;
        borrarRegion(id);
        cout<<"=== Se ha borrado la region ===";
        
    }else if (opcion == 4){
        string fecha;
        cout <<"==== Borrando Tiempo ==="<<endl;
        cout << "\n Fecha(YYYY/MM/DD): "; cin >> fecha; cout << endl;
        borrarTiempo(obtenerFechadeString(fecha));
        cout<<"=== Se ha borrado el Tiempo ===";
        
    }else if (opcion == 5){
        string nombre;
        cout <<"==== Borrando Lugar ==="<<endl;
        cout << "\nNombre: "; cin >> nombre; cout << endl;
        borrarLugar(nombre);
        cout<<"=== Se ha borrado el lugar ===";
        
    }else if (opcion == 6){
        string fechaE;
        cout <<"==== Borrando Efimeridad ==="<<endl;
        cout << "\n Fecha(YYYY/MM/DD): "; cin >> fechaE; cout << endl;
        borrarTiempo(obtenerFechadeString(fechaE));
        cout<<"=== Se ha borrado la Efimeridad ===";
        
    }

}

void menuModificar(){
    cout << "\n--------------------BIENVENIDO AL MENU DE MODIFICAR------------------------" << endl;
    int opcion;
    cout << "\n1. Modificar Persona";
    cout << "\n2. Modificar luvia";
    cout << "\n3. Modificar Region";
    cout << "\n4. Modifcar Lugar";
    cout << "\n5. Modificar Efimeridad";
    cout << "\n6. Modificar Tiempo" << endl;

    cout << "\nDigite su opción a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        string nombre, lugarResidencia,agnoResidencia;
        int cedula,cedulaN;

        cout <<"==== Modificando Persona ==="<<endl;
        cout << "\nCedula de la persona a modificar: "; cin >> cedula; cout << endl;
        cout << "\nNuevo Nombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nNueva Cedula: "; cin >> cedulaN; cout << endl;
        cout << "\nNuevo Lugar Residencia: "; getline(cin >> ws,lugarResidencia); cout << endl;
        cout << "\nNuevo Año Residencia: "; cin >> agnoResidencia; cout << endl;

        if (buscarPersona(cedula) != NULL){
            modificarPersona(cedula,cedulaN,nombre,lugarResidencia,agnoResidencia);
            cout<<"Personas Modificada Correctamente";
        }else{
            cout<<"No se puede modificar a la persona, al parecer no existe";
        }
    }else if (opcion == 2)
    {

        string codigo, codigoN, nombre;
        int rangoPromedioEn_MM;
        cout <<"==== Modificando Lluvia ==="<<endl;
        cout << "\nCodigo de la lluvia a modificar: "; cin >> codigo; cout << endl;
        cout << "\nNuevo Codigo: "; cin >> codigoN; cout << endl;
        cout << "\nNuevo Nombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nNuevo Rango en Promedio(en MM): "; cin >> rangoPromedioEn_MM; cout << endl;

        if (buscarLluvia(codigo) != NULL){
            modificarLluvia(codigo,codigoN,nombre,rangoPromedioEn_MM);
            cout<<"Lluvia Modificada Correctamente";
        }else{
            cout<<"No se pudo modificar la lluvia";
        }
        
    }else if (opcion == 3)
    {
        string nombre, ubicacion;
        int id,idN;
        cout <<"==== Modificando Region ==="<<endl;
        cout << "\nID de la region a modificar: "; cin >> id; cout << endl;
        cout << "\nNuevo ID: "; cin >> idN; cout << endl;
        cout << "\nNuevo Nombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nNueva Ubicacion: "; getline(cin >> ws,ubicacion); cout << endl;

        if (buscarRegion(id) != NULL){
            modificarRegion(id,idN,nombre,ubicacion);
            cout<<"Region Modificada Correctamente";
        }else{
            cout<<"No se pudo modificar la region";
        }
        
        
    }else if(opcion == 4){
        string nombre,nombreN;
        int poblacion;
        double metrosCuadrados;
        cout <<"==== Modificando Lugar ==="<<endl;
        cout << "\nNombre del lugar a modificar: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nNuevo Nombre: "; getline(cin >> ws,nombreN); cout << endl;
        cout << "\nNueva Poblacion: "; cin >> poblacion; cout << endl;
        cout << "\nNuevo Metros Cuadrados: "; cin >> metrosCuadrados; cout << endl;

        if (buscarLugar(nombre) != NULL){
            modificarLugar(nombre,nombreN,poblacion,metrosCuadrados);
            cout<<"Lugar Modificado Correctamente";
        }else{
            cout<<"No se pudo modificar el lugar";
        }
    }else if(opcion == 5){
        string nombre,fecha,fechaN,horaSalida,horaOcultamiento;
        cout <<"==== Modificando Efimeridad ==="<<endl;
        cout << "\nFecha de efimeridad a modificar: "; cin >> fecha; cout << endl;
        cout << "\nNuevo Nombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nNueva Fecha(YYYY/MM/DD): "; cin >> fechaN; cout << endl;
        cout << "\nNueva Hora Salida(HH:MM): "; cin >> horaSalida; cout << endl;
        cout << "\nNueva Hora Ocultamieto(HH:MM): "; cin >> horaOcultamiento; cout << endl;
        tm* fechaB = obtenerFechadeString(fecha);
        tm* fechaNN = obtenerFechadeString(fechaN);
        tm* horaS = obtenerHoradeString(horaSalida);
        tm* horaO = obtenerHoradeString(horaOcultamiento); 

        if (buscarEfemeridad(fechaB) != NULL){
            modificarEfimeridad(nombre,fechaB,fechaNN,horaS,horaO);
            cout<<"Efimeridad Modificada Correctamente";
        }else{
            cout<<"No se pudo modificar la Efimeridad";
        }

    }else if(opcion == 6){
        string fecha,fechaN;
        bool siLlovio = false;
        int precipitacion,tempMaxima,tempMinima,velocidadViento,direccionViento,humedadRelativa;
        string lluvia;
        cout <<"==== Insertando Tiempo ==="<<endl;
        cout << "\nFecha del tiempo a modificar(YYYY/MM/DD): "; cin >> fecha; cout << endl;
        cout << "\nNueva Fecha(YYYY/MM/DD): "; cin >> fechaN; cout << endl;
        cout << "\nNueva Precipitacion: "; cin >> precipitacion; cout << endl;
        cout << "\nNueva Temperatura Maxima: "; cin >> tempMaxima; cout << endl;
        cout << "\nNueva Temperatura Minima: "; cin >> tempMinima; cout << endl;
        cout << "\nNueva Velocidad del viento: "; cin >> velocidadViento; cout << endl;
        cout << "\nNueva Direccion del viento: "; cin >> direccionViento; cout << endl;
        cout << "\nNueva Humedad del viento: "; cin >> humedadRelativa; cout << endl;
        cout << "\nNuevo Llovio(s/n): "; cin >> lluvia;cout<< endl;
        if(siLlovio == 's'){
            siLlovio = true;
        }
        tm*fB = obtenerFechadeString(fecha);
        tm*fN = obtenerFechadeString(fecha);
        int agno = fB->tm_year;
        int mes = fB->tm_mon;
        int dia = fB->tm_mday;

        if (buscarTiempo(agno,mes,dia) != NULL){
            modificarTiempo(fB,fN,precipitacion,tempMaxima,tempMinima,velocidadViento,direccionViento,humedadRelativa,siLlovio);
            cout<<"Tiempo Modificado Correctamente";
        }else{
            cout<<"No se pudo modificar el tiempo";
        }
    }
}





void menuInserciones(personas* personaLogeada)
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
    cout << "\n8. Insertar en sublista tiempo (Personas)" << endl;



    cout << "\nDigite su opción a ejecutar: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        string nombre, lugarResidencia,agnoResidencia;
        int cedula;

        cout <<"==== Insertando Persona ==="<<endl;
        cout << "\nNombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nCedula: "; cin >> cedula; cout << endl;
        cout << "\nLugar Residencia: "; getline(cin >> ws,lugarResidencia); cout << endl;
        cout << "\nAño Residencia: "; cin >> agnoResidencia; cout << endl;

        if (buscarPersona(cedula) == NULL){
            listaPersonas = insertarPersona(nombre,cedula,lugarResidencia,agnoResidencia);
            cout<<"Personas Insertada Correctamente";
        }else{
            cout<<"No se pudo inserta a la persona, al parecer YA EXISTE";
        }
    }
    else if (opcion == 2)
    {

        string codigo, nombre;
        int rangoPromedioEn_MM;
        cout <<"==== Insertando Lluvia ==="<<endl;
        cout << "\nCodigo: "; cin >> codigo; cout << endl;
        cout << "\nNombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nRango en Promedio(en MM): "; cin >> rangoPromedioEn_MM; cout << endl;

        if (buscarLluvia(codigo) == NULL){
            listaLluvia= insertarLluvia(codigo,nombre,rangoPromedioEn_MM,listaLluvia);
            cout<<"Lluvia Insertada Correctamente";
        }else{
            cout<<"No se pudo inserta la lluvia, al parecer YA EXISTE";
        }
        
    }
    else if (opcion == 3)
    {
        string nombre, ubicacion;
        int id;
        cout <<"==== Insertando Region ==="<<endl;
        cout << "\nID: "; cin >> id; cout << endl;
        cout << "\nNombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nUbicacion: "; getline(cin >> ws,ubicacion); cout << endl;

        if (buscarRegion(id) == NULL){
            listaRegion = insertarRegion(id,nombre,ubicacion,listaRegion);
            cout<<"Region Insertada Correctamente";
        }else{
            cout<<"No se pudo inserta la region, al parecer YA EXISTE";
        }
        
        
    }else if(opcion == 4){
        string nombre;
        int poblacion;
        double metrosCuadrados;
        cout <<"==== Insertando Lugar ==="<<endl;
        cout << "\nNombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nPoblacion: "; cin >> poblacion; cout << endl;
        cout << "\nMetros Cuadrados: "; cin >> metrosCuadrados; cout << endl;

        if (buscarLugar(nombre) == NULL){
            listaLugar = insertarLugar(nombre,poblacion,metrosCuadrados,listaLugar);
            cout<<"Lugar Insertado Correctamente";
        }else{
            cout<<"No se pudo inserta el lugar, al parecer YA EXISTE";
        }

    }else if(opcion == 5){
        string nombre,fecha,horaSalida,horaOcultamiento;
    

        cout <<"==== Insertando Efimeridad ==="<<endl;
        cout << "\nNombre: "; getline(cin >> ws,nombre); cout << endl;
        cout << "\nFecha(YYYY/MM/DD): "; cin >> fecha; cout << endl;
        cout << "\nHora Salida(HH:MM): "; cin >> horaSalida; cout << endl;
        cout << "\nHora Ocultamieto(HH:MM): "; cin >> horaOcultamiento; cout << endl;
        tm* f = obtenerFechadeString(fecha);
        tm* horaS = obtenerHoradeString(horaSalida);
        tm* horaO = obtenerHoradeString(horaOcultamiento); 

        if (buscarEfemeridad(f) == NULL){
            listaEfimeridades = insertarEfimeridad(nombre,f,horaS,horaO);
            cout<<"Efimeridad Insertada Correctamente";
        }else{
            cout<<"No se pudo inserta la Efimeridad, al parecer YA EXISTE";
        }

    }else if(opcion == 6){
        string fecha;
        bool siLlovio = false;
        int precipitacion,tempMaxima,tempMinima,velocidadViento,direccionViento,humedadRelativa;
        string lluvia;
        cout <<"==== Insertando Tiempo ==="<<endl;
        cout << "\nFecha(YYYY/MM/DD): "; cin >> fecha; cout << endl;
        cout << "\nPrecipitacion: "; cin >> precipitacion; cout << endl;
        cout << "\nTemperatura Maxima: "; cin >> tempMaxima; cout << endl;
        cout << "\nTemperatura Minima: "; cin >> tempMinima; cout << endl;
        cout << "\nVelocidad del viento: "; cin >> velocidadViento; cout << endl;
        cout << "\nDireccion del viento: "; cin >> direccionViento; cout << endl;
        cout << "\nHumedad del viento: "; cin >> humedadRelativa; cout << endl;
        cout << "\nLlovio(s/n): "; cin >> lluvia;cout<< endl;
        if(siLlovio == 's'){
            siLlovio = true;
        }

        tm*f = obtenerFechadeString(fecha);
        int agno = f->tm_year;
        int mes = f->tm_mon;
        int dia = f->tm_mday;

        if (buscarTiempo(agno,mes,dia) == NULL){
            listaTiempo = insertarTiempo(f,precipitacion,tempMaxima,tempMinima,velocidadViento,direccionViento,humedadRelativa,siLlovio);
            cout<<"Tiempo insertado Correctamente";
        }else{
            cout<<"No se pudo inserta el tiempo, al parecer YA EXISTE";
        }

    }else if(opcion == 7){
        string nombreLugar,fecha;

        cout <<"==== Insertando en Sublista de Tiempo(Lugar) ==="<<endl;
        cout << "\nFecha del tiempo(YYYY/MM/DD):"; cin >> fecha; cout << endl;
        cout << "\nNombre del lugar: "; getline(cin >> ws,nombreLugar); cout << endl;
        
    
        tm* f = obtenerFechadeString(fecha);

        relacionarTiempoLugar(f,nombreLugar);

    }
    else if(opcion ==8){
        string fecha;
        int cedula;

        cout <<"==== Insertando en Sublista de Tiempo(Persona) ==="<<endl;
        cout << "\nFecha del tiempo(YYYY/MM/DD): "; cin >> fecha; cout << endl;
    
        tm* f = obtenerFechadeString(fecha);

        relacionarTiempoPersona(f,personaLogeada->cedula);

    }
    else
    {
        cout << "La opción digitada es inválida";
        //main();
    }
}

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
    cout << "\n8. Imprimir sublista tiempo (Personas)" << endl;



    cout << "\nDigite su opción a ejecutar: ";
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
    else if(opcion == 4)
    {    
        imprimirLugar(listaLugar);
    }
    else if(opcion == 5)
    {
        imprimirEfimeridades(listaEfimeridades);
    }
    else if(opcion == 6)
    {
        imprimirListaTiempo(listaTiempo);
    }
    else if(opcion == 7)
    {
        string nombre;
        cout << "\n\nEscriba el nombre del lugar: ";
        cin >> nombre;
        imprimirTiempoPorLugar(nombre);
        
    }
    else if(opcion ==8)
    {
        int cedula;
        cout << "\n\nEscriba la cédula de la persona: ";
        cin >> cedula;
        imprimirTimepoPorPersona(cedula);
    }
    else
    {
        cout << "La opción digitada es inválida";
        //main();
    }
}

void menuConsultas()
{
    cout << "\n--------------------BIENVENIDO AL MENU DE CONSULTAS------------------------" << endl;
    int opcion;
    cout << "\n1. Imprimir el día en el sol sale más temprano y el día en el que el sol se oculta más temprano.";
    cout << "\n2. Imprimir las horas con mayor diferencia de salida del sol en un año.";
    cout << "\n3. Imprimir los extremos (seco/lluvioso) de un lugar en un determinado año.";
    cout << "\n4. Imprimir la persona que ha hecho mayor caantidad de registros de tiempo." << endl;

    cout << "\nDigite su opción a ejecutar: ";
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
        cout << "La opción digitada es inválida";
        //main();
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
        cout << "\n------------ESCRIBA SU NÚMERO DE CÉDULA PARA INGRESAR -------------" << endl;
        int cedula;
        cout << "\nCédula: "; cin >> cedula; cout << endl;
        loginPersona = buscarPersona(cedula);
        if (loginPersona == NULL)
        {
            cout << "\nLo sentimos, intente de nuevo" << endl;
        }
        else
        {
            while (true){
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
                cout << "\nDigite su opción: ";
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
                
                else if (opcion == 0)
                    break;
            }                       

            
        }
    }


   
    return 0;
}