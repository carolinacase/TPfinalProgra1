#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct
{
    char nombre[DIM_STRINGS];
    char apellido[DIM_STRINGS];
    char dni[10];
    char telefono[20];
    int activo;
} stCliente;


// Clientes
stCliente cargarDatosDelCliente();
void altaCliente(char nombreArchivo[]);
void MostrarClientes(char nombreArchivo[]);



#endif // CLIENTES_H_INCLUDED
