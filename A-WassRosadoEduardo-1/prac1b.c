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
  @param a dimension 1
  @param b dimension 2
  @return puntero a la estructura
 */
double **leer_matriz(int a, int b) {
    int i = 0, j = 0;
    double **matriz = gen_matriz(a, b);

    if ( matriz != NULL ) {
        for ( i = 0 ; i < a ; i++ ) {
            for ( j = 0 ; j < b ; j++ ) {
                scanf("%lf", &matriz[i][j]);
            }
        }
    }

    return matriz;
}

/**
  Genera una matriz de tamaño n
  @param n dimensiones matriz
  @return puntero a la estructura
**/
double *gen_vector(int n) {
    return (double *) malloc(n * sizeof(double));
}


/**
  Funcion para leer valores de matriz por teclado
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
    printf("\n==================================");
    for ( i = 0 ; i < n ; i++ ) {
      printf("\n%f", vector[i]);
    }
    printf("\n==================================");
    
}

/**
  Muestra matriz por pantalla
  @param n numero de elementos
  @param matriz punto a la matriz
 */
void mostrar_matriz(int n, int m, double **M) {
    int i = 0, j = 0;
    printf("\n==================================");
    for ( i = 0 ; i < n ; i++ )  {
        printf("\n");
        for ( j = 0 ; j < m ; j++ ) {
            printf(" %f ", M[i][j]);
        }
    }
    printf("\n==================================");
}


/**
  Crea una copia del vector que le pasemos
  @param n dimension vector
  @param V 
  @return puntero a la nueva copia
**/
double *copia_vector(int n, double *V) {
    int i;
    double *C = gen_vector(n);

    if ( C != NULL && V != NULL ) {
        for ( i = 0; i < n ; i++ ){
            C[i] = V[i];
        }
    }

    return C;
}


double **copia_matriz(int n, int m, double **M) {
    int i,j;
    double **cm = gen_matriz(n, m);

    if ( cm != NULL && M != NULL ) {
        for ( i = 0 ; i < n ; i++ ){
            for ( j = 0 ; j < m ; j++ ) {
                cm[i][j] = M[i][j];
            }
        }
    }

    return cm;
}

void free_matriz(int n, double **M) {
    int i;
    for ( i = 0 ; i < n ; i++ )
        free(M[i]);
    free(M);
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

int gausspivot(int n, double **A, double *v, double tol) {
  
    /** Version 2.0 **/
    int i,j,k,l, pivot;
    double aux1,aux2, d;
    
    for(i=0; i<n-1; i++) {
    
      if(fabs(A[i][i])<tol){
        return KO;
      }
      /* al princpio suponemos pivot = i */
      pivot = i;
      
      /* Buscar si hay alguno mayor en la columna */
      for(j=i+1; j<n; j++){
        if(A[j][i] > A[i][i]){
          /* Si encontramos mayor => nuevo pivot */
          pivot = j;
        }
      }
      
      
      if(pivot != i){
        /* Intercambiar fila j por fila i */
        for(l=0;l<n;l++){
          /* Recorre columnas de fila pivot, cambiando valores con fila superior */
          aux1 = A[pivot][l];
          A[pivot][l] = A[pivot-1][l];
          A[pivot-1][l] = aux1;
        }
        
        /* Intercambiar tambien vector v */
        aux2 = v[pivot];
        v[pivot] = v[pivot-1];
        v[pivot-1] = aux2;
      }
      
      
      
      /* Triangulizar */
      for (j=i+1 ; j<n ; j++) {
      
        if(A[j][j]==0){
          d = 0;
        } else {
          d = A[j][i] / A[i][i];
        }
        
        
        for (k=i ; k<n ; k++) {
          /* Restar filas */
          A[j][k] = A[j][k] - (A[i][k]*d);
        }
        /* Lo mismo con el vector */
        v[j] = v[j] - v[i]*d;
      }

    }
    
    return OK;
  
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
    double **copiaA = NULL, *copiaB = NULL;

    /* Leer dimensiones */
    printf("\nDimensiones matriz: ");
    scanf("%d", &n);
    
    /* Leer tolerancia */
    printf("\nTolerancia: ");
    scanf("%lf", &tol);
    
    /* Leer matriz */
    printf("\nMatriz ecuaciones (A):");
    A = leer_matriz(n, n);
    
    /* Leer vector terminos indp. */
    printf("\nVector terms. indep. (B):");
    B = leer_vector(n);
    
    x = gen_vector(n);

    /* Guardar copias */
    copiaA = copia_matriz(n, n, A);
    copiaB = copia_vector(n, B);

    printf("A:\n");
    mostrar_matriz(n, n, A);

    printf("\nB:\n");
    mostrar_vector(n, B);

    if ( gausspivot(n, A, B, tol) == OK ){
        printf("\nA:\n");
        mostrar_matriz(n, n, A);
    
        printf("\nB:\n");
        mostrar_vector(n, B);
    
        if ( resoltrisup(n, A, B, x, tol) == OK ) {
            printf("\nX:\n");
            mostrar_vector(n, x);
    
            mod = calcular_bondad(n, n, copiaA, x, copiaB);
    
            printf("\nIndiciador bondad solucion: %15.e\n", mod);
        } else {
            printf("No se puede calcular la solucion del sistema.\n");
        }
    } else{
        printf("No se pudo aplicar el metodo de Gauss con pivoteo.\n");
    }
    

    free_matriz(n, A);
    free_matriz(n, copiaA);
    free(B);
    free(copiaB);
    free(x);

    return 0;
}