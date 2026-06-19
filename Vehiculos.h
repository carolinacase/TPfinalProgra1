#ifndef VEHICULOS_H_INCLUDED
#define VEHICULOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_PATENTE 8
#define DIM_STRINGS 20
#define DIM_VEHICULOS 10

typedef struct
{
    int id;
    char patente[DIM_PATENTE];
    char tipo[DIM_STRINGS];
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
void ingresarTipoVehiculo(char destino[]);
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

//FUNCIONES PARA BUSCAR Y MOSTRAR VEHICULO
void buscarYMostrarVehiculo(char nombreArchivo[]);
void mostrarUnVehiculo(stVehiculo aux);

//FUNCION MENU LISTAR
void menuOrdenacionVehiculos(char nombreArchivo[]);

//FUNCION PARA COPIAR ARCHIVO AL ARREGLO
int copiarArchiAArreglo(char nombreArchivo[], stVehiculo arreglo[], int dimension);

//FUNCION PARA ORDENAR UN ARREGLO POR SELECCION
int buscarMenor(stVehiculo arregloSeleccion[], int i, int validos);
void ordenarArregloSeleccion(stVehiculo arregloSeleccion[], int validos);

//FUNCION PARA ORDENAR UN ARREGLO POR INSERCION
void insertar(stVehiculo arregloInsercion[], int posInicial, stVehiculo dato);
void ordenarArregloInsercion(stVehiculo arregloInsercion[], int validos);

//FUNCION PARA MOSTRAR UN ARREGLO
void mostrarArregloVehiculos(stVehiculo arreglo[], int validos);

//FUNCIONES EXTRAS
void limpiarSaltoLinea(char cadena[]);
void mostrarPatentesDisponiblesPorTipo(char nombreArchivo[], char tipoBuscado[]);
int verificarVehiculoPorPatenteYTipo(char nombreArchivo[], char patenteBuscada[], char tipoBuscado[]);
void cambiarDisponibilidadVehiculo(char nombreArchivo[], char patenteBuscada[], int nuevoEstado);

#endif // VEHICULOS_H_INCLUDED
