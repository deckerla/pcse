// Homework 0 for PSCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// random number program
void initialize(float **array,int nE){
	int i,j;
	srand((unsigned)time(NULL));
	for (i=0; i<nE; i++){
		for (j=0; j<nE; j++){
			 array[i][j] = rand()*1.0/(1.0*RAND_MAX);			
		}
		
	}
	
	return ;
}

// smoothing program
void smooth(float **x, float **y, int nE, float a, float b, float c){
	int j, i;
	for (i=1;i<nE-1;i++){
		for (j=1;j<nE-1; j++){
			
			y[i][j] = a * (x[i-1][j-1]+x[i+1][j-1]+x[i+1][j+1]) 
				+ b * (x[i-1][j]+x[i+1][j]+x[i][j-1]+x[i][j+1]) 
				+ c * x[i][j];
		}
		
	}
	return;
}


// threshold counting
void count(float **x, int nE, float t, int *below){
	int counter = 0;	
	
	int i,j;
	for (i=1; i< nE-1; i++){
		for(j=1;j<nE-1;j++){
			if (x[i][j] < t){
				//printf("hello there ");
				counter = counter+1;
			}
			
		}
		
	}
	*below = (int)count;
	return ; 
	
}
int main()
{
	float a=0.05, b=0.1, c=0.4; //constants
	float t=0.1 ;// threshold
	
	int n = 16384; //precursor
	int nE = n + 2; //number of elements in each dimension
	int i;
	float *x[nE], *y[nE];
	
	//times
	float t_start , t_end , t_alloc_x, t_alloc_y, t_initialize, t_smooth, t_count_x, t_count_y;
	
	t_start = clock();
	for (i=0; i<nE; i++){
		x[i] = (float *)malloc(nE * sizeof(float));	
	}
	t_end = clock();
	
	t_alloc_x = (t_end-t_start)/(float)CLOCKS_PER_SEC;
		
	t_start = clock();
	for (i=0; i<nE; i++){
		y[i] = (float *)malloc(nE * sizeof(float));	
	}
	t_end = clock();
	
	t_alloc_y = (t_end-t_start)/(float)CLOCKS_PER_SEC;
	
	// initalize with random numbers
	t_start = clock();
	initialize(x,nE);
	t_end = clock();
	
	t_initialize = (t_end-t_start)/(float)CLOCKS_PER_SEC;
	
	// smooth
	t_start = clock();
	smooth(x,y,nE,a,b,c);
	t_end = clock();
	t_smooth = (t_end-t_start)/(float)CLOCKS_PER_SEC;
	
	int belowX, belowY;
	// count elements below
	
	t_start = clock();
	count(x,nE,t, &belowX);
	t_end = clock();
	t_count_x = (t_end-t_start)/(float)CLOCKS_PER_SEC;
	
	t_start = clock();
	count(y,nE,t,&belowY);
	t_end = clock();
	t_count_y = (t_end-t_start)/(float)CLOCKS_PER_SEC;	
	
	//printf("%d \n",belowX);
	
	// free arrays
	free(*x);
	free(*y);
	
	// display results
	// how many total elements?
	int totE = nE*nE;
	// interior?
	int intE = n*n;
	int bytes = totE * sizeof(float);
	//fractional content
	float fracX = 1.0*belowX/(1.0*totE);
	float fracY = 1.0*belowY/(1.0*intE);
	printf("\n\n RESULTS");
	printf("                                                ,,,\n                                                       (o o)\n----------------------------------------------------ooO-(_)-Ooo-------\n");

	printf("%d Elements per row or column \n",nE);
	printf("%d Inner elements per row or column \n",n);
	printf("%d Total elements per array \n",totE);
	printf("%d Interior elements per array \n",intE);
	printf("%d bytes used per array \n",bytes);
	printf("############################################################ \n");
	printf("Threshold Value is %g \n",t);
	printf("%d X elements below threshold \n",belowX);
	printf("%d Y elements below threshold \n",belowY);
	printf("Fraction of X elements below threshold is %g \n",fracX);
	printf("Fraction of Y elements below threshold is %g \n",fracY);
	printf("(Y calculation doesn't include exterior elements)\n");
	printf("############################################################ \n")	;
	printf("TIMING INFO (s) \n");
	printf("Alloc X \t Alloc Y \t Initialize \t Smooth \t Count X \t Count Y \n");
	printf("%g \t %g \t %g \t %g \t %g \t %g \n",t_alloc_x,t_alloc_y,t_initialize,t_smooth,t_count_x,t_count_y);
	printf("############################################################ \n")	;	
	
		return 0;

}


