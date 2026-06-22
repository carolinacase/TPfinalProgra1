#include "alquileres.h"
#include <time.h>
#include "pila.h"

void menuAlquileres(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[])
{
    int opcion;
    int cantidad;

    do
    {
        printf("===================================\n");
        printf("       GESTION DE ALQUILERES       \n");
        printf("===================================\n");
        printf("1. Alta     - Registrar un alquiler\n");
        printf("2. Baja     - Cancelar/Finalizar alquiler\n");
        printf("3. Modificar- Agregar dias al alquiler\n");
        printf("4. Consulta - Buscar alquiler por patente\n");
        printf("5. Listar   - Ordenar alquileres\n");
        printf("6. Mostrar  - Mostrar alquileres\n");
        printf("0. Volver al menu principal\n");
        printf("===================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            altaAlquiler(archivoAlquileres, archivoVehiculos, archivoClientes);
            break;
        case 2:
            bajaAlquiler(archivoAlquileres);
            break;
        case 3:
            modificarAlquiler(archivoAlquileres);
            break;
        case 4:
            buscarYMostrarAlquiler(archivoAlquileres);
            break;
        case 5:
        {
            int opcionOrden;
            stAlquiler *arregloAlq = NULL;

            printf("\n--- ORDENAR ALQUILERES ---\n");
            printf("1. Ordenar alfabeticamente por patente (seleccion)\n");
            printf("2. Ordenar por costo total (insercion)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcionOrden);

            cantidad = PasarAlquileresAunArreglo(archivoAlquileres, &arregloAlq);

            if(cantidad > 0)
            {
                if(opcionOrden == 1)
                {
                    OrdenarAlquileresPorSeleccion(arregloAlq, cantidad);
                }
                else if(opcionOrden == 2)
                {
                    ordenarAlquileresPorInsercion(arregloAlq, cantidad);
                }

                mostrarArrDeAlquileres(arregloAlq, cantidad);

                free(arregloAlq);
            }
            else
                printf("No hay alquileres registrados.\n");
        }
        break;
        case 6:
        {
            int opcionMostrar;
            printf("\n--- MOSTRAR ALQUILERES ---\n");
            printf("1. Alquileres activos\n");
            printf("2. Alquileres finalizados\n");
            printf("3. Alquileres recientes\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcionMostrar);

            if(opcionMostrar == 1)
                mostrarAlquileres(archivoAlquileres);
            else if(opcionMostrar == 2)
                MostrarAlquileresFinalizados(archivoAlquileres);
            else if(opcionMostrar == 3)
                mostrarAlquileresRecientesEnPila(archivoAlquileres);
            else
                printf("Opcion invalida.\n");
        }
        break;
        case 0:
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(opcion != 0);

}

// ALTA: GUARDA UN ALQUILER NUEVO EN EL ARCHIVO
void altaAlquiler(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[])
{
    stAlquiler aux;
    int dias = 0;

    printf("\n--- REGISTRAR NUEVO ALQUILER ---\n");
    printf("(Ingrese '0' en cualquier momento para cancelar la operacion)\n\n");

    if(solicitarYValidarCliente(archivoClientes, aux.dniCliente) == 0)
    {
        printf("\nOperacion cancelada, volviendo al menu\n");
    }
    else if(solicitarYValidarVehiculo(archivoVehiculos, aux.patente) == 0)
    {
        printf("\nOperacion cancelada, volviendo al menu\n");
    }
    else
    {
        aux.id = obtenerNuevoIdAlquiler(archivoAlquileres);

        cargarAlquiler(&aux, &dias);

        aux.fechaFin = calcularFechaFin(aux.fechaInicio, dias);

        float precioPorDia = obtenerPrecioPorDia(archivoVehiculos, aux.patente);
        aux.costoTotal = (float)dias * precioPorDia;

        FILE *archi = NULL;
        archi = fopen(archivoAlquileres, "ab");

        if(archi != NULL)
        {
            fwrite(&aux, sizeof(stAlquiler), 1, archi);
            fclose(archi);

            cambiarDisponibilidadVehiculo(archivoVehiculos, aux.patente, 1);

            printf("\n==============================================\n");
            printf(" ALQUILER REGISTRADO CON EXITO!\n");
            printf(" Fin de alquiler: %d/%d/%d\n", aux.fechaFin.dia, aux.fechaFin.mes, aux.fechaFin.anio);
            printf(" ID Alquiler: %d\n", aux.id);
            printf(" Costo Total a pagar: $%.2f\n", aux.costoTotal);
            printf("==============================================\n");
        }
    }
}

// GENERA UN ID QUE SE INCREMENTA BUSCANDO EL ULTIMO EN EL ARCHIVO
int obtenerNuevoIdAlquiler(char nombreArchivo[])
{
    int maxId = 0;
    stAlquiler aux;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0)
        {
            if(aux.id > maxId)
            {
                maxId = aux.id;
            }
        }
        fclose(archi);
    }

    return maxId + 1;
}

// CARGA LOS DATOS DE UN ALQUILER POR TECLADO
void cargarAlquiler(stAlquiler *aux, int *diasAlquilados)
{
    time_t actual = time(NULL);
    struct tm *fecha = localtime(&actual);

    do
    {
        printf("Ingrese el dia de inicio (1-30): ");
        scanf("%d", &aux->fechaInicio.dia);

        if(aux->fechaInicio.dia < 1 || aux->fechaInicio.dia > 30)
        {
            printf("Dia invalido. Ingrese nuevamente.\n");
        }
    }
    while(aux->fechaInicio.dia < 1 || aux->fechaInicio.dia > 30);

    aux->fechaInicio.mes = fecha->tm_mon + 1;
    aux->fechaInicio.anio = fecha->tm_year + 1900;

    printf("Fecha de inicio registrada: %02d/%02d/%d\n", aux->fechaInicio.dia, aux->fechaInicio.mes, aux->fechaInicio.anio);

    printf("Por cuantos dias se alquila el vehiculo?: ");
    scanf("%d", diasAlquilados);

    aux->eliminado = 0;
}

//RETORNA EL PRECIO DEL VEHICULO PEDIDO
float obtenerPrecioPorDia(char nombreArchivo[], char patenteBuscada[])
{
    stVehiculo aux;

    int encontrado = 0;

    float precio;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {

        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(strcmp(aux.patente, patenteBuscada) == 0 && aux.eliminado == 0)
            {
                encontrado = 1;

                precio = aux.precioPorDia;
            }
        }
        fclose(archi);

        if(encontrado == 0)
        {
            printf("\nNo se encontro ningun vehiculo activo con la patente: %s\n", patenteBuscada);
        }
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }

    return precio;
}

//VALIDAR UN DNI EXISTENTE
int solicitarYValidarCliente(char archivoClientes[], char destinoDni[])
{
    int existeCliente = 0;

    do
    {
        printf("Ingrese el DNI del cliente: ");
        fflush(stdin);
        fgets(destinoDni, DIM_DNI, stdin);
        limpiarSaltoLinea(destinoDni);

        if(strcmp(destinoDni, "0") == 0)
        {
            return 0;
        }
        else
        {
            existeCliente = ValidarClienteExistente(archivoClientes, destinoDni);

            if(existeCliente == 0)
            {
                printf("ERROR: El DNI '%s' no esta registrado. Intente nuevamente.\n\n", destinoDni);
            }
        }
    }
    while(existeCliente == 0);

    return 1;
}

//VALIDAR UNA PATENTE EXISTENTE
int solicitarYValidarVehiculo(char archivoVehiculos[], char destinoPatente[])
{
    int existeVehiculo = 0;
    char tipoElegido[DIM_STRINGS];
    char tiposVehiculos[3][DIM_STRINGS] = {"Sedan","SUV","Pick-Up"};

    int tipoOpcion = seleccionarTipoVehiculo();

    if(tipoOpcion == 0)
    {
        return 0;
    }

    strcpy(tipoElegido, tiposVehiculos[tipoOpcion - 1]);

    printf("\n=======================================================");
    printf("\n  VEHICULOS DISPONIBLES DE TIPO: %s", tipoElegido);
    printf("\n=======================================================\n");

    mostrarPatentesDisponiblesPorTipo(archivoVehiculos, tipoElegido);

    printf("=======================================================\n\n");

    do
    {
        printf("Ingrese la patente del vehiculo: ");
        fflush(stdin);
        fgets(destinoPatente, DIM_PATENTE, stdin);
        limpiarSaltoLinea(destinoPatente);

        strupr(destinoPatente);

        if(strcmp(destinoPatente, "0") == 0)
        {
            return 0;
        }
        else
        {
            existeVehiculo = verificarVehiculoPorPatenteYTipo(archivoVehiculos, destinoPatente, tipoElegido);

            if(existeVehiculo == 0)
            {
                printf("ERROR: La patente '%s' no pertenece a un %s disponible. Pruebe otra de la lista.\n\n", destinoPatente, tipoElegido);
            }
            else if(existeVehiculo == -1)
            {
                printf("ERROR: El %s con patente '%s' ya fue alquilado. Elija otro de la lista.\n\n", tipoElegido, destinoPatente);
            }
        }
    }
    while(existeVehiculo <= 0);

    return 1;
}

int seleccionarTipoVehiculo()
{
    int opcion;
    char tiposVehiculos[3][DIM_STRINGS] = {"Sedan","SUV","Pick-Up"};

    do
    {
        printf("\n====== SELECCIONE TIPO DE VEHICULO ======\n");
        printf("1. %s\n", tiposVehiculos[0]);
        printf("2. %s\n", tiposVehiculos[1]);
        printf("3. %s\n", tiposVehiculos[2]);
        printf("0. Cancelar operacion\n");

        printf("Seleccione una opcion (0-3): ");
        scanf("%d", &opcion);

        if(opcion < 0 || opcion > 3)
        {
            printf("Opcion incorrecta. Intente nuevamente.\n");
        }

    }
    while(opcion < 0 || opcion > 3);

    return opcion;
}

//CALCULAR FECHA EN QUE TERMINA UN ALQUILER
stFecha calcularFechaFin(stFecha inicio, int diasAlquilados)
{
    stFecha fin = inicio;

    fin.dia = fin.dia + diasAlquilados;

    while (fin.dia > 30)
    {
        fin.dia = fin.dia - 30;
        fin.mes = fin.mes + 1;
    }

    while (fin.mes > 12)
    {
        fin.mes = fin.mes - 12;
        fin.anio = fin.anio + 1;
    }

    return fin;
}

//ELIMINAR ALQUILER
void bajaAlquiler(char nombreArchivo[])
{
    int encontrado = 0;

    char dniBuscado[DIM_DNI];

    stAlquiler aux;

    //HACER FUNCION PARA MOSTRAR ALQUILERES: mostrarAlquileres(nombreArchivo);

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        printf("Ingrese el DNI del cliente: ");
        fflush(stdin);
        fgets(dniBuscado, DIM_DNI, stdin);
        limpiarSaltoLinea(dniBuscado);

        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0 && encontrado == 0)
        {
            if(strcmp(aux.dniCliente, dniBuscado) == 0  && aux.eliminado == 0)
            {
                encontrado = 1;

                aux.eliminado = 1; // marca como eliminado

                fseek(archi, sizeof(stAlquiler) * (-1), SEEK_CUR);
                fwrite(&aux, sizeof(stAlquiler), 1, archi);
                fseek(archi, 0, SEEK_CUR);

                printf("Alquiler del cliente %s dado de baja correctamente.\n", dniBuscado);
            }
        }
        fclose(archi);

        if(encontrado == 0)
            printf("No se encontro ningun alquiler activo con DNI %s.\n", dniBuscado);
    }
}

//MOSTRAR ALQUILERES
void mostrarAlquileres(char nombreArchivo[])
{
    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        mostrarAlquileresRecursivamente(archi);

        fclose(archi);
    }
    else
    {
        printf("\nERROR: No hay vehiculos cargados\n");
    }
}
//MOSTRAR TODOS LOS ALQUILERES (CON RECURSIVA)
void mostrarAlquileresRecursivamente(FILE *archi)
{
    stAlquiler aux;

    if(fread(&aux, sizeof(stAlquiler), 1, archi) > 0)
    {
        if(aux.eliminado == 0)
        {
            printf("\n--- Alquiler ---\n");
            printf("ID:                  %d\n", aux.id);
            printf("DNI:                 %s\n", aux.dniCliente);
            printf("Patente:             %s\n", aux.patente);
            printf("Inicio de alquiler:  %d/%d/%d\n", aux.fechaInicio.dia, aux.fechaInicio.mes, aux.fechaInicio.anio);
            printf("Fin de alquiler:     %d/%d/%d\n", aux.fechaFin.dia, aux.fechaFin.mes, aux.fechaFin.anio);
            printf("Costo total:         $%.2f\n", aux.costoTotal);
        }
        mostrarAlquileresRecursivamente(archi);
    }
}

//MODIFICAR ALQUILER
void modificarAlquiler(char nombreArchivo[])
{
    stAlquiler aux;

    int diasExtras;

    int idBuscado = 0;

    int encontrado = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        printf("\nIngrese el ID del vehiculo a modificar: ");
        scanf("%d", &idBuscado);

        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0 && encontrado == 0)
        {
            if(aux.id == idBuscado && aux.eliminado == 0)
            {
                encontrado = 1;

                printf("\nIngrese cuantos dias desea agregar al alquiler: ");
                scanf("%d", &diasExtras);

                aux.fechaFin = calcularFechaFin(aux.fechaFin, diasExtras);

                fseek(archi, sizeof(stAlquiler) * (-1), SEEK_CUR);

                fwrite(&aux, sizeof(stAlquiler), 1, archi);

                fseek(archi, 0, SEEK_CUR);

                printf("Dias modificados correctamente.\n");
            }
        }
        fclose(archi);

        if(encontrado == 0)
        {
            printf("No se encontro ningun alquiler activo con ID %d.\n", idBuscado);
        }
    }
}
//MOSTRAR UN ALQUILER
void mostrarUnAlquiler(stAlquiler aux)
{
    printf("===========================================\n");
    printf("           DETALLE DEL ALQUILER            \n");
    printf("===========================================\n");
    printf(" ID Alquiler  : #%02d\n", aux.id); // %04d le mete ceros si es un ID bajo (Ej: #0005)
    printf(" DNI Cliente  : %s\n", aux.dniCliente);
    printf(" Patente Auto : [%s]\n", aux.patente);
    printf("-------------------------------------------\n");
    printf(" Fecha Inicio : %02d/%02d/%d\n", aux.fechaInicio.dia, aux.fechaInicio.mes, aux.fechaInicio.anio);
    printf(" Fecha Fin    : %02d/%02d/%d\n", aux.fechaFin.dia, aux.fechaFin.mes, aux.fechaFin.anio);
    printf("-------------------------------------------\n");
    printf(" COSTO TOTAL  : $%.2f\n", aux.costoTotal);
    printf(" Estado       : %s\n", (aux.eliminado == 0) ? "ACTIVO" : "FINALIZADO/CANCELADO");
    printf("===========================================\n\n");
}

//BUSCAR Y MOSTRAR UN ALQUILER ESPECIFICO
void buscarYMostrarAlquiler(char nombreArchivo[])
{
    stAlquiler aux;
    char patenteBuscada[DIM_PATENTE];
    int encontrado = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        printf("Ingrese la patente a buscar: ");
        getchar();
        fgets(patenteBuscada, DIM_PATENTE, stdin);
        limpiarSaltoLinea(patenteBuscada);

        strupr(patenteBuscada);

        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0 && encontrado == 0)
        {
            if(strcmp(aux.patente, patenteBuscada) == 0 && aux.eliminado == 0)
            {
                encontrado = 1;

                mostrarUnAlquiler(aux);
            }
        }
        fclose(archi);

        if(encontrado == 0)
        {
            printf("\nNo se encontro ningun vehiculo activo con la patente: %s\n", patenteBuscada);
        }
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

//BUSCAR Y MOSTRAR ALQUILERES DADOS DE BAJA
void MostrarAlquileresFinalizados(char nombreArchivo[])
{
    stAlquiler aux;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {

        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0)
        {
            if(aux.eliminado == 1)
            {
                mostrarUnAlquiler(aux);
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

void mostrarArrDeAlquileres (stAlquiler ArregloAlq[], int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        mostrarUnAlquiler(ArregloAlq[i]);
    }
}
//○------------------------------ Listados --------------------------------
//● Listar todos los datos por orden alfabético por el método de selección
//(campo a elegir de acuerdo a las structs elegidas
int PasarAlquileresAunArreglo(char nombreArchivo[], stAlquiler **arreglo)
{
    int cantidad = 0;

    stAlquiler aux;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0)
        {
            if(aux.eliminado == 0)
            {
                *arreglo = realloc(*arreglo, (cantidad + 1) * sizeof(stAlquiler));

                (*arreglo)[cantidad] = aux;

                cantidad++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
    return cantidad;
}
//---------OR. POR SELECCION (POR PATENTES DEL VEHICULO ALQUILADO)--------
void OrdenarAlquileresPorSeleccion(stAlquiler arreglo[], int cantidad)
{
    int i;
    int j;
    int minPos;
    stAlquiler temp;

    for(i = 0; i < cantidad - 1; i++)
    {
        minPos = i;
        for(j = i + 1; j < cantidad; j++)
        {
            if(strcmp(arreglo[j].patente, arreglo[minPos].patente) < 0)
                minPos = j;
        }
        if(minPos != i)
        {
            temp = arreglo[i];
            arreglo[i] = arreglo[minPos];
            arreglo[minPos] = temp;
        }
    }
}

//---------OR. POR INSERCION (POR COSTO TOTAL)--------
void ordenarAlquileresPorInsercion(stAlquiler arreglo[], int cantidad)
{
    int i = 1;
    while(i < cantidad)
    {
        insercionDeDato(arreglo, i-1, arreglo[i]);
        i++;
    }
}

void insercionDeDato(stAlquiler arreglo[], int ultPos, stAlquiler aux)
{
    int i = ultPos;
    while(i >= 0 && aux.costoTotal < arreglo[i].costoTotal)
    {
        arreglo[i+1] = arreglo[i];
        i--;
    }
    arreglo[i+1] = aux;
}

//FUNCIONES PARA MOSTRAR LOS ALQUILERES RECIENTES
void mostrarAlquileresRecientesEnPila(char nombreArchivo[])
{
    Pila destino;
    inicpila(&destino);

    copiarIdsAPila(nombreArchivo, &destino);

    if(!pilavacia(&destino))
    {
        char continuar = 's';

        while(continuar == 's' && !pilavacia(&destino))
        {
            mostrarAlquileresPorId(nombreArchivo, desapilar(&destino));

            if(!pilavacia(&destino))
            {
                printf("Desea ver el alquiler anterior? (s/n): ");
                scanf(" %c", &continuar);
            }
            else
            {
                printf("\n[SISTEMA]: Se ha llegado al final del historial de alquileres.\n");
            }
        }
    }
    else
    {
        printf("\nNo hay alquileres disponibles para mostrar\n");
    }

}

void copiarIdsAPila(char nombreArchivo[], Pila *destino)
{
    stAlquiler aux;

    FILE *archi = NULL;
    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stAlquiler), 1, archi) > 0)
        {
            if(aux.eliminado == 0)
            {
                apilar(destino, aux.id);
            }
        }
    }
    else
    {
        printf("\nERROR: No hay vehiculos cargados\n");
    }
}

void mostrarAlquileresPorId(char nombreArchivo[], int id)
{
    stAlquiler aux;

    FILE *archi = NULL;
    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        fseek(archi, (id - 1) * sizeof(stAlquiler), SEEK_SET);
        fread(&aux, sizeof(stAlquiler), 1, archi);

        mostrarUnAlquiler(aux);
    }
    else
    {
        printf("\nERROR: No hay vehiculos cargados\n");
    }
}













