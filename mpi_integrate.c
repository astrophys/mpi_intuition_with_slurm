/**************************************************************
 *  AUTHOR : Ali Snedden
 *  DATE   : 7/1/15
 *  LICENSE: 7/1/15
 *  PURPOSE: To refresh myself on how using MPI. Let's do a 
 *           numerical integration using the trapezoidal rule.
 *  NOTES  :
 *  
 *
 *
 *************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/* 
 *  y-squared.
 */
double y(double x)
{
    return x*x;
}


int main(int argc, char * argv[])
{
    int taskID = -1;
    int NTasks = -1;
    /*double i    =  0;
    double xmax = 10;
    double xmin =  0;
    double dx   = 0.00001;
    double task_xmax = 0;
    double task_xmin = 0;
    double task_result = 0;
    double glob_result = 0;
    */



    /* MPI Initializations */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskID);
    MPI_Comm_size(MPI_COMM_WORLD, &NTasks);


   
    /* Get each Task's Range.*/
    //task_xmin = taskID * (xmax - xmin) / NTasks;
    //task_xmax = (taskID + 1) * (xmax - xmin) / NTasks;


    /* Break up integration*/ 
    /*for(i=task_xmin; i<task_xmax; i+=dx)
    {
        task_result += (y(i+dx) - y(i)) * dx / 2.0 +  y(i) * dx;
    }*/
  

    /* Collect Results */
    //MPI_Reduce(&task_result, &glob_result, 1, MPI_DOUBLE, MPI_SUM, 0, 
    //           MPI_COMM_WORLD);


    
    printf("Hello World from Task %i\n", taskID);
    /*if(taskID == 0)
    {
        printf("Integration from %f to %f of x2 = %f\n", xmin, xmax, glob_result);
    }*/

    MPI_Finalize();
    return 0;
}






