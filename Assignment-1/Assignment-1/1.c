#include <stdio.h>
#include <math.h>

typedef struct {
    char *name;
    double (*f)(double);
} Fun;

double f1(double n) { return n * log2(n); }
double f2(double n) { return 12 * sqrt(n); }
double f3(double n) { return 1 / n; }
double f4(double n) { return pow(n, log2(n)); }
double f5(double n) { return 100*n*n + 6*n; }
double f6(double n) { return pow(n, 0.51); }
double f7(double n) { return n*n - 324; }
double f8(double n) { return 50 * sqrt(n); }
double f9(double n) { return 2 * pow(n, 3); }
double f10(double n) { return pow(3, n); }
double f11(double n) { return pow(2, 32) * n; }
double f12(double n) { return log2(n); }

int main()
{
    double n = 1000;

    Fun a[] = {
        {"n log2(n)", f1}, {"12 sqrt(n)", f2}, {"1/n", f3},
        {"n^(log2 n)", f4}, {"100n^2+6n", f5}, {"n^0.51", f6},
        {"n^2-324", f7}, {"50n^0.5", f8}, {"2n^3", f9},
        {"3^n", f10}, {"2^32 n", f11}, {"log2(n)", f12}
    };

    int size = 12;

    for (int i = 0; i < size-1; i++)
        for (int j = 0; j < size-i-1; j++)
            if (a[j].f(n) > a[j+1].f(n)) {
                Fun t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }

    printf("Increasing Order of Growth:\n");
    for (int i = 0; i < size; i++)
        printf("%d. %s\n", i+1, a[i].name);

    return 0;
}