#include <stdio.h>
#include <stdlib.h>

typedef struct matriz{
  float **matriz;
  int filas;
  int columnas;
} Matriz;

Matriz inicializarMatriz(int filas, int columnas);
void liberarMatriz(Matriz matriz);
int resolverGaussJordan (Matriz matriz);
void imprimirMatriz(Matriz matriz);
int sumarMatrices(Matriz destino, Matriz m1, Matriz m2);
int restarMatrices(Matriz destino, Matriz m1, Matriz m2);
int multiplicarMatrices(Matriz destino, Matriz m1, Matriz m2);
void hacerCero(Matriz matriz, int pivote);
int validarMatriz(Matriz matriz);

void rellenarMatriz(Matriz matriz);
void rellenarMatrizCuadrada(Matriz matriz);

int main(){
  int fila=3,columna=4, error = 0;
  Matriz m1 = inicializarMatriz(fila, columna);
  Matriz m2 = inicializarMatriz(fila, columna);
  Matriz m3 = inicializarMatriz(3, 3);
  Matriz m4 = inicializarMatriz(3, 3);

  rellenarMatrizCuadrada(m3);
  rellenarMatriz(m1);
  rellenarMatriz(m2);

  printf("\nMatriz A (Matriz original):\n");
  imprimirMatriz(m1);
  printf("\n\n-------------------------------------\n\n");

  printf("Suma A+A\n");
  sumarMatrices(m1, m1, m1);
  imprimirMatriz(m1);
  printf("\n\n-------------------------------------\n\n");

  printf("Restar (A+A) - A\n");
  restarMatrices(m1, m1, m2);
  imprimirMatriz(m1);
  printf("\n\n-------------------------------------\n\n");

  printf("Gauss Jordan A\n");
  imprimirMatriz(m2);
  printf("\n\n");
  error = resolverGaussJordan(m2);
  imprimirMatriz(m2);
  if(error == 1){
    printf("El sistema no tiene soluciones\n");
  } else if(error == 2){
    printf("El sistema tiene soluciones infinitas\n");
  }
  printf("\n\n-------------------------------------\n\n");

  printf("Matriz B:\n");
  imprimirMatriz(m3);
  printf("\nMultiplicar B*B\n");
  multiplicarMatrices(m4, m3, m3);
  imprimirMatriz(m4);

  liberarMatriz(m1);
  liberarMatriz(m2);
  liberarMatriz(m3);
  liberarMatriz(m4);

  return 0;
}

/*
  Metodo de eliminación de Gauss Jordan.
  Recibe una matriz matriz y regresa un número entero dependiendo de la solución.
  0: El sistema si tiene soluciones
  1: El sistema no tiene solución
  2: El sistema tiene soluciones infinitas
*/
int resolverGaussJordan(Matriz matriz)
{
  int i,j, error, pivote = 0;
  float modificador, temporalElemento;

  //intercambiar renglones en caso de que el valor de la primera pos	sea == 0
  if(matriz.matriz[0][0] == 0)
  {
    for(i=1;i<=matriz.filas;i++)
    {
      if(matriz.matriz[i][0] != 0)
      {
        for(j=0;j<matriz.columnas;j++)
        {
        temporalElemento = matriz.matriz[i][j];
        matriz.matriz[i][j]= matriz.matriz[0][j];
        matriz.matriz[0][j] = temporalElemento;
        }
      break;
      }
    }
  }

  //Hacer 1 el pivote de la fila actual
  for(i=0; i<matriz.filas; i++)
  {
    modificador = matriz.matriz[i][i];
    for(j=0; j<matriz.columnas; j++)
    {
    	matriz.matriz[i][j] /= modificador;
    }

    //Hacer 0 el resto de la columna
    hacerCero(matriz, pivote);

    pivote++;
    imprimirMatriz(matriz);
    printf("\n\n");

    if((error = validarMatriz(matriz)))
    {
      return error;
    }
  } //Fin for filas

  return 0;
}

/*
  Parte de Gauss Jordan
  Revisa la última fila de la Matriz para determinar
  si tiene soluciones infinitas o no tiene soluciones
  Recibe una matriz y regresa un número entero
  1: No tiene soluciones
  2: Tiene soluciones infinitas
*/
int validarMatriz(Matriz matriz)
{
  int contador=0, j;
  for(j=0;j<matriz.columnas;j++)
  {
    if((int)matriz.matriz[matriz.filas-1][j] == 0)
    {
      contador++;
    }
  }//Fin for
  if(contador >= matriz.columnas-1)
  {
    if((int)matriz.matriz[matriz.filas-1][matriz.columnas-1] == 0)
    {
      return 2;
    } else {
      return 1;
    }
  }
  return 0;
}

void hacerCero(Matriz matriz, int pivote)
{
  int i ,j;
  float modificador;
  for(i=0; i<matriz.filas; i++)
  {
    if (i == pivote)
    {
      continue;
    }
    modificador = matriz.matriz[i][pivote]*-1;
    for(j=0; j<matriz.columnas; j++)
    {
      matriz.matriz[i][j] += matriz.matriz[pivote][j]*modificador;
    }
  }
}


int sumarMatrices(Matriz destino, Matriz m1, Matriz m2)
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
      destino.matriz[i][j] = m1.matriz[i][j] + m2.matriz[i][j];
    }
  }
  return 0;
}

int restarMatrices(Matriz destino, Matriz m1, Matriz m2)
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
      destino.matriz[i][j] = m1.matriz[i][j] - m2.matriz[i][j];
    }
  }
  return 0;
}

int multiplicarMatrices(Matriz destino, Matriz m1, Matriz m2)
{
  int i, j, k;
  float resultado = 0;

  if(m1.columnas != m2.filas){
    return 1;
  }

  for(i=0; i<m1.filas; i++)
  {
    for(j=0; j<m2.columnas; j++)
    {
      for(k=0; k<m1.columnas; k++)
      {
        resultado += m1.matriz[i][k] * m2.matriz[k][j];
      }
      destino.matriz[i][j] = resultado;
      resultado = 0;
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

    //Sin solucion
    // matriz.matriz[0][0] = 1;
    // matriz.matriz[0][1] = -3;
    // matriz.matriz[0][2] = 2;
    // matriz.matriz[0][3] = -4;
    //
    // matriz.matriz[1][0] = 2;
    // matriz.matriz[1][1] = 5;
    // matriz.matriz[1][2] = -3;
    // matriz.matriz[1][3] = 1;
    //
    // matriz.matriz[2][0] = 3;
    // matriz.matriz[2][1] = 2;
    // matriz.matriz[2][2] = -1;
    // matriz.matriz[2][3] = -2;

    //soluciones infinitas
    matriz.matriz[0][0] = 1;
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

    //Soluciones reales
    // matriz.matriz[0][0] = 2;
    // matriz.matriz[0][1] = -3;
    // matriz.matriz[0][2] = 6;
    // matriz.matriz[0][3] = -4;
    //
    // matriz.matriz[1][0] = 3;
    // matriz.matriz[1][1] = 1;
    // matriz.matriz[1][2] = -5;
    // matriz.matriz[1][3] = 8;
    //
    // matriz.matriz[2][0] = 7;
    // matriz.matriz[2][1] = -1;
    // matriz.matriz[2][2] = 1;
    // matriz.matriz[2][3] = 6;
}

void rellenarMatrizCuadrada(Matriz matriz){
    matriz.matriz[0][0] = 1;
    matriz.matriz[0][1] = 2;
    matriz.matriz[0][2] = 3;

    matriz.matriz[1][0] = 4;
    matriz.matriz[1][1] = 5;
    matriz.matriz[1][2] = 6;

    matriz.matriz[2][0] = 7;
    matriz.matriz[2][1] = 8;
    matriz.matriz[2][2] = 9;
}
