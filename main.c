#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdint.h>

extern uint8_t asmImgCvtGrayDoubleToInt(double num);
void run();
void average_time(int w, int h);

uint8_t cImgCvtGrayDoubleToInt(double num) {
    double scaled = num * 255.0;
    int rounded_result = (int)nearbyint(scaled);
    return (uint8_t)rounded_result;
}

/************************** TESTING based on specs **********************************/
void run() {
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

    printf("\n[C] (Results in uint8):\n");
    for (int i = 0; i < height1; i++) {
        for (int j = 0; j < width1; j++) {
            if (i == 0 && j == 0)
                printf("%hhu", resultArrayC[i][j]);
            else
                printf(", %hhu", resultArrayC[i][j]);
        }

        printf("\n");
    }

    printf("\n[ASM] (Results in uint8):\n");
    for (int i = 0; i < height1; i++) {
        for (int j = 0; j < width1; j++) {
            if (i == 0 & j == 0)  printf("%hhu", resultArrayASM[i][j]);
            else printf(", %hhu", resultArrayC[i][j]);

        }
        printf("\n");
    }
}

/************************** Average Time Computation **********************************/
void average_time(int w, int h) {
    printf("\n\n*******Average Time Computation*******\n");

    int widthT = w;
    int heightT = h;
    int runs = 30;
    double total_time_asm = 0.0;
    double total_time_c = 0.0;

    // Allocate memory
    double** arrayT = (double**)malloc(widthT * sizeof(double*));
    UINT8** resultArrayT_ASM = (UINT8**)malloc(widthT * sizeof(UINT8*));
    UINT8** resultArrayT_C = (UINT8**)malloc(widthT * sizeof(UINT8*));

    if (!arrayT || !resultArrayT_ASM || !resultArrayT_C) {
        perror("Memory allocation failed");
        free(arrayT);
        free(resultArrayT_ASM);
        free(resultArrayT_C);
        return; // Exit on memory allocation error
    }

    for (int i = 0; i < widthT; i++) {
        arrayT[i] = (double*)malloc(heightT * sizeof(double));
        resultArrayT_ASM[i] = (UINT8*)malloc(heightT * sizeof(UINT8));
        resultArrayT_C[i] = (UINT8*)malloc(heightT * sizeof(UINT8));

        if (!arrayT[i] || !resultArrayT_ASM[i] || !resultArrayT_C[i]) {
            perror("Memory allocation failed");
            return; // Cleanup required
        }
    }

    srand(time(NULL));

    for (int i = 0; i < widthT; i++) {
        for (int j = 0; j < heightT; j++) {
            arrayT[i][j] = (double)rand() / RAND_MAX;
        }
    }

    printf("Starting performance measurement for %d runs...\n", runs);

    FILE* exec_file = fopen("execution_times.csv", "w");
    if (!exec_file) {
        perror("Error opening execution times file");
        return;
    }
    fprintf(exec_file, "Run,Time_ASM,Time_C\n");

    for (int r = 0; r < runs; r++) {
        clock_t start_time = clock();

        for (int i = 0; i < widthT; i++) {
            for (int j = 0; j < heightT; j++) {
                resultArrayT_ASM[i][j] = asmImgCvtGrayDoubleToInt(arrayT[i][j]);
            }
        }

        clock_t end_time = clock();
        double time_taken_asm = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_asm += time_taken_asm;

        printf("Run %d: Assembly function execution time = %.6f seconds\n", r + 1, time_taken_asm);

        start_time = clock();

        for (int i = 0; i < widthT; i++) {
            for (int j = 0; j < heightT; j++) {
                resultArrayT_C[i][j] = cImgCvtGrayDoubleToInt(arrayT[i][j]);
            }
        }

        end_time = clock();
        double time_taken_c = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        total_time_c += time_taken_c;

        printf("Run %d: C function execution time = %.6f seconds\n", r + 1, time_taken_c);

        fprintf(exec_file, "%d,%.6f,%.6f\n", r + 1, time_taken_asm, time_taken_c);
    }

    fclose(exec_file);
    printf("\nExecution times have been written to 'execution_times.csv'.\n");

    double average_time_asm = total_time_asm / runs;
    double average_time_c = total_time_c / runs;

    printf("\nSummary:\n");
    printf("Average Assembly execution time: %.6f seconds\n", average_time_asm);
    printf("Average C execution time: %.6f seconds\n", average_time_c);


    FILE* avg_exec_file = fopen("avg_execution_times.csv", "a");
    fprintf(avg_exec_file, "%d,%d,%.6f,%.6f\n", heightT, widthT, average_time_asm, average_time_c);
    fclose(avg_exec_file); 

    printf("Average runtime has been saved to avg_execution_times.\n");
    for (int i = 0; i < widthT; i++) {
        free(arrayT[i]);
        free(resultArrayT_ASM[i]);
        free(resultArrayT_C[i]);
    }
    free(arrayT);
    free(resultArrayT_ASM);
    free(resultArrayT_C);
}


int main() {
    char ans;
    int width, height;
    //run();
    //printf("\nWould you like to get the average run time for C and x86-64? (Y/N)? "); 
    //scanf_s(" %c", &ans);
    //if (ans == 'Y' || ans == 'y') {
        printf("Input number of width of the image: ");
        scanf_s("%d", &width);
        printf("Input number of height of the image: ");
        scanf_s("%d", &height);
        average_time(width, height);
    //}
    return 0;

}