#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1], R[n2];

    for(int i=0;i<n1;i++)
        L[i]=arr[l+i];

    for(int i=0;i<n2;i++)
        R[i]=arr[m+1+i];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2){
        if(L[i]<=R[j])
            arr[k++]=L[i++];
        else
            arr[k++]=R[j++];
    }

    while(i<n1)
        arr[k++]=L[i++];

    while(j<n2)
        arr[k++]=R[j++];
}

void mergeSort(int arr[], int l, int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

// 3-way merge
void merge3(int arr[], int l, int m1, int m2, int r){

    int n1=m1-l+1;
    int n2=m2-m1;
    int n3=r-m2;

    int A[n1],B[n2],C[n3];

    for(int i=0;i<n1;i++)
        A[i]=arr[l+i];

    for(int i=0;i<n2;i++)
        B[i]=arr[m1+1+i];

    for(int i=0;i<n3;i++)
        C[i]=arr[m2+1+i];

    int i=0,j=0,k=0,t=l;

    while(i<n1 && j<n2 && k<n3){
        if(A[i]<=B[j] && A[i]<=C[k])
            arr[t++]=A[i++];
        else if(B[j]<=A[i] && B[j]<=C[k])
            arr[t++]=B[j++];
        else
            arr[t++]=C[k++];
    }

    while(i<n1 && j<n2)
        arr[t++]=(A[i]<=B[j])?A[i++]:B[j++];

    while(i<n1 && k<n3)
        arr[t++]=(A[i]<=C[k])?A[i++]:C[k++];

    while(j<n2 && k<n3)
        arr[t++]=(B[j]<=C[k])?B[j++]:C[k++];

    while(i<n1)
        arr[t++]=A[i++];

    while(j<n2)
        arr[t++]=B[j++];

    while(k<n3)
        arr[t++]=C[k++];
}

void mergeSort3(int arr[], int l, int r){

    if(l>=r)
        return;

    int third=(r-l)/3;

    int m1=l+third;
    int m2=l+2*third+1;

    if(m2>r)
        m2=r;

    mergeSort3(arr,l,m1);
    mergeSort3(arr,m1+1,m2);
    mergeSort3(arr,m2+1,r);

    merge3(arr,l,m1,m2,r);
}

int main(){

    printf("Size\tMerge(ms)\t3-Way(ms)\n");

    for(int n=100000;n<=1000000;n+=100000){

        int *a=malloc(n*sizeof(int));
        int *b=malloc(n*sizeof(int));

        for(int i=0;i<n;i++){
            a[i]=rand();
            b[i]=a[i];
        }

        clock_t start,end;

        start=clock();
        mergeSort(a,0,n-1);
        end=clock();
        double t1=(double)(end-start)*1000/CLOCKS_PER_SEC;

        start=clock();
        mergeSort3(b,0,n-1);
        end=clock();
        double t2=(double)(end-start)*1000/CLOCKS_PER_SEC;

        printf("%d\t%.2f\t\t%.2f\n",n,t1,t2);

        free(a);
        free(b);
    }

    return 0;
}