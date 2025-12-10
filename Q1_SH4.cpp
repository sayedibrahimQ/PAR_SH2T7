#include <bits/stdc++.h>

using namespace std;
bool finished = false;
bool Tobaccoavb = false;
bool paperavb = false;
bool matchesavb = false;
bool istaken = true;
int counter = 0;
pthread_mutex_t mymutex;


void* AgentWork(void* args) {

  srand(time(0));

  while (!finished) {


    if (istaken && !finished) {

      int i = rand() % 3;

      if (i == 0) {
        cout << "generating tobacco and paper" << endl;
        paperavb = true;
        Tobaccoavb = true;
        istaken = false;
      }
      else if (i == 1) {
        cout << "generating tobacco and matches" << endl;
        matchesavb = true;
        Tobaccoavb = true;
        istaken = false;
      } else {
        cout << "generating paper and matches" << endl;
        matchesavb = true;
        paperavb = true;
        istaken = false;
      }
    }
  }
}

void* Tobaco_Smoker(void* args) {

  while (!finished) {


    if (paperavb && matchesavb && !istaken) {
      cout << "collected paper and matches to make cigarette..." << endl;
      paperavb = false;
      matchesavb = false;
      istaken = true;
      counter++;
      if (counter == 10) finished = true;
    }
  }

  return NULL;
}

void* paper_Smoker(void* args) {

  while (!finished) {


    if (Tobaccoavb && matchesavb && !istaken) {
      cout << "collected tobacco and matches to make cigarette..." << endl;
      Tobaccoavb = false;
      matchesavb = false;
      istaken = true;
      counter++;
      if (counter == 10) finished = true;
    }
  }

  return NULL;
}

void* Matches_Smoker(void* args) {

  while (!finished) {


    if (paperavb && Tobaccoavb && !istaken) {
      cout << "collected paper and tobacco to make cigarette..." << endl;
      paperavb = false;
      Tobaccoavb = false;
      istaken = true;
      counter++;
      if (counter == 10) finished = true;
    }
  }
  return NULL;
}

int main() {
  pthread_t TobaccoSmokers;
  pthread_t MatchesSmokers;
  pthread_t PaperSmokers;
  pthread_t Agent;
  pthread_create(&Agent, NULL, AgentWork, NULL);
  pthread_create(&TobaccoSmokers, NULL, Tobaco_Smoker, NULL);
  pthread_create(&MatchesSmokers, NULL, Matches_Smoker, NULL);
  pthread_create(&PaperSmokers, NULL, paper_Smoker, NULL);

  pthread_join(TobaccoSmokers, NULL);
  pthread_join(MatchesSmokers, NULL);
  pthread_join(PaperSmokers, NULL);
  pthread_join(Agent, NULL);
  return 0;
}