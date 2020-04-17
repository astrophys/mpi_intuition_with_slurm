# Understanding Running MPI with SLURM

## What this code does
This code uses the trapezoidal rule to integrate a function, `y(x)` over the interval
`[x_{min}, x_{max}]`. It breaks up the integration across multiple processors using
MPI. It does this integration 100 times, in order to make it take minutes to
complete. This ensures that there is time to inspect the processes running on 
different computers.

I use this code to better understand how to run MPI jobs in SLURM.

## Dependencies
1. `MPI`, tested with `openmpi-1.8` and `mvapich2-2.1`
2. `C-compiler`, tested with `GCC/4.9.2
3. `SLURM`, tested with 17.11.7.
Note we use modules to manage software on our system. Any mechanism to get the 
compilers and commands in your shell `PATH` is acceptable.


## Insight
### Interactive allocation
In order for these examples to work, you need to ensure that the number of
`--ntasks` you request is greater than or equal to the number of cores you request
when with `mpirun` (see the `-np` argument).

##### Example 1
Working on the login node to the cluster, we make an allocation.
`salloc` spawns a new shell (still on the login node). From this new shell, we can
run our MPI job. SLURM behind the seens dispatches the work from the login node
to the interactive allocation. `stdout` gets routed back to the login node.
When you execute `mpirun`, log into the nodes and run `top` to inspect.

    $ module load openmpi-1.8/gcc-4.9.2
    $ mpicc mpi_integrate.c 
    $ salloc --ntasks=2 --nodes=2     # Gets two nodes with 1 core each, spawns new shell
         (within new shell...)       
    $ mpirun -np 2 ./a.out            # Works as expected, both cores, one on each node does work. Use a seperate shell to log into each node in allocation and run `top`



##### Example 2 - what NOT to do
Working on the login node to the cluster, we make an allocation. Then from any shell
try to access the allocation.

     $ module load openmpi-1.8/gcc-4.9.2
     $ mpicc mpi_integrate.c 
     $ salloc --ntasks=2 --nodes=2     # Gets two nodes with 1 core each
          (from any shell...)
     $ srun --mpi=openmpi --jobid=XXXX mpirun -np 2 ./a.out # WHOOPS! This is basically running two instances of `mpirun -np 2 ./a.out`, one on each node
     



