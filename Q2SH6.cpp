#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    int n,p;
    cout<<"enter ur size"<<endl;
    cin>>n;
    cout<<"enter number of threads"<<endl;
    cin>>p;


    int* arr=new int[n];
    srand(time(0));
    for (int i=0;i<n;i++)
        {
            arr[i]=rand()%10+1;
            cout<<arr[i]<<" ";
        }
    int sum=0;
    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(p) reduction(+:sum)
    for (int i=0;i<n;i++)
        sum+=arr[i];

    double end = omp_get_wtime();

    cout << "ans => " << sum << endl;

}