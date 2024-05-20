/* sim.h
 *
 * DEFINITIONS OF FUNCTIONS AND TYPES.
 *
 */

struct location {          /* a location is specified by x and y coordinates */
  double x;
  double y;
};

struct cov {                         /* Covariance for Gaussian distribution */
  double sigma_x;                       /* standard deviation in x direction */
  double sigma_y;                       /* standard deviation in y direction */
  double rho;                                                 /* correlation */
};

struct person {                              /* a person is characterised by */
  struct location home;                       /* geographic location of home */
  double complexity;                           /* complexity of banking task */
  double patience;                              /* persons queueing patience */
}; 

struct queue {                      /* queues in banks have a teller that is */
  enum { open, closed } status;                     /* either open or closed */
  double efficiency;                         /* efficiency of banking person */
  int length;                                        /* has a current length */
  struct person *person;                   /* and contains a bunch of people */
};

struct bank {                                  /* banks are characterised by */
  struct location loc;                                /* geographic location */
  int size;                          /* the size gives the number of tellers */
  int call;        /* if a queue grows longer than call, a new one is opened */
  int max_q_lengths;                /* maximum possible length of each queue */
  struct queue *queue;                            /* and queues of customers */
};

struct area {                                       /* residental areas have */
  struct location centre;                   /* geographic location of centre */
  struct cov cov;                                 /* covariance for the area */
  double pop;                                         /* and population size */
};

enum extrema { min, max };

extern const int no_banks;
extern const int no_areas;
extern unsigned short int rs1[3];

extern struct bank *bank;
extern struct area *area;
extern double temperature;
double sim(void);
double sq(double);
double rand_exp(unsigned short int *state);
double rand_gaus(unsigned short int *state);
double erand48(unsigned short int *state);
int    rand_pois(double intensity, unsigned short int *state);
void   rand_mgaus(int n, double **a, double *p, unsigned short int *state);
struct person get_person(struct area place);
void   service(struct bank branch, int time);
