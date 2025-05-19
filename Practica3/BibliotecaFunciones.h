#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void llenarArreglo(int arr[], int n) {
    if (n >= 0) {
        printf("Ingresa el elemento %d: ", n + 1);
        scanf("%d", &arr[n]);
        llenarArreglo(arr, n-1);
    }
}

void mostrar_arreglo(int *arreglo,int numero){
	for (int i=0; i< numero; i++){
		printf("%d ",*(arreglo+i));
	}
	printf("\n");;
}

int suma_recursiva(int *arreglo, int inicio, int final) {
    if (inicio > final) {
        return 0;
    }
    return arreglo[inicio] + suma_recursiva(arreglo, inicio + 1, final);
}

void comparacion(int *arreglo, int inicio_arreglo, int final_arreglo, int * best_value, int *subarrgl) {
    int valor;
    if (inicio_arreglo==final_arreglo){
        if (arreglo[inicio_arreglo]>(*best_value)){
            (*best_value)=arreglo[inicio_arreglo];
            subarrgl[0]=inicio_arreglo;
            subarrgl[1]=final_arreglo;
        }
    } else {
        valor=suma_recursiva(arreglo,inicio_arreglo,final_arreglo);
        if(valor>(*best_value)){
            (*best_value)=valor;
            subarrgl[0]=inicio_arreglo;
            subarrgl[1]=final_arreglo;
        }  
    }
    
    if(inicio_arreglo<final_arreglo) {
        int mitad=(inicio_arreglo+final_arreglo)/2;
        comparacion(arreglo,inicio_arreglo,mitad,best_value,subarrgl);

        if (((inicio_arreglo+final_arreglo)%2)==0){
            comparacion(arreglo,mitad,final_arreglo,best_value,subarrgl);
        } else {
            comparacion(arreglo,mitad+1,final_arreglo,best_value,subarrgl);
        }
    }
}

void busqueda(int **arreglo,int *largo, int *menu) {
    int inicio_opcional,final_opcional=*largo;
    int subarregl[2];
    int best_value=0;
    printf("BUSQUEDA SUBARREGLO MAS ALTO\n");
    
    printf("El arreglo original es: ");
    mostrar_arreglo(*arreglo, *largo); 

    comparacion(*arreglo,inicio_opcional,final_opcional-1,&best_value,subarregl);

    printf("El mejor subarreglo son las siguientes coordenadas: %d %d\n",subarregl[0],subarregl[1]);
    printf("El mejor valor es: %d\n",best_value);
}