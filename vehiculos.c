<<<<<<< HEAD

=======
#include "Vehiculos.h"
>>>>>>> main
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
<<<<<<< HEAD
        printf("0. Salir\n");
=======
        printf("6. Mostrar Vehiculos\n");
        printf("0. Volver al menu principal\n");
>>>>>>> main

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
<<<<<<< HEAD
            MostrarVehiculos(nombreArchivo);
            break;
        case 4:
            modificarVehiculo(nombreArchivo);
            break;
        case 5:
        //OrdenarPorInsercion(nombreArchivo);
        case 0:
            printf("Salir\n");
=======
            modificarVehiculo(nombreArchivo);
            break;
        case 4:
            buscarYMostrarVehiculo(nombreArchivo);
            break;
        case 5:
            menuOrdenacionVehiculos(nombreArchivo);
            break;
        case 6:
            mostrarVehiculos(nombreArchivo);
            break;
        case 0:
>>>>>>> main
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
<<<<<<< HEAD
=======
        system("pause");
        system("cls");
>>>>>>> main
    }
    while(opcion != 0);
}

<<<<<<< HEAD
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
=======
// ALTA: GUARDA UN VEHICULO NUEVO EN EL ARCHIVO
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

// CARGA LOS DATOS DE UN VEHICULO POR TECLADO
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

//CONTAR LOS VEHICULOS QUE HAY EN EL ARCHIVO
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

// GENERA UN ID QUE SE INCREMENTA BUSCANDO EL ULTIMO EN EL ARCHIVO
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

// BAJA LOGICA
>>>>>>> main
void bajaVehiculo(char nombreArchivo[])
{
    int idBuscado, encontrado = 0;
    stVehiculo aux;

<<<<<<< HEAD
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
=======
    mostrarVehiculos(nombreArchivo);

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        printf("Ingrese el ID del vehiculo a dar de baja: ");
        scanf("%d", &idBuscado);

        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(aux.id == idBuscado && aux.eliminado == 0)
            {
                encontrado = 1;

                aux.eliminado = 1; // marca como eliminado
>>>>>>> main

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
<<<<<<< HEAD
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
=======
}

// MODIFICAR VEHICULO
void modificarVehiculo(char nombreArchivo[])
{
    stVehiculo aux;
    int idBuscado = 0;
    int encontrado = 0;

    mostrarVehiculos(nombreArchivo);
>>>>>>> main

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
<<<<<<< HEAD
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
=======
        printf("\nIngrese el ID del vehiculo a modificar: ");
        scanf("%d", &idBuscado);

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
>>>>>>> main
            }
        }
        fclose(archi);

        if(encontrado == 0)
            printf("No se encontro ningun vehiculo activo con ID %d.\n", idBuscado);
    }
<<<<<<< HEAD
=======
}

//MOSTRAR VEHICULOS
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

//BUSCAR Y MOSTRAR VEHICULO
void buscarYMostrarVehiculo(char nombreArchivo[])
{
    stVehiculo aux;
    char patenteBuscada[DIM_PATENTE];
    int encontrado = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        printf("Ingrese la patente a buscar: ");
        getchar();
        fgets(patenteBuscada, DIM_PATENTE, stdin);
        limpiarSaltoLinea(patenteBuscada);

        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encontrado == 0)
        {
            if(strcmp(aux.patente, patenteBuscada) == 0 && aux.eliminado == 0)
            {
                encontrado = 1;

                mostrarUnVehiculo(aux);
            }
        }
        fclose(archi);

        if(encontrado == 0)
        {
            printf("\nNo se encontro ningun vehiculo activo con la patente: %s\n", patenteBuscada);
        }
    }
>>>>>>> main
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
<<<<<<< HEAD
=======

void mostrarUnVehiculo(stVehiculo aux)
{
    printf("\n--- VEHICULO ENCONTRADO ---\n");
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

//MENU DE LISTAR
void menuOrdenacionVehiculos(char nombreArchivo[])
{
    int opcion;

    stVehiculo arregloOrdenSeleccion[DIM_VEHICULOS];
    stVehiculo arregloOrdenInsercion[DIM_VEHICULOS];

    int validosSeleccion = copiarArchiAArreglo(nombreArchivo, arregloOrdenSeleccion, DIM_VEHICULOS);

    int validosInsercion = copiarArchiAArreglo(nombreArchivo, arregloOrdenInsercion, DIM_VEHICULOS);

    if(validosSeleccion > 0 && validosInsercion > 0)
    {
        do
        {
            printf("\n--- MENU DE ORDENACION Y LISTADOS ---\n");
            printf("1. Listar por marca (Orden alfabetico - Seleccion)\n");
            printf("2. Listar por precio por dia (Menor a mayor - Insercion)\n");
            printf("0. Volver al menu anterior\n");

            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);

            switch(opcion)
            {
            case 1:
                ordenarArregloSeleccion(arregloOrdenSeleccion, validosSeleccion);
                mostrarArregloVehiculos(arregloOrdenSeleccion, validosSeleccion);
                break;
            case 2:
                ordenarArregloInsercion(arregloOrdenInsercion, validosInsercion);
                mostrarArregloVehiculos(arregloOrdenInsercion, validosInsercion);
                break;
            case 0:
                break;
            default:
                printf("\nOpcion incorrecta\n.");
                break;
            }
            system("pause");
            system("cls");
        }
        while(opcion != 0);
    }
    else
    {
        printf("\nNo hay vehiculos registrados activos en el sistema para ordenar.\n");
    }
}

//COPIAR ARCHIVO A ARREGLOS
int copiarArchiAArreglo(char nombreArchivo[], stVehiculo arreglo[], int dimension)
{
    stVehiculo aux;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    int validos = 0;

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && validos < dimension)
        {
            if(aux.eliminado == 0)
            {
                arreglo[validos] = aux;

                validos++;
            }
        }
        fclose(archi);
    }

    return validos;
}

//ORDENAR POR SELECCION
int buscarMenor(stVehiculo arregloSeleccion[], int i, int validos)
{
    int posMenor = i;

    for(int x = i + 1; x < validos; x++)
    {
        if(strcmp(arregloSeleccion[posMenor].marca, arregloSeleccion[x].marca) > 0)
        {
            posMenor = x;
        }
    }

    return posMenor;
}

void ordenarArregloSeleccion(stVehiculo arregloSeleccion[], int validos)
{
    stVehiculo aux;
    int posMenor;

    for(int i = 0; i < validos - 1; i++)
    {
        posMenor = buscarMenor(arregloSeleccion, i, validos);

        aux = arregloSeleccion[posMenor];

        arregloSeleccion[posMenor] = arregloSeleccion[i];

        arregloSeleccion[i] = aux;
    }
}

//ORDENAR POR INSERCION
void insertar(stVehiculo arregloInsercion[], int posInicial, stVehiculo dato)
{
    int i = posInicial;

    while(i >= 0 && dato.precioPorDia < arregloInsercion[i].precioPorDia)
    {
        arregloInsercion[i + 1] = arregloInsercion[i];

        i--;
    }

    arregloInsercion[i + 1] = dato;
}

void ordenarArregloInsercion(stVehiculo arregloInsercion[], int validos)
{
    int i = 0;

    while(i < validos - 1)
    {
        insertar(arregloInsercion, i, arregloInsercion[i + 1]);

        i++;
    }
}

//MOSTRAR ARREGLO
void mostrarArregloVehiculos(stVehiculo arreglo[], int validos)
{
    if(validos == 0)
    {
        printf("\nNo hay vehiculos para listar.\n");
    }
    else
    {
        for(int i = 0; i < validos; i++)
        {
            printf("\n\n--- Vehiculo #%d ---\n\n", i + 1);
            printf("ID:            %d\n",     arreglo[i].id);
            printf("Patente:       %s\n",     arreglo[i].patente);
            printf("Marca:         %s\n",     arreglo[i].marca);
            printf("Modelo:        %s\n",     arreglo[i].modelo);
            printf("Kilometraje:   %d km\n",  arreglo[i].kilometraje);
            printf("Precio/dia:    $%.2f\n",  arreglo[i].precioPorDia);

            if(arreglo[i].disponible == 0)
            {
                printf("DISPONIBLE\n");
            }
            else if(arreglo[i].disponible == 1)
            {
                printf("NO DISPONIBLE\n");
            }
        }
        printf("\n");
    }
}

// Elimina el caracter de salto de linea '\n' que introduce fgets al presionar Enter
void limpiarSaltoLinea(char cadena[])
{
    int posicion = strcspn(cadena, "\n");

    cadena[posicion] = '\0';
}






















>>>>>>> main
