#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int sharedNum=0;
int evenCounter=0;
int oddCounter=0;
bool finished=false;
bool numCollected=true;

pthread_mutex_t mylock;

void*Agent(void*arg){
    string name=*(string*)arg;
    while(!finished){
        pthread_mutex_lock(&mylock);
        if(numCollected && !finished){
            sharedNum=rand()%10+1;
            cout<<name<<" generated "<<sharedNum<<endl;
            numCollected=false;
        }
        pthread_mutex_unlock(&mylock);
}
    return NULL;

}

void*Collector(void*arg){
    while(!finished){
        pthread_mutex_lock(&mylock);
        if(!numCollected && !finished){
            if(sharedNum%2==0){
                evenCounter++;
                cout<<"collect => "<<sharedNum<<" and even count="<<evenCounter<<endl;
            }else{
                oddCounter++;
                cout<<"collect => "<<sharedNum<<" and odd count="<<oddCounter<<endl;
            }
            numCollected=true;
            if(evenCounter>=100 || oddCounter>=100)
                finished=true;
        }
        pthread_mutex_unlock(&mylock);
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    pthread_mutex_init(&mylock,NULL);
    pthread_t agent1,agent2,collector;
    string name1="Agent1",name2="Agent2";

    pthread_create(&agent1,NULL,Agent,&name1);
    pthread_create(&agent2,NULL,Agent,&name2);
    pthread_create(&collector,NULL,Collector,NULL);

    pthread_join(agent1,NULL);
    pthread_join(agent2,NULL);
    pthread_join(collector,NULL);

    if(evenCounter>=100)
        cout<<"even counter reacher 100 first"<<endl;
    else
        cout<<"odd counter reacher 100 first"<<endl;

    return 0;
}