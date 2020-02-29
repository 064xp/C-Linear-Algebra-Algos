#include <stdio.h>
#include <stdlib.h>

float **inicializarMatriz(int filas, int columnas);
void liberarMatriz(float **matriz, int filas, int columnas);
void resolverGaussJordan (float **matriz, int filas, int columnas);
void imprimirMatriz(float **matriz, int fila, int columna);
void rellenarMatriz(float **matriz, int filas, int columnas);

int main(){
    int filas = 3, columnas = 3;
    float **matriz = inicializarMatriz(filas, columnas);
    rellenarMatriz(matriz, filas, columnas);
    imprimirMatriz(matriz, filas, columnas);
    printf("\n\n\n");
    resolverGaussJordan(matriz, filas, columnas);
    liberarMatriz(matriz, filas, columnas);
}

void resolverGaussJordan (float **matriz, int filas, int columnas)
{
	int i,j;
	int filaActual = 0;
	float valorDividir;
	float temporalElemento;
    int valorMultiplicar;

//intercambiar renglones en caso de que el valor de la primera pos	sea == 0 
// convertirlo en un ciclo
	if(matriz[filaActual][filaActual] == 0) 
	{
		if(matriz[filaActual+1][filaActual] == 0)
		{
			temporalElemento = matriz[filaActual+1][filaActual];
			matriz[filaActual+1][filaActual]= matriz[filaActual][filaActual];
			matriz[filaActual][filaActual] = temporalElemento;
		}
	}
	
	//Hacer 1 la fila actual
	valorDividir = matriz[filaActual][filaActual];
	for(i=0; i<columnas ;i++)
	{
		matriz[filaActual][i] /= valorDividir;

	}

    //Hacer 0 el resto de la columna

    

    i=0;
		valorMultiplicar = matriz[filas+1][i]*matriz[filas][i]*-1;
	for(i=1;i<=filas;i++)
	{
		for(j=0;j<columnas;j++)
		{
			matriz[filas+i][j] = matriz[filas][j]*valorMultiplicar+matriz[filas+i][j];
		}
	}


    imprimirMatriz(matriz, filas, columnas);
}

float **inicializarMatriz(int filas, int columnas){
    int i;
    float **matriz = malloc(sizeof(float *) * filas);
    if (matriz){
      for (i = 0; i < filas; i++){
        matriz[i] = malloc(sizeof (float) * columnas);
        if(matriz[i] == NULL){
            perror("Peluquin");
            exit(1);
        }
      }
    } else {
        perror("Peluquin");
        exit(1);
    }

    return matriz;
}

void liberarMatriz(float **matriz, int filas, int columnas){
    int i, j;
    for(i=0; i<filas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void imprimirMatriz(float **matriz, int fila, int columna)
{
    int i, j;
    for(i=0;i<fila;i++)
		{
			for(j=0;j<columna;j++)
			{
				printf("%0.2f ", matriz[i][j]);
			}
			printf("\n");
		}
}

//FUNCIONES DE DESARROLLO
void rellenarMatriz(float **matriz, int filas, int columnas){
    matriz[0][0] = 2;
    matriz[0][1] = 6;
    matriz[0][2] = 10;

    matriz[1][0] = 16;
    matriz[1][1] = 24;
    matriz[1][2] = 12;

    matriz[2][0] = 4;
    matriz[2][1] = 8;
    matriz[2][2] = 18;
}