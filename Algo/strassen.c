#include <stdio.h>
#include <stdlib.h>


void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

void add(int **a, int**b, int**c, int k){
    int i, j;
    for(i=0; i<k; i++){
        for(j=0; j<k; j++){
            c[i][j]= a[i][j]+b[i][j];
        }
    }
}

void sub(int **a, int**b, int**c, int k){
    int i, j;
    for(i=0; i<k; i++){
        for(j=0; j<k; j++){
            c[i][j]= a[i][j]-b[i][j];
        }
    }
}

int **alloc(int k){
    int **a;
    a= (int **)malloc(sizeof(int *)*k);
    for(int i=0; i<k; i++){
        a[i]= (int *)malloc(sizeof(int)*k);
    }
    return a;
}

void strassen(int **a, int**b, int**c, int k){
    if(k==1){
        c[0][0]= a[0][0]*b[0][0];
        return;
    }
    int h= k/2;
    int **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22, **m1, **m2, **m3, **m4, **m5, **m6, **m7, **c11, **c12, **c22, **c21;
    a11= alloc(h);
    a12= alloc(h);
    a21= alloc(h);
    a22= alloc(h);


    b11= alloc(h);
    b12= alloc(h);
    b21= alloc(h);
    b22= alloc(h);


    m1= alloc(h);
    m2= alloc(h);
    m3= alloc(h);
    m4= alloc(h);
    m5= alloc(h);
    m6= alloc(h);
    m7= alloc(h);

    for(int i=0; i<h; i++){
        for(int j=0; j<h; j++){
            a11[i][j]= a[i][j];
            a12[i][j]= a[i][j+h];
            a21[i][j]= a[i+h][j];
            a22[i][j]= a[i+h][j+h];
            

            b11[i][j]= b[i][j];
            b12[i][j]= b[i][j+h];
            b21[i][j]= b[i+h][j];
            b22[i][j]= b[i+h][j+h];

        }
    }
    int **t1, **t2;

    t1= alloc(h);
    t2= alloc(h);

    add(a11, a22, t1, h);
    add(b11, b22, t2, h);
    strassen(t1, t2, m1, h);


    add(a21, a22, t2, h);
    strassen(t2, b11, m2, h);


    sub(b12, b22, t1, h);
    strassen(a11, t1, m3, h);


    sub(b21, b11, t1, h);
    strassen(a22, t1, m4, h);


    add(a11, a12, t1, h);
    strassen(t1, b22, m5,h);


    sub(a21, a11, t1, h);
    add(b11, b12, t2, h);
    strassen(t1, t2, m6, h);
    

    sub(a12, a22, t1, h);
    add(b21, b22, t2, h);
    strassen(t1, t2, m7, h);


    c11= alloc(h);
    c12= alloc(h);
    c21= alloc(h);
    c22= alloc(h);
    add(m1, m4, t1, h);
    sub(m7, m5, t2, h);
    add(t1, t2, c11, h);
    
    add(m3, m5, c12, h);

    add(m2, m4, c21, h);

    add(m3, m6, t1, h);
    sub(m1, m2, t2, h);
    add(t1, t2, c22, h);

    for(int i=0; i<h; i++){
        for(int j=0; j<h; j++){
            c[i][j]= c11[i][j];
            c[i][j+h]= c12[i][j];
            c[i+h][j]= c21[i][j];
            c[i+h][j+h]= c22[i][j];
        }
    }

    free_matrix(a11, h); 
    free_matrix(a12, h); 
    free_matrix(a21, h); 
    free_matrix(a22, h); 

    free_matrix(b11, h); 
    free_matrix(b12, h); 
    free_matrix(b21, h); 
    free_matrix(b22, h); 

    free_matrix(c11, h); 
    free_matrix(c12, h); 
    free_matrix(c21, h); 
    free_matrix(c22, h); 
    
    free_matrix(m1, h); 
    free_matrix(m2, h); 
    free_matrix(m3, h); 
    free_matrix(m4, h); 
    free_matrix(m5, h); 
    free_matrix(m6, h); 
    free_matrix(m7, h);

    free_matrix(t1, h); 
    free_matrix(t2, h); 



}


void print_matrix(int **mat, int n, const char* name) {
    printf("--- Matrix %s (%dx%d) ---\n", name, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int n = 4; // Matrix dimension (must be a power of 2)

    int **A = alloc(n);
    int **B = alloc(n);
    int **C = alloc(n);

    // Populate A and B with sample values
    int val = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = val;
            B[i][j] = val + 1;
            val++;
        }
    }

    print_matrix(A, n, "A");
    print_matrix(B, n, "B");

    strassen(A, B, C, n);

    print_matrix(C, n, "C (Result = A x B)");

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}

