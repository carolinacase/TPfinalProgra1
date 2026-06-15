#ifndef VEHICULOS_H_INCLUDED
#define VEHICULOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_PATENTE 8
#define DIM_STRINGS 20
#define DIM_VEHICULOS 4

typedef struct
{
    int id;
    char patente[DIM_PATENTE];
    char marca[DIM_STRINGS];
    char modelo[DIM_STRINGS];
    int kilometraje;
    float precioPorDia;
    int eliminado; // 0 = no eliminado, 1 = eliminado
    int disponible; // 0 = disponible, 1 = no disponible
} stVehiculo;

//FUNCION MENU
void menuVehiculos(char nombreArchivo[]);

//FUNCIONES PARA CARGAR VEHICULOS
void altaVehiculo(char nombreArchivo[]);
int validarPatenteEnArchivo(char nombreArchivo[], char dominio[]);
void cargarVehiculo(stVehiculo *aux);
int contarVehiculosEnArchivo(char nombreArchivo[]);
int obtenerNuevoId(char nombreArchivo[]);

//FUNCION PARA ELIMINAR VEHICULO
void bajaVehiculo(char nombreArchivo[]);

//FUNCION PARA MODIFICAR VEHICULO
void modificarVehiculo(char nombreArchivo[]);

//FUNCIONES PARA MOSTRAR VEHICULOS
void mostrarVehiculos(char nombreArchivo[]);
void mostrarVehiculosRecursivamente(FILE *archi, int contador);

//FUNCIONES EXTRAS
void limpiarSaltoLinea(char cadena[]);

#endif // VEHICULOS_H_INCLUDED
