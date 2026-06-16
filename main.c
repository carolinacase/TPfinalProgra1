#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Clientes.h"
#include "Vehiculos.h"

int main()
{
    system("color 9f");
    char archivoVehiculos[]  = "vehiculos.bin";
    char archivoClientes[]   = "clientes.bin";
    char archivoAlquileres[] = "alquileres.bin";
    int opcion;
    do
    {
        printf("\n------SISTEMA DE ALQUILER DE VEHICULOS------\n");
        printf("1. Gestion de vehiculos\n");
        printf("2. Gestion de clientes\n");
        printf("3. Gestion de Rentas y Devoluciones\n");
        printf("0. Salir\n");
        printf("--------------------------------------------\n");
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
