#include "Alquileres.h"

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
            // altaAlquiler(...)
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
void cargarAlquiler(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[])
{

}

































