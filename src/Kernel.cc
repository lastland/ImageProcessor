#include "Kernel.hh"

void MakeKernel3X3Cross(Kernel *kernel)
{
    MakeKernelZero(kernel);
    
    kernel->value[kernel_size / 2][kernel_size / 2] = 1;
    kernel->value[kernel_size / 2 - 1][kernel_size / 2] = 1;
    kernel->value[kernel_size / 2][kernel_size / 2 - 1] = 1;
    kernel->value[kernel_size / 2 + 1][kernel_size / 2] = 1;
    kernel->value[kernel_size / 2][kernel_size / 2 + 1] = 1;
}

void MakeKernelZero(Kernel *kernel)
{
    for (int i = 0; i < kernel_size; i++)
        for (int j = 0; j < kernel_size; j++)
            kernel->value[i][j] = 0;
}
