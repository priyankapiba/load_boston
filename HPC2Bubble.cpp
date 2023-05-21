#include<iostream>
#include<omp.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubble(int arr[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1-i; j++ ){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void pBubble(int arr[], int n){
    for(int i = 0; i < n-1; i++){
        #pragma omp parallel for
        for(int j = 0; j < n-i-1; j++ ){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
        
        #pragma omp barrier
        
        #pragma omp for
        for(int j = 2; j < n-i-1; j+=2 ){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void printArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}

int main()
{
    time_point<system_clock> start, end;
    int size = 1000;
    int arr[size], brr[size];
    for(int i = 0; i < size; i++){
        int k = rand()%100;
        arr[i] = k;
        brr[i] = k;
     
    }
    
    cout << "\nNormal"<< endl; 
    start = system_clock::now();
    bubble(arr, size);
    // printArray(arr, size);
    end = system_clock::now();
    duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count();
    cout << "\nParallel"<< endl; 
    start = system_clock::now();
    pBubble(brr, size);
    // printArray(brr, size);
    end = system_clock::now();
    elapsed_seconds = end - start;
    cout << elapsed_seconds.count();

    return 0;
}