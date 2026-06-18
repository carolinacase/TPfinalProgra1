#include "Clientes.h"

void menuClientes(char nombreArchivo[])
{
    int opcion;
    int validos;
    char dniBuscado[DIM_DNI];
    char dniModificar[DIM_DNI];
    char nuevoTel[DIM_DNI];
    char dniEncontrado[DIM_DNI];
    int cantidad = 0;
    stCliente *arreglo = NULL; //puntero inicializado para utilizar en Realloc

    do
    {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Alta de cliente\n"); //
        printf("2. Mostrar clientes\n");
        printf("3. Dar de baja un cliente\n");
        printf("4. Modificar Contacto\n");
        printf("5. Buscar Cliente por DNI\n");
        printf("6. Ordenar Alfabeticamente (Con Seleccion)\n");
        printf("0. Volver al menu principal\n");
        printf("Ingrese una opcion:\n");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            validos = altaCliente(nombreArchivo);
            break;
        case 2:
            MostrarClientes(nombreArchivo);
            break;
        case 3:
            printf("Ingrese el DNI del cliente que desea dar de baja:\n");
            fflush(stdin);
            scanf("%s", dniBuscado);
            DarDeBajaUnCliente(nombreArchivo, dniBuscado);
            break;

        case 4:
            printf("Ingrese el DNI del cliente a modificar:\n");
            fflush(stdin);
            scanf("%s", dniModificar);
            printf("Ingrese el nuevo telefono: ");
            fflush(stdin);
            scanf("%s", nuevoTel);
            modificarTelefonoCliente(nombreArchivo, dniModificar, nuevoTel);
            break;
        case 5:
            printf("Ingrese el DNI del cliente para buscar:\n");
            fflush(stdin);
            scanf("%s", dniEncontrado);
            consultarCliente(nombreArchivo, dniEncontrado);
            break;
        case 6:
        {
            int opcionOrden;
            printf("\n--- ORDENAR CLIENTES ---\n");
            printf("1. Ordenar alfabeticamente por apellido (seleccion)\n");
            printf("2. Ordenar por numero de DNI (insercion)\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcionOrden);
            cantidad = PasarClientesAunArreglo(nombreArchivo, &arreglo);

            if(cantidad > 0)
            {
                if(opcionOrden == 1)
                    OrdenarClientesPorSeleccion(arreglo, cantidad);
                else if(opcionOrden == 2)
                    ordenarArregloPorInsercion(arreglo, cantidad);

                mostrarArrDeClientes(arreglo, cantidad);
                free(arreglo);
            }
            else
                printf("No hay clientes registrados.\n");
        }
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
    char confirmacion;

    do
    {
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

        mostrarUnCliente(cliente);

        printf("Seguro que los datos son correctos? (s/n):\n");
        fflush(stdin);
        scanf(" %c", &confirmacion);

    }
    while(confirmacion != 's' && confirmacion != 'S');

    cliente.activo = 1;
    return cliente;
}

int altaCliente(char nombreArchivo[])
{
    stCliente nuevo;
    int cantidad = 0;
    int validarCliente;

    do
    {
        nuevo = cargarDatosDelCliente();  ////● Carga de Datos
        validarCliente = ValidarClienteExistente (nombreArchivo,nuevo.dni); ////○ Verificar de no cargar repetidos

        if(validarCliente == 1)
        {
            printf("El cliente que desea ingresar YA EXISTE en el sistema. Ingrese otro.\n");
        }

    }
    while(validarCliente == 1);

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL && (validarCliente == 0))
    {
        fwrite(&nuevo, sizeof(stCliente), 1, archi);//Escribe en el archivo

        printf("Cliente dado de alta correctamente.\n");////○ Aviso de Alta
        cantidad++;
        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }

    return cantidad;
}

int ValidarClienteExistente (char nombreArchivo[], char dni[])
{
    stCliente aux;
    int encontrado = 0;

    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0 && encontrado == 0)
        {
            if((strcmp(aux.dni, dni) == 0) && aux.activo == 1)
                encontrado = 1;
        }
        fclose(archi);
    }
    return encontrado;
}

//-------------------------MOSTRAR CLIENTES-------------------------
void mostrarUnCliente(stCliente unCliente)
{
    printf("-----------DATOS DEL CLIENTE-----------\n");
    printf("  Nombre:    %s %s\n", unCliente.nombre, unCliente.apellido);
    printf("  DNI:       %s\n", unCliente.dni);
    printf("  Telefono:  %s\n", unCliente.telefono);
    printf("---------------------------------------\n");

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

void DarDeBajaUnCliente(char nombreArchivo[], char dniBuscado[]) //No esta muy justificado porque deberiamos borrar un cliente, pero si es necesario existe
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
//○ Modificación

//----------------------MODIFICAR TELEFONO DEL CLIENTE -----------------
//los demas datos no deberian ser modificados ya que dni y nombre del cliente no deberian cambiarse

void modificarTelefonoCliente(char nombreArchivo[], char dniBuscado[], char nuevoTelefono[])
{
    int dniEncontrado = 0;
    stCliente aux;

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0 && dniEncontrado == 0)
        {
            if(strcmp(aux.dni, dniBuscado) == 0 && aux.activo == 1) //● Buscar dato
            {
                dniEncontrado = 1;
                strcpy(aux.telefono, nuevoTelefono);
                fseek(archi, sizeof(stCliente) * (-1), SEEK_CUR); //● Modificar dato
                fwrite(&aux, sizeof(stCliente), 1, archi);
                printf("Telefono modificado correctamente.\n");
            }
        }
        fclose(archi);//● Guardar el dato modificado en el archivo

        if(dniEncontrado == 0)
            printf("No se encontro ningun cliente con ese DNI.\n");
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}
//○---------------------------Consulta
//● Buscar una struct en particular de acuerdo a uno o varios campos a elección
//del usuario del sistema y mostrar los distintos campos de la struct (por ejemplo:
//buscar un empleado por su dni)

void consultarCliente(char nombreArchivo[], char dniBuscado[])
{
    int dniEncontrado = 0;
    stCliente aux;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0 && dniEncontrado == 0)
        {
            if(strcmp(aux.dni, dniBuscado) == 0 && aux.activo == 1)
            {
                dniEncontrado = 1;
                mostrarUnCliente(aux); //(búsqueda de un dato en particular y mostrado del mismo)
            }
        }
        fclose(archi);

        if(dniEncontrado == 0)
            printf("No se encontro ningun cliente con ese DNI.\n");
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
}

//○------------------------------ Listados --------------------------------
//● Listar todos los datos por orden alfabético por el método de selección
//(campo a elegir de acuerdo a las structs elegidas)int PasarClientesAunArreglo(char nombreArchivo[], stCliente **arreglo)
int PasarClientesAunArreglo(char nombreArchivo[], stCliente **arreglo)
{
    int cantidad = 0;
    stCliente aux;

    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.activo == 1)
            {
                *arreglo = realloc(*arreglo, (cantidad + 1) * sizeof(stCliente));
                (*arreglo)[cantidad] = aux;
                cantidad++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }
    return cantidad;
}
// Ordenar por apellido - metodo seleccion

void OrdenarClientesPorSeleccion(stCliente arreglo[], int cantidad)
{
    int i;
    int j;
    int minPos;
    stCliente temp;

    for(i = 0; i < cantidad - 1; i++)
    {
        minPos = i;
        for(j = i + 1; j < cantidad; j++)
        {
            if(strcmp(arreglo[j].apellido, arreglo[minPos].apellido) < 0)
                minPos = j;
        }
        if(minPos != i)
        {
            temp = arreglo[i];
            arreglo[i] = arreglo[minPos];
            arreglo[minPos] = temp;
        }
    }
}

void mostrarArrDeClientes(stCliente arreglo[], int cantidad)
{
    printf("\n--- CLIENTES ORDENADOS ALFABETICAMENTE ---\n");
    int i;
    for(i = 0; i < cantidad; i++)
        mostrarUnCliente(arreglo[i]);
}

//● Listar todos los datos por orden numérico por el método de inserción
//(campo a elegir de acuerdo a las structs elegidas)

//Ordenar por insercion - en relacion a su numero de Dni (ordena clientes de menores a mayores)

void ordenarArregloPorInsercion(stCliente arreglo[], int cantidad)
{
    int i = 1;
    while(i < cantidad)
    {
        insertar(arreglo, i-1, arreglo[i]);
        i++;
    }
}

void insertarDato(stCliente arreglo[], int ultPos, stCliente dato)
{
    int i = ultPos;
    while(i >= 0 && strcmp(dato.dni, arreglo[i].dni) < 0)
    {
        arreglo[i+1] = arreglo[i];
        i--;
    }
    arreglo[i+1] = dato;
}
//● Como opcional, y de forma adicional a lo anterior, pueden listar sólo los que
//cumplan cierto criterio (listados con filtro - por ejemplo: todos los productos de
//cierta categoría, todos los alumnos con nota del 6 al 8, etc)
