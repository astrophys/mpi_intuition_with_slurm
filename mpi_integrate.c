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

/*
void print_message(char * str, int verbose)
{
    if(verbose == 1){
        printf("%s",str)
    }else{
        printf("%s",str)
    }
}
*/

double compute_integral(int xmin, int xmax, int ntasks, int taskID, int step, char * hostname)
{
    /* Get each Task's Range.*/
    double task_xmin = taskID * (xmax - xmin) / ntasks;
    double task_xmax = (taskID + 1) * (xmax - xmin) / ntasks;
    double dx   = 0.00001;
    double task_result = 0;
    double i=0;
    printf("Task %i step %i host %s : [%.3f,%.3f]\n", taskID, step, hostname, task_xmin, task_xmax);
    fflush(stdout);
    
    
    /* Break up integration*/ 
    for(i=task_xmin; i<task_xmax; i+=dx)
    {
        // Trapezoidal rule
        task_result += (y(i+dx) - y(i)) * dx / 2.0 +  y(i) * dx;
    }
    return(task_result);
}


int main(int argc, char * argv[])
{
    int taskID = -1;
    int ntasks = -1;
    int nSteps = 100;
    int step = 0;
    int verbose = 0;
    double xmax = 1000;
    double xmin =  0;
    double task_result = 0;
    double glob_result = 0;
    char hostname[250];
    hostname[249]='\0';

    /* MPI Initializations */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskID);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    gethostname(hostname, 1023);
    printf("Hello World from Task %i on %s\n", taskID,hostname);


    /* Master Loop */ 
    for(step=0; step<nSteps; step++){
        if(taskID == 0){
            //printf("Step : %i\n", step);
            task_result = compute_integral(xmin, xmax, ntasks, taskID, step,
                                           hostname);

        }else{
            task_result = compute_integral(xmin, xmax, ntasks, taskID, step,
                                           hostname);
        }
        MPI_Barrier(MPI_COMM_WORLD);    // Ensure every task completes

        /* Collect Results */
        MPI_Reduce(&task_result, &glob_result, 1, MPI_DOUBLE, MPI_SUM, 0, 
                   MPI_COMM_WORLD);

        if(taskID == 0)
        {
            printf("Step %i host %s Integration from %f to %f of x2 = %f\n\n", step,
                   hostname, xmin, xmax, glob_result);
            fflush(stdout);
        }
        glob_result=0;
    }

    MPI_Finalize();
    return 0;
}






