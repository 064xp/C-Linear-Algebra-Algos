#include <stdio.h>
#include <stdlib.h>

typedef struct matriz{
  float **matriz;
  int filas;
  int columnas;
} Matriz;

Matriz inicializarMatriz(int filas, int columnas);
void liberarMatriz(Matriz matriz);
void resolverGaussJordan (Matriz *matriz);
void imprimirMatriz(Matriz matriz);
int sumarMatrices(Matriz *destino, Matriz m1, Matriz m2);
int restarMatrices(Matriz *destino, Matriz m1, Matriz m2);
void hacerCero(Matriz *matriz, int pivote);

void rellenarMatriz(Matriz matriz);

int main(){
    Matriz m1 = inicializarMatriz(3, 4);
    Matriz m2 = inicializarMatriz(3, 4);
    rellenarMatriz(m1);
    rellenarMatriz(m2);

    printf("Matriz A:\n");
    imprimirMatriz(m1);

    printf("\n\n\nSuma A+A\n");
    sumarMatrices(&m1, m1, m1);
    imprimirMatriz(m1);

    printf("\n\n\nRestar (A+A) - A\n");
    restarMatrices(&m1, m1, m2);
    imprimirMatriz(m1);

    printf("\n\n\nGauss Jordan A\n");
    resolverGaussJordan(&m2);
    imprimirMatriz(m2);

    liberarMatriz(m1);
    liberarMatriz(m2);
	
	return 0;
}

void resolverGaussJordan(Matriz *matriz)
{
  int i,j;
  float modificador;
  int pivote = 0;

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
  for(i=0; i<matriz->filas; i++)
  {
    //Hacer 1 la fila actual
    modificador = matriz->matriz[i][i];
    for(j=0; j<matriz->columnas; j++)
    {
    	matriz->matriz[i][j] /= modificador;
    }
    //Hacer 0 el resto de la columna
    hacerCero(matriz, pivote);
	pivote++;
	imprimirMatriz(*matriz);
	printf("\n\n");
  } //Fin for filas
}

void hacerCero(Matriz *matriz, int pivote)
{
	int i ,j;
	float modificador;
	for(i=0; i<matriz->filas; i++)
	{
		if (i == pivote)
		{
			continue;
		}
		modificador = matriz->matriz[i][pivote]*-1;
		for(j=0; j<matriz->columnas; j++)
		{
			matriz->matriz[i][j] += matriz->matriz[pivote][j]*modificador;
		}
	}
}


int sumarMatrices(Matriz *destino, Matriz m1, Matriz m2)
{
  int i, j;
  if(m1.filas != m2.filas || m1.columnas != m2.columnas)
  {
    return 1;
  }
  for(i=0; i<m1.filas; i++)
  {
    for(j=0; j<m1.columnas; j++)
    {
      destino->matriz[i][j] = m1.matriz[i][j] + m2.matriz[i][j];
    }
  }
  return 0;
}

int restarMatrices(Matriz *destino, Matriz m1, Matriz m2)
{
  int i, j;
  if(m1.filas != m2.filas || m1.columnas != m2.columnas)
  {
    return 1;
  }
  for(i=0; i<m1.filas; i++)
  {
    for(j=0; j<m1.columnas; j++)
    {
      destino->matriz[i][j] = m1.matriz[i][j] - m2.matriz[i][j];
    }
  }
  return 0;
}

Matriz inicializarMatriz(int filas, int columnas)
{
    int i;
    Matriz matriz;

    matriz.filas = filas;
    matriz.columnas = columnas;
    matriz.matriz = (float **)malloc(sizeof(float *) * filas);
    if (matriz.matriz)
    {
      for (i = 0; i < filas; i++)
      {
        matriz.matriz[i] = malloc(sizeof (float) * columnas);
        if(matriz.matriz[i] == NULL)
        {
            perror("Error Alocando Matriz 01");
            exit(1);
        }
      }
    } else {
        perror("Error Alocando Matriz 02");
        exit(1);
    }

    return matriz;
}

void liberarMatriz(Matriz matriz)
{
    int i, j;
    for(i=0; i<matriz.filas; i++)
    {
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
    matriz.matriz[0][0] = 1;
    matriz.matriz[0][1] = -2;
    matriz.matriz[0][2] = 3;
    matriz.matriz[0][3] = 2;

    matriz.matriz[1][0] = 2;
    matriz.matriz[1][1] = 1;
    matriz.matriz[1][2] = -4;
    matriz.matriz[1][3] = -1;

    matriz.matriz[2][0] = 1;
    matriz.matriz[2][1] = 1;
    matriz.matriz[2][2] = -1;
    matriz.matriz[2][3] = 1;
}
