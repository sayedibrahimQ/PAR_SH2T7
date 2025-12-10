#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

const int N=5;
pthread_mutex_t forks[N];
pthread_mutex_t mymutex;

void* philosopher(void* arg){
    int id=intptr_t(arg);
    int left=id;
    int right=(id+1)%N;

    while(true){
        pthread_mutex_lock(&mymutex);
            cout<<"left fork "<<id<<endl;
        pthread_mutex_unlock(&mymutex);

        pthread_mutex_lock(&forks[left]);
        Sleep(5);

        pthread_mutex_lock(&forks[right]);
        cout<<"right fork "<<id<<endl;


        cout<<"Philosopher"<<id<<" is eating"<<endl;

        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);


    }
    return NULL;
}

int main(){

    for(int i=0;i<N;i++)
        pthread_mutex_init(&forks[i],NULL);

    pthread_t philosophers[N];
    for(int i=0;i<N;i++){
        pthread_create(&philosophers[i],NULL,philosopher,(void*)i);
    }

    for(int i=0;i<N;i++)
        pthread_join(philosophers[i],NULL);

    return 0;
}