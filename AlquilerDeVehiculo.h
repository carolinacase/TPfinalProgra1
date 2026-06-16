#ifndef ALQUILERDEVEHICULO_H_INCLUDED
#define ALQUILERDEVEHICULO_H_INCLUDED

typedef struct {
    char dniCliente[10];
    char patenteVehiculo[8];
    char fechaInicio[12];
    char fechaFin[12];
    float costoPorDia;
    float costoTotal;
    int activo;
} stAlquiler;


#endif // ALQUILERDEVEHICULO_H_INCLUDED
