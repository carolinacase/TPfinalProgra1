#include <stdio.h>
#include <stdlib.h>
#include "Vehiculos.h"
//ACA AGREGA TU CLIENTE.H



/*typedef struct
{
    int idAlquiler;
    int idCliente;
    int idVehiculo;
    char fecha_inicio[11];
    char fecha_fin[11];
    int cantDias;
    float totalCosto;
    int dadoDeBaja;
} stAlquiler;

void menuClientes(char nombreArchivo[]);

// Clientes
stCliente cargarDatosDelCliente();
void altaCliente(char nombreArchivo[]);
void MostrarClientes(char nombreArchivo[]);*/

int main()
{
    system("color 9f");

    char archivoVehiculos[]  = "vehiculos.bin";
    char archivoClientes[]   = "clientes.bin";
    char archivoAlquileres[] = "alquileres.bin";

    int opcion;

    do
    {
        printf("\n---------------SISTEMA DE ALQUILER DE VEHICULOS------------------------\n");
        printf("1. Gestion de vehiculos\n");
        printf("2. Gestion de clientes\n");
        printf("3. Realizar alquiler\n");
        printf("4. Devolver vehiculo\n");
        printf("5. Listados\n");
        printf("0. Salir\n");
        printf("----------------------------------------\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            menuVehiculos(archivoVehiculos);
            break;
        case 2:
            //menuClientes(archivoClientes);
            break;
        case 3:
            printf("Realizar Alquiler\n");
            break;
        case 4:
            printf("Realizar devolucion\n");
            break;
        case 5:
            printf("Mostrar\n");
            break;
        case 0:
            printf("\n¡Saludos!\n");
            break;
        default:
            printf("\nOpcion invalida. Intente de nuevo.\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(opcion != 0);

    return 0;
}

/*
void menuClientes(char nombreArchivo[])
{
    int opcion;

    do
    {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Alta de cliente\n"); //
        printf("2. Mostrar clientes\n");
        printf("0. Volver al menu principal\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            altaCliente(nombreArchivo);
            break;
        case 2:
            MostrarClientes(nombreArchivo);
            break;
        case 0:
            printf("Salir.\n");
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
    }
    while(opcion != 0);
}

// ---------------------------------------------------------------
// FUNCIONES DE CLIENTES
// ---------------------------------------------------------------

stCliente cargarDatosDelCliente()
{
    stCliente cliente;

    printf("Ingrese nombre: ");
    fflush(stdin);
    scanf(" %s", cliente.nombre);

    printf("Ingrese apellido: ");
    fflush(stdin);
    scanf(" %s", cliente.apellido);

    printf("Ingrese DNI: ");
    fflush(stdin);
    scanf(" %s", cliente.dni);

    printf("Ingrese telefono: ");
    fflush(stdin);
    scanf(" %s", cliente.telefono);

    cliente.activo = 1;

    return cliente;
}

void altaCliente(char nombreArchivo[])
{
    stCliente nuevo = cargarDatosDelCliente();

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        fwrite(&nuevo, sizeof(stCliente), 1, archi);
        fclose(archi);
        printf("Cliente dado de alta correctamente.\n");
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

void MostrarClientes(char nombreArchivo[])
{
    stCliente aux;
    int contador = 0;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        printf("\n-------------------------LISTA DE CLIENTES---------------------------\n");


        while(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.activo == 1)
            {
                contador++;
                printf("\n--- Cliente #%d ---\n", contador);
                printf("  Nombre:    %s %s\n", aux.nombre, aux.apellido);
                printf("  DNI:       %s\n", aux.dni);
                printf("  Telefono:  %s\n", aux.telefono);
            }
        }

        printf("\n---------------------------------------------------------------\n");
        if(contador == 0)
            printf("  No hay clientes registrados.\n");
        else
            printf("  Total de clientes activos: %d\n", contador);
        printf("---------------------------------------------------------------\n");

        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
*/
