#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Clientes.h>

#define MAX_VEHICULOS 20 //Agregué dimension para el arreglo estatico para cargar vehiculos (flota).
#define DIM_PATENTE 8
#define DIM_STRINGS 30

int main()
{
    system("color 5f");

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
            menuClientes(archivoClientes);
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
            printf("\nSalir\n");
            break;
        default:
            printf("\nOpcion invalida. Intente de nuevo.\n");
            break;
        }
    }
    while(opcion != 0);

    return 0;
}
