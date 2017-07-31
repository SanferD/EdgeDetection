#include <stdio.h>

#include "io.h"
#include "kernels.h"

void 
get_thinning_kernel0(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[0][0] = kernel->image[0][1] = kernel->image[0][2] = 1;
	kernel->image[1][0] = kernel->image[1][1] = kernel->image[1][2] = 1;
	kernel->image[2][0] = kernel->image[2][1] = kernel->image[2][2] = 1;
}

void 
get_thinning_kernel1(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[0][0] = kernel->image[1][1] = 1;
	kernel->image[1][0] = kernel->image[0][1] = -1;
	
	kernel->image[0][2] = kernel->image[1][2] = kernel->image[2][2] = 0;
	kernel->image[2][0] = kernel->image[2][1] = 0;
}

void 
get_thinning_kernel2(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[0][2] = kernel->image[1][1] = 1;
	kernel->image[0][1] = kernel->image[1][2] = -1;
	
	kernel->image[0][0] = kernel->image[1][0] = kernel->image[2][0] = 0;
	kernel->image[2][0] = kernel->image[2][1] = kernel->image[2][2] = 0;
}

void 
get_thinning_kernel3(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[2][2] = kernel->image[1][1] = 1;
	kernel->image[1][2] = kernel->image[2][1] = -1;
	
	kernel->image[0][0] = kernel->image[1][0] = kernel->image[2][0] = 0;
	kernel->image[0][1] = kernel->image[0][2] = 0;
}

void 
get_thinning_kernel4(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[2][0] = kernel->image[1][1] = 1;
	kernel->image[1][0] = kernel->image[2][1] = -1;
	
	kernel->image[0][2] = kernel->image[1][2] = kernel->image[2][2] = 0;
	kernel->image[0][0] = kernel->image[0][1] = 0;
}

void 
get_thinning_kernel5(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[1][0] = kernel->image[1][2] = 1;
	kernel->image[0][1] = kernel->image[2][1] = -1;
	
	kernel->image[0][0] = kernel->image[0][2] = kernel->image[1][1] = 0;
	kernel->image[2][0] = kernel->image[2][2] = 0;
}

void 
get_thinning_kernel6(IMG_Char *kernel)
{
	allocate_image_char(kernel, 3, 3);

	kernel->image[0][1] = kernel->image[2][1] = 1;
	kernel->image[1][0] = kernel->image[1][2] = -1;
	
	kernel->image[0][0] = kernel->image[0][2] = kernel->image[1][1] = 0;
	kernel->image[2][0] = kernel->image[2][2] = 0;
}


void
sobel_kernels(IMG_Char *kx, IMG_Char *ky)
{
	allocate_image_char(kx, 3, 3);
	allocate_image_char(ky, 3, 3);

	kx->image[0][0] = ky->image[0][0] = (char) -1;
	kx->image[0][1] = ky->image[1][0] = (char) 0;
	kx->image[0][2] = ky->image[2][0] = (char) 1;

	kx->image[1][0] = ky->image[0][1] = (char) -2;
	kx->image[1][1] = ky->image[1][1] = (char) 0;
	kx->image[1][2] = ky->image[2][1] = (char) 2;

	kx->image[2][0] = ky->image[0][2] = (char) -1;
	kx->image[2][1] = ky->image[1][2] = (char) 0;
	kx->image[2][2] = ky->image[2][2] = (char) 1;
}

void 
get_thinning_kernel(IMG_Char *kernel, int n)
{
	switch (n)
	{
		case 0:
			get_thinning_kernel0(kernel);
			break;
		case 1:
			get_thinning_kernel1(kernel);
			break;
		case 2:
			get_thinning_kernel2(kernel);
			break;
		case 3:
			get_thinning_kernel3(kernel);
			break;
		case 4:
			get_thinning_kernel4(kernel);
			break;
		case 5:
			get_thinning_kernel5(kernel);
			break;
		case 6:
			get_thinning_kernel6(kernel);
			break;
	}

}

void
robert_kernels(IMG_Char *kx, IMG_Char *ky)
{
	kx->rows = ky->rows = kx->cols = ky->cols = 2;
	allocate_image_char(kx, 2, 2);
	allocate_image_char(ky, 2, 2);

	kx->image[0][0] = ky->image[0][1] = 1;
	kx->image[1][1] = ky->image[1][0] = -1;

	kx->image[0][1] = ky->image[0][0] = 0;
	kx->image[1][0] = ky->image[1][1] = 0;
}