// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "quantized_datatypes.h"
#include "predict.h"
#include "scales.h"

#define FPSIZE 16

int INPUT_SIZE, OUTPUT_SIZE;

// Comparator function for sorting doubles.
int compare_doubles(const void *a, const void *b) {
  const double *da = (const double *) a;
  const double *db = (const double *) b;

  return (*da > *db) - (*da < *db);
}

// Function for computing the deviation from the expected doubleing point
// result and returning the largest such deviation found.

double compute_error(const Q31_T* const pred, const double* const label,
                    double* const errors, SCALE_T scl) {
  double agg_diff = 0.0;

  for (unsigned i = 0; i < OUTPUT_SIZE; i++) {
    double f_pred = ((double)pred[i]) / pow(2, -scl);
    double single_diff = fabs(f_pred - label[i]);
    agg_diff = single_diff > agg_diff ? single_diff : agg_diff;
    errors[i] = single_diff;
  }

  return agg_diff;
}

// Function for computing the 95th percentile deviation among all the outputs.
double aggregate_error(double* errors, unsigned len) {
  qsort(errors, len, sizeof(double), compare_doubles);
  unsigned index = (unsigned) round(fmax((0.95 * len - 1), 0));
  return errors[index];
}

void parse_csv_q15p(char* line, Q15_T** array, int size, int scale) {
  char* linepointer = line;
  for (int i = 0; i < size; i++) {

    char *tok = strtok(linepointer, ",");
    if (linepointer != NULL) {
      linepointer = NULL;
    }
    if (tok == NULL) {
      printf("Illegal State. Check the input files.\n");
      return -1;
    }

    float num = atof(tok);
    array[i][0] = (Q15_T)(ldexp(num, -scale));
  }
  return;
}

void parse_csv_d(char* line, double* array, int size) {
  char* linepointer = line;
  for (int i = 0; i < size; i++) {

    char *tok = strtok(linepointer, ",");
    if (linepointer != NULL) {
      linepointer = NULL;
    }
    if (tok == NULL) {
      printf("Illegal State. Check the input files.\n");
      return -1;
    }

    float num = atof(tok);
    array[i] = num;
  }
  return;
}

/** Run this test using the following command:
 * $: ./test_quantized_face_detection <log.txt>
 *  By default, all tests run without using bit-shifting operations.
 */
int main(int argc, char **argv) {
  unsigned patches;
  FILE *xFile, *yFile, *outputLog;
  if (argc != 4) {
    printf("Improper Number of Arguments Provided!\n");
    return -1;
  } else {
    xFile = fopen("input/X.csv", "r");
    yFile = fopen("input/Y.csv", "r");
    INPUT_SIZE = atoi(argv[1]);
    OUTPUT_SIZE = atoi(argv[2]);
    outputLog = fopen(argv[3], "w");
  }

  if (xFile == NULL) {
    printf("An error occured while opening the X (input) file.\n");
    return -1;
  }
  if (yFile == NULL) {
    printf("An error occured while opening the Y (ground truth) file.\n");
    return -1;
  }
  if (outputLog == NULL) {
    printf("An error occured while opening the output log file.\n");
    return -1;
  }


  char* xLine = malloc(FPSIZE * INPUT_SIZE);
  char* yLine = malloc(FPSIZE * OUTPUT_SIZE);


  Q15_T** x = malloc(sizeof(Q15_T*) * INPUT_SIZE);
  for (int i = 0; i < INPUT_SIZE; i++) {
    x[i] = malloc(sizeof(Q15_T));
  }

  double* y = malloc(sizeof(double) * OUTPUT_SIZE);
  Q31_T* pred = malloc(sizeof(Q31_T) * OUTPUT_SIZE);
  double* allErrors = malloc(sizeof(double) * OUTPUT_SIZE);

  int i = 0;
  double aggregate = 0.0;

  while (fgets(xLine, FPSIZE * INPUT_SIZE, xFile)) {
    if (fgets(yLine, FPSIZE * OUTPUT_SIZE, yFile)) {
      parse_csv_q15p(xLine, x, INPUT_SIZE, scaleForX);
      parse_csv_d(yLine, y, OUTPUT_SIZE);
    } else {
      printf("Illegal State. Check input and output files.");
      return -1;
    }

    seedotFixed(x, pred);


    compute_error(pred, y, allErrors, scaleForY);

    aggregate += aggregate_error(allErrors, OUTPUT_SIZE);
    i++;
  }

  printf("%f", aggregate / i);

  free(xLine);
  free(yLine);
  
  for (int i = 0; i < INPUT_SIZE; i++) {
    free(x[i]);
  }
  free(x);
  free(y);

  return 0;
}