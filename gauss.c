#include <stdio.h>
#include <stdlib.h>

typedef struct matriz{
  float **matriz;
  int filas;
  int columnas;
} Matriz;

Matriz inicializarMatriz(int filas, int columnas);
void liberarMatriz(Matriz matriz);
void resolverGaussJordan (Matriz matriz);
void imprimirMatriz(Matriz matriz);

void rellenarMatriz(Matriz matriz);

int main(){
    Matriz m1 = inicializarMatriz(3, 4);
    rellenarMatriz(m1);
    imprimirMatriz(m1);

    printf("\n\n\n");
    // resolverGaussJordan(m1);
    imprimirMatriz(m1);
    liberarMatriz(m1);
}

void resolverGaussJordan (Matriz matriz)
{
  int i,j;
  float valorDividir;
  float temporalElemento;
  int valorMultiplicar;

  // //intercambiar renglones en caso de que el valor de la primera pos	sea == 0
  // // TODO convertirlo en un ciclo
  // if(matriz.matriz[filaActual][filaActual] == 0)
  // {
  // 	if(matriz.matriz[filaActual+1][filaActual] == 0)
  // 	{
  // 		temporalElemento = matriz.matriz[filaActual+1][filaActual];
  // 		matriz.matriz[filaActual+1][filaActual]= matriz.matriz[filaActual][filaActual];
  // 		matriz.matriz[filaActual][filaActual] = temporalElemento;
  // 	}
  // }
  //
  for(i=0; i<matriz.filas; i++)
  {
    //Hacer 1 la fila actual
    valorDividir = matriz.matriz[i][i];
    for(j=0; j<matriz.columnas; j++)
    {
    	matriz.matriz[i][j] /= valorDividir;
    }

    //Hacer 0 el resto de la columna

  } //Fin for filas
}

Matriz inicializarMatriz(int filas, int columnas){
    int i;
    Matriz matriz;

    matriz.filas = filas;
    matriz.columnas = columnas;
    matriz.matriz = (float **)malloc(sizeof(float *) * filas);
    if (matriz.matriz){
      for (i = 0; i < filas; i++){
        matriz.matriz[i] = malloc(sizeof (float) * columnas);
        if(matriz.matriz[i] == NULL){
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

void liberarMatriz(Matriz matriz){
    int i, j;
    for(i=0; i<matriz.filas; i++){
        free(matriz.matriz[i]);
    }
    free(matriz.matriz);
}

void imprimirMatriz(Matriz matriz)
{
    int i, j;
    for(i=0;i<matriz.filas;i++)
		{
			for(j=0;j<matriz.columnas;j++)
			{
				printf("%0.2f ", matriz.matriz[i][j]);
			}
			printf("\n");
		}
}

//FUNCIONES DE DESARROLLO
void rellenarMatriz(Matriz matriz){
    /*
    | 1   -2  4  -2 |
    | 2  -1   2   4 |
    | 3   -3  6   2 |
    */
    matriz.matriz[0][0] = 2;
    matriz.matriz[0][1] = -2;
    matriz.matriz[0][2] = 4;
    matriz.matriz[0][3] = -2;

    matriz.matriz[1][0] = 2;
    matriz.matriz[1][1] = -1;
    matriz.matriz[1][2] = 2;
    matriz.matriz[1][3] = 4;

    matriz.matriz[2][0] = 3;
    matriz.matriz[2][1] = -3;
    matriz.matriz[2][2] = 6;
    matriz.matriz[2][3] = 2;
}
