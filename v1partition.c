
///this is the version where we read it first & partition array.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_barrier_t barrier;
int *PrimeFactors(int num);
int max (int *nums, int length);
//void partition (struct targs *thread);
void sample();
void *thread_func(void *args);

struct targs {
    int id;
    int length;
    int nfacs;//number of nums to factor.
    int nthreads;//number threads
    int *query;//all will get same data?
    //somehow have array of factors.
    int start;//where to start and stop in the array
    int stop;
};

int main(int argc, char*argv[]) {
    if (argc != 2) {
	    printf("Usage: %s <input file>\n",argv[0]);
	    return 1;
    }
    int nfacs, nthreads, ret;
    pthread_t *pt;
    struct targs data;
    struct targs *tparams;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
	    perror("fopen");
	    return 1;
	}
    fscanf(f, "%d %d", &nfacs, &nthreads);
    tparams = malloc(sizeof(struct targs) * nthreads);
    pt = malloc(sizeof(pthread_t) * nthreads);
   //sample();
    /*printf("Input the number of numbers whose number of unique prime factors you want:\n");
    scanf("%d",&nfacs);//better way to handle than scanf.
    printf("input the number of threads you want to use: \n");
    scanf("%d",&nthreads);
    printf("Enter %d integers: \n",nfacs);*/
    data->query = malloc(sizeof(int)*nfacs);
    int **factors = malloc((sizeof(int*)*nfacs));
    printf("nfacs: %d\n",nfacs);
    for (int i=0; i<nfacs; i++) {
        //scanf("%d", &tparams->query[i]);
	fscanf(f, "%d", &data->query[i]);
    }
	
    for (int i=0; i<nthreads; i++) {
	    pt[i] = i;
    }
    for (int i=0; i<nthtreads; i++) {
	tparams[i].nthreads = ntthreads;
	tparams[i].id = i;
	tparams[i].nfacs = nfacs;
	tparams[i]->query = data->query;//vs .? 
    }


    ret = pthread_create(&pt[i],0,thread_func,&tparams[i]);
    //in future, use struct

     File *o = fopen("output.txt", "a");
    //for (int i=0; i<nfacs; i++) {
	    //write to file
	    //
    fclose(f);
    fclose(o);
    free(data->query);
    for (int i=0; i<nfacs; i++) {
        free(factors[i]);
    }
    free(factors);
    //allocate thread args at some point.
    printf("Hello, World!\n");
    return 0;
}
void *thread_func(int *args) {
    struct targs data = args;
    for (int i=0; i<data->nfacs; i++) {
        printf("querys[%d] = %d\n",i,data->query[i]);
        factors[i] = PrimeFactors(tparams->query[i]);//array of pointers to list of prime factors
    }
    for (int i=0; i<data->nfacs; i++) {
        printf("Factors: %d, %d\n",factors[i][0],factors[i][1]);
        //for (int j=0; j<) print them all at some point
    }	
}

void partition (struct targs *thread) {//how is it conflicting?
    int mod = thread->length % thread->nthreads;
    int pert;
    if (!mod) {//for divisible.
        pert = thread->length / thread->nthreads;
        thread->start = thread->id * pert;
        thread->stop = thread->start + pert - 1;
    }
    //worry about non-divisibility cases once you get this one under control.
}
//next step: make it work with a struct.

int *PrimeFactors(int num) {//returns pointer to list of factors.
    int max = 0;
    int even = 0;//is it even or not?
    int factors = 0;//number of factors.
    //int len = 10;
    //int *pfacs = malloc(sizeof(int)*len);
    printf("%d\n",num);
    int temp = num;
    while (!(temp % 2)) {//while even
        printf("temp = %d, ",temp);
        if (num == temp) {
            factors++;
            even = 1;
        }
        temp = temp /2;
        printf("temp %d to %d, ",2*temp,temp);
    }
    int sq = ((int)trunc(sqrt((float)(temp))))+1;
    printf("sq: %d\n",sq);
    int *pfacs = malloc(sizeof(int)*sq);//typecasting in C vs python
    if (even) {
        pfacs[0] = 2;
    }
    for (int i=3; i < temp; i+=2) {//step through odd numbers.
        int first = 1;
        printf("mod = %d,",temp%i);
        while (!(temp % i)) {//while because might be divisible by i multiple times
            //add some varible to track if it is the first time it has been divided by i.
            if (first){
                pfacs[factors] = i;
                first--;
                factors++;
            }
            temp = temp / i;
        }
    }
    if (temp > 2) {
        pfacs[factors] = temp;
        factors++;
    }
    /*if (temp == num) {
        pfacs[0] = num;
    }*/
    //temp = 2?
    return pfacs;//return list of factors.
}
int max(int *nums, int length) {//returns max of a list of integers.
    int max = 0;
    for (int j=0; j < length; j++) {
        if(nums[j] > max) {
            max = nums[j];
        }
    }
    return max;
}
void sample() {
    int **twoD = malloc(sizeof(int*)*2);
    int *oneD = malloc(sizeof(int)*5);
    int *oneD2 = malloc(sizeof(int)*5);
    for (int i=0; i<5; i++) {
        oneD[i] = 2*i+1;
        oneD2[i] = 2*i;
    }
    twoD[0] = oneD;
    twoD[1] = oneD2;
    for (int i=0; i < 5; i++) {
        printf("twoD[0][%d]=%d twoD[1][%d]=%d\n",i,twoD[0][i],i,twoD[1][i]);
    }
    free(oneD);
    free(oneD2);
    free(twoD[0]);
    free(twoD[1]);
    free(twoD);
}
