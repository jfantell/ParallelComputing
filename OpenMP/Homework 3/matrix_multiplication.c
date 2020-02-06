// OpenMP header 
#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

void matrix_mult(int r, int c, int **A, int **B, int **C){

	int i, j, k;
	#pragma omp parallel shared(A,B,C) private(i,j,k)
	// printf("Number of threads actually used %d\n", omp_get_num_threads());
	#pragma omp for simd
	for(i = 0; i < r; ++i) {
		for(j = 0; j < c ; j++){
			for(k=0; k < c ; k++){
				C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
			}
		}
	}
}

int ** initialize_matrix(int r, int c, char type){
	int ** M;
	int i, j, k;
	M = (int **)malloc(r * sizeof(int *)); 
	for (i=0; i<r; i++) {
		M[i] = (int *)malloc(c * sizeof(int));
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

	// printf("Starting matrix multiply program\n");
	// printf("How many threads would you like to use?\n");
	
	// //Get user input : number of desired threads to use
	// char num_threads_buffer[4];
	// fgets(num_threads_buffer,4,stdin);

	//parse string input
	// int num_threads = atoi(num_threads_buffer);

	//setup variables to record elapsed time
	clock_t start, end;
    double elapsed_time;
    double cum_elapsed_time, avg_elapsed_time;
    int i, j;
    int n = 10; //Number of trials to run per experiment
	
	int r = 500, c = 500;
	int **A;
	int **B;
	int **C;
	
	A = initialize_matrix(r,c,'A');
	B = initialize_matrix(r,c,'B');
	C = initialize_matrix(r,c,'C');

	int threads[7] = {1, 2, 4, 8, 16, 32, 64};
	for(i=0; i < 7; i++){
		cum_elapsed_time = 0;
		for(j=0; j<n; j++){ //Three experiments for each number of threads
			start = clock();
			omp_set_num_threads(threads[i]);
			matrix_mult(r, c, A, B, C);
			end = clock();
			elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;
			cum_elapsed_time += elapsed_time;
		}
		avg_elapsed_time = cum_elapsed_time / n;
		printf("Num threads %d Average elapsed time %f\n", threads[i], avg_elapsed_time);
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