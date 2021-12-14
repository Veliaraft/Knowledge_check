#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>

double fRand(double fMin, double fMax);

int main(){
    srand(time(NULL));
    double bubble;
    double one = 1;
    double *ls = new double [10];
    for(int i = 0; i < 10; i++){
        ls[i] = fRand(-100, 100);
    }
    for(int i = 0; i < 10; i++){
        for(int j = i; j < 10; j++){
            if (fmod(ls[j], 1) < fmod(ls[i], 1)){
                bubble  = ls[i];
                ls[i] = ls[j];
                ls[j] = bubble;
            }
        }
    }
    for(int i = 0; i < 10; i++)
        std::cout << ls[i] << "\n";
    system("Pause");
}

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
