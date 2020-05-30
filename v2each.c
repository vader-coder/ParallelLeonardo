//I think this version is supposed to be a version where each thread gets the list of prime factors for each
//number that the input file reads. Then at the end 1 thread will output the numbers to an output file.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

/* This file will read numbers from an input file and write the prime factors of each number in an output file. Each number will have a thread which finds its prime factors. Only one thread will write the factors to the file.*/

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_barrier_t barrier;
int *PrimeFactors(int num);//returns list of prime factors of a number.
int max (int *nums, int length);//returns max # in an array.
//void partition (struct targs *thread);
void sample();
void *thread_func(void *args);

struct targs {//could add a max onehere, too.
    int id;//place in the list of threads.
    int num;//number to factor.
    int *facs;//list of factors
    int len;//number of factors
};

int main(int argc, char*argv[]) {
    if (argc != 3) {
	    printf("Usage: %s <input file> <output file>\n",argv[0]);
	    return 1;
    }
    int nNums, nthreads, ret;//number of facotrs, number of threads, return value? 
    pthread_t *threads;//thread pointer
    struct targs data;
    struct targs *tparams;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
	    perror("fopen");
	    return 1;
	}
    fscanf(f, "%d %d", &nNums, &nthreads);//won't use nthreads here.
    tparams = malloc(sizeof(struct targs) * nNums);
    pt = malloc(sizeof(pthread_t) * Nnums);
   //sample();
    /*printf("Input the number of numbers whose number of unique prime factors you want:\n");
    scanf("%d",&nfacs);//better way to handle than scanf.
    printf("input the number of threads you want to use: \n");
    scanf("%d",&nthreads);
    printf("Enter %d integers: \n",nfacs);*/
    //here we are in the conversion process.
    int *query = malloc(sizeof(int)*nNums);//stores numbers read from file
    int **factors = malloc((sizeof(int*)*nNums));//stores list of factors
    printf("nNums: %d\n",nNums);
    //Here is my PLACE!
    for (int i=0; i<nNums; i++) {
        //scanf("%d", &tparams->query[i]);
	//synchronization? mbe lock around fscanf to tparams.
	fscanf(f, "%d", query[i]);
	threads[i] = i;
	tparams[i].id = i;
	tparams[i].num = query[i];
	ret = pthread_create(&threads[i],0,thread_func,&tparams[i]);//create thread.
	//figure out a way to modify **factors w/in thread?
	if (ret) {
		printf("pthread_create error");
		free_args(query, factors, nNum);
		exit(1);
	}
    }
	 
     for (int i=0; i<nNums; i++) {
	    ret = pthread_join(pt[i],0);//parent thread reaps other threads.
	    if (ret) {
		    printf("pthread_join error");
		    free_args(query, factors, nNum);
		    exit(1);
	    }
     }
	//should only have one thread. maybe we should do printing in the threads function? 
     File *o = fopen(argv[2], "a");
    for (int i=0; i<nNums; i++) {//loops though # of numbers factored.
	    fprintf(o, "%d: ", query[i]);
	    for (int j=0; j<tparams[i].len; j++) {//loop through factors & print thme on each line
		    fprintf(o, "%d ",tparams[i]->facs[j]);
		
		}
	    fprintf(o, "\n");//enter to go to next line
    }
	    //write to file. at some point, use
		//length of factors to write it out.
	fprintf(o, "%d", factors[0][0]);//mk sure works
	    //
    fclose(f);
    fclose(o);
    free_args(query, factors, Nnum);//make sure right.
    //allocate thread args at some point.
    printf("Hello, World!\n");
    return 0;
}
void *thread_func(int *args) {//void *args?
    struct targs data = args;
	PrimeFactors(data->num, args);//return list of factors.
	//should set this pointer to be the list of factors.
	//pthread_mutex_lock(&mutex);//do we need to lock this? only one will access each factors[i] at a time. 
	//factors[data->num] = &facs;
	//pthread_mutex_unlock(&mutex); 
   
}
void free_args(int *query, int **factors, int nNums) {
	free(query);
	for (int i=0; i<nNums; i++) {
		free(factors[i]);
	}
	free(factors);
}


int* PrimeFactors(int num, int *args) {//returns pointer to list of factors.
    int max = 0;
    int even = 0;//is it even or not?
    int factors = 0;//number of factors.
    /*int len = 10;
    int *pfacs = malloc(sizeof(int)*len);*/
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
    int *pfacs = malloc(sizeof(int)*sq);//does this risk a race condition? might do factors[num] instaead.
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
    args->facs = &pfacs;
    args->len = factors.
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

