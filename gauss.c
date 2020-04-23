#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int numerador;
  int denominador;
} FRAC;

typedef struct matriz {
  FRAC ** matriz;
  int filas;
  int columnas;
} Matriz;

int resolverGaussJordan(Matriz matriz);
int sumarMatrices(Matriz destino, Matriz m1, Matriz m2);
int restarMatrices(Matriz destino, Matriz m1, Matriz m2);
int multiplicarMatrices(Matriz destino, Matriz m1, Matriz m2);
void hacerCero(Matriz matriz, int pivote);
void hacerCeroDebajo(Matriz matriz, int pivote);
void triangularSuperior(Matriz matriz);
int validarMatriz(Matriz matriz);
FRAC calcularDeterminante(Matriz matriz);
FRAC calcularTraza (Matriz matriz);
FRAC mult(FRAC a, FRAC b);
FRAC divi(FRAC a, FRAC b);
FRAC suma(FRAC a, FRAC b);
FRAC rest(FRAC a, FRAC b);
FRAC simplificacion(FRAC);

void imprimirMatriz(Matriz matriz);
void liberarMatriz(Matriz matriz);
Matriz inicializarMatriz(int filas, int columnas);
void rellenarMatriz(Matriz matriz);
void rellenarMatrizCuadrada(Matriz matriz);

int main() {
  int fila = 3, columna = 4, error = 0;
  Matriz m1 = inicializarMatriz(fila, columna);
  Matriz m2 = inicializarMatriz(fila, columna);
  Matriz m3 = inicializarMatriz(3, 3);
  Matriz m4 = inicializarMatriz(3, 3);
  FRAC det, traza;

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
  if (error == 1) {
    printf("El sistema no tiene soluciones\n");
  } else if (error == 2) {
    printf("El sistema tiene soluciones infinitas\n");
  }
  printf("\n\n-------------------------------------\n\n");

  printf("Matriz B:\n");
  imprimirMatriz(m3);
  printf("\nMultiplicar B*B\n");
  multiplicarMatrices(m4, m3, m3);
  imprimirMatriz(m4);

  printf("\nDeterminante B\n");
  det = calcularDeterminante(m3);
  printf("%i/%i\n", det.numerador, det.denominador);

  rellenarMatrizCuadrada(m3);

  printf("\nTraza B\n");
  traza = calcularTraza(m3);
  printf("%i/%i\n", traza.numerador, traza.denominador);

  liberarMatriz(m1);
  liberarMatriz(m2);
  liberarMatriz(m3);
  liberarMatriz(m4);

  return 0;
}

/*
Funciones para operar con fracciones
*/

FRAC mult(FRAC a, FRAC b) {
  FRAC c;
  c.numerador = a.numerador * b.numerador;
  c.denominador = a.denominador * b.denominador;
  c = simplificacion(c);
  return c;
}

FRAC divi(FRAC a, FRAC b) {
  FRAC c;
  c.numerador = a.numerador * b.denominador;
  c.denominador = a.denominador * b.numerador;
  c = simplificacion(c);
  return c;
}

FRAC suma(FRAC a, FRAC b) {
  FRAC c;
  c.numerador = a.numerador * b.denominador + b.numerador * a.denominador;
  c.denominador = a.denominador * b.denominador;
  c = simplificacion(c);
  return c;
}

FRAC rest(FRAC a, FRAC b) {
  FRAC c;
  c.numerador = a.numerador * b.denominador - b.numerador * a.denominador;
  c.denominador = a.denominador * b.denominador;
  c = simplificacion(c);
  return c;
}

FRAC simplificacion(FRAC a) {
  int i = 2;

  while (i abs(<= a.numerador)) {
    while (a.numerador % i == 0 && a.denominador % i == 0) {
      a.numerador = a.numerador / i;
      a.denominador = a.denominador / i;
    }
    i++;
  }

  if (a.denominador < 0) {
    a.numerador *= -1;
    a.denominador *= -1;
  }
  return a;
}

/*
Metodo de eliminación de Gauss Jordan.
Recibe una matriz matriz y regresa un número entero dependiendo de la solución.
0: El sistema si tiene soluciones
1: El sistema no tiene solución
2: El sistema tiene soluciones infinitas
*/
int resolverGaussJordan(Matriz matriz) {
  int i, j, error, pivote = 0;
  FRAC modificador, temporalElemento;

  //intercambiar renglones en caso de que el valor de la primera pos	sea == 0
  if (matriz.matriz[0][0].numerador == 0) {
    for (i = 1; i <= matriz.filas; i++) {
      if (matriz.matriz[i][0].numerador != 0) {
        for (j = 0; j < matriz.columnas; j++) {
          temporalElemento = matriz.matriz[i][j];
          matriz.matriz[i][j] = matriz.matriz[0][j];
          matriz.matriz[0][j] = temporalElemento;
        }
        break;
      }
    }
  }

  //Hacer 1 el pivote de la fila actual
  for (i = 0; i < matriz.filas; i++) {
    modificador = matriz.matriz[i][i];
    for (j = 0; j < matriz.columnas; j++) {
      matriz.matriz[i][j] = divi(matriz.matriz[i][j], modificador);
      //matriz.matriz[i][j] /= modificador;
    }

    //Hacer 0 el resto de la columna
    hacerCero(matriz, pivote);

    pivote++;
    imprimirMatriz(matriz);
    printf("\n\n");

    if ((error = validarMatriz(matriz))) {
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
int validarMatriz(Matriz matriz) {
  int contador = 0, j;
  for (j = 0; j < matriz.columnas; j++) {
    if ((int) matriz.matriz[matriz.filas - 1][j].numerador == 0) {
      contador++;
    }
  } //Fin for
  if (contador >= matriz.columnas - 1) {
    if ((int) matriz.matriz[matriz.filas - 1][matriz.columnas - 1].numerador == 0) {
      return 2;
    } else {
      return 1;
    }
  }
  return 0;
}

void hacerCero(Matriz matriz, int pivote) {
  int i, j;
  FRAC modificador;
  FRAC valor;
  valor.numerador = -1;
  valor.denominador = 1;

  for (i = 0; i < matriz.filas; i++) {
    if (i == pivote) {
      continue;
    }
    modificador = mult(matriz.matriz[i][pivote], valor);
    for (j = 0; j < matriz.columnas; j++) {
      matriz.matriz[i][j] = suma(matriz.matriz[i][j], mult(matriz.matriz[pivote][j], modificador));
    }
  }
}

/*
Algoritmos de operaciones de Matrices
*/

int sumarMatrices(Matriz destino, Matriz m1, Matriz m2) {
  int i, j;
  if (m1.filas != m2.filas || m1.columnas != m2.columnas) {
    return 1;
  }
  for (i = 0; i < m1.filas; i++) {
    for (j = 0; j < m1.columnas; j++) {
      destino.matriz[i][j] = suma(m1.matriz[i][j], m2.matriz[i][j]);
    }
  }
  return 0;
}

int restarMatrices(Matriz destino, Matriz m1, Matriz m2) {
  int i, j;
  if (m1.filas != m2.filas || m1.columnas != m2.columnas) {
    return 1;
  }
  for (i = 0; i < m1.filas; i++) {
    for (j = 0; j < m1.columnas; j++) {
      destino.matriz[i][j] = rest(m1.matriz[i][j], m2.matriz[i][j]);
    }
  }
  return 0;
}

int multiplicarMatrices(Matriz destino, Matriz m1, Matriz m2) {
  int i, j, k;
  FRAC resultado;

  resultado.numerador = 0;
  resultado.denominador = 1;

  if (m1.columnas != m2.filas) {
    return 1;
  }

  for (i = 0; i < m1.filas; i++) {
    for (j = 0; j < m2.columnas; j++) {
      for (k = 0; k < m1.columnas; k++) {
        resultado = suma(resultado, mult(m1.matriz[i][k], m2.matriz[k][j]));
        //resultado += m1.matriz[i][k] * m2.matriz[k][j];
      }
      destino.matriz[i][j] = resultado;
      //resultado = 0;
      resultado.numerador = 0;
      resultado.denominador = 1;
    }
  }
  return 0;
}

void hacerCeroDebajo(Matriz matriz, int pivote){
  int i, j;
  FRAC menosUno = {-1,1};
  FRAC modificador;

  if(pivote == matriz.filas -1){
    return;
  }

  for(i=pivote+1; i < matriz.filas; i++){
    modificador = mult(menosUno, divi(matriz.matriz[i][pivote], matriz.matriz[pivote][pivote]));
    for(j=pivote; j < matriz.columnas; j++){
      matriz.matriz[i][j] = suma(matriz.matriz[i][j], mult(modificador, matriz.matriz[pivote][j]));
    }
  }
}

void triangularSuperior(Matriz matriz){
  int i;
  for(i=0; i<matriz.filas; i++){
    hacerCeroDebajo(matriz, i);
  }
}

FRAC calcularTraza (Matriz matriz){
  int i;
  FRAC traza = {0, 1};

  for(i=0; i<matriz.filas; i++){
    traza = suma(traza, matriz.matriz[i][i]);
  }
  return traza;
}

FRAC calcularDeterminante(Matriz matriz){
  int i;
  FRAC determinante = matriz.matriz[0][0];

  triangularSuperior(matriz);

  for(i=1; i<matriz.filas; i++){
    determinante = mult(determinante, matriz.matriz[i][i]);
  }

  return determinante;
}

/*******************************************************************************
                  Funciones de Desarrollo

Las funciones que siguen, son unicamente para auxiliar durante el desarrollo
no forman parte de los algoritmos

*******************************************************************************/

Matriz inicializarMatriz(int filas, int columnas) {
int i;
Matriz matriz;

matriz.filas = filas;
matriz.columnas = columnas;
matriz.matriz = (FRAC ** ) malloc(sizeof(FRAC * ) * filas);
if (matriz.matriz) {
  for (i = 0; i < filas; i++) {
    matriz.matriz[i] = malloc(sizeof(FRAC) * columnas);
    if (matriz.matriz[i] == NULL) {
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

void liberarMatriz(Matriz matriz) {
int i, j;
for (i = 0; i < matriz.filas; i++) {
  free(matriz.matriz[i]);
}
free(matriz.matriz);
}

void imprimirMatriz(Matriz matriz) {
int i, j;
for (i = 0; i < matriz.filas; i++) {
  for (j = 0; j < matriz.columnas; j++) {
    if (matriz.matriz[i][j].denominador == 1) {
      printf("%i  ", matriz.matriz[i][j].numerador);
    } else if (matriz.matriz[i][j].numerador == 0) {
      printf("%i  ", matriz.matriz[i][j].numerador);
    } else if (matriz.matriz[i][j].numerador == matriz.matriz[i][j].denominador) {
      printf("1  ");
    } else if (matriz.matriz[i][j].numerador % matriz.matriz[i][j].denominador == 0) {
      printf("%i  ", matriz.matriz[i][j].numerador / matriz.matriz[i][j].denominador);
    } else {
      printf("%i/%i  ", matriz.matriz[i][j].numerador, matriz.matriz[i][j].denominador);
    }
  }
  printf("\n");
}
}

void rellenarMatriz(Matriz matriz) {
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
matriz.matriz[0][0].numerador = 1;
matriz.matriz[0][0].denominador = 2;

matriz.matriz[0][1].numerador = -1;
matriz.matriz[0][1].denominador = 1;

matriz.matriz[0][2].numerador = 1;
matriz.matriz[0][2].denominador = 1;

matriz.matriz[0][3].numerador = -2;
matriz.matriz[0][3].denominador = 1;

matriz.matriz[1][0].numerador = 6;
matriz.matriz[1][0].denominador = 1;

matriz.matriz[1][1].numerador = -1;
matriz.matriz[1][1].denominador = 1;

matriz.matriz[1][2].numerador = 2;
matriz.matriz[1][2].denominador = 1;

matriz.matriz[1][3].numerador = 4;
matriz.matriz[1][3].denominador = 1;

matriz.matriz[2][0].numerador = 3;
matriz.matriz[2][0].denominador = 1;

matriz.matriz[2][1].numerador = -3;
matriz.matriz[2][1].denominador = 1;

matriz.matriz[2][2].numerador = 6;
matriz.matriz[2][2].denominador = 1;

matriz.matriz[2][3].numerador = 2;
matriz.matriz[2][3].denominador = 1;

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

void rellenarMatrizCuadrada(Matriz matriz) {

matriz.matriz[0][0].numerador = 1;
matriz.matriz[0][0].denominador = 1;

matriz.matriz[0][1].numerador = 2;
matriz.matriz[0][1].denominador = 1;

matriz.matriz[0][2].numerador = 3;
matriz.matriz[0][2].denominador = 1;

matriz.matriz[1][0].numerador = 4;
matriz.matriz[1][0].denominador = 1;

matriz.matriz[1][1].numerador = 5;
matriz.matriz[1][1].denominador = 1;

matriz.matriz[1][2].numerador = 6;
matriz.matriz[1][2].denominador = 1;

matriz.matriz[2][0].numerador = 7;
matriz.matriz[2][0].denominador = 1;

matriz.matriz[2][1].numerador = 8;
matriz.matriz[2][1].denominador = 1;

matriz.matriz[2][2].numerador = 9;
matriz.matriz[2][2].denominador = 1;

// matriz.matriz[0][0].numerador = 6;
// matriz.matriz[0][0].denominador = 1;
//
// matriz.matriz[0][1].numerador = 7;
// matriz.matriz[0][1].denominador = 1;
//
// matriz.matriz[0][2].numerador = 9;
// matriz.matriz[0][2].denominador = 1;
//
// matriz.matriz[1][0].numerador = 13;
// matriz.matriz[1][0].denominador = 1;
//
// matriz.matriz[1][1].numerador = 13;
// matriz.matriz[1][1].denominador = 1;
//
// matriz.matriz[1][2].numerador = 12;
// matriz.matriz[1][2].denominador = 1;
//
// matriz.matriz[2][0].numerador = 2;
// matriz.matriz[2][0].denominador = 1;
//
// matriz.matriz[2][1].numerador = 2;
// matriz.matriz[2][1].denominador = 1;
//
// matriz.matriz[2][2].numerador = 1;
// matriz.matriz[2][2].denominador = 1;
}
