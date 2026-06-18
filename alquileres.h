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
int obtenerNuevoIdAlquiler(char nombreArchivo[]);
void cargarAlquiler(stAlquiler *aux, int *diasAlquilados);
float obtenerPrecioPorDia(char nombreArchivo[], char patenteBuscada[]);

























#endif
