/* gen.c
 *
 * GENERATE CASES FOR THE "BANK" DATASETS AND WRITE THEM TO STANDARD OUTPUT.
 *
 * This program repeatedly initialises the variables controling the bank-queue
 * simulation program and calls te "sim" function. The purpose is either to
 * generate a set of data, or to estimate the noise level in a dataset, 
 * depending on the command line options. 
 *
 * Note, that the program uses several "seeds" for the random number generator
 * functions, since for purposes of estimating noise levels, one requires the
 * capability of resetting the generator that generates the initial
 * configuration, but a new random sequence for the simulation. */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sim.h"

const int no_banks = 3;
const int no_areas = 3;
unsigned short int rs1[3], rs2[3], rs3[3]; /* random number generator states */

struct bank *bank;
struct area *area;
double temperature;


/* The "setup" function, initialises the parameters controling the simulation,
 * using various random number generating functions, and random state variable
 * "rs2". */   

void setup(void)
{
  int mxql, i, j;

  temperature = 1.0/(1.0+exp(rand_gaus(rs2)-0.5));
  area[0].centre.x = 2.0*erand48(rs2)-1.0;
  area[0].centre.y = 2.0*erand48(rs2)-1.0;
  bank[1].loc.x = 2.0*erand48(rs2)-1.0;
  bank[1].loc.y = 2.0*erand48(rs2)-1.0;
  area[1].pop = 1.1*rand_exp(rs2);
  area[2].pop = 1.1*rand_exp(rs2);
  mxql = (int) (5.0 + 4.0*erand48(rs2));
  for (i=0; i<no_banks; i++) {                       /* Initialize the banks */
    bank[i].max_q_lengths = mxql;
    bank[i].call = mxql - 3;
    bank[i].queue[0].status = open;
    bank[i].queue[0].length = 0; 
    for (j=1; j<bank[i].size; j++) {
      bank[i].queue[j].status = closed;
      bank[i].queue[j].length = 0;
    }    
  }
}


/* The "do_sim" function first corrupts some of the parameters controling the
 * simulation by random amounts, and then calls to simulation procedure, and
 * returns the result. The purpose of the corruption, is to add noise to the
 * datasets. */

double do_sim(void)
{
  area[0].centre.y = (area[0].centre.y + erand48(rs1))/2.0;
  area[0].centre.x = (area[0].centre.x + erand48(rs1))/2.0;
  bank[1].loc.x = (bank[1].loc.x + erand48(rs1) - 0.5)/1.5;
  bank[1].loc.y = (bank[1].loc.y + erand48(rs1) - 0.5)/1.5;
  area[1].pop = (area[1].pop + 3.1*rand_exp(rs1))/2.0;
  area[2].pop = area[2].pop * (0.5 + 1.0*erand48(rs1));
  return sim();
}


/* The "gen_data" function repeatedly sets up datastructures, and echoes
 * parameters and the simulation result to standard output. */

void gen_data(int n)
{
  int c;

  for (c=0; c<n; c++) {
    setup();
    printf("%10.6f ", area[0].centre.x);
    printf("%10.6f ", area[0].centre.y);
    printf("%10.6f ", bank[1].loc.x);
    printf("%10.6f ", bank[1].loc.y);
    printf("%10.6f ", area[1].pop);
    printf("%10.6f ", area[2].pop);
    printf("%10.6f ", temperature);
    printf("%4d ", bank[0].max_q_lengths);
    printf("%10.6f\n", do_sim());
  }
}


/* The "estimate_noise" function, calls the simulator with "samples" different
 * inputs, each "resamples" times. It estimates the variance of the signal to
 * be predicted, as well as the noise. The noise is the variance of the signal
 * when presented multiple times with identical inputs. These variences are
 * then averaged over the input distribution. */ 

void estimate_noise(int samples, int resamples)
{
  int    i, j, c;
  double y, x, x2, X = 0.0, X2 = 0.0, var, noise = 0.0;

  for (c=0; c<samples; c++) {
    x = x2 = 0.0; 
    for (j=0; j<3; j++) rs3[j] = rs2[j];          /* save state 2 in state 3 */
    for (i=0; i<resamples; i++) {
      for (j=0; j<3; j++) rs2[j] = rs3[j];                /* restore state 2 */
      setup();
      y = do_sim();
      x += y;
      x2 += sq(y);
    }
    X += y;
    X2 += sq(y);
    noise += x2/(resamples-1.0) - sq(x)/(resamples*(resamples-1.0));
  }
  var = X2/(samples-1.0) - sq(X)/(samples*(samples-1.0));
  printf("Noise: %10.6f, Variance: %10.6f, Noise/Variance: %10.6f\n",
          noise/samples, var, noise/var/samples);
}


/* The "main" function first sets up the data structures for simulation. One of
 * two possible scenarios are executed, depending on the command line options:
 * When no options are given, a dataset is generated and written to standard
 * output. If the option "-noise" is given, then the variance and noise in the
 * signal to be predicted is estimated. The noise is estimated by resampling
 * the simulation several times with the same inputs. */ 

main(int argc, char **argv)
{
  int    i, j;

  if (argc !=  1 && (argc != 2 || strcmp(argv[1], "-noise") != 0)) {
    fprintf(stderr, "Usage: %s [-noise]\n", argv[0]);
    exit(-1);
  }

  for (i=0; i<3; i++)           /* initialize random number generator states */
    { rs1[i]=0; rs2[i]=0; }

  bank = (struct bank *) malloc((size_t) no_banks*sizeof(struct bank));
  area = (struct area *) malloc((size_t) no_areas*sizeof(struct area));
  bank[0].size = 2;
  bank[1].size = 3;
  bank[2].size = 4;
  for (i=0; i<no_banks; i++) {
    bank[i].queue = (struct queue *)
                            malloc((size_t) bank[i].size*sizeof(struct queue));
    for (j=0; j<bank[i].size; j++)
      bank[i].queue[j].person = (struct person *)
                                     malloc((size_t) 15*sizeof(struct person));
  }
  for (i=0; i<no_areas; i++) {
    area[i].cov.sigma_x = 0.5;
    area[i].cov.sigma_y = 0.5;
    area[i].cov.rho = 0.1;
  }
  area[0].pop = 1.9;
  bank[0].loc.x =  0.1;
  bank[0].loc.y =  0.1;
  area[1].centre.x = -0.2;
  area[1].centre.y = -0.5;
  area[2].centre.x = 0.2;
  area[2].centre.y = 0.3;
  bank[2].loc.x = -0.7;
  bank[2].loc.y =  0.1;
  for (i=0; i<no_banks; i++) {                       /* Initialize the banks */
    bank[i].queue[0].efficiency = 1.0;
    for (j=1; j<bank[i].size; j++)
      bank[i].queue[j].efficiency = bank[i].queue[0].efficiency;
  }

  if (argc == 1)                                        /* Generate dataset? */
    gen_data(8192);                                   /* generate 8192 cases */
  else                                    /* otherwise, estimate noise level */
    estimate_noise(1000, 10);      /* sampling at 1000 inputs, each 10 times */
 
  free(bank); free(area);
}









