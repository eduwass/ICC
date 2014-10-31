/* WASS: ROSADO: EDUARDO: 41511602Y */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Cargar cabecera de nuestras funciones */
#include "prac1funs.h"

/* Constantes resultado: */
#define OK 0
#define KO 1

double determinante_matriz(double **a,int n) {
   int i,j,j1,j2;
   double det = 0;
   double **m = NULL;

   if (n == 1) { 
      det = a[0][0];
   } else if (n == 2) {
      det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
   } else {
      det = 0;
      for (j1=0;j1<n;j1++) {
         m = malloc((n-1)*sizeof(double *));
         for (i=0;i<n-1;i++)
            m[i] = malloc((n-1)*sizeof(double));
         for (i=1;i<n;i++) {
            j2 = 0;
            for (j=0;j<n;j++) {
               if (j == j1)
                  continue;
               m[i-1][j2] = a[i][j];
               j2++;
            }
         }
         det += pow(-1.0,1.0+j1+1.0) * a[0][j1] * determinante_matriz(m,n-1);
         for (i=0;i<n-1;i++)
            free(m[i]);
         free(m);
      }
   }
   return(det);
}


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

    for ( i = 0 ; i < n ; i++ ) {
      printf(" %16.7e \n", vector[i]);
    }
    
}

int inversaA(int n, double **A, double **B, double tol){
    
    int i,j,k;
    double c,d;
    double det;
    
    mostrar_matriz(n,n,A);
    det = determinante_matriz(A,n);
    
    if(det==0){
        /* Si det = 0, no tiene inversa */
        return KO;
    }
    
    /* Crear matriz identidad */
    for (i=0 ; i<n ; i++) {
        for(j=0;j<n;j++){
            if(i==j){
                /* Rellenar diagonal con 1's */
                B[i][j] = 1;
            } else {
                /* El resto 0's */
                B[i][j] = 0;
            }
        }
    }
    
    /* Pivoteando */
    for(i=n-1;i>0;i--) {
        if( A[i-1][0] < A[i][0] ) {
            /* Si es menor hay que cambiar fila */
            for(j=0;j<n;j++) {
                /* pivotar A */
                c = A[i][j];
                A[i][j]=A[i-1][j];
                A[i-1][j]=c; 
                /* pivotar B */
                d = B[i][j];
                B[i][j]=B[i-1][j];
                B[i-1][j]=d;
            }
            
        }
    }
    
    for(i=0;i<n;i++) {
        
        for(j=0;j<n;j++) {
        
            if(j!=i) {
                
                if(fabs(A[j][i])<tol){
                    A[j][i] = 0;
                }
                
                d = A[j][i]/A[i][i];
                
                for(k=0;k<n;k++){
                    /* Operar sobre A */
                    A[j][k] -= A[i][k] * d;
                    /* Operar sobre B */
                    B[j][k] -= B[i][k] * d;
                    
                }
                
            }
        }
        
    }
    
    for(i = 0; i<n; i++) {
        d = A[i][i];
        for(j = 0;j<n;j++) {
            /* divison sobre ambas */
            A[i][j] = A[i][j]/d;
            B[i][j] = B[i][j]/d;
        }
    }
    
    
    return OK;
}

void copiar_en_matriz(int n, double **A, double **C) {
    int i,j;

    if ( A != NULL && C != NULL ) {
        for ( i=0 ; i < n ; i++ ){
            for ( j = 0; j < n ; j++ ) {
                C[i][j] = A[i][j];
            }
        }
    }
}

int main(void) {
    
    int n = 0, result;
    double tol = 0.f;
    double **A, **B, **C = NULL;
    double **copiaA = NULL;
    /* Leer dimensiones */
    printf("\nDimensiones matriz: ");
    scanf("%d", &n);
    
    /* Leer tolerancia */
    printf("\nTolerancia: ");
    scanf("%lf", &tol);
    
    /* Leer matriz */
    printf("\nMatriz ecuaciones (A):");
    A = leer_matriz(n, n);
    B = gen_matriz(n,n);
    C = gen_matriz(n,n);
    copiaA = gen_matriz(n,n);
    copiar_en_matriz(n,A,copiaA);
    
    /* Calcular matriz inversa */
    result = inversaA(n,A,B,tol);
    if(result==KO){
        printf("\nNo tiene matriz inversa");
    } else {
        printf("\nSolucion: Matriz inversa:");
        mostrar_matriz(n,n,B);
    }
    
    
    /* Comprobar que el producto nos da la identidad
    C = A·B */
    prodMatMat(n,copiaA,B,C);
    
    printf("\nComprobar solucion\n(deberia salir una matriz identidad)");
    mostrar_matriz(n,n,C);
    
    return 0;
}



