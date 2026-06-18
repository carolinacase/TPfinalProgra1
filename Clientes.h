#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_STRINGS 50
#define DIM_DNI 10
#define MAX_CLIENTES 100

typedef struct
{
    char nombre[DIM_STRINGS];
    char apellido[DIM_STRINGS];
    char dni[10];
    char telefono[20];
    int activo;
} stCliente;

void menuClientes(char nombreArchivo[]);
//FUNCIONES PARA CARGA DE CLIENTES
stCliente cargarDatosDelCliente();
int altaCliente(char nombreArchivo[]);
int ValidarClienteExistente (char nombreArchivo[], char dni[]);

//FUNCIONES PARA MOSTRAR
void mostrarUnCliente(stCliente unCliente);
void MostrarClientes(char nombreArchivo[]);
//-----------PARA ARREGLO------------
void mostrarArrDeClientes(stCliente arreglo[], int cantidad);

// FUNCION PARA REALIZAR BAJA LOGICA DE UN CLIENTE
void DarDeBajaUnCliente(char nombreArchivo[], char dniBuscado[]);

//FUNCION PARA MODIFICAAR UN CAMPO DEL CLIENTE
void modificarTelefonoCliente(char nombreArchivo[], char dniBuscado[], char nuevoTelefono[]);

//FUNCION PARA BUSCAR UN CLIENTE POR DNI
void consultarCliente(char nombreArchivo[], char dniBuscado[]);

//FUNCION PARA PASAR LOS CLIENTES EXISTENTES EN EL ARCHIVO A UN ARREGLO DINAMICO
int PasarClientesAunArreglo(char nombreArchivo[], stCliente **arreglo);

//FUNCION PARA ORDENAR A LOS CLIENTES ALFABETICAMENTE (CON SELECCION)
void OrdenarClientesPorSeleccion(stCliente arreglo[], int cantidad);

//FUNCION PARA ORDENAR A LOS CLIENTES POR DNI (CON INSERCION)
void insertarDato(stCliente arreglo[], int ultPos, stCliente dato);
void ordenarArregloPorInsercion(stCliente arreglo[], int cantidad);

#endif // CLIENTES_H_INCLUDED
