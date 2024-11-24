#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdint.h>

// External assembly function
extern UINT8 asmImgCvtGrayDoubleToInt(double num);

UINT8 cImgCvtGrayDoubleToInt(double num) {
    double scaled = num * 255.0;
    int rounded_result = nearbyint(scaled);
    return (UINT8)rounded_result;
}

int main() {
    
    int width1 = 4;
    int height1 = 3;

    double array[3][4] = {
        {0.25, 0.35, 0.45, 0.33},
        {0.55, 0.65, 0.75, 0.33},
        {0.85, 0.95, 0.15, 0.33}
    };

    UINT8 resultArrayC[3][4];
    UINT8 resultArrayASM[3][4];

    for (int i = 0; i < height1; i++) {
        for (int j = 0; j < width1; j++) {
            resultArrayC[i][j] = cImgCvtGrayDoubleToInt(array[i][j]);
            resultArrayASM[i][j] = asmImgCvtGrayDoubleToInt(array[i][j]);
        }
    }

    printf("Original Array (Gray Double Floating Point):\n");
    for (int i = 0; i < height1; i++) {
        for (int j = 0; j < width1; j++) {
            printf("%.2f\t", array[i][j]);
        }
        printf("\n");
    }

    printf("\nProcessed Array[C] (Results in uint8):\n");
    for (int i = 0; i < height1; i++) {
        for (int j = 0; j < width1; j++) {
            printf("%hhu\t", resultArrayC[i][j]);
        }
        printf("\n");
    }

    printf("\nProcessed Array[ASM] (Results in uint8):\n");
    for (int i = 0; i < height1; i++) {
        for (int j = 0; j < width1; j++) {
            printf("%hhu\t", resultArrayASM[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n\n");

    /************************** TESTING **********************************/        

    /*
    int widthT = 1000;
    int heightT = 1000;
    
    double** arrayT = (double**)malloc(widthT * sizeof(double*));
    UINT8** resultArrayT = (UINT8**)malloc(widthT * sizeof(UINT8*));

    for (int i = 0; i < widthT; i++) {
        arrayT[i] = (double*)malloc(heightT * sizeof(double));
        resultArrayT[i] = (UINT8*)malloc(heightT * sizeof(UINT8));
    }

    srand(time(NULL));    //random number generator

    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            arrayT[i][j] = (double)rand() / RAND_MAX; // Random double between 0 and 1
        }
    }


    int runs = 30;
    double total_time = 0.0;

    for (int r = 0; r < runs; r++) {
        clock_t start_time = clock();

        // Apply the assembly function to each element
        for (int i = 0; i < widthT; i++) {
            for (int j = 0; j < heightT; j++) {
                resultArrayT[i][j] = asmImgCvtGrayDoubleToInt(arrayT[i][j]);
            }
        }

        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time += time_taken;

        printf("Run %d Execution Time: %.6f seconds\n", r + 1, time_taken);
    }

    printf("\nOriginal Array (Random Doubles):\n");
    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            printf("%.2f \t", arrayT[i][j]);
        }
        printf("\n");
    }

    printf("\nProcessed Array (Integer Results):\n");
    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            printf("%hhu \t", resultArrayT[i][j]);
        }
        printf("\n");
    }
    
    double average_time = total_time / runs;
    printf("\nAverage Execution Time over %d runs: %.6f seconds\n", runs, average_time);

    // Free allocated memory
    for (int i = 0; i < widthT; i++) {
        free(arrayT[i]);
        free(resultArrayT[i]);
    }
    free(arrayT);
    free(resultArrayT);
    */
    return 0;
}
