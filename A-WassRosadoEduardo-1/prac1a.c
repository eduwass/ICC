/* WASS: ROSADO: EDUARDO: 41511602Y */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Cargar cabecera de nuestras funciones */
#include "prac1funs.h"

/* Constantes resultado: */
#define OK 0
#define KO 1

/**
  Genera una matriz de dos dimensiones
  @param a dimension uno
  @param b dimension dos
  @return puntero a la estructura
**/
double **gen_matriz(int a, int b) {
    double **matriz = NULL;
    int i,x;
    /* Reservar espacio filas */
    matriz = (double **) malloc(a * sizeof(double *));
    if ( matriz != NULL ) {
        for (i=0;i<a;i++ ) {
            /* Reservar columnas */
            matriz[i] = (double *) malloc(b * sizeof(double));
            if ( matriz[i] == NULL ) {
                /* Si no queda espacio liberarlo */
                for ( x = 0 ; x < i ; x++ ){ free(matriz[x]); }
                free(matriz);
                matriz = NULL;
                break;
            }
        }
    }

    return matriz;
}

/**
  Funcion para leer valores de matriz doble por teclado
  @param n numero elementos matriz
  @return puntero a la estructura
 */
double **leer_matriz(int n, int m) {
    int i = 0, j = 0;
    double **M = gen_matriz(n, m);

    if ( M != NULL ) {
        for ( i = 0 ; i < n ; i++ ) {
            for ( j = 0 ; j < m ; j++ ) {
                scanf("%lf", &M[i][j]);
            }
        }
    }

    return M;
}

/**
  Genera un vector de tamaño n
  @param n dimensiones vector
  @return puntero a la estructura
**/
double *gen_vector(int n) {
    return (double *) malloc(n * sizeof(double));
}


/**
  Funcion para leer valores de vector por teclado
  @param n numero elementos matriz
  @return puntero a la estructura
 */
double *leer_vector(int n) {
    int i = 0;
    double *v = NULL;

    v = gen_vector(n);
    if ( v != NULL ) {
        for ( i = 0 ; i < n ; i++ ) {
            scanf("%lf", &v[i]);
        }
    }

    return v;
}

/**
  Muestra vector por pantalla
  @param n numero de elementos
  @param vector puntero al vector
 */
void mostrar_vector(int n, double *vector) {
    int i = 0;

    for ( i = 0 ; i < n ; i++ ) {
      printf(" %16.7e \n", vector[i]);
    }
    
}


double modulo_vector(int n, double *V) {
    int i = 0;
    double r = 0.f;

    for ( i = 0 ; i < n ; i++ ) {
        r += V[i] * V[i];
    }
    r = sqrt(r);

    return r;
}


double *resta_vector(int n, double *U, double *V) {
    int i;
    double *R = gen_vector(n);

    if ( R != NULL && U != NULL && V != NULL ) {
        for ( i = 0 ; i < n ; i++ ){
            R[i] = U[i] - V[i];
        }
    }

    return R;
}

double calcular_bondad(int n, int m, double **A, double *X, double *B) {
    double *y = NULL;
    y = gen_vector(n); /* Hacer espacio para la solucion */
    prodMatVec(n,A,X,y); /* y = Ax*/
    y = resta_vector(n, y, B); /* y= Ax-B */
    return modulo_vector(n, y);
}


int main(void) {
    int n = 0;
    double tol, mod;
    double **A = NULL, *B = NULL, *x = NULL;

    printf("\nDimensiones matriz: ");
    scanf("%d", &n);
    
    printf("\nTolerancia: ");
    scanf("%lf", &tol);
    
    printf("\nMatriz ecuaciones (A):");
    A = leer_matriz(n, n);
    
    printf("\nVector terminos indep. (B):");
    B = leer_vector(n);
    
    
    x = gen_vector(n);

    if ( A != NULL && B != NULL && x != NULL ) {
        resoltrisup(n, A, B, x, tol);
        mostrar_vector(n, x);
    }
    
    
    mod = calcular_bondad(n, n, A, x, B);
    printf("\nIndiciador bondad solucion: %15.e\n", mod);

    return 0;
}