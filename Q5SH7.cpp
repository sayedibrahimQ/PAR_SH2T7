#include <iostream>
#include <omp.h>
#include <cmath>
#include <ctime>
using namespace std;

int* prefix_sum(int *X,int n){
    int *s=new int[n];
    int *Y=new int[n];
    int *Z=new int[n];

    if(n==1){
        s[0]=X[0];
        return s;
    }

    #pragma omp parallel
    {
        #pragma omp for
        for(int i=0;i<=n/2;i++){
            Y[i]=X[2*i]+X[2*i+1];
        }
        #pragma omp barrier

        #pragma omp single
        Z=prefix_sum(Y,n/2);
        #pragma omp barrier

        #pragma omp for
        for(int i=0;i<n;i++){
            if(i==0) s[i]=X[i];
            else if(i%2==1) s[i]=Z[i/2];
            else s[i]=Z[(i-1)/2]+X[i];
        }
        #pragma omp barrier
    }
    return s;
}

int main(){
    srand(time(0));
    int size;
    cin>>size;
    int n=pow(2,size);
    int *arr=new int[n];
    for(int i=0;i<n;i++){
        arr[i]=rand()%11;
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    int *ans=prefix_sum(arr,n);
    for(int i=0;i<n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}