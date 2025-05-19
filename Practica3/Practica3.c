#include "BibliotecaFunciones.h"

void menu_recursi(int repeticiones) {
    int opcion_escoger;

    system("cls");
    if (repeticiones>0){                //Seleccion de opcion a escoger
        printf("MENU DE OPCIONES\n"
            "Escoga la operacion a realizar, de las siguientes opciones.\n"
            "1. Arreglo de Suma Maxima\n"
            "2. Multiplicacion de matrices\n"
            "3. Inversor de arreglo\n"
            "Opcion a escoger: ");
        scanf("%d", &opcion_escoger);
        fflush(stdin);

        switch (opcion_escoger)             //Switch para controlar opciones
        {
        case 1:
            sumaMaxima();
            break;
        case 2:
            muestraCreacion();
            break;
        case 3: 
            break;
        default:
            break;
        }

        menu_recursi(repeticiones-1);
    } else {
        printf("Opciones finalizadas, se ha acabado el programa");      //Finalizacion del programa
        return;
    }
}

int main() {
    int numero_opciones;
    printf("Bienvenido a la practica 3\n"
    "Aqui trabajemos con el paradigma de divide y venceras que se basa en lo que conocemos como recursividad\n");
    printf("Ingrese el numero de operaciones a realizar, con la finalidad de ver todos los ejercicios\n");
    printf("Numero de operaciones: ");
    scanf("%d",&numero_opciones);
    fflush(stdin);
    printf(("Muchas gracias, prodeciendo al menu de operaciones"));
    Sleep(2);
    system("cls");
    menu_recursi(numero_opciones);
    return 0;
}