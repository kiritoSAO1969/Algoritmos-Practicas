#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//ESTRUCTURA DE INVERSION -- Exlusica funciones de inversion
typedef struct {
    int i, j;
} Inversion;

//FUNCIONES DE DECORACION

//FUNCIONES DE GENERACION-MUESTRA-LLENADO DE ARREGLO
void mostrarArreglo(int * arreglo, int n, int i, int inicial, int final) {
    //Llamada recursiva de impresion de arreglo
    if (i < n) {
        if (i==inicial){        //Personalizacion para corchete inicial, inicial es para marcar de donde inicia
            printf(("["));
            printf("%d ", arreglo[i]);
            mostrarArreglo(arreglo, n, i + 1, inicial, final);      //Personalizacion para corchete final, final es el final del arreglo
        } else if (i==final){
            printf("%d]", arreglo[i]);
            mostrarArreglo(arreglo, n, i + 1, inicial, final); 
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

void creacionArreglo(int **arreglo, int *largoArreglo) {
    printf("=======================================================\n"
           "|             INICIO DE CREACION DE ARREGLO           |\n"
           "=======================================================\n"
           "Ingrese el largo del arreglo a crear (maximo 20): ");
    scanf("%d", largoArreglo);
    fflush(stdin);

    *arreglo = (int*)calloc(*largoArreglo, sizeof(int));
    if (*arreglo == NULL) {
        printf("\n-------------------------------------------------------\n"
               "Error: Memoria insuficiente para generar el arreglo.\n"
               "Regresando al menú...\n"
               "-------------------------------------------------------\n");
        Sleep(5000);
        return;
    }

    printf("-------------------------------------------------------\n"
           "¡Arreglo creado correctamente! Ahora lo llenaremos.\n"
           "-------------------------------------------------------\n");
    llenarArreglo(*arreglo, *largoArreglo, 0);

    printf("=======================================================\n"
           "|               ARREGLO CREADO EXITOSAMENTE            |\n"
           "=======================================================\n");
    printf("Contenido del arreglo: ");
    mostrarArreglo(*arreglo, *largoArreglo, 0, 0, (*largoArreglo) - 1);
    printf("\n=======================================================\n");
    Sleep(5000);
}


//FUNCIONES DE GENERACION-MUESTRA-LLENADO DE MATRIZ
void llenarMatriz(int **matriz, int filas, int columnas, int i, int j) {
    if (i < filas) {
        if (j < columnas) {
            printf("Ingrese el elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
            llenarMatriz(matriz, filas, columnas, i, j+1);  // llenado de siguiente columna
        } else {
            llenarMatriz(matriz, filas, columnas, i+1, 0);  // llenado de siguiente fila
        }
    }
}

void mostrarMatriz(int **matriz, int filas, int columnas, int i, int j) {
    if (i < filas) {
        if (j < columnas) {
            if (j==0) {
                printf("[");
                printf("%d ", matriz[i][j]);
                mostrarMatriz(matriz, filas, columnas, i, j+1); //Llamada recursiva para mostrar siguiente columnas
            } else if (j==columnas-1){
                printf("%d]", matriz[i][j]);
                mostrarMatriz(matriz, filas, columnas, i, j+1); //Llamada recursiva para mostrar siguiente columnas
            } else { 
                printf("%d ", matriz[i][j]);
                mostrarMatriz(matriz, filas, columnas, i, j+1); //Llamada recursiva para mostrar siguiente columnas
            }
        } else {
            printf("\n");
            mostrarMatriz(matriz, filas, columnas, i+1, 0); //Llamada recursiva para mostrar siguiente fila desde 0
        }
    }
}

void asignarEspacioFilasRecursivo(int ***matriz, int columnas, int filaActual, int totalFilas) {
    if (filaActual < totalFilas) {
        (*matriz)[filaActual] = (int *)calloc(columnas, sizeof(int));   //Creacion de cada fila como arreglo
        if ((*matriz)[filaActual] == NULL) {
            printf("Memoria insuficiente en fila %d\nVolviendo al menú...\n", filaActual);
            Sleep(5000);
            return;
        }
        asignarEspacioFilasRecursivo(matriz, columnas, filaActual+1, totalFilas);   //Llamada recursiva para ir asignando fxf
    }
}

void creacionMatriz(int ***matriz, int *filas, int *columnas) {
    printf("Iniciemos creando la matriz\n");
        printf("Ingrese el numero de filas de la matriz (en numero y MAX=20): ");
        scanf("%d", filas);
        fflush(stdin);
        printf("Ingrese el numero de columnas de la matriz (en numero y MAX=20): ");
        scanf("%d", columnas);
        fflush(stdin);

        // Asignar memoria para las filas, se crea como un arreglo de punteros para que estos sean las filas
        *matriz = (int **)calloc(*filas, sizeof(int *));        //Creacion de los subarreglos
        if (*matriz == NULL) {
            printf("Memoria insuficiente para las filas\nVolviendo al menú...\n");
            Sleep(5000);
            return;
        }

        // Funcion de asignacion de manera recursiva para cada fila, aqui ya se crean los arreglos de cada fila
        asignarEspacioFilasRecursivo(matriz, *columnas, 0, *filas);

        //Llenado de la matriz
        printf("Ahora procederemos con el llenado de la matriz:\n");    
        llenarMatriz(*matriz, *filas, *columnas, 0, 0);

        //Muestra de la matriz
        printf("\nLa matriz creada es:\n");
        mostrarMatriz(*matriz, *filas, *columnas, 0, 0);
        Sleep(5000);
}

void liberacionFilasMatriz(int ***matriz, int filaActual, int totalFilas) {
    if (filaActual < totalFilas) {
        free((*matriz)[filaActual]);    //Se va liberando la memoria de cada arreglo, fila por fila
        liberacionFilasMatriz(matriz, filaActual + 1, totalFilas);      //Llamada recursiva hasta que se acaben todas las filas
    }
}

void muestraCreacion() {    //Borrar despues de la creacion de su funcion de multiplicacion de matriz
    int **matriz;
    int filas, columnas;
    creacionMatriz(&matriz, &filas, &columnas);

    liberacionFilasMatriz(&matriz, 0, filas);    
    free(matriz);
    matriz=NULL;
}

//FUNCIONES PARA SUMA MAXIMA
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
    printf("=======================================================\n"
           "|                RESULTADOS: SUMA MAXIMA              |\n"
           "=======================================================\n");
    
    printf("RESULTADOS\n"         //Muestra resultados
        "Arreglo original:");      //Muestra arreglo original
    mostrarArreglo(*arreglo, largo, 0, 0, largo-1);

    printf("\n-------------------------------------------------------\n");
    printf("Suma maxima encontrada: %d\n", best_value);
    printf("Indices del sub-arreglo: [%d, %d]\n", subarregl[0], subarregl[1]);
    printf("Sub-arreglo con suma maxima: ");
    mostrarArreglo(*arreglo, (subarregl[1])+1, subarregl[0], subarregl[0], subarregl[1]);
    printf("\n-------------------------------------------------------\n");
    Sleep(5000);
}

void sumaMaxima(void) {
    int * arreglo;
    int largoArregl;

    system("cls");
    printf("=======================================================\n"
           "|                SUMA MAXIMA EN UN ARREGLO            |\n"
           "=======================================================\n");

    printf("-> Ha seleccionado la opcion de Suma Maxima del arreglo.\n"
           "-> Empezaremos creando el arreglo a trabajar...\n");
    creacionArreglo(&arreglo, &largoArregl);            //Creacion y llenado de arreglo
    
    printf("\n-------------------------------------------------------\n"
           "Procediendo a calcular la Suma Maxima del arreglo...\n"
           "-------------------------------------------------------\n");
    Sleep(3000); 
    busquedaSumMaxima(&arreglo, largoArregl);           //Operacion de la busqueda maxima y muestra de resultados
    free(arreglo);                                      //Liberacion de memoria
    arreglo = NULL;
}

//SECCION DE INVERSION
static long merge_count_recursivo(int arr[], int temp[], int i, int j, int mid, int right, Inversion invs[], int *inv_index, int k, long inv_count) {
    if (i >= mid && j > right) return inv_count;

    if (i < mid && (j > right || arr[i] <= arr[j])) {
        temp[k] = arr[i];
        return merge_count_recursivo(arr, temp, i + 1, j, mid, right, invs, inv_index, k + 1, inv_count);
    }

    if (j <= right) {
        temp[k] = arr[j];
        for (int x = i; x < mid; x++) {
            invs[*inv_index] = (Inversion){ x, j };
            (*inv_index)++;
            inv_count++;
        }
        return merge_count_recursivo(arr, temp, i, j + 1, mid, right, invs, inv_index, k + 1, inv_count);
    }

    return inv_count;
}

static void copia_merge_resultado(int arr[], int temp[], int left, int right) {
    if (left > right) return;
    arr[left] = temp[left];
    copia_merge_resultado(arr, temp, left + 1, right);
}

static long merge_count(int arr[], int temp[], int left, int mid, int right, Inversion invs[], int *inv_index) {
    long inv_count = merge_count_recursivo(arr, temp, left, mid, mid, right,
                                           invs, inv_index, left, 0);
    copia_merge_resultado(arr, temp, left, right);
    return inv_count;
}

static long sort_count(int arr[], int temp[], int left, int right, Inversion invs[], int *inv_index) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    long inv = 0;
    inv += sort_count(arr, temp, left, mid, invs, inv_index);
    inv += sort_count(arr, temp, mid + 1, right, invs, inv_index);
    inv += merge_count(arr, temp, left, mid + 1, right, invs, inv_index);
    return inv;
}

void mostrarInversiones(Inversion invs[], int index, int total, int *original) {
    if (index >= total) return;
    printf("(%d,%d) => %d > %d\n",
           invs[index].i, invs[index].j,
           original[invs[index].i],
           original[invs[index].j]);
    mostrarInversiones(invs, index + 1, total, original);
}

void mostrarArregloOrdenado(int *arr, int n, int i) {
    if (i >= n) {
        printf("\n");
        return;
    }
    printf("%d ", arr[i]);
    mostrarArregloOrdenado(arr, n, i + 1);
}

void inversorDeArreglo(void) {
    int *arr = NULL, n;
    system("cls");
    printf("=======================================================\n"
           "|                INVERSION DE ELEMENTOS               |\n"
            "=======================================================\n");

    printf("-> Ha seleccionado la opcion inversion del arreglo.\n"
           "-> Empezaremos creando el arreglo a trabajar...\n");
    creacionArreglo(&arr, &n);
    
    printf("\n-------------------------------------------------------\n"
           "Procediendo a calcular la inversion del arreglo...\n"
           "-------------------------------------------------------\n");
    Sleep(3000); 

    // Validación del arreglo
    if (!arr || n < 2) {
        printf("\n--------------------------------------------------------\n"
               "No hay suficientes elementos para invertir.\n"
               "-------------------------------------------------------\n");
        free(arr);
        return;
    }

    // Asignación de estructuras auxiliares
    int *temp = malloc(n * sizeof(int));
    Inversion *invs = malloc(sizeof(Inversion) * n * (n - 1) / 2);
    int *original = malloc(n * sizeof(int));
    memcpy(original, arr, n * sizeof(int));

    // Cálculo de inversiones
    int inv_total = 0;
    long total = sort_count(arr, temp, 0, n - 1, invs, &inv_total);

    system("cls");
    printf("=======================================================\n"
           "|                RESULTADOS: INVERSION                |\n"
           "=======================================================\n");
    
    printf("RESULTADOS\n"         //Muestra resultados
        "Arreglo original:");      //Muestra arreglo original
    mostrarArreglo(arr, n, 0, 0, n-1);
    printf("\n-------------------------------------------------------\n");
    printf("Numero total de inversiones: %ld\n", total);
    if (inv_total > 0) {
        printf("Lista de inversiones detectadas:\n");
        mostrarInversiones(invs, 0, inv_total, original);
    } else {
        printf("No se encontraron inversiones.\n");
    }
    printf("-------------------------------------------------------"
           "\nArreglo ordenado:");
    mostrarArregloOrdenado(arr, n, 0);
    printf("-------------------------------------------------------\n");

    // Liberación de memoria
    free(arr);
    free(temp);
    free(invs);
    free(original);
}

