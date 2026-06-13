#ifndef VEHICULOS_H_INCLUDED
#define VEHICULOS_H_INCLUDED


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
stVehiculo cargarVehiculo(char nombreArchivo[]);
void menuVehiculos(char nombreArchivo[]);
int obtenerNuevoId(char nombreArchivo[]);
void altaVehiculo(char nombreArchivo[]);
void bajaVehiculo(char nombreArchivo[]);
void MostrarVehiculos(char nombreArchivo[]);
void modificarVehiculo(char nombreArchivo[]);


#endif // VEHICULOS_H_INCLUDED
