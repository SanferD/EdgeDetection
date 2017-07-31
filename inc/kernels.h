#ifndef _KERNELS_H
#define _KERNELS_H

#include "types.h"

void 
get_thinning_kernel(IMG_Char *kernel, int n);

void 
get_thinning_kernel0(IMG_Char *kernel);

void 
get_thinning_kernel1(IMG_Char *kernel);

void 
get_thinning_kernel2(IMG_Char *kernel);

void 
get_thinning_kernel3(IMG_Char *kernel);

void 
get_thinning_kernel4(IMG_Char *kernel);

void 
get_thinning_kernel5(IMG_Char *kernel);

void 
get_thinning_kernel6(IMG_Char *kernel);

void 
sobel_kernels(IMG_Char *kx, IMG_Char *ky);

void
robert_kernels(IMG_Char *kx, IMG_Char *ky);

#endif