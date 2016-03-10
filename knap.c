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

   fscanf(fp, "%d %d", &N, &C);
   printf("The number of objects is %d, and the capacity is %d.\n", N, C);

   size    = N * sizeof(int);
   weights = (int *)malloc(size);
   profits = (int *)malloc(size);

   if ( weights == NULL || profits == NULL ) {
      printf("[ERROR] : Failed to allocate memory for weights/profits.\n");
      exit(1);
   }

   for ( i=0 ; i < N ; i++ ) {
      count = fscanf(fp, "%d %d", &(weights[i]), &(profits[i]));
      if ( count != 2 ) {
         printf("[ERROR] : Input file is not well formatted.\n");
         exit(1);
      }
   }

   fclose(fp);

   
   initialize_timer ();
   start_timer();
   // Solve for the optimal profit (create the table)





   // We only time the creation of the table

  stop_timer();
   time = elapsed_time ();

   printf("The optimal profit is %d Time taken : %lf.\n");

 // End of "Solve for the optimal profit"


// Find the solution (choice vector) by backtracking through the table

     
      printf("Solution vector is: \n");

      if (verbose) {
	// print the solution vector 
      }

   return 0;
}
