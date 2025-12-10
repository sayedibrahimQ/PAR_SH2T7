#include <bits/stdc++.h>

using namespace std;

bool finished = false;
bool VegetableReady = false;
bool BeefReady = false;
bool BreadReady = false;
int counter = 0;

pthread_mutex_t mymutex;

void* VegetableWork(void* args) {
    while (!finished) {
        pthread_mutex_lock(&mymutex);
        if (!VegetableReady&!finished) {
            cout << "make Vegetableavb to be used.." << endl;
            VegetableReady = true;
        }
        pthread_mutex_unlock(&mymutex);
    }
    return NULL;
}

void* BeefWork(void* args) {
    while (!finished) {
        pthread_mutex_lock(&mymutex);
        if (!BeefReady&!finished) {
            cout << "make beefavb to be used.." << endl;
            BeefReady = true;
        }
        pthread_mutex_unlock(&mymutex);
    }
    return NULL;
}

void* BreadWork(void* args) {
    while (!finished) {
        pthread_mutex_lock(&mymutex);
        if (!BreadReady&!finished) {
            cout << "make breadavb to be used.." << endl;
            BreadReady = true;
        }
        pthread_mutex_unlock(&mymutex);
    }
    return NULL;
}

void* AssemblerWork(void* args) {
    while (!finished) {
        pthread_mutex_lock(&mymutex);
        if (VegetableReady && BeefReady && BreadReady&!finished) {
            cout << "assembling the burger..." << endl;
            VegetableReady = false;
            BeefReady = false;
            BreadReady = false;
            counter++;
            if (counter == 5) finished = true;
        }
        pthread_mutex_unlock(&mymutex);
    }
    return NULL;
}

int main() {
  pthread_t Vegetable_Worker;
  pthread_t Beef_Worker;
  pthread_t Bread_Worker;
  pthread_t Assembler;
  pthread_create(&Assembler, NULL, AssemblerWork, NULL);
  pthread_create(&Vegetable_Worker, NULL, VegetableWork, NULL);
  pthread_create(&Beef_Worker, NULL, BeefWork, NULL);
  pthread_create(&Bread_Worker, NULL, BreadWork, NULL);

  pthread_join(Vegetable_Worker, NULL);
  pthread_join(Beef_Worker, NULL);
  pthread_join(Bread_Worker, NULL);
  pthread_join(Assembler, NULL);
  return 0;
}