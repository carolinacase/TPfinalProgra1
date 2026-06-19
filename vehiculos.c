#include "Vehiculos.h"
// ------------------------------FUNCIONES DE VEHICULOS---------------------------------

void menuVehiculos(char nombreArchivo[])
{
    int opcion;

    do
    {
        printf("===================================\n");
        printf("       GESTION DE VEHICULOS        \n");
        printf("===================================\n");
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
            buscarYMostrarVehiculo(nombreArchivo);
            break;
        case 5:
            menuOrdenacionVehiculos(nombreArchivo);
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

                // Funcion para convertir a mayusculas la patente ingresada
                strupr(dominio);

                patenteRepetidaArchivo = validarPatenteEnArchivo(nombreArchivo, dominio);

                if(patenteRepetidaArchivo == 1)
                {
                    printf("PATENTE YA CARGADA, INGRESE OTRA\n");
                }
            }
            while(patenteRepetidaArchivo == 1);
            //---------------------------------------------------------------

            strcpy(aux.patente, dominio);

            ingresarTipoVehiculo(aux.tipo);

            cargarVehiculo(&aux);

            aux.id = obtenerNuevoId(nombreArchivo);

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

void ingresarTipoVehiculo(char destino[])
{
    int opcion;

    char tiposVehiculos[3][DIM_STRINGS] = {"Sedan","SUV","Pick-Up"};

    do
    {
        printf("\n\n======TIPOS DE VEHICULOS======\n");
        printf("1.%s\n", tiposVehiculos[0]);
        printf("2.%s\n", tiposVehiculos[1]);
        printf("3.%s\n", tiposVehiculos[2]);

        printf("Que tipo de vehiculo desea ingresar (1-3): ");
        scanf("%d", &opcion);

        if(opcion < 1 || opcion > 3)
        {
            printf("Opcion incorrecta. Intente nuevamente\n");
        }
        else
        {
            printf("Tipo de vehiculo seleccionado: %s\n", tiposVehiculos[opcion - 1]);
        }
    }
    while(opcion < 1 || opcion > 3);

    strcpy(destino, tiposVehiculos[opcion - 1]);
}

// CARGA LOS DATOS DE UN VEHICULO POR TECLADO
void cargarVehiculo(stVehiculo *aux)
{
    printf("Ingrese la marca: ");
    fflush(stdin);
    fgets(aux->marca, DIM_STRINGS, stdin);
    limpiarSaltoLinea(aux->marca);
    strupr(aux->marca);

    printf("Ingrese el modelo: ");
    fflush(stdin);
    fgets(aux->modelo, DIM_STRINGS, stdin);
    limpiarSaltoLinea(aux->modelo);
    strupr(aux->modelo);

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

    return maxId + 1;
}

// BAJA LOGICA
void bajaVehiculo(char nombreArchivo[])
{
    int idBuscado, encontrado = 0;
    stVehiculo aux;

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
}

// MODIFICAR VEHICULO
void modificarVehiculo(char nombreArchivo[])
{
    stVehiculo aux;
    int idBuscado = 0;
    int encontrado = 0;

    mostrarVehiculos(nombreArchivo);

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
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
            }
        }
        fclose(archi);

        if(encontrado == 0)
        {
            printf("No se encontro ningun vehiculo activo con ID %d.\n", idBuscado);
        }
    }
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
        if(aux.eliminado == 1)
        {
            contador = contador - 1;
        }

        if(contador <= 0)
        {
            contador = 1;
        }

        if(aux.eliminado == 0)
        {
            printf("\n\n---- Vehiculo #%d ----\n\n", contador);
            printf("ID:               %d\n", aux.id);
            printf("Patente:          %s\n", aux.patente);
            printf("Tipo de vehiculo: %s\n", aux.tipo);
            printf("Marca:            %s\n", aux.marca);
            printf("Modelo:           %s\n", aux.modelo);
            printf("Kilometraje:      %d km\n", aux.kilometraje);
            printf("Precio/dia:       $%.2f\n", aux.precioPorDia);

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

        // Funcion para convertir a mayusculas la patente ingresada
        strupr(patenteBuscada);

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
    else
    {
        printf("\nERROR: No hay vehiculos cargados\n");
    }
}

void mostrarUnVehiculo(stVehiculo aux)
{
    printf("\n--- VEHICULO ENCONTRADO ---\n");
    printf("ID:               %d\n", aux.id);
    printf("Patente:          %s\n", aux.patente);
    printf("Tipo de vehiculo: %s\n", aux.tipo);
    printf("Marca:            %s\n", aux.marca);
    printf("Modelo:           %s\n", aux.modelo);
    printf("Kilometraje:      %d km\n", aux.kilometraje);
    printf("Precio/dia:       $%.2f\n", aux.precioPorDia);

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
        printf("\nERROR: No hay vehiculos cargados\n");
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
            printf("ID:               %d\n", arreglo[i].id);
            printf("Patente:          %s\n", arreglo[i].patente);
            printf("Tipo de vehiculo: %s\n", arreglo[i].tipo);
            printf("Marca:            %s\n", arreglo[i].marca);
            printf("Modelo:           %s\n", arreglo[i].modelo);
            printf("Kilometraje:      %d km\n", arreglo[i].kilometraje);
            printf("Precio/dia:       $%.2f\n", arreglo[i].precioPorDia);

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

//MUESTRA LAS PATENTES DE LOS VEHICULOS DISPONIBLES
void mostrarPatentesDisponiblesPorTipo(char nombreArchivo[], char tipoBuscado[])
{
    stVehiculo aux;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0)
        {
            if(strcmp(aux.tipo, tipoBuscado) == 0 && aux.eliminado == 0 && aux.disponible == 0)
            {
                printf("\nPatente de vehiculo disponible: |%s|\n", aux.patente);
            }
        }
    }
    else
    {
        printf("\nERROR: No hay vehiculos cargados\n");
    }
}

//VALIDAR PATENTE POR TIPO DE VEHICULO
int verificarVehiculoPorPatenteYTipo(char nombreArchivo[], char patenteBuscada[], char tipoBuscado[])
{
    stVehiculo aux;

    int estado = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && estado == 0)
        {
            if(strcmp(patenteBuscada, aux.patente) == 0 && strcmp(tipoBuscado, aux.tipo) == 0 && aux.eliminado == 0)
            {
                if(aux.disponible == 0)
                {
                    estado = 1;
                }
                else
                {
                    estado = -1;
                }
            }
        }
        fclose(archi);
    }

    return estado;
}

//CAMBIAR EL CAMPO DISPONIBLE SI SE ALQUILO ESE AUTO
void cambiarDisponibilidadVehiculo(char nombreArchivo[], char patenteBuscada[], int nuevoEstado)
{
    stVehiculo aux;
    int encotrado = 0;

    FILE *archi = NULL;

    archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stVehiculo), 1, archi) > 0 && encotrado == 0)
        {
            if(strcmp(aux.patente, patenteBuscada) == 0 && aux.eliminado == 0)
            {
                aux.disponible = nuevoEstado;

                encotrado = 1;

                fseek(archi, (-1) * sizeof(stVehiculo), SEEK_CUR);

                fwrite(&aux, sizeof(stVehiculo), 1, archi);

                fseek(archi, 0, SEEK_CUR);
            }
        }
        fclose(archi);
    }
}























