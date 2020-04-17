#!/bin/bash
#SBATCH --ntasks=2
#SBATCH --nodes=2

# NOTE : in order for this to run, np <= ntasks
module load openmpi-1.8/gcc-4.9.2
mpirun -np 2 ./a.out
