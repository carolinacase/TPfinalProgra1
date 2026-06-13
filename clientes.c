#include "Clientes.h"

void menuClientes(char nombreArchivo[])
{
    int opcion;
    char dniBuscado[10];

    do
    {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Alta de cliente\n"); //
        printf("2. Mostrar clientes\n");
        printf("3. Dar de baja un cliente\n");
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
        case 3:
            printf("Ingrese el DNI del cliente que desea dar de baja: ");
            fflush(stdin);
            scanf("%s", dniBuscado);
            DarDeBajaUnCliente(nombreArchivo, dniBuscado);
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
////○ Alta
////● Carga de Datos
////○ Verificar de no cargar repetidos
////● Guardar en Archivo

void altaCliente(char nombreArchivo[]) //Falta verificacion de carga repetida
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
//-------------------------MOSTRAR CLIENTES-------------------------
void mostrarUnCliente(stCliente unCliente)
{
    printf("  Nombre:    %s %s\n", unCliente.nombre, unCliente.apellido);
    printf("  DNI:       %s\n", unCliente.dni);
    printf("  Telefono:  %s\n", unCliente.telefono);

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
                mostrarUnCliente(aux);
                contador++;
            }
        }

        printf("\n---------------------------------------------------------------\n");
        if(contador == 0)
            printf("  No hay clientes registrados.\n");
        else
            printf("  Total de clientes activos: %d\n", contador);
        printf("------------------------- --------------------------------------\n");

        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
//-------------------------BAJA LOGICA-------------------------

void DarDeBajaUnCliente(char nombreArchivo[], char dniBuscado[])
{
    int dniEncontrado = 0;
    stCliente aux;

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0 && dniEncontrado == 0) //////● Buscar el dato en el archivo
        {
            if((strcmp(aux.dni, dniBuscado) == 0)&& aux.activo == 1)
            {
                dniEncontrado = 1;
                aux.activo = 0; ////○ Baja LOGICA
                fseek(archi, sizeof(stCliente) * (-1), SEEK_CUR);
                fwrite(&aux, sizeof(stCliente), 1, archi); ////● Eliminar el dato ( pisarlo con otro valor)
                printf("Cliente dado de baja correctamente.\n");
            }
        }
        fclose(archi); ////● Guardar los cambios en el archivo

        if(dniEncontrado == 0)
            printf("No se encontro ningun cliente con ese DNI.\n");
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
