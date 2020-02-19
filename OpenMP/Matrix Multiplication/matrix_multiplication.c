// OpenMP header 
#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

void matrix_mult(int r, int c, float **A, float **B, float **C){

	int i, j, k;
	#pragma omp parallel shared(A,B,C) private(i,j,k)
	#pragma omp for simd
	for(i = 0; i < r; ++i) {
		for(j = 0; j < c ; j++){
			for(k=0; k < c ; k++){
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
	 
	double start; 
	double end; 
    double elapsed_time;
    double cum_elapsed_time, avg_elapsed_time;
    int i, j;
    int n = 10; //Number of trials to run per experiment
	
	int r = 100, c = 100;
	float **A;
	float **B;
	float **C;
	
	A = initialize_matrix(r,c,'A');
	B = initialize_matrix(r,c,'B');
	C = initialize_matrix(r,c,'C');

	int threads[7] = {1, 2, 4, 8, 16, 32, 64};
	for(i=0; i < 7; i++){
		cum_elapsed_time = 0;
		omp_set_num_threads(threads[i]);
		for(j=0; j<n; j++){ //Three experiments for each number of threads
			start = omp_get_wtime();
			matrix_mult(r, c, A, B, C);
			end = omp_get_wtime();
			elapsed_time = end-start;
			cum_elapsed_time += elapsed_time;
		}
		avg_elapsed_time = cum_elapsed_time / n;
		printf("Number of threads utilized: %d | Average elapsed time over %d runs: %f\n", threads[i], n, avg_elapsed_time);
	}

	//Free A
	for (i=0; i<r; i++) 
		 free(A[i]);
	free(A);

	//Free B
	for (i=0; i<r; i++) 
		 free(B[i]);
	free(B);
	
} 