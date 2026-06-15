#include "Vehiculos.h"
// ------------------------------FUNCIONES DE VEHICULOS---------------------------------

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
        printf("6. Mostrar Vehiculos\n");
        printf("0. Volver al menu principal\n");

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
            modificarVehiculo(nombreArchivo);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            mostrarVehiculos(nombreArchivo);
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

// Alta: guarda un vehiculo nuevo en el archivo
void altaVehiculo(char nombreArchivo[])
{
    int patenteRepetidaArchivo = 0;

    char dominio[DIM_PATENTE];

    char continuar = 's';

    stVehiculo aux;

    int vehiculosTotales = contarVehiculosEnArchivo(nombreArchivo);

    if(vehiculosTotales < DIM_VEHICULOS)
    {
        do
        {
            //----------------BUSCAR PATENTE QUE NO SE REPITA EN EL ARCHIVO
            do
            {
                printf("Ingrese la patente: ");
                fflush(stdin);
                fgets(dominio, DIM_STRINGS, stdin);
                limpiarSaltoLinea(dominio);

                patenteRepetidaArchivo = validarPatenteEnArchivo(nombreArchivo, dominio);

                if(patenteRepetidaArchivo == 1)
                {
                    printf("PATENTE YA CARGADA, INGRESE OTRA\n");
                }
            }
            while(patenteRepetidaArchivo == 1);
            //---------------------------------------------------------------

            strcpy(aux.patente, dominio);

            cargarVehiculo(&aux);

            aux.id = obtenerNuevoId(nombreArchivo) + 1;

            FILE *archi = NULL;

            archi = fopen(nombreArchivo, "ab");

            if(archi != NULL)
            {
                fwrite(&aux, sizeof(stVehiculo), 1, archi);
                fclose(archi);
            }

            vehiculosTotales = contarVehiculosEnArchivo(nombreArchivo);

            if(vehiculosTotales >= DIM_VEHICULOS)
            {
                printf("\nFlota de autos llena\n");
                continuar = 'n';
            }
            else
            {
                printf("Desea cargar otro vehiculo? (s/n): ");
                fflush(stdin);
                scanf(" %c", &continuar);
            }
        }
        while(continuar == 's');
    }
    else
    {
        printf("\nFlota de autos llena\n");
    }
}

int validarPatenteEnArchivo(char nombreArchivo[], char dominio[])
{
    stVehiculo aux;
    int encontrado = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
        {
            if(strcmp(dominio, aux.patente) == 0 && aux.eliminado == 0)
            {
                encontrado = 1;
            }
            else if(strcmp(dominio, aux.patente) == 0 && aux.eliminado == 1)
            {
                encontrado = 0;
            }
        }
        fclose(archi);
    }

    return encontrado;
}

// Carga los datos de un vehiculo por teclado
void cargarVehiculo(stVehiculo *aux)
{
    printf("Ingrese la marca: ");
    fflush(stdin);
    fgets(aux->marca, DIM_STRINGS, stdin);
    limpiarSaltoLinea(aux->marca);

    printf("Ingrese el modelo: ");
    fflush(stdin);
    fgets(aux->modelo, DIM_STRINGS, stdin);
    limpiarSaltoLinea(aux->modelo);

    printf("Ingrese el kilometraje: ");
    fflush(stdin);
    scanf("%d", &aux->kilometraje);

    printf("Ingrese el precio por dia: ");
    fflush(stdin);
    scanf("%f", &aux->precioPorDia);

    aux->eliminado = 0;

    aux->disponible = 0;
}

//Contar los vehiculos que hay en el archivo
int contarVehiculosEnArchivo(char nombreArchivo[])
{
    stVehiculo aux;
    int contador = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
        {
            if(aux.eliminado == 0)
            {
                contador++;
            }
        }
        fclose(archi);
    }

    return contador;
}

// Genera un ID que se incrementa buscando el ultimo en el archivo
int obtenerNuevoId(char nombreArchivo[])
{
    int maxId = 0;
    stVehiculo aux;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
        {
            if(aux.id > maxId)
            {
                maxId = aux.id;
            }
        }
        fclose(archi);
    }

    return maxId;
}

// Baja logica
void bajaVehiculo(char nombreArchivo[])
{
    int idBuscado, encontrado = 0;
    stVehiculo aux;

    mostrarVehiculos(nombreArchivo);

    printf("Ingrese el ID del vehiculo a dar de baja: ");
    scanf("%d", &idBuscado);

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(aux.id == idBuscado && aux.eliminado == 0)
            {
                encontrado = 1;

                aux.eliminado = 1; // marca como eliminado

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

// MODIFICAR VEHICULO
void modificarVehiculo(char nombreArchivo[])
{
    stVehiculo aux;
    int idBuscado = 0;
    int encontrado = 0;

    mostrarVehiculos(nombreArchivo);

    printf("\nIngrese el ID del vehiculo a modificar: ");
    scanf("%d", &idBuscado);

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(aux.id == idBuscado && aux.eliminado == 0)
            {
                encontrado = 1;

                printf("Ingrese el precio nuevo: ");
                scanf("%f", &aux.precioPorDia);

                // Retroceder el cursor un struct y sobreescribir

                fseek(archi, sizeof(stVehiculo) * (-1), SEEK_CUR);

                fwrite(&aux, sizeof(stVehiculo), 1, archi);

                fseek(archi, 0, SEEK_CUR);

                printf("Precio modificado correctamente.\n");
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
void mostrarVehiculos(char nombreArchivo[])
{
    int contador = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        mostrarVehiculosRecursivamente(archi, contador);

        fclose(archi);
    }
    else
    {
        printf("\nERROR: No hay vehiculos cargados\n");
    }
}

void mostrarVehiculosRecursivamente(FILE *archi, int contador)
{
    stVehiculo aux;

    if(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
    {
        if(aux.eliminado == 0)
        {
            printf("\n\n--- Vehiculo #%d ---\n\n", contador);
            printf("ID:            %d\n",     aux.id);
            printf("Patente:       %s\n",     aux.patente);
            printf("Marca:         %s\n",     aux.marca);
            printf("Modelo:        %s\n",     aux.modelo);
            printf("Kilometraje:   %d km\n",  aux.kilometraje);
            printf("Precio/dia:    $%.2f\n",  aux.precioPorDia);

            if(aux.disponible == 0)
            {
                printf("DISPONIBLE\n");
            }
            else if(aux.disponible == 1)
            {
                printf("NO DISPONIBLE\n");
            }
        }

        mostrarVehiculosRecursivamente(archi, contador + 1);
    }
}


// Elimina el caracter de salto de linea '\n' que introduce fgets al presionar Enter
void limpiarSaltoLinea(char cadena[])
{
    int posicion = strcspn(cadena, "\n");

    cadena[posicion] = '\0';
}






















