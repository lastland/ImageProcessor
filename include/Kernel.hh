#ifndef _KERNEL_H_
#define _KERNEL_H_

const int kernel_size = 5;

struct Kernel
{
    int value[kernel_size][kernel_size];
};

void MakeKernel3X3Cross(Kernel*);
void MakeKernelZero(Kernel*);

#endif /* _KERNEL_H_ */
