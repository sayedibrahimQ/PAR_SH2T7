#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

int main(){
    srand(time(0));

    int n,m;
    cout<<"enter matrix size n and m : ";
    cin>>n>>m;

    int **a=new int*[n];
    for(int i=0; i<n; i++)
        a[i]=new int[m];

    int *b=new int[m];
    int *c=new int[n];

    cout<<"matrix a"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            a[i][j]=rand()%10;
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"vector b"<<endl;
    for(int j=0; j<m; j++){
        b[j]=rand()%10;
        cout<<b[j]<<" ";
    }
    cout<<endl;

    double t1=omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for(int i=0; i<n; i++){
        c[i]=0;
        for(int j=0; j<m; j++){
            c[i]+=a[i][j]*b[j];
        }
    }

    double t2=omp_get_wtime();

    cout<<"result vector c"<<endl;
    for(int i=0; i<n; i++)
        cout<<c[i]<<" ";
    cout<<endl;

    cout<<"time taken : "<<t2-t1<<" sec"<<endl;

    return 0;
}