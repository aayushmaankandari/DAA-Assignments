#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

// Recursive FFT
void fft(complex double *a, int n, int invert) {
    if (n == 1) return;

    complex double *a0 = malloc(n / 2 * sizeof(complex double));
    complex double *a1 = malloc(n / 2 * sizeof(complex double));
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    fft(a0, n / 2, invert);
    fft(a1, n / 2, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    complex double w = 1;
    complex double wn = cos(ang) + sin(ang) * I;

    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }

    free(a0);
    free(a1);
}

// Convolution using FFT
void convolution(double *A, double *B, double *C, int n) {
    int size = 1;
    while (size < 2 * n) size <<= 1;

    complex double *fa = calloc(size, sizeof(complex double));
    complex double *fb = calloc(size, sizeof(complex double));

    for (int i = 0; i < n; i++) {
        fa[i] = A[i];
        fb[i] = B[i];
    }

    fft(fa, size, 0);
    fft(fb, size, 0);

    for (int i = 0; i < size; i++)
        fa[i] *= fb[i];

    fft(fa, size, 1);

    for (int i = 0; i < 2 * n - 1; i++)
        C[i] = creal(fa[i]);

    free(fa);
    free(fb);
}

// Driver code
int main() {
    int n = 4;
    double A[] = {1, 2, 3, 4};
    double B[] = {5, 6, 7, 8};
    double C[2 * n - 1];

    convolution(A, B, C, n);

    printf("Convolution result:\n");
    for (int i = 0; i < 2 * n - 1; i++)
        printf("%.2f ", C[i]);
    printf("\n");

    return 0;
}
