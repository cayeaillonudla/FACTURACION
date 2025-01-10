#ifndef FUNCIONES_H
#define FUNCIONES_H

struct Producto {
    char nombre[50];
    int cantidad;
    float precio;
};

struct Factura {
    char nombre[20];
    int cedula;
    int nProductos; 
    struct Producto productos[5];
    float total; 
    int estado;
};

void createFactura();
void saveFactura(struct Factura *factura);
void leerCadena(char *cadena, int longitud);
void readFactura();
void updateFactura();
int findByCedula(int cedula);
void deleteFactura();
#endif 