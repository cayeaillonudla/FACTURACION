#include <stdio.h>
#include "funciones.h"
#include <string.h>

int main (int argc, char *argv[]) {
    printf("Bienvenido al sistema de facturacion\n");
    int opciones;
    do{
        printf("1. Crear factura\n");
        printf("2. Leer facturas\n");
        printf("3. Actualizar factura\n");
        printf("4. Eliminar factura\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opciones);
        switch(opciones){
            case 1:
                createFactura();
                break;
            case 2:
                readFactura();
                break;
            case 3:
                updateFactura();
                break;  
            case 4:
                deleteFactura();
                break;
            case 5:
                printf("Gracias por usar el sistema de facturacion\n");
                break;  
            default:
                printf("Opcion invalida\n");
                break;
        }
    }while(opciones != 5);
}