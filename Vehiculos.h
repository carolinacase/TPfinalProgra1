#ifndef VEHICULOS_H_INCLUDED
#define VEHICULOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_PATENTE 8
#define DIM_STRINGS 30
#define DIM_VEHICULOS 20

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

// Vehiculos
void menuVehiculos(char nombreArchivo[], stVehiculo vehiculos[]);
int contarVehiculosEnArchivo(char nombreArchivo[]);
int cargarVehiculo(stVehiculo vehiculos[], int dimension, char nombreArchivo[]);
int obtenerNuevoId(char nombreArchivo[]);
void altaVehiculo(char nombreArchivo[], stVehiculo vehiculos[]);
void bajaVehiculo(char nombreArchivo[]);
void MostrarVehiculos(char nombreArchivo[]);
void modificarVehiculo(char nombreArchivo[]);


#endif // VEHICULOS_H_INCLUDED
