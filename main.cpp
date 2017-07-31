#include <stdio.h>
#include <stdlib.h>

#include "convolution.h"
#include "io.h"
#include "kernels.h"
#include "ops.h"
#include "proc.h"
#include "types.h"

void
sobel(IMG_Char input, IMG_Char thin, unsigned char gthresh, 
	  float athresh, unsigned char efactor, char *fn);
void
robert(IMG_Char input, IMG_Char thin, unsigned char gthresh, 
	   float athresh, unsigned char efactor, char *fn);
int 
main(int argc, char *argv[])
{
	/* Setup input. */
	char *file_names[2] = { (char*)"lena.jpg", (char*)"HappyFish.jpg" };
	
	unsigned char gthresh_sobel[2] = { 120, 100 };
	float athresh_sobel[2] = { 100.0, 170.0 };
	unsigned char efactor_sobel[2] = { 1, 2 };

	unsigned char gthresh_robert[2] = { 27, 60 };
	float athresh_robert[2] = { 100.0, 200.0 };
	unsigned char efactor_robert[2] = { 2, 1 };

	IMG_Char input[2];
	IMG_Char thin[2];

	int i;
	for (i=0; i!=2; i++)
	{
		/* Read the image into an array of signed chars. */
		char dir[100];
		sprintf(dir, "test_data/%s", file_names[i]);
		read_image_char(dir, &input[i]);

		allocate_image_char(&thin[i], input[i].rows, input[i].cols);

		/* Perform sobel. */
		sobel(input[i], 
			  thin[i], 
			  gthresh_sobel[i], 
			  athresh_sobel[i], 
			  efactor_sobel[i],
			  file_names[i]);
	
		/* Perform robert. */
		robert(input[i], 
			   thin[i], 
			   gthresh_robert[i], 
			   athresh_robert[i], 
			   efactor_robert[i],
			   file_names[i]);
		
	}

	return 0;
}

void
sobel(IMG_Char input, IMG_Char thin, 
	  unsigned char gthresh, float athresh, 
	  unsigned char efactor, char *fn)
{
	char name[5][100];

	/* Get the sobel kernels. */
	IMG_Char kernelX, kernelY;
	sobel_kernels(&kernelX, &kernelY);

	/* Covolve the input with the sobel kernels. */
	IMG_Char outputX, outputY;
	outputX.rows = outputY.rows = input.rows;
	outputX.cols = outputY.cols = input.cols;

	allocate_image_char(&outputX, input.rows, input.cols);
	allocate_image_char(&outputY, input.rows, input.cols);

	convolution(input, kernelX, outputX);
	convolution(input, kernelY, outputY);

	/* Get the magnitude and direction of the gradients. */
	IMG_Char grad; IMG_Float angle;
	grad.rows = angle.rows = input.rows;
	grad.cols = angle.cols = input.cols;

	allocate_image_char(&grad, input.rows, input.cols);
	allocate_image_float(&angle, input.rows, input.cols);

	gradient_magnitude(outputX, outputY, grad);
	gradient_direction(outputX, outputY, angle);

	sprintf(name[0], "test_results/Sobel Gradient Magnitude Image of %s", fn);
	sprintf(name[1], "test_results/Sobel Gradient Direction Image of %s", fn);

	write_image_char(name[0], grad);
	write_image_float(name[1], angle);

	free_image_char(&outputX);
	free_image_char(&outputY);

	/* Threshold the gradient values. */
	IMG_Char mbin, abin;
	mbin.rows = abin.rows = input.rows;
	mbin.cols = abin.cols = input.cols;

	allocate_image_char(&mbin, input.rows, input.cols);
	allocate_image_char(&abin, input.rows, input.cols);

	threshold_char(grad, mbin, gthresh);
	threshold_float(angle, abin, athresh);

	sprintf(name[2], "test_results/Sobel Threshold Gradient Magnitude of %s", fn);
	sprintf(name[3], "test_results/Sobel Threshold Gradient Direction of %s", fn);

	write_image_char(name[2], mbin);
	write_image_char(name[3], abin);

	/* Perform edge enlargement. */
	IMG_Char enlarge;
	enlarge.rows = input.rows;
	enlarge.cols = input.cols;

	allocate_image_char(&enlarge, input.rows, input.cols);

	enlarge_char(mbin, enlarge, efactor);

	free_image_char(&mbin);
	free_image_char(&abin);

	thinning_char(enlarge, thin);

	sprintf(name[4], "test_results/Sobel Edge Thinned Image of %s", fn);
	write_image_char(name[4], thin);

	free_image_char(&enlarge);	
}

void
robert(IMG_Char input, IMG_Char thin, 
	  unsigned char gthresh, float athresh, 
	  unsigned char efactor, char *fn)
{
	char name[5][100];

	/* Get the robert kernels. */
	IMG_Char kernelX, kernelY;
	robert_kernels(&kernelX, &kernelY);

	/* Covolve the input with the robert kernels. */
	IMG_Char outputX, outputY;
	outputX.rows = outputY.rows = input.rows;
	outputX.cols = outputY.cols = input.cols;

	allocate_image_char(&outputX, input.rows, input.cols);
	allocate_image_char(&outputY, input.rows, input.cols);

	convolution(input, kernelX, outputX);
	convolution(input, kernelY, outputY);

	/* Get the magnitude and direction of the gradients. */
	IMG_Char grad; IMG_Float angle;
	grad.rows = angle.rows = input.rows;
	grad.cols = angle.cols = input.cols;

	allocate_image_char(&grad, input.rows, input.cols);
	allocate_image_float(&angle, input.rows, input.cols);

	gradient_magnitude(outputX, outputY, grad);
	gradient_direction(outputX, outputY, angle);

	sprintf(name[0], "test_results/Robert Gradient Magnitude Image of %s", fn);
	sprintf(name[1], "test_results/Robert Gradient Direction Image of %s", fn);

	write_image_char(name[0], grad);
	write_image_float(name[1], angle);
	
	free_image_char(&outputX);
	free_image_char(&outputY);

	/* Threshold the gradient values. */
	IMG_Char mbin, abin;
	mbin.rows = abin.rows = input.rows;
	mbin.cols = abin.cols = input.cols;

	allocate_image_char(&mbin, input.rows, input.cols);
	allocate_image_char(&abin, input.rows, input.cols);

	threshold_char(grad, mbin, gthresh);
	threshold_float(angle, abin, athresh);

	sprintf(name[2], "test_results/Robert Threshold Gradient Magnitude of %s", fn);
	sprintf(name[3], "test_results/Robert Threshold Gradient Direction of %s", fn);

	write_image_char(name[2], mbin);
	write_image_char(name[3], abin);

	/* Perform edge enlargement. */
	IMG_Char enlarge;
	enlarge.rows = input.rows;
	enlarge.cols = input.cols;

	allocate_image_char(&enlarge, input.rows, input.cols);

	enlarge_char(mbin, enlarge, efactor);

	free_image_char(&mbin);
	free_image_char(&abin);

	thinning_char(enlarge, thin);

	sprintf(name[4], "test_results/Robert Edge Thinned Image of %s", fn);
	write_image_char(name[4], thin);

	free_image_char(&enlarge);	
}
