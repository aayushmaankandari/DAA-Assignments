#include <stdio.h>
#include <math.h>

int main() {
    int n;

printf("n,O(1),O(log n),O(n)\n");

for(n = 1; n <= 100; n += 5)
{
    printf("%d,1,%.2f,%d\n", n, log2(n), n);
}
    return 0;
}