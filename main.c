#include <stdio.h>
#include "libreria.h"

int main() {
    int opcion;

    inicializarSistema();
    configurarFabrica();

    do {
        printf("\n--- MENU FABRICA ---\n");
        printf("1. Ingresar\n");
        printf("2. Editar\n");
        printf("3. Eliminar\n");
        printf("4. Reporte\n");
        printf("5. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: ingresarProductos(); break;
            case 2: editarProducto(); break;
            case 3: eliminarProducto(); break;
            case 4: mostrarReporte(); break;
            case 5: printf("Bye!\n"); break;
            default: printf("Error.\n");
        }
    } while(opcion != 5);

    return 0;
}