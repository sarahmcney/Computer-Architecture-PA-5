#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Markers used to bound trace regions of interest */
volatile char MARKER_START, MARKER_END;

int main(int argc, char* argv[])
{

    /* Record marker addresses */
    FILE* marker_fp = fopen(".marker","w");
    assert(marker_fp);
    fprintf(marker_fp, "%llx\n%llx",
        (unsigned long long int) &MARKER_START,
        (unsigned long long int) &MARKER_END );
    fclose(marker_fp);

    if (argc!=3) {
        printf("Usage: ./cacheBlocking <matrix_a_file> <matrix_b_file>\n");
        exit(EXIT_FAILURE);
    }

    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t n;
    fscanf(matrix_a_fp, "%ld\n", &n);
    int* a = calloc( n*n, sizeof(int) );
    for ( size_t i=0; i<n; i++ ) {
        for ( size_t k=0; k<n; k++ )
            fscanf(matrix_a_fp, "%d ", &a[i*n+k]);
        fscanf(matrix_a_fp, "\n");
    }
    fclose(matrix_a_fp);

    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t m;
    fscanf(matrix_b_fp, "%ld\n", &m);
    assert( n==m );
    int* b = calloc( n*n, sizeof(int) );
    for ( size_t k=0; k<n; k++ ) {
        for ( size_t j=0; j<n; j++ )
            fscanf(matrix_b_fp, "%d ", &b[k*n+j]);
        fscanf(matrix_b_fp, "\n");
    }
    fclose(matrix_b_fp);

    int* c = calloc( n*n, sizeof(int) );
    MARKER_START = 211;
    int i, j, k, i1, j1, k1;
    int bsize = 2;
    for(i = 0; i < n; i += bsize) {
        for(j = 0; j < n; j += bsize) {
            for(k = 0; k < n; k += bsize) {
                for(i1 = i; i1 < i+bsize; i1++) {
                    for(j1 = j; j1 < j+bsize; j1++) {
                        for(k1 = k; k1 < k+bsize; k1++) {
                            c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];
                        }
                    }
                }
            }
        }
    }

   /* int i, j, k, kk, jj;
    double sum;
    int bsize = 2;
    int en = bsize * (n/bsize);

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            c[i][j] = 0.0;
        }
    }*/
    /*for(kk = 0; kk < en; kk += bsize) {
        for(jj = 0; jj < en; jj += bsize) {
            for(i = 0; i < n; i++) {
                for(j = jj; j < jj + bsize; j++) {
                    sum = c[i][j];
                    for(k = kk; k < kk + bsize; k++) {
                        sum += a[i][k]*b[k][j];
                    }
                    c[i][j] = sum;
                }
            }
        }
    }*/
    // ikj
    // for ( size_t i=0; i<n; i++ ) {
    //     for ( size_t k=0; k<n; k++ ) {
    //         int r = a[i*n+k];
    //         for ( size_t j=0; j<n; j++ ) {
    //             c[i*n+j] += r * b[k*n+j];
    //         }
    //     }
    // }

    // kij
    // for ( size_t k=0; k<n; k++ ) {
    //     for ( size_t i=0; i<n; i++ ) {
    //         int r = a[i*n+k];
    //         for ( size_t j=0; j<n; j++ ) {
    //             c[i*n+j] += r * b[k*n+j];
    //         }
    //     }
    // }

    // jki
    /*for ( size_t j=0; j<n; j++ ) {
        for ( size_t k=0; k<n; k++ ) {
            int r = b[k*n+j];
            for ( size_t i=0; i<n; i++ ) {
                c[i*n+j] += a[i*n+k] * r;
            }
        }
    }*/
    MARKER_END = 211;

    for ( size_t i=0; i<n; i++ ) {
        for ( size_t j=0; j<n; j++ ) {
            printf( "%d ", c[i*n+j] );
        }
        printf( "\n" );
    }

    free(c);
    free(b);
    free(a);
    exit(EXIT_SUCCESS);

}
