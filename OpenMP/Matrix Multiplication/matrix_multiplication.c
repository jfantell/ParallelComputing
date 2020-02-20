#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

//Matrix Multiplication using OpenMP
//	Algorithm overview: https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
//Compile instructions:
//	gcc -o matrixmult matrix_multiplication.c -fopenmp
//Run instructions:
// ./matrixmult
void matrix_mult(int n, int m, int p, float **A, float **B, float **C){

	int i, j, k;
	#pragma omp parallel shared(A,B,C) private(i,j,k)
	#pragma omp for simd
	for(i = 0; i < n; ++i) {
		for(j = 0; j < p ; j++){
			for(k=0; k < m ; k++){
				C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
			}
		}
	}
}

float ** initialize_matrix(int r, int c, char type){
	float ** M;
	int i, j, k;
	M = (float **)malloc(r * sizeof(float *)); 
	for (i=0; i<r; i++) {
		M[i] = (float *)malloc(c * sizeof(float));
		for(j=0; j<c; j++){
			if(type == 'A'){
				M[i][j] = i*3 + (j*j)%5;
			}
			else if(type == 'B'){
				M[i][j] = i*2 + (j*j)%7;
			}
			else{
				M[i][j] = 0;
			}
		}
	}
	return M;
}
  
int main(int argc, char* argv[]) 
{
	//Record duration for each experiment
	double start; 
	double end; 
    double elapsed_time;
    double cum_elapsed_time, avg_elapsed_time;

 	//Number of experiments to run for each thread count
    int n = 10;

    //Number of thread counts to test
    int threads[7] = {1, 2, 4, 8, 16, 32, 64};
	
	//Dimensions of matrices
	int n = 100, m = 100, p = 100;
	float **A;
	float **B;
	float **C;
	
	//Initialize 3 matrices
	A = initialize_matrix(n,m,'A');
	B = initialize_matrix(m,p,'B');
	C = initialize_matrix(n,p,'C');

	//Multiply matrices
	//Record average elapsed time for each thread count
	for(int i=0; i < 7; i++){
		cum_elapsed_time = 0;
		omp_set_num_threads(threads[i]);
		for(int j=0; j<n; j++){
			start = omp_get_wtime();
			matrix_mult(n, m, p, A, B, C);
			end = omp_get_wtime();
			elapsed_time = end-start;
			cum_elapsed_time += elapsed_time;
		}
		avg_elapsed_time = cum_elapsed_time / n;
		printf("Number of threads utilized: %d | Average elapsed time over %d runs: %f\n", threads[i], n, avg_elapsed_time);
	}

	//Free A
	for (int i=0; i<r; i++) 
		 free(A[i]);
	free(A);

	//Free B
	for (int i=0; i<r; i++) 
		 free(B[i]);
	free(B);
	
} 