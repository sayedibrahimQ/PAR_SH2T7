#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

long long fib_task(int n) {
    if(n==0) return 0;
    if(n==1) return 1;

    int x,y;

    #pragma omp task shared(x)
    x=fib_task(n-1);

    #pragma omp task shared(y)
    y=fib_task(n-2);

    #pragma omp taskwait
    return x+y;
}

int main() {
    int n;
    cout<<"enter ur num"<<endl;;
    cin>>n;
    int* fib=new int[n];
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        for(int i=0;i<n;i++)
            fib[i]=fib_task(i);
    }

    double end=omp_get_wtime();

    for(int i=0;i<n;i++)
        cout << fib[i] << " ";

    return 0;
}