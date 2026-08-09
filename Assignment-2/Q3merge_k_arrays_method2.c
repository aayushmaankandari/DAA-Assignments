#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int a[], int l, int m, int r){

    int n1=m-l+1,n2=r-m;

    int L[n1],R[n2];

    for(int i=0;i<n1;i++) L[i]=a[l+i];
    for(int i=0;i<n2;i++) R[i]=a[m+1+i];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2)
        a[k++]=(L[i]<=R[j])?L[i++]:R[j++];

    while(i<n1)
        a[k++]=L[i++];

    while(j<n2)
        a[k++]=R[j++];
}

int main(){

    int n=1000;

    printf("k\tTime(ms)\n");

    for(int k=2;k<=10;k++){

        int total=n*k;

        int *arr=malloc(total*sizeof(int));

        for(int i=0;i<total;i++)
            arr[i]=rand();

        clock_t start=clock();

        for(int i=1;i<k;i++)
            merge(arr,0,i*n-1,(i+1)*n-1);

        clock_t end=clock();

        printf("%d\t%.2f\n",k,
        (double)(end-start)*1000/CLOCKS_PER_SEC);

        free(arr);
    }

    return 0;
}