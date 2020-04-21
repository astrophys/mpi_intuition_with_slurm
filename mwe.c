#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char * argv[])
{
    int taskID = -1;
    int ntasks = -1;
    int nSteps = 100;           // Number of times to do the integration
    int step = 0;               // Current step
    char hostname[250];
    hostname[249]='\0';

    /* MPI Initializations */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskID);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    gethostname(hostname, 249);
    printf("Hello from Task %i on %s\n", taskID,hostname);


    /* Master Loop */ 
    for(step=0; step<nSteps; step++){
        printf("%i   : task %i   hostname %s\n", step, taskID, hostname);
        usleep(1000000);
        fflush(stdout);
        MPI_Barrier(MPI_COMM_WORLD);    // Ensure every task completes
    }

    MPI_Finalize();
    return 0;
}
