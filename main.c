#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#include "Vehiculos.h"
#include "Clientes.h"
#include "alquileres.h"

int main()
{
    system("color 9f");

    char archivoVehiculos[]  = "vehiculos.bin";
    char archivoClientes[]   = "clientes.bin";
    char archivoAlquileres[] = "alquileres.bin";

    int opcion;

    do
    {
        printf("============================================\n");
        printf("    SISTEMA DE ALQUILER DE VEHICULOS        \n");
        printf("============================================\n");
        printf("1. Gestion de Vehiculos\n");
        printf("2. Gestion de Clientes\n");
        printf("3. Gestion de Alquileres\n");
        printf("0. Salir\n");
        printf("============================================\n");
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
            menuAlquileres(archivoAlquileres, archivoVehiculos, archivoClientes);
            break;
        case 0:
            printf("\nAdios!\n");
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
