#include <stdio.h>
#include <string.h>
#include "funciones.h"


void saveFactura(struct Factura *factura){
    FILE *archivo;
    archivo = fopen("facturas.dat", "ab+");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }else{
        fwrite(factura, sizeof(struct Factura), 1, archivo);
        printf("Factura guardada con exito\n");
    }

    fclose(archivo);
}

void leerCadena(char *cadena, int longitud){
    fflush(stdin);
    fgets(cadena, longitud, stdin);
    int len = strlen(cadena)-1;
    cadena[len] = '\0';
}

void createFactura() {
    struct Factura factura;
    factura.total = 0; 
    factura.estado = 1; 

    printf("Ingrese el nombre del cliente: ");
    leerCadena(factura.nombre, 20); 

    printf("Ingrese la cedula del cliente: ");
    while (scanf("%d", &factura.cedula) != 1 || factura.cedula <= 0) {
        printf("Cedula invalida. Ingrese un numero positivo: ");
        while (getchar() != '\n'); 
    }

    printf("Ingrese el numero de productos (maximo 5): ");
    while (scanf("%d", &factura.nProductos) != 1 || factura.nProductos < 1 || factura.nProductos > 5) {
        printf("Numero de productos invalido. Ingrese un numero entre 1 y 5: ");
        while (getchar() != '\n'); 
    }

    for (int i = 0; i < factura.nProductos; i++) {
        printf("Ingrese el nombre del producto %d: ", i + 1);
        leerCadena(factura.productos[i].nombre, 50);

        printf("Ingrese la cantidad del producto %d: ", i + 1);
        while (scanf("%d", &factura.productos[i].cantidad) != 1 || factura.productos[i].cantidad <= 0) {
            printf("Cantidad invalida. Ingrese un numero positivo: ");
            while (getchar() != '\n'); 
        }

        printf("Ingrese el precio del producto %d: ", i + 1);
        while (scanf("%f", &factura.productos[i].precio) != 1 || factura.productos[i].precio < 0) {
            printf("Precio invalido. Ingrese un numero positivo: ");
            while (getchar() != '\n'); 
        }

        factura.total += factura.productos[i].cantidad * factura.productos[i].precio;
    }

    saveFactura(&factura);
}

void readFactura() {
    FILE *archivo;
    struct Factura factura;
    archivo = fopen("facturas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    } else {
        printf("Facturas activas:\n");
        while (fread(&factura, sizeof(struct Factura), 1, archivo)) {
            if (factura.estado == 1) { // Solo mostrar facturas activas
                printf("Nombre del cliente: %s\n", factura.nombre);
                printf("Cedula del cliente: %d\n", factura.cedula);
                for (int i = 0; i < factura.nProductos; i++) {
                    printf("%d\t\t%s\t\t%d\t\t%.2f\n", i + 1, factura.productos[i].nombre,
                           factura.productos[i].cantidad, factura.productos[i].precio);
                }
                printf("Total: %.2f\n", factura.total);
                printf("\n");
            }
        }
    }
    fclose(archivo);
}

void updateFactura() {
    FILE *archivo;
    struct Factura factura;
    int cedula;

    printf("Ingrese la cedula de la factura a actualizar: ");
    while (scanf("%d", &cedula) != 1 || cedula <= 0) {
        printf("Cedula invalida. Ingrese un numero positivo: ");
        while (getchar() != '\n'); 
    }

    archivo = fopen("facturas.dat", "rb+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    int found = 0;
    while (fread(&factura, sizeof(struct Factura), 1, archivo)) {
        if (factura.cedula == cedula) {
            found = 1;
            printf("Factura encontrada. Ingrese los nuevos datos:\n");
            printf("Ingrese el nombre del cliente: ");
            leerCadena(factura.nombre, 20);

            printf("Ingrese el numero de productos (maximo 5): ");
            while (scanf("%d", &factura.nProductos) != 1 || factura.nProductos < 1 || factura.nProductos > 5) {
                printf("Numero de productos invalido. Ingrese un numero entre 1 y 5: ");
                while (getchar() != '\n');
            }

            factura.total = 0; 

            for (int i = 0; i < factura.nProductos; i++) {
                printf("Ingrese el nombre del producto %d: ", i + 1);
                leerCadena(factura.productos[i].nombre, 50);

                printf("Ingrese la cantidad del producto %d: ", i + 1);
                while (scanf("%d", &factura.productos[i].cantidad) != 1 || factura.productos[i].cantidad <= 0) {
                    printf("Cantidad invalida. Ingrese un número positivo: ");
                    while (getchar() != '\n'); 
                }

                printf("Ingrese el precio del producto %d: ", i + 1);
                while (scanf("%f", &factura.productos[i].precio) != 1 || factura.productos[i].precio < 0) {
                    printf("Precio invalido. Ingrese un numero positivo: ");
                    while (getchar() != '\n'); 
                }

                factura.total += factura.productos[i].cantidad * factura.productos[i].precio;
            }

            fseek(archivo, -sizeof(struct Factura), SEEK_CUR);
            fwrite(&factura, sizeof(struct Factura), 1, archivo);
            printf("Factura actualizada con exito\n");
            break;
        }
    }

    if (!found) {
        printf("Factura no encontrada\n");
    }

    fclose(archivo);
}

int findByCedula(int cedula) {
    FILE *archivo;
    struct Factura factura;

    archivo = fopen("facturas.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    while (fread(&factura, sizeof(struct Factura), 1, archivo)) {
        if (factura.cedula == cedula) {
            printf("Factura encontrada:\n");
            printf("Nombre del cliente: %s\n", factura.nombre);
            printf("Cedula del cliente: %d\n", factura.cedula);
            for (int i = 0; i < factura.nProductos; i++) {
                printf("%d\t\t%s\t\t%d\t\t%.2f\n", i + 1, factura.productos[i].nombre,
                       factura.productos[i].cantidad, factura.productos[i].precio);
            }
            printf("Total: %.2f\n", factura.total);
            fclose(archivo);
            return 1; 
        }
    }

    fclose(archivo);
    return 0; 
}

void deleteFactura() {
    FILE *archivo;
    struct Factura factura;
    int cedula;
    int found = 0;

    printf("Ingrese la cedula de la factura a eliminar: ");
    while (scanf("%d", &cedula) != 1 || cedula <= 0) {
        printf("Cédula invalida. Ingrese un número positivo: ");
        while (getchar() != '\n'); // Limpiar el buffer
    }

    archivo = fopen("facturas.dat", "rb+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (fread(&factura, sizeof(struct Factura), 1, archivo)) {
        if (factura.cedula == cedula) {
            found = 1; 
            factura.estado = 0; // Cambiar a inactivo
            fseek(archivo, -sizeof(struct Factura), SEEK_CUR); // Volver al inicio de la factura
            fwrite(&factura, sizeof(struct Factura), 1, archivo); // Guardar cambios
            printf("Factura con cedula %d eliminada con exito.\n", cedula);
            break;
        }
    }

    if (!found) {
        printf("Factura no encontrada\n");
    }

    fclose(archivo);
}