#include "Clientes.h"

void menuClientes(char nombreArchivo[])
{
    int opcion;
    char dniBuscado[DIM_DNI];
    char dniModificar[DIM_DNI];
    char nuevoTel[DIM_DNI];
    char dniEncontrado[DIM_DNI];

    do
    {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Alta de cliente\n"); //
        printf("2. Mostrar clientes\n");
        printf("3. Dar de baja un cliente\n");
        printf("4. Modificar Contacto\n");
        printf("5. Buscar Cliente por DNI\n");
        printf("0. Volver al menu principal\n");
        printf("Ingrese una opcion:\n");
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
            consultarCliente(nombreArchivo, dniBuscado);
            break;
        case 6:
            listarClientesAlfabetico(nombreArchivo);
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

////○ Verificar de no cargar repetidos


void altaCliente(char nombreArchivo[]) //Falta verificacion de carga repetida
{
    stCliente nuevo = cargarDatosDelCliente();////● Carga de Datos

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        fwrite(&nuevo, sizeof(stCliente), 1, archi); //Escribe en el archivo
        fclose(archi);
        printf("Cliente dado de alta correctamente.\n");////○ Alta
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
    }

    close(archi);////● Guardar en Archivo
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
//○ Consulta
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
//(campo a elegir de acuerdo a las structs elegidas)
//● Listar todos los datos por orden numérico por el método de inserción
//(campo a elegir de acuerdo a las structs elegidas)
//● Como opcional, y de forma adicional a lo anterior, pueden listar sólo los que
//cumplan cierto criterio (listados con filtro - por ejemplo: todos los productos de
//cierta categoría, todos los alumnos con nota del 6 al 8, etc)

void PasarClientesAunArreglo(char nombreArchivo[])
{
    stCliente arreglo[MAX_CLIENTES];
    int cantidad = 0;
    stCliente aux;

    // Cargar clientes activos en el arreglo
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0 && cantidad < MAX_CLIENTES)
        {
            if(aux.activo == 1)
            {
                arreglo[cantidad] = aux;
                cantidad++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error: no se pudo abrir el archivo.\n");
        return;
    }

    if(cantidad == 0)
    {
        printf("No hay clientes registrados.\n");
        return;
    }



}
int OrdenarClientesPorSeleccion()
{
    // Ordenar por apellido - metodo seleccion
    int i, j, minPos;
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

void mostrarArrDeClientes()
{
    printf("\n--- CLIENTES ORDENADOS ALFABETICAMENTE ---\n");
    for(i = 0; i < cantidad; i++)
        mostrarUnCliente(arreglo[i]);
}
