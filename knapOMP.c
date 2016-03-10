//
// File name   : knap.c
// Description : Dynamic Programming for the 0/1 knapsack  problem. 
//

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"


#define    MAX(x,y)   ((x)>(y) ? (x) : (y))
#define    table(i,j)    table[(i)*(C+1)+(j)]

int main(int argc, char **argv) {

   FILE   *fp;
   int    N, C;                   // # of objects, capacity 
   int    *weights, *profits;     // weights and profits
   int    verbose;
	int*	solution_vector;
	// table
	int *table;

   // Temp variables
   int    i, j, count, size;

   // Time
   double time;

   // Read input file:
   //  first line:  # of objects, knapsack capacity, 
   //  next lines:   weight and profit  of next object (1 object per line)
   if ( argc > 1 ) {
      fp = fopen(argv[1], "r"); 
      if ( fp == NULL) {
         printf("[ERROR] : Failed to read file named '%s'.\n", argv[1]);
         exit(1);
      }
   } else {
      printf("USAGE : %s [filename].\n", argv[0]);
      exit(1);
   }

   if (argc > 2) verbose = 1; else verbose = 0;

   if(fscanf(fp, "%d %d", &N, &C) != 2)
	{
		printf("could not read number of objects or capacity\n");
		exit(1);
	}
	
   printf("The number of objects is %d, and the capacity is %d.\n", N, C);

   size    = (N+ 1) * sizeof(int);
   weights = (int *)malloc(size);
   profits = (int *)malloc(size);

   if ( weights == NULL || profits == NULL ) {
      printf("[ERROR] : Failed to allocate memory for weights/profits.\n");
      exit(1);
   }

	weights[0] = 0;
	profits[0] = 0;
   
	solution_vector = malloc(sizeof(int) * N); 
	table = (int *)malloc(sizeof(int) * (N + 1)  * (C + 1));
	
   for ( i=1 ; i <= N ; i++ ) {
		for(j = 0; j <= C; j++)
			table(i-1,j) = 0;
		solution_vector[i-1] = 0;
	  	count = fscanf(fp, "%d %d", &(weights[i]), &(profits[i]));
	
      if ( count != 2 ) {
      	printf("[ERROR] : Input file is not well formatted.\n");
      	exit(1);
     	}
   }

	for(j = 0; j <= C; j++)
		table(N,j) = 0;

   fclose(fp);

	// init timer
   initialize_timer ();
   start_timer();

   // Solve for the optimal profit (create the table)
	for(i = 1; i <= N ; i++)
	{
		#pragma omp parallel for schedule(static) 
		for(j = 0; j <= C; j++)
		{
			if(weights[i] > j)
			{
				table(i,j) = table(i-1, j);
			}
			else
			{
				table(i,j) = MAX(table(i-1, j), profits[i] + table(i-1, j - weights[i]));
			}
		}
		// TODO maybe get rid of barrier
		#pragma omp barrier
	}
	
   // We only time the creation of the table

	stop_timer();
   time = elapsed_time ();

	printf("The optimal profit is %d Time taken : %lf.\n", table(N,C), time);

 // End of "Solve for the optimal profit"


// Find the solution (choice vector) by backtracking through the table

      printf("Solution vector is: \n");

      if (verbose) {
      	i = N;
			j = C;
			while(i > 0 && j > 0)
			{
				if(table(i,j) == table(i-1,j))
				{
					solution_vector[i-1] = 0;
				}
				else
				{
					solution_vector[i-1] = 1;
					j = j - weights[i];
				}
				
				i--;

			}
			printf(" --> ");
			for(i = 0; i < N; i++)
				printf("%d ", solution_vector[i]);
			printf("\n");
		}

	free(solution_vector);
	free(weights);
	free(profits);
	free(table);

   return 0;
}
