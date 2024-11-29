Specifications

Implement a program that converts the grayscale image representation from float based to integer based using C and x86 assembly language. Implement the function imgCvtGrayDoubleToInt(). 
Input- height, width, double float pixel values
Process: I=255(f).

Code
The C kernel is written as a function that is within the same file as the main.c program. It simply multiplies the given double float value to 255.0 and rounded the resulting value using round to nearest-ties to even. Then it converts it into uint8 by typecasting. 


Figure 01. C Kernel

The Assembly kernel is written in a separate .asm file entitled asmfuncImgCvtGrayDoubleToInt.asm and is called using the function declaration extern extern uint8_t asmImgCvtGrayDoubleToInt(double num) and function call resultArrayASM[i][j] = asmImgCvtGrayDoubleToInt([i][j]).  The Assembly file receives the parameter from C and passes it on to the xmm0, a simd register. Then var1 having a value of 255.0 is stored into xmm1 in preparation for multiplication. Using mulsd, xmm0 and xmm1 are multiplied together, and the product is stored in xmm0. Further, xmm0 as double float based value is converted into scalar double word integer using RAX  and rounded using round to nearest-ties to even. 

Figure 02. Assembly Kernel

The user is expected to input the width and height in the first line accordingly. Then, depending on the indicated image dimensions of height m and width n, it is expected that the user inputs the corresponding double float based values following m x n row-wise. Malloc was utilized to allocate memory dynamically for various array used in the program, allowing handling larger array sizes. Further, the memory was deallocated at the end of the program. Function under stdlib h and time.h were used to generate random values between 0 and 1 inclusive. 

Correctness Check
Initially, the outputs from C and x86 programs were manually computed and were evaluated using the expected values stated on the project specification. Following these values, attached below are the expected and actual values of both C and x86 programs using the round to nearest-ties to even with image dimensions of 3 x 4. 
INPUTS:
Height, Width : 3 4
Pixel Values:
0.25 0.35 0.45 0.33
0.55 0.65 0.75 0.33
0.85 0.95 0.15 0.33
OUTPUT
64, 89, 115, 84
140, 166, 191, 84
217, 242, 38, 84


Figure 03. Correctness Check


Analysis of Data
For each kernel version, the values for n (image dimensions) are [10, 10] , [100, 100], and [1000, 1000], [10000, 10000] which was extended as the first three were only required in the specification. For each version (debug and release version), each vector size value was executed 50 times to get the average execution time of the mapping function per both kernels. 

Debug Version

Figure 04. Debug Version 100*100 Execution Times Across Iterations Line Chart

Figure 05. Debug Version 1000*1000 Execution Times Across Iterations Line Chart

Figure 06. Debug Version 10000*10000 Execution Times Across Iterations Line Chart

Release Version

Figure 07. Debug Version 100*100 Execution Times Across Iterations Line Chart

Figure 08. Debug Version 1000*1000 Execution Times Across Iterations Line Chart

Figure 09. Debug Version 10000*10000 Execution Times Across Iterations Line Chart

Average Execution Time






