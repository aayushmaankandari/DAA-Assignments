#include <stdio.h>

void multiplyPattern(int M1, int M2, int N1, int N2, int *P1, int *P2) {
    *P1 = M1*N1 + M2*N2;
    *P2 = M1*N2 + M2*N1;
}

int main() {
    int M1=2, M2=3, N1=4, N2=5;
    int P1, P2;
    multiplyPattern(M1, M2, N1, N2, &P1, &P2);
    printf("Result matrix:\n%d %d\n%d %d\n", P1, P2, P2, P1);
    return 0;
}
