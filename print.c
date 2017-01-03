#include <stdio.h>
#include <stdint.h>

void
clflush(volatile void *p)
{
    asm volatile ("clflush (%0)" :: "r"(p));
}

uint64_t
rdtsc()
{
    unsigned long a, d;
    asm volatile ("rdtsc" : "=a" (a), "=d" (d));
    return a | ((uint64_t)d << 32);
}

volatile int i;

void
test(int *n, float *avrg, int *min, int *max, FILE *fp)
{
    uint64_t start, end;
    volatile int j;
    

    start = rdtsc();
    j = i;
    end = rdtsc();
    if((end-start)>0){
	(*avrg)=(float)(((end-start)+(*avrg)*(*n))/((*n)+1));
	if((end-start)<(*min)){
	    (*min)=end-start;
	}
	if((end-start)>(*max)){
	    (*max)=(end-start);
	}
    (*n)++;

    fprintf(fp,"%lu\n",(end-start));

    }
}

int
main(int ac, char **av)
{
    /*test();
    test();
    printf("flush: ");
    clflush(&i);
    test();
    test();
	*/
    int n=0;
    int min=100;
    int max=0;
    float avrg=0;
    FILE * fp;
    fp = fopen ("file.txt", "w");




   

	for( ; ;){test(&n,&avrg,&min,&max,fp);}

    fclose(fp);

    return 0;
}
