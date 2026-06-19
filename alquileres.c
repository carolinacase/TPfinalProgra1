#include "alquileres.h"

void menuAlquileres(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[])
{
    int opcion;
    stAlquiler *arreglo = NULL;
    int cantidad;

    do
    {
        printf("\n--- MENU ALQUILER ---\n");
        printf("1. Registrar un Alquiler\n");
        printf("2. Cancelar/Finalizar Alquiler\n");
        printf("3. Modificar Alquiler\n");
        printf("4. Buscar Alquiler\n");
        printf("5. Ordenar alquileres\n");
        printf("6. Mostrar alquileres\n");
        printf("0. Volver al menu principal\n");

        printf("\nIngrese una opcion: ");
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
            printf("\n--- ORDENAR ALQUILERES ---\n");
            printf("1. Ordenar alfabeticamente por apellido (seleccion)\n");
            printf("2. Ordenar por numero de DNI (insercion)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcionOrden);
            cantidad = PasarClientesAunArreglo(nombreArchivo, &arreglo);

            if(cantidad > 0)
            {
                if(opcionOrden == 1)
                    OrdenarClientesPorSeleccion(arreglo, cantidad);
                else if(opcionOrden == 2)
                    ordenarArregloPorInsercion(arreglo, cantidad);

                mostrarArrDeClientes(arreglo, cantidad);
                free(arreglo);
            }
            else
                printf("No hay clientes registrados.\n");
        }
        case 6:
            mostrarAlquileres(archivoAlquileres);
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

            printf("\n==============================================\n");
            printf(" ALQUILER REGISTRADO CON EXITO!\n");
            printf("Fin de alquiler: %d/%d/%d\n", aux.fechaFin.dia, aux.fechaFin.mes, aux.fechaFin.anio);
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
    printf("Ingrese el dia de inicio: ");
    scanf("%d", &aux->fechaInicio.dia);

    printf("Ingrese el mes de inicio: ");
    scanf("%d", &aux->fechaInicio.mes);

    printf("Ingrese el anio de inicio: ");
    scanf("%d", &aux->fechaInicio.anio);

    printf("¿Por cuantos dias se alquila el vehiculo?: ");
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

    do
    {
        printf("Ingrese la patente del vehiculo: ");
        fflush(stdin);
        fgets(destinoPatente, DIM_PATENTE, stdin);
        limpiarSaltoLinea(destinoPatente);

        if(strcmp(destinoPatente, "0") == 0)
        {
            return 0;
        }
        else
        {
            existeVehiculo = validarPatenteEnArchivo(archivoVehiculos, destinoPatente);

            if(existeVehiculo == 0)
            {
                printf("ERROR: La patente '%s' no existe en el sistema. Intente nuevamente.\n\n", destinoPatente);
            }
        }
    }
    while(existeVehiculo == 0);

    return 1;
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

//BUSCAR Y MOSTRAR ALQUILER
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

void mostrarUnAlquiler(stAlquiler aux)
{
    printf("\n--- ALQUILER ENCONTRADO ---\n");
    printf("\n--- Alquiler ---\n");
    printf("ID:                  %d\n", aux.id);
    printf("DNI:                 %s\n", aux.dniCliente);
    printf("Patente:             %s\n", aux.patente);
    printf("Inicio de alquiler:  %d/%d/%d\n", aux.fechaInicio.dia, aux.fechaInicio.mes, aux.fechaInicio.anio);
    printf("Fin de alquiler:     %d/%d/%d\n", aux.fechaFin.dia, aux.fechaFin.mes, aux.fechaFin.anio);
    printf("Costo total:         $%.2f\n", aux.costoTotal);
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
            if(aux.activo == 1)
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
//ORDENAMIENTO POR INSERCION
void ordenarArregloPorInsercion(stAlquiler arreglo[], int cantidad)
{
    int i = 1;
    while(i < cantidad)
    {
        insertar(arreglo, i-1, arreglo[i]);
        i++;
    }
}

void insertarDato(stAlquiler arreglo[], int ultPos, stCliente dato)
{
    int i = ultPos;
    while(i >= 0 && strcmp(dato.dni, arreglo[i].dni) < 0)
    {
        arreglo[i+1] = arreglo[i];
        i--;
    }
    arreglo[i+1] = dato;
}
