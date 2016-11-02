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
test()
{
    uint64_t start, end;
    volatile int j;

    start = rdtsc();
    j = i;
    end = rdtsc();
    printf("took %lu ticks\n", end - start);
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
	for( ; ;){test();}
    return 0;
}