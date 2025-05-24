#include "BibliotecaFunciones.h"

void menu_recursi(int repeticiones) {
    int opcion_escoger;

    system("cls");
    if (repeticiones > 0) {
        printf("=======================================================\n"
               "|                    MENU DE OPCIONES                 |\n"
               "=======================================================\n"
               "Seleccione la operacion que desea realizar:\n"
               "  1. Arreglo de Suma Maxima\n"
               "  2. Multiplicacion de Matrices\n"
               "  3. Inversor de Arreglo\n"
               "-------------------------------------------------------\n"
               "Opcion a escoger: ");
        scanf("%d", &opcion_escoger);
        int c; while ((c = getchar()) != '\n' && c != EOF);

        printf("\nHas seleccionado la opcion: %d\n", opcion_escoger);
        printf("=======================================================\n");

        switch (opcion_escoger) {
            case 1:
                sumaMaxima();
                break;
            case 2:
                muestraCreacionMultiplicacion();
                break;
            case 3:
                inversorDeArreglo();
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
        system("pause");
        system("cls");
        menu_recursi(repeticiones - 1);
    } else {
        printf("\n=======================================================\n"
               "|              Opciones finalizadas. Gracias :)        |\n"
               "=======================================================\n");
    }
}

int main() {
    int numero_opciones;

    printf("=======================================================\n"
           "|               BIENVENIDO A LA PRACTICA 3            |\n"
           "=======================================================\n"
           "En esta practica trabajaremos con el paradigma de\n"
           "'Divide y Venceras', usando recursividad.\n\n");

    printf("Ingrese el numero de operaciones a realizar para poder\n"
           "visualizar todos los ejercicios.\n"
           "Numero de operaciones: ");
    scanf("%d", &numero_opciones);
    int c; while ((c = getchar()) != '\n' && c != EOF);

    if (numero_opciones <= 0) {
        printf("El numero de operaciones debe ser mayor a 0.\n");
        return 1;
    }

    printf("======================================================\n"
           "| Muchas gracias, procesando la cantidad indicada... |\n"
           "======================================================\n");
    Sleep(2000);
    system("cls");

    menu_recursi(numero_opciones);
    
    return 0;
}