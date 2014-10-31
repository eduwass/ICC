/* WASS: ROSADO: EDUARDO: 41511602Y */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Cargar cabecera de nuestras funciones */
#include "prac1funs.h"

/* Constantes resultado: */
#define OK 0
#define KO 1

int resoltrisup(int n, double **A, double *B, double *x, double tol) {
    
  /* Si alguno de los valores es menor que la tolerancia => desestimar */
  int i,j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(fabs(A[i][j])<tol){
				A[i][j]=0;
			}
		}
	}
  	
	
	for (i=n-1; i>=0; i--) { 
	    /*Recorrer filas*/
      x[i] = B[i]; /*inicialmente consideramos sol = ter. indep.*/                  
      for (j=n-1; j>i; j--){
          /*recorrer columna e ir restando coef. * sol act.*/
          x[i]-=A[i][j]*x[j];        
      }
      if (A[i][i]==0){
          /*si coef. diagonal = 0 => error*/
          return KO;
      } else {
         /* sino, sol = sol / coef.diagonal*/
          x[i]/=A[i][i];
      }
  }
  
  return OK;
    
}


/**
  Producto de una matriz por un vector
  @param n dimesniones matriz
  @param m dimensiones vector
  @param M puntero a la matriz
  @param V puntero al vector
  @return puntero al vector resultado
 */
void prodMatVec(int n, double **A, double *x, double *y) {
    int i,j;
    
    for ( i = 0 ; i < n ; i++ ) {
        y[i] = 0;
        for ( j = 0 ; j < n ; j++ ) {
           /* sumatorio del producto de casilas de M * casilla V */
            y[i] += A[i][j] * x[j];
        }
    }
}

/**
 Producto de dos matrices
 @param n dimensiones matrices
 @param A puntero a matriz 1
 @param B puntero a matriz 2
 @param C puntero a matriz resultado
**/
void prodMatMat(int n, double **A, double **B, double **C) {
  
  int i,j,k;
  
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      for(k=0;k<n;k++){
        
        C[i][j] += A[i][k] * B[k][j];
          
      }
    }
  }
  
}