#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

// ESTRUCTURA DE INVERSION -- Exclusiva funciones de inversion
typedef struct {
    int i, j;
} Inversion;

// FUNCIONES DE DECORACION

// FUNCIONES DE GENERACION-MUESTRA-LLENADO DE ARREGLO
void mostrarArreglo(int *arreglo, int n, int i, int inicial, int final) {
    if (i < n) {
        if (i == inicial) {
            printf("[");
            printf("%d", arreglo[i]);
            if (i == final) printf("]");
            else printf(" ");
            mostrarArreglo(arreglo, n, i + 1, inicial, final);
        } else if (i == final) {
            printf("%d]", arreglo[i]);
            mostrarArreglo(arreglo, n, i + 1, inicial, final);
        } else {
            printf("%d ", arreglo[i]);
            mostrarArreglo(arreglo, n, i + 1, inicial, final);
        }
    }
}

void llenarArreglo(int *arreglo, int n, int i) {
    if (i < n) {
        printf("Ingresa el elemento %d: ", i + 1);
        scanf("%d", &arreglo[i]);
        // Limpiar buffer después de scanf
        int c; while ((c = getchar()) != '\n' && c != EOF);
        llenarArreglo(arreglo, n, i + 1);
    }
}

void creacionArreglo(int **arreglo, int *largoArreglo) {
    printf("=======================================================\n"
           "|             INICIO DE CREACION DE ARREGLO           |\n"
           "=======================================================\n"
           "Ingrese el largo del arreglo a crear (maximo 20): ");
    scanf("%d", largoArreglo);
    int c; while ((c = getchar()) != '\n' && c != EOF);

    if (*largoArreglo <= 0 || *largoArreglo > 20) {
        printf("Tamaño inválido, debe ser entre 1 y 20.\n");
        return;
    }

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

// FUNCIONES PARA SUMA MAXIMA
int suma_recursiva(int *arreglo, int inicio, int final) {
    if (inicio > final) {
        return 0;
    }
    return arreglo[inicio] + suma_recursiva(arreglo, inicio + 1, final);
}

void comparacion(int *arreglo, int inicio_arreglo, int final_arreglo, int *best_value, int *subarrgl) {
    int valor;

    if (inicio_arreglo == final_arreglo) {
        if (arreglo[inicio_arreglo] > (*best_value)) {
            (*best_value) = arreglo[inicio_arreglo];
            subarrgl[0] = inicio_arreglo;
            subarrgl[1] = final_arreglo;
        }
    } else {
        valor = suma_recursiva(arreglo, inicio_arreglo, final_arreglo);
        if (valor > (*best_value)) {
            (*best_value) = valor;
            subarrgl[0] = inicio_arreglo;
            subarrgl[1] = final_arreglo;
        }
    }

    if (inicio_arreglo < final_arreglo) {
        int mitad = (inicio_arreglo + final_arreglo) / 2;
        comparacion(arreglo, inicio_arreglo, mitad, best_value, subarrgl);

        if (((inicio_arreglo + final_arreglo) % 2) == 0) {
            comparacion(arreglo, mitad, final_arreglo, best_value, subarrgl);
        } else {
            comparacion(arreglo, mitad + 1, final_arreglo, best_value, subarrgl);
        }
    }
}

void busquedaSumMaxima(int *arreglo, int largo) {
    int subarregl[2];
    if (largo <= 0) {
        printf("El arreglo está vacío.\n");
        return;
    }
    int best_value = arreglo[0];  // Inicializar con primer elemento
    comparacion(arreglo, 0, largo - 1, &best_value, subarregl);

    system("cls");
    printf("=======================================================\n"
           "|                RESULTADOS: SUMA MAXIMA              |\n"
           "=======================================================\n");

    printf("RESULTADOS\nArreglo original: ");
    mostrarArreglo(arreglo, largo, 0, 0, largo - 1);

    printf("\n-------------------------------------------------------\n");
    printf("Suma maxima encontrada: %d\n", best_value);
    printf("Indices del sub-arreglo: [%d, %d]\n", subarregl[0], subarregl[1]);
    printf("Sub-arreglo con suma maxima: ");
    mostrarArreglo(arreglo, (subarregl[1]) + 1, subarregl[0], subarregl[0], subarregl[1]);
    printf("\n-------------------------------------------------------\n");
    Sleep(5000);
}

void sumaMaxima(void) {
    int *arreglo = NULL;
    int largoArregl;

    system("cls");
    printf("=======================================================\n"
           "|                SUMA MAXIMA EN UN ARREGLO            |\n"
           "=======================================================\n");

    printf("-> Ha seleccionado la opcion de Suma Maxima del arreglo.\n"
           "-> Empezaremos creando el arreglo a trabajar...\n");
    creacionArreglo(&arreglo, &largoArregl);

    if (arreglo == NULL || largoArregl <= 0) {
        printf("No se pudo crear el arreglo correctamente.\n");
        return;
    }

    printf("\n-------------------------------------------------------\n"
           "Procediendo a calcular la Suma Maxima del arreglo...\n"
           "-------------------------------------------------------\n");
    Sleep(3000);
    busquedaSumMaxima(arreglo, largoArregl);

    free(arreglo);
    arreglo = NULL;
}

// SECCION DE INVERSION
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

    if (!arr || n < 2) {
        printf("\n--------------------------------------------------------\n"
               "No hay suficientes elementos para invertir.\n"
               "-------------------------------------------------------\n");
        free(arr);
        return;
    }

    int *temp = malloc(n * sizeof(int));
    Inversion *invs = malloc(sizeof(Inversion) * n * (n - 1) / 2);
    int *original = malloc(n * sizeof(int));
    memcpy(original, arr, n * sizeof(int));

    int inv_total = 0;
    long total = sort_count(arr, temp, 0, n - 1, invs, &inv_total);

    system("cls");
    printf("=======================================================\n"
           "|                RESULTADOS: INVERSION                |\n"
           "=======================================================\n");

    printf("RESULTADOS\nArreglo original: ");
    mostrarArreglo(original, n, 0, 0, n - 1);
    printf("\n-------------------------------------------------------\n");
    printf("Numero total de inversiones: %ld\n", total);
    if (inv_total > 0) {
        printf("Lista de inversiones detectadas:\n");
        mostrarInversiones(invs, 0, inv_total, original);
    } else {
        printf("No se encontraron inversiones.\n");
    }
    printf("-------------------------------------------------------\nArreglo ordenado: ");
    mostrarArregloOrdenado(arr, n, 0);
    printf("-------------------------------------------------------\n");

    // Liberación de memoria
    free(arr);
    free(temp);
    free(invs);
    free(original);
}

// SECCION DE MATRIZ (multiplicación)

int esPotenciaDeDos(int n) {                    //Funcion que verifica si un numero es potencia de 2 (retorna 1 si es potencia)
    return (n != 0) && ((n & (n - 1)) == 0);
}

void crearFila(int **matriz, int i, int n) {    //Funcion para crear filas de la matriz
    if (i == n) return;
    matriz[i] = calloc(n, sizeof(int));
    crearFila(matriz, i + 1, n);
}

int **crearMatriz(int n) {                       //Creacion de la matriz (nxn)
    int **matriz = malloc(n * sizeof(int *));
    crearFila(matriz, 0, n);
    return matriz;
}

void liberarMatrizRec(int **M, int i, int n) {
    if (i == n) return;
    free(M[i]);
    liberarMatrizRec(M, i + 1, n);
}

void liberarMatriz(int **M, int n) {
    liberarMatrizRec(M, 0, n);
    free(M);
}

void leerMatrizRec(int **M, int n, char nombre, int i, int j) {       //Lectura de valores de la matriz desde consola
    if (i >= n) return;
    if (j >= n) {
        leerMatrizRec(M, n, nombre, i + 1, 0);
        return;
    }
    printf("%c[%d][%d]: ", nombre, i, j);
    scanf("%d", &M[i][j]);
    int c; while ((c = getchar()) != '\n' && c != EOF);
    leerMatrizRec(M, n, nombre, i, j + 1);
}

void leerMatriz(int **M, int n, char nombre) {                       //Funcion principal para leer la matriz
    printf("\nIngresa los valores de la matriz %c (%dx%d):\n", nombre, n, n);
    leerMatrizRec(M, n, nombre, 0, 0);
}

void imprimirMatrizRec(int **M, int n, int i, int j) {               //Funcion recursiva para impresion de la matriz
    if (i >= n) return;
    if (j >= n) {
        printf("\n");
        imprimirMatrizRec(M, n, i + 1, 0);
        return;
    }
    printf("%4d ", M[i][j]);
    imprimirMatrizRec(M, n, i, j + 1);
}

void imprimirMatriz(int **M, int n) {                                //Funcion principal para impresion de la matriz
    imprimirMatrizRec(M, n, 0, 0);
}

void sumaRec(int **A, int **B, int **C, int n, int i, int j) {     //Funcion recursica para suma de matrices
    if (i >= n) return;
    if (j >= n) {
        sumaRec(A, B, C, n, i + 1, 0);
        return;
    }
    C[i][j] = A[i][j] + B[i][j];
    sumaRec(A, B, C, n, i, j + 1);
}

void suma(int **A, int **B, int **C, int n) {    //Funcion principal para suma de matrices
    sumaRec(A, B, C, n, 0, 0);
}

void copiarSubmatrices(int **src, int **dst, int iOffset, int jOffset, int n, int i, int j) {
    if (i >= n) return;
    if (j >= n) {
        copiarSubmatrices(src, dst, iOffset, jOffset, n, i + 1, 0);
        return;
    }
    dst[i][j] = src[i + iOffset][j + jOffset];
    copiarSubmatrices(src, dst, iOffset, jOffset, n, i, j + 1);
}

void combinarSubmatrices(int **src, int **dst, int iOffset, int jOffset, int n, int i, int j) {
    if (i >= n) return;
    if (j >= n) {
        combinarSubmatrices(src, dst, iOffset, jOffset, n, i + 1, 0);
        return;
    }
    dst[i + iOffset][j + jOffset] = src[i][j];
    combinarSubmatrices(src, dst, iOffset, jOffset, n, i, j + 1);
}

//Algoritmo de multiplicacion usando "divide y venceras"

void multiplicar(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    int **A11 = crearMatriz(newSize), **A12 = crearMatriz(newSize);   //Creacion de submatrices
    int **A21 = crearMatriz(newSize), **A22 = crearMatriz(newSize);
    int **B11 = crearMatriz(newSize), **B12 = crearMatriz(newSize);
    int **B21 = crearMatriz(newSize), **B22 = crearMatriz(newSize);
    int **C11 = crearMatriz(newSize), **C12 = crearMatriz(newSize);
    int **C21 = crearMatriz(newSize), **C22 = crearMatriz(newSize);
    int **temp1 = crearMatriz(newSize), **temp2 = crearMatriz(newSize);

    copiarSubmatrices(A, A11, 0, 0, newSize, 0, 0);           //Division de matrices originales en submatrices
    copiarSubmatrices(A, A12, 0, newSize, newSize, 0, 0);
    copiarSubmatrices(A, A21, newSize, 0, newSize, 0, 0);
    copiarSubmatrices(A, A22, newSize, newSize, newSize, 0, 0);

    copiarSubmatrices(B, B11, 0, 0, newSize, 0, 0);
    copiarSubmatrices(B, B12, 0, newSize, newSize, 0, 0);
    copiarSubmatrices(B, B21, newSize, 0, newSize, 0, 0);
    copiarSubmatrices(B, B22, newSize, newSize, newSize, 0, 0);

    multiplicar(A11, B11, temp1, newSize);             //Calculo recursivo de las submatrices
    multiplicar(A12, B21, temp2, newSize);
    suma(temp1, temp2, C11, newSize);

    multiplicar(A11, B12, temp1, newSize);
    multiplicar(A12, B22, temp2, newSize);
    suma(temp1, temp2, C12, newSize);

    multiplicar(A21, B11, temp1, newSize);
    multiplicar(A22, B21, temp2, newSize);
    suma(temp1, temp2, C21, newSize);

    multiplicar(A21, B12, temp1, newSize);
    multiplicar(A22, B22, temp2, newSize);
    suma(temp1, temp2, C22, newSize);

    combinarSubmatrices(C11, C, 0, 0, newSize, 0, 0);                                   //Combinacion de submatrices
    combinarSubmatrices(C12, C, 0, newSize, newSize, 0, 0);
    combinarSubmatrices(C21, C, newSize, 0, newSize, 0, 0);
    combinarSubmatrices(C22, C, newSize, newSize, newSize, 0, 0);

    liberarMatriz(A11, newSize); liberarMatriz(A12, newSize);                           //Liberacion de submatrices   
    liberarMatriz(A21, newSize); liberarMatriz(A22, newSize);
    liberarMatriz(B11, newSize); liberarMatriz(B12, newSize);
    liberarMatriz(B21, newSize); liberarMatriz(B22, newSize);
    liberarMatriz(C11, newSize); liberarMatriz(C12, newSize);
    liberarMatriz(C21, newSize); liberarMatriz(C22, newSize);
    liberarMatriz(temp1, newSize); liberarMatriz(temp2, newSize);
}

int muestraCreacionMultiplicacion(void) {
    int n;
    system("cls");
    printf("============================================================================\n"
           "|                  MULTIPLICACION DE MATRICES                     |\n"
           "===========================================================================\n");
    printf("Ingresa el tamano de las matrices (potencia de 2): ");                                //Lectura/validacion del tamaño
    scanf("%d", &n);
    int c; while ((c = getchar()) != '\n' && c != EOF);

    if (!esPotenciaDeDos(n)) {
        printf("\nEl tamano debe ser una potencia de 2 (como 2, 4, 8, 16...)\n\n");
        printf("Si se desea otro tamano diferente a una potencia de 2 debera rellenar de 0 los\n");
        printf("espacios restantes de su matriz hasta alcanzar la potencia de 2 mas cercana\n\n");
        return 1;
    }

    //Creacion/operacion con las matrices

    int **A = crearMatriz(n);
    int **B = crearMatriz(n);
    int **C = crearMatriz(n);

    leerMatriz(A, n, 'A');
    leerMatriz(B, n, 'B');

    multiplicar(A, B, C, n);
 
    //Mostrar resultados

    system("cls");
    printf("=======================================================================\n"
           "|                        RESULTADOS: MULTIPLICACION                   |\n"
           "=======================================================================\n");

    printf("\n\nResultado de A * B:\n");
    imprimirMatriz(C, n);

    //Liberar memoria

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}