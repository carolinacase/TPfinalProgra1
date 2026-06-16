#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <string.h>
#include "Clientes.h"

#define MAX_VEHICULOS 20 //Agregué dimension para el arreglo estatico para cargar vehiculos (flota).
#define DIM_PATENTE 8
#define DIM_STRINGS 30
=======
#include "Vehiculos.h"
>>>>>>> main

int main()
{
    system("color 9f");

    char archivoVehiculos[]  = "vehiculos.bin";
    char archivoClientes[]   = "clientes.bin";
    char archivoAlquileres[] = "alquileres.bin";

    int opcion;

    do
    {
<<<<<<< HEAD
        printf("\n------SISTEMA DE ALQUILER DE VEHICULOS------\n");
        printf("1. Gestion de vehiculos\n");
        printf("2. Gestion de clientes\n");
        printf("3. Gestion de Alquileres\n");
        printf("0. Salir\n");
        printf("----------------------------------------------\n");
=======
        printf("\n------SISTEMA DE ALQUILER DE VEHICULOS----\n");
        printf("1. Gestion de vehiculos\n");
        printf("2. Gestion de clientes\n");
        printf("3. Gestion de Rentas y Devoluciones\n");
        printf("0. Salir\n");
        printf("--------------------------------------------\n");
>>>>>>> main
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            //menuVehiculos(archivoVehiculos);
            break;
        case 2:
            break;
        case 3:
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
