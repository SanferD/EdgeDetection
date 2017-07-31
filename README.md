# EdgeDetection

## Running the Code
Runs on Linux.
Uses opencv library to read and write images only.
All other operations are done using standard C.
To compile: make
To run: ./main

## Description of code

Test images are contained in the folder test_data
Running ./main will read the files in test\_data, read each input image, extract its edges and gradients, and save the results in test\_results folder.
If you are adding new images then you will need to change line 21 in main.cpp
