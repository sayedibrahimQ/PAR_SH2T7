#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

set<char> Vowels = {'a','e','i','o','u'};
bool IsVowel(char c){
    return Vowels.find(tolower(c)) != Vowels.end();
}

int main() {
    int n;
    cout << "enter ur num" << endl;
    cin >> n;

    string* arr = new string[n];
    char** matrix = new char*[n];

    for(int i=0;i<n;i++){
        cin >> arr[i];
        matrix[i] = new char[arr[i].size()];
        for(int j=0;j<arr[i].size();j++)
            matrix[i][j] = arr[i][j];
    }

    map<char,int> Count;

    double start = omp_get_wtime();

    #pragma omp parallel for
    for(int i=0;i<n;i++){
        map<char,int> localCount;
        for(int j=0;j<arr[i].size();j++){
            char c = tolower(matrix[i][j]);
            if(IsVowel(c))
                localCount[c]++;
        }

        #pragma omp critical
        {
            for(auto x : localCount)
                Count[x.first] += x.second;
        }

    }
    

    double end = omp_get_wtime();
    cout<<"************************Matrix*********************"<<endl;;
    for(int i=0;i<n;i++){
        for(int j=0;j<arr[i].size();j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    cout << "Vowel counts:\n";
    for(auto x : Count)
        cout << x.first << " : " << x.second << endl;




    return 0;
}