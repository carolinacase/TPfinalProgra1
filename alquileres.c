#include "alquileres.h"

void menuAlquileres(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[])
{
    int opcion;

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
            // bajaAlquiler(...)
            break;
        case 3:
            // modificarAlquiler(...)
            break;
        case 4:
            // buscarAlquiler(...)
            break;
        case 5:
            // menuOrdenacionAlquileres(...)
            break;
        case 6:
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

//FUNCIONES PARA CARGAR UN ALQUILER
void altaAlquiler(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[])
{
    stAlquiler aux;

    int existeCliente = 0;
    int existeVehiculo = 0;
    int dias = 0;

    printf("\n--- REGISTRAR NUEVO ALQUILER ---\n");
    printf("(Ingrese '0' en cualquier momento para cancelar la operacion)\n\n");

    //VALIDACION DEL CLIENTE
    do
    {
        printf("Ingrese el DNI del cliente: ");
        fflush(stdin);
        fgets(aux.dniCliente, DIM_DNI, stdin);
        limpiarSaltoLinea(aux.dniCliente);

        if(strcmp(aux.dniCliente, "0") == 0)
        {
            existeCliente = 1;
        }
        else
        {
            existeCliente = ValidarClienteExistente(archivoClientes, aux.dniCliente);

            if(existeCliente == 0)
            {
                printf("ERROR: El DNI '%s' no esta registrado. Intente nuevamente.\n\n", aux.dniCliente);
            }
        }
    }
    while(existeCliente == 0);

    if(strcmp(aux.dniCliente, "0") == 0)
    {
        printf("\nOperacion cancelada, volviendo al menu\n");
    }
    else
    {
        //VALIDACION DEL VEHICULO
        do
        {
            printf("Ingrese la patente del vehiculo: ");
            fflush(stdin);
            fgets(aux.patente, DIM_PATENTE, stdin);
            limpiarSaltoLinea(aux.patente);

            if(strcmp(aux.patente, "0") == 0)
            {
                existeVehiculo = 1;
            }
            else
            {
                existeVehiculo = validarPatenteEnArchivo(archivoVehiculos, aux.patente);

                if(existeVehiculo == 0)
                {
                    printf("ERROR: La patente '%s' no existe en el sistema. Intente nuevamente.\n\n", aux.patente);
                }
            }
        }
        while(existeVehiculo == 0);

        if(strcmp(aux.patente, "0") == 0)
        {
            printf("\nOperacion cancelada, volviendo al menu\n");
        }
        else
        {
            aux.id = obtenerNuevoIdAlquiler(archivoAlquileres);

            cargarAlquiler(&aux, &dias);

            float precioPorDia = obtenerPrecioPorDia(archivoVehiculos, aux.patente);
            aux.costoTotal = (float)dias * precioPorDia;


            FILE *archi = NULL;
            archi = fopen(archivoAlquileres, "ab");

            if(archi != NULL)
            {
                fwrite(&aux, sizeof(stAlquiler), 1, archi);
                fclose(archi);

                printf("\n==============================================\n");
                printf(" ¡ALQUILER REGISTRADO CON EXITO!\n");
                printf(" ID Alquiler: %d\n", aux.id);
                printf(" Costo Total a pagar: $%.2f\n", aux.costoTotal);
                printf("==============================================\n");
            }
        }
    }
}

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





























