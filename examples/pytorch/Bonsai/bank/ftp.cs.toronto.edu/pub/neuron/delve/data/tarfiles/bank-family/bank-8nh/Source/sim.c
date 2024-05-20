/* sim.c
 *
 * SIMULATE A DAY OF BANKING AND RETURN THE AVERAGE REJECTION RATE.
 *
 * This file contains the routines implementing the simulation of a queueing
 * system in a bank. The characteristics of the simulation are set up by the
 * calling program, which initialises the global "area" and "bank" structures.
 * The "area" variables contain information about the location, distribution,
 * and population of the residintial areas where the customers come from.
 * Customers are characterised by their home location, their banking task
 * complexity and their patience (which determines how willing they are to
 * change queues. The bank variables contain information about the location,
 * size, and efficiency of the various banks. In addition, there is a global
 * "temperature" variable, which is used when the customers chose which bank
 * to go to, through a Boltzmann distribution depending on distances. */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sim.h"


/* In this function, a person enters a bank branch and lines up in the shortest
 * queue that has an open teller and which is not full. If all queues are full
 * the person is turned away */ 

enum {accepted, refused} enter_bank(struct bank branch, struct person customer)
{
  struct queue *queue = &(branch.queue[extreme_queue(min, branch)]); 

  if (queue->length == branch.max_q_lengths)
    return refused;
  queue->person[queue->length++] = customer;
  return accepted;
}


/* The "sim" function, simulates a day of banking activity and returns the 
 * fraction of custumers that were rejected, because the bank queues were full.
 * The simulation is discretized into 420 one-minute time-slices. In each time
 * slice several things happen in seccession: 1) new customers arrive, and
 * are accepted or rejected, 2) customers receive service, if they finish they
 * leave and other customers advance in the queue, 3) impatient customers may
 * change queue, if they see other queues that are significantly shorter, 4)
 * tellers with empty queues close and 5) new tellers open if existing queues
 * are too long. Customers appear from the areas according to a Poission
 * distribution with an intensity given by the population. */

double sim(void)
{
  int    i, j, k, t, rejects = 0, accepts = 0;
  struct person person;

  for (t=0; t<420; t++) {                   /* a banking day has 420 minutes */
    for (i=0; i<no_areas; i++) {                   /* people arrive at banks */
      j = rand_pois(area[i].pop, rs1);
      for (j--; j>=0; j--) {
        person = get_person(area[i]);  
        k = select_bank(person, temperature);
        if (enter_bank(bank[k], person) == refused)
          rejects++;
        else
          accepts++;          
      }
    }
    for (i=0; i<no_banks; i++)                      /* customers get service */
      service(bank[i], t);
  }

  return (double) rejects/(rejects+accepts);
}  


/* The "get_person" function, returns a random person from a specified area.
 * The x and y coordinate of the persons home are drawn at random from a two
 * dimensinoal Gussian distribution with specified covariance matrix. The
 * complexity of the persons banking task is drawn from an exponential
 * distribution, and the persons patience is drawn from a uniform distribution.
 */

struct person get_person(struct area place)
{
  int    i, n = 2;
  double *x, **a;
  struct person person;

  x = (double *) malloc((size_t) n*sizeof(double));
  a = (double **) malloc((size_t) n*sizeof(double *));
  a[0] = (double *) malloc((size_t) n*n*sizeof(double));
  for (i=1; i<n; i++) a[i] = a[i-1]+n;

  a[0][0] = sq(place.cov.sigma_x);
  a[0][1] = place.cov.sigma_x * place.cov.sigma_y * place.cov.rho;
  a[1][1] = sq(place.cov.sigma_y);

  rand_mgaus(n, a, x, rs1);

  person.home.x = place.centre.x + x[0];
  person.home.y = place.centre.y + x[1];
  person.complexity = rand_exp(rs1);
  person.patience = erand48(rs1);

  free(a[0]); free(a); free(x);
  return person;
}


/* This function selects and returns a bank for a person. The bank selection is
 * based on the Euclidian distance between the persons home and the different
 * banks. The choice follows the Boltzmann distribution, using the distances
 * as energies and depends on the ficticious temperature parameter. */

int select_bank(struct person person, double temp)
{
  double *x, z = 0;
  int    i;

  x = (double *) malloc((size_t) no_banks*sizeof(double));
  
  for (i=0; i<no_banks; i++) {
    x[i] = exp(-sqrt(sq(bank[i].loc.x-person.home.x) +
                     sq(bank[i].loc.y-person.home.y))/temp);
    z += x[i];
  }
  z *= erand48(rs1);
  i = 0;
  while (i<no_banks && (z -= x[i]) > 0) i++;

  free(x);
  return i;
} 


/* Function returns the identety of the queue with the most extreme length. The
 * type of extrema can be either min or max. If no queues are open, -1 will be
 * returned; */

int extreme_queue(enum extrema type, struct bank branch)
{
  int extr, i = 0, j;

  while (branch.queue[i].status == closed && i < branch.size) i++;
  if (i == branch.size)
    return -1; 
  extr = branch.queue[i].length;
  for (j=i+1; j<branch.size; j++)
    if (branch.queue[j].status == open)
      if ((type == min && branch.queue[j].length < extr) ||
          (type == max && branch.queue[j].length > extr))
        extr = branch.queue[i=j].length;
  
  return i;
}


/* The service function is called once per minute for each bank; several things
 * happen in sequence: 1) first customers are given service, reducing the
 * remaining complexity of their tasks. If customers finish, they exit and
 * other people in the queue advance, 2) impatient customers may change queues
 * if other queues are shorter. The probability of a staying is the customers
 * patience (which is in the interval [0, 1]) raised to the power of the
 * difference of his current position and the length of the smallest queue.
 * 3) if any queues are empty, the teller closes, and 4) if the longest queue
 * is longer the the specified "call" parameter, then a new teller is opened.
 */

void service(struct bank branch, int time)
{
  int i, j, min;
  struct queue *queue;
  double work; 

  for (i=0; i<branch.size; i++) {                  /* give a unit of service */
    queue = &(branch.queue[i]); 
    if (queue->status == open) {
      work = queue->efficiency;
      while (queue->length > 0 && work > queue->person[0].complexity) {
        work -= queue->person[0].complexity;
        for (j=1; j<queue->length; j++)
          queue->person[j-1] = queue->person[j];
        queue->length--;
      }
      if (queue->length > 0)
        queue->person[0].complexity -= work;
    } 
  }

  min = branch.queue[extreme_queue(min, branch)].length;  /* let impatient.. */
  for (j = min+1; j<branch.max_q_lengths; j++)                /* customers.. */
    for (i=0; j>min && i<branch.size; i++) {                 /* change queue */
      queue = &(branch.queue[i]); 
      if ((queue->status == open) && (queue->length >= j)) {
        if (min == 0) 
          min = change_queue(branch, queue, j);
        else if (pow(queue->person[j].patience, (double) j-min) < erand48(rs1))
          min = change_queue(branch, queue, j);
      }
    }

  for (i=0; i<branch.size; i++)           /* close tellers with no customers */
    if (branch.queue[i].length == 0)
      branch.queue[i].status = closed;
  if ((i = extreme_queue(max, branch)) == -1) /* but leave at least one open */
    branch.queue[0].status = open;
  else if (branch.queue[i].length > branch.call) {         /* open another.. */
    j = 0;                                                   /* if necessary */
    while (branch.queue[j].status == open && j < branch.size) j++;
    if (j < branch.size)
      branch.queue[j].status = open;
  }
}

     
/* In this function a single customer changes queue, whithin the specified
 * branch. The queue which the customer changes from is passed to the function
 * as well as the customers identity (position in queue). The changee moves to
 * the shortest available queue. All customers behind the changee advance one
 * place. The queue-lengths are updated, and the length of the shortes queue
 * after the change is returned. */  

int change_queue(struct bank branch, struct queue *queue, int changee)
{
  int i = extreme_queue(min, branch);

  branch.queue[i].person[branch.queue[i].length++] = queue->person[changee];
  for (i=changee+1; i<queue->length; i++)
    queue->person[i-1] = queue->person[i];      /* waiting customers advance */
  queue->length--;

  return branch.queue[extreme_queue(min, branch)].length;
}


/* Square function */

double sq(double x)
{
  return x*x;
}


/* Generate sample from exponential distribution */

double rand_exp(unsigned short int *state)
{
  return -log(erand48(state));
}


/* Generate sample from poisson distribution with given intesity */

int rand_pois(double intensity, unsigned short int *state)
{
  double t = 0.0;
  int    i = 0;

  while ((t += rand_exp(state)/intensity) < 1.0) i++;
  return i;
}  


/* Generate sample from zero mean unit variance Gaussian distribuiton */

double rand_gaus(unsigned short int *state)
{
  return cos(6.283185*erand48(state)) * sqrt(-2.0*log(erand48(state)));
}


/* Generate sample from multi-dimensional Gaussian with given covariance. The
 * parameters to the function are the dimensionality "n", and the cavariance
 * matrix a, and the vector p returning the sample. The "a" matrix is
 * destroyed by the function */

void rand_mgaus(int n, double **a, double *p, unsigned short int *state)
{
  int    i, j, k;
  double s, *d, *r;

  d = (double *) malloc((size_t) n*sizeof(double));
  r = (double *) malloc((size_t) n*sizeof(double));

  for (i=0; i<n; i++)             /* do Cholesky decomposition of "a" matrix */
    for (j=i; j<n; j++) {
      s = a[i][j];
      for (k=i-1; k>=0; k--) s -= a[i][k]*a[j][k];
      if (i == j) {
        if (s <= 0.0) {
          fprintf(stderr,
             "Error: Matrix for inversion is not positive definite... bye!\n");
          exit(-1);
        }
        d[i] = sqrt(s);
      } else a[j][i] = s/d[i];
    }

  for (i=0; i<n; i++)          /* generate a vector of random normal numbers */
    r[i] = rand_gaus(state);

  for (i=0; i<n; i++) {       /* multiply random vector with cholesky factor */
    s = d[i]*r[i];
    for (j=0; j<i; j++) 
      s += a[i][j]*r[j];
    p[i] = s;
  }
  free(d); free(r);
}










