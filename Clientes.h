#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_STRINGS 50
#define DIM_DNI 10

typedef struct
{
    char nombre[DIM_STRINGS];
    char apellido[DIM_STRINGS];
    char dni[10];
    char telefono[20];
    int activo;
} stCliente;

// Prototipos
stCliente cargarDatosDelCliente();
void altaCliente(char nombreArchivo[]);
void MostrarClientes(char nombreArchivo[]);
void menuClientes(char nombreArchivo[]);
void DarDeBajaUnCliente(char nombreArchivo[], char dniBuscado[]);
void modificarTelefonoCliente(char nombreArchivo[], char dniBuscado[], char nuevoTelefono[]);
void consultarCliente(char nombreArchivo[], char dniBuscado[]);

#endif // CLIENTES_H_INCLUDED
