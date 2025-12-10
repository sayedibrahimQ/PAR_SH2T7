#include <iostream>
#include <cmath>
#include <omp.h>
using namespace std;

bool isPrime(int num) {
    if(num<2)
     return false;
    for(int i=2;i*i<=num;i++)
    {
        if(num%i==0)
            return false;
    }

    return true;
}

int main() {

    for(int n=0;n<=7;n++){
        int num=pow(10,n);
        int primeCount = 0;

        double start = omp_get_wtime();

        #pragma omp parallel for reduction(+:primeCount)
        for(int i = 2; i <= num; i++){
            if(isPrime(i))
                primeCount += 1;
        }

        double end = omp_get_wtime();
        int nonPrimeCount =num-primeCount;
cout << "num = " << num<< " | primecount = " << primeCount<< " | non primecount = "
 << nonPrimeCount<< " | time = " << (end-start) << " second\n";

    }

    return 0;
}