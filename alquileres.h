#ifndef ALQUILERES_H_INCLUDED
#define ALQUILERES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehiculos.h"

typedef struct {
    char dniCliente[10];
    char patenteVehiculo[8];
    char fechaInicio[12];
    char fechaFin[12];
    float costoPorDia;
    float costoTotal;
    int activo;
} stAlquiler;

//FUNCION MENU
void menuAlquileres(char archivoAlquileres[]);

//


























#endif
