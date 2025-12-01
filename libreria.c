#include <stdio.h>
#include <string.h>
#include "libreria.h" 


char nombres[MAX_PROD][LEN_NOMBRE];
int demandas[MAX_PROD];
float tiempoUnitario[MAX_PROD];
float recursosUnitarios[MAX_PROD];
int existe[MAX_PROD]; // 1 = Ocupado, 0 = Vacío


float tiempoFabricaDisponible = 0;
float recursosFabricaDisponibles = 0;

int buscarProducto(char nombreBusqueda[]) {
    for(int i = 0; i < MAX_PROD; i++) {
        if(existe[i] == 1) {
            if(strcmp(nombres[i], nombreBusqueda) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void inicializarSistema() {
    for(int i=0; i<MAX_PROD; i++) {
        existe[i] = 0; 
    }
}

void configurarFabrica() {
    printf("\n--- CONFIGURACION DE FABRICA ---\n");
    do {
        printf("Ingrese Tiempo Total Disponible (positivo): ");
        if (scanf("%f", &tiempoFabricaDisponible) != 1 || tiempoFabricaDisponible <= 0) {
            printf("Entrada inválida. Intente de nuevo.\n");
            while (getchar() != '\n'); // Limpiar buffer
        } else {
            break;
        }
    } while (1);

    do {
        printf("Ingrese Recursos Totales Disponibles (positivo): ");
        if (scanf("%f", &recursosFabricaDisponibles) != 1 || recursosFabricaDisponibles <= 0) {
            printf("Entrada inválida. Intente de nuevo.\n");
            while (getchar() != '\n'); // Limpiar buffer
        } else {
            break;
        }
    } while (1);
}

void ingresarProductos() {
    for (int i = 0; i < MAX_PROD; i++) {
        if (existe[i] == 0) {
            printf("\n--- Producto %d ---\n", i + 1);
            printf("Nombre: ");
            scanf("%s", nombres[i]);

            do {
                printf("Cantidad (positiva): ");
                if (scanf("%d", &demandas[i]) != 1 || demandas[i] <= 0) {
                    printf("Entrada inválida. Intente de nuevo.\n");
                    while (getchar() != '\n'); // Limpiar buffer
                } else {
                    break;
                }
            } while (1);

            do {
                printf("Tiempo unitario (positivo): ");
                if (scanf("%f", &tiempoUnitario[i]) != 1 || tiempoUnitario[i] <= 0) {
                    printf("Entrada inválida. Intente de nuevo.\n");
                    while (getchar() != '\n'); // Limpiar buffer
                } else {
                    break;
                }
            } while (1);

            do {
                printf("Recursos unitarios (positivo): ");
                if (scanf("%f", &recursosUnitarios[i]) != 1 || recursosUnitarios[i] <= 0) {
                    printf("Entrada inválida. Intente de nuevo.\n");
                    while (getchar() != '\n'); // Limpiar buffer
                } else {
                    break;
                }
            } while (1);

            existe[i] = 1;
        }
    }
    printf("Carga finalizada.\n");
}

void editarProducto() {
    char busca[LEN_NOMBRE];
    printf("Nombre a editar: ");
    scanf("%s", busca);

    int pos = buscarProducto(busca);

    if (pos != -1) {
        do {
            printf("Nuevo dato Cantidad (positiva): ");
            if (scanf("%d", &demandas[pos]) != 1 || demandas[pos] <= 0) {
                printf("Entrada inválida. Intente de nuevo.\n");
                while (getchar() != '\n'); // Limpiar buffer
            } else {
                break;
            }
        } while (1);

        do {
            printf("Nuevo dato Tiempo (positivo): ");
            if (scanf("%f", &tiempoUnitario[pos]) != 1 || tiempoUnitario[pos] <= 0) {
                printf("Entrada inválida. Intente de nuevo.\n");
                while (getchar() != '\n'); // Limpiar buffer
            } else {
                break;
            }
        } while (1);

        do {
            printf("Nuevo dato Recursos (positivo): ");
            if (scanf("%f", &recursosUnitarios[pos]) != 1 || recursosUnitarios[pos] <= 0) {
                printf("Entrada inválida. Intente de nuevo.\n");
                while (getchar() != '\n'); // Limpiar buffer
            } else {
                break;
            }
        } while (1);

        printf("Actualizado.\n");
    } else {
        printf("No encontrado.\n");
    }
}

void eliminarProducto() {
    char busca[LEN_NOMBRE];
    printf("Nombre a eliminar: ");
    scanf("%s", busca);

    int pos = buscarProducto(busca);

    if (pos != -1) {
        existe[pos] = 0;
        printf("Eliminado.\n");
    } else {
        printf("No encontrado.\n");
    }
}

void mostrarReporte() {
    float tiempoTotalReq = 0;
    float recursosTotalReq = 0;
    
    printf("\n--- REPORTE ---\n");
    printf("PROD\tCANT\tTIEMPO\tRECURSOS\n");
    
    for(int i = 0; i < MAX_PROD; i++) {
        if(existe[i] == 1) {
            float t_prod = demandas[i] * tiempoUnitario[i];
            float r_prod = demandas[i] * recursosUnitarios[i];
            
            tiempoTotalReq += t_prod;
            recursosTotalReq += r_prod;
            
            printf("%s\t%d\t%.1f\t%.1f\n", nombres[i], demandas[i], t_prod, r_prod);
        }
    }
    
    printf("\n--- RESULTADOS ---\n");
    printf("Tiempo Requerido: %.2f (Disp: %.2f)\n", tiempoTotalReq, tiempoFabricaDisponible);
    printf("Recursos Requeridos: %.2f (Disp: %.2f)\n", recursosTotalReq, recursosFabricaDisponibles);
    
    if(tiempoTotalReq <= tiempoFabricaDisponible && recursosTotalReq <= recursosFabricaDisponibles) {
        printf("CONCLUSION: SI se puede cumplir la demanda.\n");
    } else {
        printf("CONCLUSION: NO se puede cumplir (Faltan recursos o tiempo).\n");
    }
}