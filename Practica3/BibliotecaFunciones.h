#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void mostrarArreglo(int * arreglo, int n, int i, int inicial, int final) {
    //Llamada recursiva de impresion de arreglo
    if (i < n) {
        if (i==inicial){        //Personalizacion para corchete inicial, inicial es para marcar de donde inicia
            printf(("["));
            printf("%d ", arreglo[i]);
            mostrarArreglo(arreglo, n, i + 1, inicial, final);      //Personalizacion para corchete final, final es el final del arreglo
        } else if (i==final){
            printf("%d", arreglo[i]);
            printf("]");
        } else {        //Caso comun de impresion
            printf("%d ", arreglo[i]);
            mostrarArreglo(arreglo, n, i + 1, inicial, final);
        }
    }
}

void llenarArreglo(int * arreglo, int n, int i) {
    if (i < n) {
        printf("Ingresa el elemento %d: ", i + 1);  //LLamada recursiva para llenar el arreglo
        scanf("%d", &arreglo[i]);
        llenarArreglo(arreglo, n, i + 1);
    }
}

void creacionArreglo(int ** arreglo, int * largoArreglo) {
    printf("Iniciemos creando el arreglo\n");
        printf("Ingrese el largo del arreglo a crear (en numero y MAX=20): ");          //Personalizacion largo del arrreglo
        scanf("%d", largoArreglo);
        fflush(stdin);

        *arreglo = (int*)calloc((*largoArreglo), (sizeof(int)));           //Creacion arreglo de manera dinamica

        if (*arreglo== NULL) {              //Chequeo en caso de error en la asignacion de memoria
            printf("Memoria insuficiente para la generacion del arreglo\nVolviendo al menu....");
            Sleep(5000);
            return;
        }

        printf("Ahora procederemos con el llenado del arreglo\n");      //Procedimiento de llenado y muestra del arreglo
        llenarArreglo(*arreglo, *largoArreglo, 0);
        printf("Se ha creado el arreglo con exito es el siguiente: ");
        mostrarArreglo(*arreglo, *largoArreglo, 0, 0, (*largoArreglo)-1);
        printf("\n");
        Sleep(5000);
}

int suma_recursiva(int *arreglo, int inicio, int final) { 
    if (inicio > final) {
        return 0;
    }
    return arreglo[inicio] + suma_recursiva(arreglo, inicio + 1, final);    //Acumulacion de la suma de valores del arreglo
}

void comparacion(int *arreglo, int inicio_arreglo, int final_arreglo, int * best_value, int *subarrgl) {
    int valor;

    //Comparacion de valores de cada arreglo
    if (inicio_arreglo==final_arreglo){                 //Caso en que solo queda un elemento
        if (arreglo[inicio_arreglo]>(*best_value)){
            (*best_value)=arreglo[inicio_arreglo];
            subarrgl[0]=inicio_arreglo;
            subarrgl[1]=final_arreglo;
        }
    } else {                    //Caso en que el arreglo contiene mas de dos elementos
        valor=suma_recursiva(arreglo,inicio_arreglo,final_arreglo);
        if(valor>(*best_value)){
            (*best_value)=valor;
            subarrgl[0]=inicio_arreglo;
            subarrgl[1]=final_arreglo;
        }  
    }
    
    if(inicio_arreglo<final_arreglo) {      //Llamada recursva de la funcion
        int mitad=(inicio_arreglo+final_arreglo)/2;
        comparacion(arreglo,inicio_arreglo,mitad,best_value,subarrgl);

        if (((inicio_arreglo+final_arreglo)%2)==0){                 //Caso numero par de elementos
            comparacion(arreglo,mitad,final_arreglo,best_value,subarrgl);
        } else {                    //Caso numero impar de elementos
            comparacion(arreglo,mitad+1,final_arreglo,best_value,subarrgl);
        }
    }
}

void busquedaSumMaxima(int **arreglo,int largo) {
    int subarregl[2];   //Areglo que almacena posiciones mejor
    int best_value=0;   //Variable almacenadora de mejor valor
    comparacion(*arreglo,0,largo-1,&best_value,subarregl);      //Calculo de la suma maxima
    
    system("cls");
    printf("Se ha encontrado el mejor maximo\n");
    
    printf("RESULTADOS\n");
    printf("El arreglo original es el siguiente: ");
    mostrarArreglo(*arreglo, largo, 0, 0, largo-1);

    printf("\n\nLa suma maxima del arreglo tiene las siguientes caracteristicas: \n");
    printf("El valor es de: %d\n",best_value);
    printf("Coordenadas del subarreglo: %d, %d\n",subarregl[0],subarregl[1]);
    printf("Subarreglo: ");
    mostrarArreglo(*arreglo, (subarregl[1])+1, subarregl[0], subarregl[0], subarregl[1]);
    Sleep(5000);
}

void sumaMaxima() {
    int * arreglo;
    int largoArregl;

    system("cls");
    printf("Ha seleccionado la opcion de sumaMaxima del arreglo\n"
            "Empezaremos creando el arreglo a trabajar\n");
    creacionArreglo(&arreglo, &largoArregl);            //Creacion y llenado de arreglo
    printf("Procediendo a realizar los calculos de la Suma Maxima del arreglo\n");
    Sleep(3000); 
    busquedaSumMaxima(&arreglo, largoArregl);           //Operacion de la busqueda maxima y muestra de resultados
    free(arreglo);                                      //Liberacion de memoria
    arreglo = NULL;
}



