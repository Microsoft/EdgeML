// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <stdio.h>
#include "quantized_utils.h"

// All values generated from Seedot on Wider Regression dataset.
// By default, all tests run without using bit-shifting operations.
// Function for matching the predicted and expected quantized outputs.
static int check_output(const INT_T* const pred, const INT_T* const expected,
                 unsigned len) {
  for (unsigned i = 0; i < len; i++)
  {
    if (pred[i] != expected[i]) {
      return 1;
    }
  }
  return 0;
}

// Test v_q_add() function.
int test_v_q_add(void) {
  const INT_T qvec_A[8] = {-425, -169, -3534, 524, -2739, 87, 52, 292};
  const INT_T qvec_B[8] = {-18777, -9518, 4055, -7309, 8584, -17257, -5280, -7933};
  const INT_T expected[8] = {-2772, -1358, -3028, -389, -1666, -2070, -608, -699};
  INT_T pred[8];

  v_q_add(&qvec_A[0], &qvec_B[0], 8, &pred[0], 1, 8, 1);
  return check_output(pred, expected, 8);
}

// Test v_q_sub() function.
int test_v_q_sub(void) {
  const INT_T qvec_A[8] = {-425, -169, -3534, 524, -2739, 87, 52, 292};
  const INT_T qvec_B[8] = {-18777, -9518, 4055, -7309, 8584, -17257, -5280, -7933};
  const INT_T expected[8] = {1922, 1020, -4040, 1437, -3812, 2244, 712, 1283};
  INT_T pred[8];

  v_q_sub(&qvec_A[0], &qvec_B[0], 8, &pred[0], 1, 8, 1);
  return check_output(pred, expected, 8);
}

// Test v_q_hadamard() function.
int test_v_q_hadamard(void) {
  const INT_T qvec_A[8] = {16378, 13638, 16378, 9787, 14861, 16378, 10661, 11018};
  const INT_T qvec_B[8] = {178, 1064, -2048, 1718, -1663, 851, 1244, 1282};
  const INT_T expected[8] = {1423, 7085, -16378, 8209, -12067, 6805, 6475, 6897};
  INT_T pred[8];

  v_q_hadamard(&qvec_A[0], &qvec_B[0], 8, &pred[0], 32, 64);
  return check_output(pred, expected, 8);
}

// Test v_q_sigmoid() function.
int test_v_q_sigmoid(void) {
  const INT_T qvec_A[8] = {-2772, -1358, -3028, -389, -1666, -2070, -608, -699};
  const INT_T expected[8] = {0, 2760, 0, 6640, 1528, 0, 5760, 5400};
  INT_T pred[8];

  v_q_sigmoid(&qvec_A[0], 8, &pred[0], 2, 1024, 2048, 11, 14);
  return check_output(pred, expected, 8);
}

// Test v_q_tanh() function.
int test_v_q_tanh(void) {
  const INT_T qvec_A[8] = {178, 1064, -4162, 1718, -1663, 851, 1244, 1282};
  const INT_T expected[8] = {178, 1064, -2048, 1718, -1663, 851, 1244, 1282};
  INT_T pred[8];

  v_q_tanh(&qvec_A[0], 8, &pred[0], 11, 11);
  return check_output(pred, expected, 8);
}

// Test v_q_scalar_add() function.
int test_v_q_scalar_add(void) {
  const INT_T qscalar_A = 30111;
  const INT_T qvec_B[8] = {16261, 13521, 16261, 9670, 14744, 16261, 10544, 10901};
  const INT_T expected[8] = {16378, 13638, 16378, 9787, 14861, 16378, 10661, 11018};
  INT_T pred[8];

  v_q_scalar_add(qscalar_A, &qvec_B[0], 8, &pred[0], 256, 1, 1);
  return check_output(pred, expected, 8);
}

// Test v_q_scalar_sub() function.
int test_v_q_scalar_sub(void) {
  const INT_T qscalar_A = 16384;
  const INT_T qvec_B[8] = {0, 2760, 0, 6640, 1528, 0, 5760, 5400};
  const INT_T expected[8] = {16384, 13624, 16384, 9744, 14856, 16384, 10624, 10984};
  INT_T pred[8];

  v_q_scalar_sub(qscalar_A, &qvec_B[0], 8, &pred[0], 1, 1, 1);
  return check_output(pred, expected, 8);
}

// Test v_q_scalar_mul() function.
int test_v_q_scalar_mul(void) {
  const INT_T qscalar_A = 32522;
  const INT_T qvec_B[8] = {16384, 13624, 16384, 9744, 14856, 16384, 10624, 10984};
  const INT_T expected[8] = {16261, 13521, 16261, 9670, 14744, 16261, 10544, 10901};
  INT_T pred[8];

  v_q_scalar_mul(qscalar_A, &qvec_B[0], 8, &pred[0], 128, 256);
  return check_output(pred, expected, 8);
}

// Test m_q_mulvec() function.
int test_m_q_mulvec(void) {
  const INT_T qmat_A[8 * 4] = {7069, -10389, 1562, -1992, 3262, -37, -1143, -995, 5513, -17035, -14615, -6636, 4733, -403, 4106, -1104, -2707, -1287, -18128, -1832, -10108, -137, 2064, 1207, 5233, 226, 831, -1909, 4489, -1099, 2845, -1261};
  const INT_T qvec_B[4] = {1040, 1919, 4254, 4024};
  const INT_T expected[8] = {-425, -169, -3534, 524, -2739, 87, 52, 292};
  INT_T pred[8];

  m_q_mulvec(&qmat_A[0], &qvec_B[0], 8, 4, &pred[0], 128, 64, 2, 0);
  return check_output(pred, expected, 8);
}

// Test arg_max() function
int test_arg_max(void) {
  
  INT_T qarg_A[10] = {1675, 9870, -9876, -1234, 5674, 28765, 9876, 12654};
  const INT_T expected = 5;
  INT_T predicted = 0;

  arg_max(qarg_A, sizeof(qarg_A)/sizeof(qarg_A[0]), &predicted);
  return predicted ==  expected ? 0 : 1;
}

// Test transpose() function
int test_transpose(void) {

  INT_T qmatrix[4][3] = {{1238, 5432, 1834},
                                {6543, -5698, -2342},
                                {9876, 5674, 8435},
                                {6542, 7824, 3924}};
  INT_T predicted[3][4];
  const INT_T expected[3][4] = {{1238, 6543, 9876, 6542},
                                 {5432, -5698, 5674, 7824},
                                  {1834, -2342, 8435, 3924}};
  INT_T qmatrix1[3][3] = {{1238, 5432, 1834},
                                {6543, -5698, -2342},
                                {9876, 5674, 8435}};
  INT_T predicted1[3][3];
  const INT_T expected1[3][3] = {{1238, 6543, 9876},
                                 {5432, -5698, 5674},
                                  {1834, -2342, 8435}};

  transpose((INT_T *)qmatrix, (INT_T *)predicted, 4, 3);
  transpose((INT_T *)qmatrix1, (INT_T *)predicted1, 3, 3);

  return check_output((INT_T *)predicted1, (INT_T *)expected1, 9) == 0 && check_output((INT_T *)predicted, (INT_T *)expected, 12) == 0 ? 0: 1; 
}

// Test adjust_scale_shr() unction
int test_adjust_scale_shl(void) {

  INT_T qmatrix[16]= {4232, -987, -2342,1232, -3242, 843, 982, 2342, 343, 6543, 987, 6542, 5674, 2876, 987, 1265};
  INT_T expected[16] = {42320, -9870, -23420,12320, -32420, 8430, 9820, 23420, 3430, 65430, 9870, 65420, 56740, 28760, 9870, 12650};
  INT_T qmatrix1[16]= {4232, -987, -2342,1232, -3242, 843, 982, 2342, 343, 6543, 987, 6542, 5674, 2876, 987, 1265};
  INT_T expected1[16] = {42320, -9870, -23420,12320, -32420, 8430, 9820, 23420, 3430, 65430, 9870, 65420, 56740, 28760, 9870, 12650};

  adjust_scale_shl(qmatrix, 2, 2, 2, 2, 10);
  adjust_scale_shl(qmatrix1, 4, 4, 0, 0, 10);

  return check_output(qmatrix, expected, 16) == 0 && check_output(qmatrix1, expected1, 16) == 0 ? 0 : 1;
}

// Test AdjustScaleShr function
int test_adjust_scale_shr(void) {
  INT_T qmatrix[16]= {4232, -9879, -2342,1232, -3242, 8432, 9823, 2342, 343, 6543, 9876, 6542, 5674, 28765, 9876, 12654};
  INT_T expected[16] = {114 ,-267 ,-63 ,33 ,-87 ,227 ,265 ,63 ,9 ,176 ,266 ,176 ,153 ,777 ,266 ,342}; 
  INT_T qmatrix1[16]= {4232, -9879, -2342,1232, -3242, 8432, 9823, 2342, 343, 6543, 9876, 6542, 5674, 28765, 9876, 12654};
  INT_T expected1[16] = {114 ,-267 ,-63 ,33 ,-87 ,227 ,265 ,63 ,9 ,176 ,266 ,176 ,153 ,777 ,266 ,342};

  adjust_scale_shr(qmatrix, 2, 2, 2, 2, 37);
  adjust_scale_shr(qmatrix1, 4, 4, 0, 0, 37);

  return check_output(qmatrix, expected, 16) == 0 && check_output(qmatrix1,expected1, 16) == 0 ? 0 : 1; 
}

// Test Reverse2 function
int test_reverse2(void) {
  INT_T qmatrix[16]= {4232, -9879, -2342,1232, -3242, 8432, 9823, 2342, 343, 6543, 9876, 6542, 5674, 28765, 9876, 12654};
  INT_T expected[16] = {1232,-2342,-9879,4232,2342,9823,8432,-3242,6542,9876,6543,343,12654,9876,28765,5674};
  INT_T expected1[16] = {5674,28765,9876,12654,343,6543,9876,6542,-3242,8432,9823,2342,4232,-9879,-2342,1232};
  INT_T predicted[16];
  INT_T predicted1[16];

  Reverse2(qmatrix, 1, 4, 4, predicted);
  Reverse2(qmatrix, 0, 4, 4,predicted1);

  return check_output(predicted,expected, 16) == 0 && check_output(predicted1,expected1, 16) == 0 ? 0: 1; 
}

// Test AddOrSubCir4D function
int test_add_or_sub_cir_4D(void) {
  INT_T arrA[16] = {1324, 5453, 3454, 3435, 8789, 3411, 5412, 8934, 6895, 1211, 6790, 5425, 8976, 4539, 9348, 9321};
  const INT_T arrB[16] = {8452, 2341, 9383, 2353, 4522, 6232, 2562, 565, 4564, 7756, 2585, 8735, 3525, 4341, 4656, 2313};
  INT_T predicted[16];
  INT_T predicted1[16];
  INT_T predicted2[16];
  INT_T predicted3[16];
  INT_T expected[16] = {18,22,25,15,43,15,32,33,37,7,36,21,43,19,45,34};
  INT_T expected1[16] = {-9,14,-2,7,15,7,3,25,8,0,8,14,15,11,17,27};
  INT_T expected2[16] = {554,662,767,460,1300,458,963,1010,1111,238,1101,659,1319,570,1356,1049};
  INT_T expected3[16] = {-290,428,-77,226,456,224,119,776,267,4,257,425,475,336,512,815};

  add_or_sub_cir_4D(arrA,arrB, predicted, 2, 2, 2, 2, 10, 20, 30, 1);
  add_or_sub_cir_4D(arrA,arrB, predicted1, 2, 2, 2, 2, 10, 20, 30, 0);
  add_or_sub_cir_4D(arrA,arrB, predicted2, 2, 2, 2, 2, 10, 20, 1, 1);
  add_or_sub_cir_4D(arrA,arrB, predicted3, 2, 2, 2, 2, 10, 20, 1, 0);

  return check_output(predicted, expected, 16) == 0 && check_output(predicted1, expected1, 16) == 0
    && check_output(predicted2, expected2, 16) == 0 && check_output(predicted3, expected3, 16) == 0 ? 0 : 1;
}

// Test AddOrSubCir2D function
int test_add_or_sub_cir_2D(void) {
  INT_T arrA[16] = {1324, 5453, 3454, 3435, 8789, 3411, 5412, 8934, 6895, 1211, 6790, 5425, 8976, 4539, 9348, 9321};
  const INT_T arrB[16] = {8452, 2341, 9383, 2353, 4522, 6232, 2562, 565, 4564, 7756, 2585, 8735, 3525, 4341, 4656, 2313};
  INT_T predicted[16];
  INT_T predicted1[16];
  const INT_T expected[16] = {18,22,27,15,43,15,33,33,37,7,38,21,43,19,46,34};
  const INT_T expected1[16] = {-9,14,-4,7,15,7,2,25,8,0,7,14,15,11,15,27};
  add_or_sub_cir_2D(arrA,arrB, predicted, 4, 4, 10, 20, 30, 1);

  add_or_sub_cir_2D(arrA,arrB, predicted1, 4, 4, 10, 20, 30, 0);
  return check_output(predicted, expected, 16) == 0 && check_output(predicted1, expected1, 16) == 0 ? 0 : 1;
}

// Test Exp() function
int test_exp(void) {
  INT_T arrA[16] = {13, 54, 34, 35, 87, 11, 41, 93, 89, 11, 90, 25, 76, 39, 48, 93};
  INT_T predicted[16];
  const INT_T expected[16] = {227,343,280,283,477,223,301,506,487,223,491,256,427,295,323,506};

  exp_scale(arrA, 4, 4, 100, 200, predicted);
  return check_output(predicted, expected, 16);
}

// Test Relu4D function
int test_relu_4D_2D(void) {
  INT_T predicted[16] = {-3648,648,-2147,-2348,1468,-4348,3648,3648,-648,9648,3778,4743,7483,-243,8,-21};
  INT_T predicted1[16] = {-3648,648,-2147,-2348,1468,-4348,3648,3648,-648,9648,3778,4743,7483,-243,8,-21};
  const INT_T expected[16] = {0,648,0,0,1468,0,3648,3648,0,9648,3778,4743,7483,0,8,0};
  const INT_T expected1[16] = {0,648,0,0,1468,0,3648,3648,0,9648,3778,4743,7483,0,8,0};

  relu_4D_2D(predicted, 2,2,2,2);
  relu_4D_2D(predicted1, 4,4,0,0);
  return check_output(predicted,expected, 16) == 0 && check_output(predicted1,expected1, 16) == 0 ? 0: 1;
}


int main() {
  if (test_v_q_add()) {
    printf("Test Failure for v_q_add()!\n");
  } else if (test_v_q_sub()) {
    printf("Test Failure for v_q_sub()!\n");
  } else if (test_v_q_hadamard()) {
    printf("Test Failure for v_q_hadamard()!\n");
  } else if (test_v_q_sigmoid()) {
    printf("Test Failure for v_q_sigmoid()!\n");
  } else if (test_v_q_tanh()) {
    printf("Test Failure for v_q_tanh()!\n");
  } else if (test_v_q_scalar_add()) {
    printf("Test Failure for v_q_scalar_add()!\n");
  } else if (test_v_q_scalar_sub()) {
    printf("Test Failure for v_q_scalar_sub()!\n");
  } else if (test_v_q_scalar_mul()) {
    printf("Test Failure for v_q_scalar_mul()!\n");
  } else if (test_m_q_mulvec()) {
    printf("Test Failure for m_q_mulvec()!\n");
  } else if (test_arg_max()) {
    printf("Test Failure for test_arg_max()!\n");
  } else if (test_transpose()) {
    printf("Test Failure for test_transpose()!\n");
  } else if (test_adjust_scale_shl()) {
    printf("Test Failure for test_adjust_scale_shl()!\n");
  } else if (test_adjust_scale_shr()) {
    printf("Test Failure for test_adjust_scale_shr()!\n");
  } else if (test_reverse2()) {
    printf("Test Failure for test_reverse2()!\n");
  } else if (test_add_or_sub_cir_4D()) {
    printf("Test Failure for test_AddOrSubCir4D()!\n");
  } else if (test_add_or_sub_cir_2D()) {
    printf("Test Failure for test_AddOrSubCir2D()!\n");
  } else if (test_exp()) {
    printf("Test Failure for test_Exp()!\n");
  } else if (test_relu_4D_2D()) {
    printf("Test Failure for test_Relu4D2D()!\n");
  }
   else {
    printf("All Tests Passed!\n");
    return 0;
  }

  return -1;
}
