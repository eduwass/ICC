/* WASS: ROSADO: EDUARDO: 41511602Y */

/*
    Constants usades a diversos llocs de l'aplicació per indicar
    el resultat de la crida d'un mètode.
 */
#define RESULT_OK 0
#define RESULT_ERROR 1


#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int resoltrisup(int n, double **A, double *B, double *x, double tol);
void prodMatVec(int n, double **A, double *x, double *y);
void prodMatMat(int n, double **A, double **B, double **C);


int resoltrisup2(int n, double **A, double *B, double *x, double tol);
#endif