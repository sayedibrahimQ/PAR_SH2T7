#include <iostream>
#include <omp.h>
using namespace std;


double factorial(int n) {
    if (n<=1)
        return 1;
    return n*factorial(n-1);
}
int main(){
    int n,m;
double **matrix;
    cout<<"enter ur size of matrix n and m"<<endl;
    cin>>n>>m;

    matrix=new double*[n];
    for(int i=0;i<n;i++)
        matrix[i]=new double[m];


    double t1=omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            double f=factorial(j+1);
            if((j+1)%2==0)
                matrix[i][j]=-1.0*f/(i+j+1);
            else
                matrix[i][j]=1.0*f/(i+j+1);
        }
    }

    double t2=omp_get_wtime();

    cout<<"answer is ***********************"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    cout<<"Time taken:"<<t2-t1<<" sec"<<endl;
}