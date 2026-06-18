#ifndef ALQUILERES_H_INCLUDED
#define ALQUILERES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vehiculos.h"
#include "Clientes.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
} stFecha;

typedef struct
{
    int id;               // ID autoincremental del alquiler
    char dniCliente[DIM_DNI];
    char patente[DIM_PATENTE];
    stFecha fechaInicio;
    stFecha fechaFin;
    float costoTotal;     // Calculado: dias * precioPorDia del vehiculo
    int eliminado;        // 0 = Activo, 1 = Cancelado o Finalizado
} stAlquiler;

//FUNCION MENU
void menuAlquileres(char archivoAlquileres[], char archivoVehiculos[], char archivoClientes[]);

//FUNCIONES PARA CARGAR UN ALQUILER
int solicitarYValidarCliente(char archivoClientes[], char destinoDni[]);
int solicitarYValidarVehiculo(char archivoVehiculos[], char destinoPatente[]);
stFecha calcularFechaFin(stFecha inicio, int diasAlquilados);
int obtenerNuevoIdAlquiler(char nombreArchivo[]);
void cargarAlquiler(stAlquiler *aux, int *diasAlquilados);
float obtenerPrecioPorDia(char nombreArchivo[], char patenteBuscada[]);

//FUNCION PARA DAR DE BAJA
void bajaAlquiler(char nombreArchivo[]);

//FUNCION PARA MOSTRAR
void mostrarAlquileres(char nombreArchivo[]);
void mostrarAlquileresRecursivamente(FILE *archi);

#endif
