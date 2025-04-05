#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define PAGESIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: tlb <loops> <pages>");
        exit(1);
    }
    int loops = atoi(argv[1]);
    int pages = atoi(argv[2]);
    if (pages <= 0 || loops <= 0) {
        printf("Invalid format.");
        exit(1);
    }
    struct timespec start, end;
    int jump = PAGESIZE / sizeof(int);
    int *a = calloc(jump * pages, sizeof(int)); // fill with zeros.
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start)) { // right before accessing the memory.
        printf("failed to set clock");
        exit(1);
    }
    for (int j = 0; j < loops; j++) {
        for (int i = 0; i < pages * jump; i += jump) {
            a[i] += 1;
        }
    }
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end)) {  // right after accessing the memory.
        printf("failed to set clock");
        exit( 1);
    }
    free(a);
    long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
    printf("%ld", elapsed_ns);
    exit(0);
}

