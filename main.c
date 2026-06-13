#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEHICULOS 20 //Agregué dimension para el arreglo estatico para cargar vehiculos (flota).
#define DIM_PATENTE 8
#define DIM_STRINGS 30

//--------------------------------STRUCTS--------------------------------


typedef struct
{
    int id;
    char patente[DIM_PATENTE];
    char marca[DIM_STRINGS];
    char modelo[DIM_STRINGS];
    int kilometraje;
    float precioPorDia;
    int disponible; // 1 = disponible | 0 = alquilado | -1 = dado de baja
} stVehiculo;

typedef struct
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

// ---------------------------PROTOTIPADO------------------------------------

// Menus
void menuVehiculos(char nombreArchivo[]);
void menuClientes(char nombreArchivo[]);

// Vehiculos
stVehiculo cargarVehiculo(char nombreArchivo[]);
int obtenerNuevoId(char nombreArchivo[]);
void altaVehiculo(char nombreArchivo[]);
void bajaVehiculo(char nombreArchivo[]);
void MostrarVehiculos(char nombreArchivo[]);
void modificarVehiculo(char nombreArchivo[]);

// Alquiler

// ------------------------------MAIN---------------------------------

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

// --------------------------MENUS SECUNDARIOS-------------------------------------

void menuVehiculos(char nombreArchivo[])
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
            altaVehiculo(nombreArchivo);
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

// ------------------------------FUNCIONES DE VEHICULOS---------------------------------

// Genera un ID que se incrementa buscando el ultimo en el archivo
int obtenerNuevoId(char nombreArchivo[])
{
    FILE *archi = NULL;
    stVehiculo aux;
    int maxId = 0;

    archi = fopen(nombreArchivo, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) == 1)
        {
            if(aux.id > maxId)
                maxId = aux.id;
        }
        fclose(archi);
    }
    return maxId + 1;
}

// Carga los datos de un vehiculo por teclado
stVehiculo cargarVehiculo(char nombreArchivo[])
{
    stVehiculo vehiculo;

    vehiculo.id = obtenerNuevoId(nombreArchivo);

    printf("ID generado automaticamente: %d\n", vehiculo.id);

    printf("Ingrese la marca: ");
    fflush(stdin);
    scanf(" %s", vehiculo.marca);

    printf("Ingrese el modelo: ");
    fflush(stdin);
    scanf(" %s", vehiculo.modelo);

    printf("Ingrese la patente: ");
    fflush(stdin);
    scanf(" %s", vehiculo.patente);

    printf("Ingrese el kilometraje: ");
    scanf("%d", &vehiculo.kilometraje);

    printf("Ingrese el precio por dia: ");
    scanf("%f", &vehiculo.precioPorDia);

    vehiculo.disponible = 1; // disponible

    return vehiculo;
}

// Alta: guarda un vehiculo nuevo en el archivo
void altaVehiculo(char nombreArchivo[])
{
    stVehiculo nuevo = cargarVehiculo(nombreArchivo);

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        fwrite(&nuevo, sizeof(stVehiculo), 1, archi);
        fclose(archi);
        printf("Vehiculo dado de alta. EL nuevo ID es: %d\n", nuevo.id);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
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

// ---------------------------------------------------------------
// FUNCIONES DE ALQUILER DE VEHICULOS
// ---------------------------------------------------------------
// Genera un ID que se incrementa buscando el ultimo en el archivo
/*int obtenerNuevoId(char nombreArchivo[])
{
    FILE *archi = NULL;
    stAlquiler aux;
    int maxId = 0;

    archi = fopen(nombreArchivo, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stAlquiler), 1, archi) == 1)
        {
            if(aux.id > maxId)
                maxId = aux.id;
        }
        fclose(archi);
    }
    return maxId + 1;
}

stAlquiler Alquiler ()
{
    stAlquiler aux;

    printf("Ingrese dni del cliente:");
    fflush(stdin);
    gets(" %i",aux.idCliente);

    printf("Ingrese el Id del vehiculo que desea Alquilar:");
    fflush(stdin);
    gets(" %i",aux.idVehiculo);

    aux.idAlquiler = obtenerNuevoId(char nombreArchivo[])

                     int idAlquiler;
    char fecha_inicio[11];
    char fecha_fin[11];
    int cantDias;
    float totalCosto;
    int dadoDeBaja;

}*/

/*int RegistroDeAlquiler (char ArchivoClientes[], char ArchivoVehiculos[])
{


    FILE *ArchivoClientes = fopen(ArchivoClientes,"rb");
    FILE *ArchivoVehiculos = fopen(ArchivoClientes,"rb");


    while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
    {
        if()


        }
}*/


