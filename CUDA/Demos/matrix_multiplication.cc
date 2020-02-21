// #include <cuda.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>

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

float * flatten(int r, int c, float ** M){
  float * M_flatten;
  int i, j, k;
  M_flatten = (float *)malloc(r * c * sizeof(float)); 
  for (i=0; i<r; i++) {
    for(j=0; j<c; j++){
      M_flatten[i*r+j] = M[i][j];
    }
  }
  return M_flatten;
}

void print_matrix(float ** M, int r, int c){
  for(int i=0; i<r; i++){
    for(int j=0; i<c; i++){
      printf("%f ",M[i][j]);
    }
    printf("\n");
  }
}

void print_vector(float * V, int size){
  for(int i=0; i<size; i++){
    printf("%f\n",V[i]);
  }
}

// __global__ void MatrixMulKernel(float* M, float* N, float* P, Int Width)
// {
//   __shared__ float ds_M[TILE_WIDTH][TILE_WIDTH];
//   __shared__ float ds_N[TILE_WIDTH][TILE_WIDTH];

//   int bx = blockIdx.x;  int by = blockIdx.y;
//   int tx = threadIdx.x; int ty = threadIdx.y;

//   int Row = by * blockDim.y + ty;
//   int Col = bx * blockDim.x + tx;
//   float Pvalue = 0;

//  // Loop over the M and N tiles required to compute the P element
//  for (int p = 0; p < n/TILE_WIDTH; ++p) {
//     // Collaborative loading of M and N tiles into shared memory
//     ds_M[ty][tx] = M[Row*Width + p*TILE_WIDTH+tx];
//     ds_N[ty][tx] = N[(t*TILE_WIDTH+ty)*Width + Col];
//     __syncthreads();

//     for (int i = 0; i < TILE_WIDTH; ++i)Pvalue += ds_M[ty][i] * ds_N[i][tx];
//     __synchthreads();
//   }	
//   P[Row*Width+Col] = Pvalue;
// }

int main(int argc, char **argv){
  //Dimensions of matrices
  int n = 2, m = 2, p = 3;
  float **h_A;
  float **h_B;
  float **h_C;
  
  //Initialize 3 matrices
  h_A = initialize_matrix(n,m,'A');
  h_B = initialize_matrix(m,p,'B');
  h_C = initialize_matrix(n,p,'C');

  //Flatten Matrices
  float *h_A_flat = (float *)malloc(n * m * sizeof(float)); 
  h_A_flat = flatten(n,m,h_A);
  print_vector(h_A_flat,n*m);
  print_matrix(h_A,n,m);

  //
  // cudaMalloc((void **) &d_A, size);
  // cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
}