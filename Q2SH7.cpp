#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

int main() {
    srand(time(0));
    int n;
    cout<<"enter ur size ";
    cin>>n;

    int** a = new int*[n];
    int** b = new int*[n];
    int** c = new int*[n];
    for(int i=0;i<n;i++) {
        a[i] = new int[n];
        b[i] = new int[n];
        c[i] = new int[n];
    }

    cout << "matrix a"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=rand()%10;
            cout<<a[i][j]<< " ";
        }
        cout << endl;
    }
    cout << "matrix b"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            b[i][j]=rand()%10;
            cout<<b[i][j]<< " ";
        }
        cout << endl;
    }

    double startw = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
                c[i][j]=0;
            for(int h=0;h<n;h++){
                c[i][j]+= a[i][h]* b[h][j];

            }
        }
    }

    double endw = omp_get_wtime();

       cout << "matrix c"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<c[i][j]<< " ";
        }
        cout << endl;
    }

    cout << "parallel time " <<(endw-startw)<<" sec";



    return 0;
}