#include "Vehiculos.h"
// ------------------------------FUNCIONES DE VEHICULOS---------------------------------

void menuVehiculos(char nombreArchivo[], stVehiculo vehiculos[])
{
    int opcion;

    do
    {
        printf("\n--- MENU VEHICULOS ---\n");
        printf("1. Cargar vehiculo\n");
        printf("2. Eliminar vehiculo\n");
        printf("3. Modificar vehiculo\n");
        printf("4. Buscar vehiculo\n");
        printf("5. Ordenar Vehiculos\n");
        printf("0. Salir\n");

        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            altaVehiculo(nombreArchivo, vehiculos);
            break;
        case 2:
            bajaVehiculo(nombreArchivo);
            break;
        case 3:
            MostrarVehiculos(nombreArchivo);
            break;
        case 4:
            modificarVehiculo(nombreArchivo);
            break;
        case 5:
        //OrdenarPorInsercion(nombreArchivo);
        case 0:
            printf("Salir\n");
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
    }
    while(opcion != 0);
}

//Contar los vehiculos que hay en el archivo
int contarVehiculosEnArchivo(char nombreArchivo[])
{
    stVehiculo;
    int cantidad = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);

        cantidad = ftell(archi) / sizeof(stVehiculo);
    }
    else
    {
        printf("\nError: no se pudo leer el archivo o está vacio\n");
    }

    return cantidad;
}

// Genera un ID que se incrementa buscando el ultimo en el archivo
int obtenerNuevoId(char nombreArchivo[])
{
    int id = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        fseek(archi, 0, SEEK_END);

        id = ftell(archi) / sizeof(stVehiculo);

        fclose(archi);
    }
    else
    {
        id = 0;
    }

    return id;
}

// Carga los datos de un vehiculo por teclado
int cargarVehiculo(stVehiculo vehiculos[], int dimension, char nombreArchivo[])
{
    char continuar = 's';
    int validos = 0;

    for(validos; validos < dimension && continuar == 's'; validos++)
    {
        vehiculos[validos].id = obtenerNuevoId(nombreArchivo);

        printf("ID: %d\n", vehiculos[validos].id);

        printf("Ingrese la marca: ");
        fflush(stdin);
        fgets(vehiculos[validos].marca, DIM_STRINGS, stdin);

        printf("Ingrese el modelo: ");
        fflush(stdin);
        fgets(vehiculos[validos].modelo, DIM_STRINGS, stdin);

        printf("Ingrese el kilometraje: ");
        scanf("%d", &vehiculos[validos].kilometraje);

        printf("Ingrese el precio por dia: ");
        scanf("%f", &vehiculos[validos].precioPorDia);

        vehiculos[validos].disponible = 1; // disponible

        printf("Desea seguir cargando (s/n): ");
        scanf(" %c", &continuar);
    }

    return validos;
}

// Alta: guarda un vehiculo nuevo en el archivo
void altaVehiculo(char nombreArchivo[], stVehiculo vehiculos[])
{
    int cantidadVehiculos = 0;

    do
    {
        cantidadVehiculos = contarVehiculosEnArchivo(nombreArchivo);

        if(cantidadVehiculos >= DIM_VEHICULOS)
        {
            printf("\nNo se pueden cargar mas autos");
        }
        else
        {
//            printf("Ingrese la patente: ");/*Esto*/
//            fflush(stdin);                 /*es para*/
//            scanf(" %s", vehiculo.patente); /*validar*/

            int validosVehiculos = cargarVehiculo(vehiculos, DIM_VEHICULOS, nombreArchivo);

        }
    }
    while(cantidadVehiculos < DIM_VEHICULOS);
}

// Baja logica: marca disponible = -1
void bajaVehiculo(char nombreArchivo[])
{
    int idBuscado, encontrado = 0;
    stVehiculo aux;

    printf("Ingrese el ID del vehiculo a dar de baja: ");
    scanf("%d", &idBuscado);

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(aux.id == idBuscado && aux.disponible != -1)
            {
                encontrado = 1;

                aux.disponible = -1; // marca como eliminado

                fseek(archi, sizeof(stVehiculo) * (-1), SEEK_CUR);
                fwrite(&aux, sizeof(stVehiculo), 1, archi);
                fseek(archi, 0, SEEK_CUR);

                printf("Vehiculo con ID %d dado de baja correctamente.\n", idBuscado);
            }
        }
        fclose(archi);

        if(encontrado == 0)
            printf("No se encontro ningun vehiculo activo con ID %d.\n", idBuscado);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

//----------------------------Mostrar Vehiculos-----------------------------------

void MostrarVehiculos(char nombreArchivo[])
{
    stVehiculo aux;
    int contador = 0;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        printf("\n-------------------LISTA DE VEHICULOS----------------------\n");


        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
        {
            if(aux.disponible != -1) // omite los dados de baja
            {
                contador++;
                printf("\n--- Vehiculo #%d ---\n", contador);
                printf("  ID:            %d\n",     aux.id);
                printf("  Patente:       %s\n",     aux.patente);
                printf("  Marca:         %s\n",     aux.marca);
                printf("  Modelo:        %s\n",     aux.modelo);
                printf("  Kilometraje:   %d km\n",  aux.kilometraje);
                printf("  Precio/dia:    $%.2f\n",  aux.precioPorDia);
                if (aux.disponible == 1)
                {
                    printf("DISPONIBLE");
                }
                else
                {
                    printf("OCUPADO");
                }
            }
        }

        printf("\n---------------------------------------------------------------\n");
        if(contador == 0)
            printf("  No hay vehiculos registrados.\n");
        else
            printf("  Total de vehiculos activos: %d\n", contador);
        printf("---------------------------------------------------------------\n");

        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

// ---------------------------------------------------------------
// MODIFICAR VEHICULO
// ---------------------------------------------------------------
void modificarVehiculo(char nombreArchivo[])
{
    stVehiculo aux;
    int idBuscado, encontrado = 0;
    int opMod;

    // Primero mostramos la lista para que el usuario vea los IDs disponibles
    MostrarVehiculos(nombreArchivo);

    printf("\nIngrese el ID del vehiculo a modificar: ");
    scanf("%d", &idBuscado);

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(aux.id == idBuscado && aux.disponible != -1)
            {
                encontrado = 1;

                printf("\n--- Que desea modificar? ---\n");
                printf("1. Precio por dia  (actual: $%.2f)\n", aux.precioPorDia);
                printf("2. Kilometraje     (actual: %d km)\n", aux.kilometraje);
                printf("3. Ambos\n");
                printf("Opcion: ");
                scanf("%d", &opMod);

                if(opMod == 1 || opMod == 3)
                {
                    printf("Nuevo precio por dia: ");
                    scanf("%f", &aux.precioPorDia);
                }

                if(opMod == 2 || opMod == 3)
                {
                    printf("Nuevo kilometraje: ");
                    scanf("%d", &aux.kilometraje);
                }

                // Retroceder el cursor un struct y sobreescribir

                fseek(archi, (long)sizeof(stVehiculo) * (-1), SEEK_CUR);
                fwrite(&aux, sizeof(stVehiculo), 1, archi);
                fseek(archi, 0, SEEK_CUR);

                printf("Vehiculo modificado correctamente.\n");
            }
        }
        fclose(archi);

        if(encontrado == 0)
            printf("No se encontro ningun vehiculo activo con ID %d.\n", idBuscado);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
