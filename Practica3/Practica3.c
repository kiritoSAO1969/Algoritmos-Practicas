#include "BibliotecaFunciones.h"

void menu_recursi(int repeticiones) {
    int opcion_escoger;

    system("cls");
    if (repeticiones > 0) {
        printf("===========================================\n"
               "|             MENÚ DE OPCIONES            |\n"
               "===========================================\n"
               "Seleccione la operación que desea realizar:\n"
               "  1. Arreglo de Suma Maxima\n"
               "  2. Multiplicacion de Matrices\n"
               "  3. Inversor de Arreglo\n"
               "-------------------------------------------\n"
               "Opcion a escoger: ");
        scanf("%d", &opcion_escoger);
        fflush(stdin);
        
        printf("\nHas seleccionado la opción: %d\n", opcion_escoger);
        printf("===========================================\n");

        switch (opcion_escoger) {
            case 1:
                sumaMaxima();
                break;
            case 2:
                muestraCreacion();
                break;
            case 3:
                inversorDeArreglo();
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }

        system("pause");  //para que no se cierre
        menu_recursi(repeticiones - 1);
    } else {
        printf("\n===========================================\n"
               "|     Opciones finalizadas. Gracias :)    |\n"
               "===========================================\n");
    }
}


int main() {
    int numero_opciones;

    printf("=======================================================\n"          //Mensaje de bienvenida
           "|               BIENVENIDO A LA PRACTICA 3            |\n"
           "=======================================================\n"
           "En esta practica trabajaremos con el paradigma\n"
           "de 'Divide y Venceras', usando recursividad.\n\n");

    printf("Ingrese el numero de operaciones a realizar\n"          //Peticion de elementos
           "para poder visualizar todos los ejercicios.\n"
           "Numero de operaciones: ");
    scanf("%d", &numero_opciones);
    fflush(stdin);

    printf("\n====================================================\n");
    printf("| Muchas gracias, procesando la cantidad indicada... |\n");
    printf("======================================================\n");
    Sleep(2000); 
    system("cls");

    menu_recursi(numero_opciones);

    return 0;
}