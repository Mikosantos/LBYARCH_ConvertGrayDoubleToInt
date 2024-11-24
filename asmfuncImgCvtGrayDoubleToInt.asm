#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdint.h>

// External assembly function
extern uint8_t asmImgCvtGrayDoubleToInt(double num);

uint8_t cImgCvtGrayDoubleToInt(double num) {
    double scaled = num * 255.0;
    int rounded_result = (int)lround(scaled);
    return (uint8_t)rounded_result;
}

int main() {
    /************************** TESTING based on specs **********************************/
        int width1, height1;

        scanf_s("%d %d", &height1, &width1);

        double** array = (double**)malloc(height1 * sizeof(double*));
        for (int i = 0; i < height1; i++) {
            array[i] = (double*)malloc(width1 * sizeof(double));
        }

        uint8_t** resultArrayC = (uint8_t**)malloc(height1 * sizeof(uint8_t*));
        uint8_t** resultArrayASM = (uint8_t**)malloc(height1 * sizeof(uint8_t*));
        for (int i = 0; i < height1; i++) {
            resultArrayC[i] = (uint8_t*)malloc(width1 * sizeof(uint8_t));
            resultArrayASM[i] = (uint8_t*)malloc(width1 * sizeof(uint8_t));
        }

        for (int i = 0; i < height1; i++) {
            for (int j = 0; j < width1; j++) {
                scanf_s("%lf", &array[i][j]);
            }
        }

        for (int i = 0; i < height1; i++) {
            for (int j = 0; j < width1; j++) {
                resultArrayC[i][j] = cImgCvtGrayDoubleToInt(array[i][j]);
                resultArrayASM[i][j] = asmImgCvtGrayDoubleToInt(array[i][j]);
            }
        }

        printf("\nOriginal Array (Gray Double Floating Point):\n");
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


    /************************** EXECUTION TIME Computation *******************************/
   /*
    int widthT = 1000;
    int heightT =1000;
    int runs = 50;
    double total_time_asm = 0.0;
    double total_time_c = 0.0;

    
    double** arrayT = (double**)malloc(widthT * sizeof(double*));
    UINT8** resultArrayT_ASM = (UINT8**)malloc(widthT * sizeof(UINT8*));
    UINT8** resultArrayT_C = (UINT8**)malloc(widthT * sizeof(UINT8*));

    for (int i = 0; i < widthT; i++) {
        arrayT[i] = (double*)malloc(heightT * sizeof(double));
        resultArrayT_ASM[i] = (UINT8*)malloc(heightT * sizeof(UINT8));
        resultArrayT_C[i] = (UINT8*)malloc(heightT * sizeof(UINT8*));

    }

    srand(time(NULL));    //random number generator

    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            arrayT[i][j] = (double)rand() / RAND_MAX; // Random double values from 0 to 1
        }
    }

    for (int r = 0; r < runs; r++) {
        clock_t start_time = clock();

        // Apply the assembly function to each element
        for (int i = 0; i < widthT; i++) {
            for (int j = 0; j < heightT; j++) {
                resultArrayT_ASM[i][j] = asmImgCvtGrayDoubleToInt(arrayT[i][j]);
            }
        }

        clock_t end_time = clock();
        double time_taken_asm = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_asm += time_taken_asm;

        printf("ASM Run %d Execution Time: %.6f seconds\n", r + 1, time_taken_asm);
    }
    printf("\n\n");
    for (int r = 0; r < runs; r++) {
        clock_t start_time = clock();

        // Apply the c function to each element
        for (int i = 0; i < widthT; i++) {
            for (int j = 0; j < heightT; j++) {
                resultArrayT_C[i][j] = cImgCvtGrayDoubleToInt(arrayT[i][j]);
            }
        }

        clock_t end_time = clock();
        double time_taken_c = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_c += time_taken_c;

        printf("C Run %d Execution Time: %.6f seconds\n", r + 1, time_taken_c);
    }

    double average_time_asm = total_time_asm / runs;
    printf("\nAverage Execution Time over %d runs using C function: %.6f seconds\n", runs, average_time_asm);
    double average_time_c = total_time_c / runs;
    printf("Average Execution Time over %d runs using X86-64 function: %.6f seconds\n", runs, average_time_c);
    
    /*
    printf("\nOriginal Array (Random Doubles):\n");
    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            printf("%.2f \t", arrayT[i][j]);
        }
        printf("\n");
    }

    printf("\nUINT8 Converted  Array (ASM):\n");
    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            printf("%hhu \t", resultArrayT_ASM[i][j]);
        }
        printf("\n");
    }

    printf("\nUINT8 Converted  Array (C):\n");
    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            printf("%hhu \t", resultArrayT_C[i][j]);
        }
        printf("\n");
    }
    
    
    for (int i = 0; i < widthT; i++) {
        free(arrayT[i]);
        free(resultArrayT_ASM[i]);
        free(resultArrayT_C[i]);
    }
    free(arrayT);
    free(resultArrayT_ASM);
    free(resultArrayT_C);
    */
    return 0;
}
