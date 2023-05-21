/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <omp.h>

using namespace std;

int minval(int arr[], int n)
{
    int minival = arr[0];
    #pragma omp parallel for reduction(min : minival)
    for(int i = 0; i<n;i++){
        if(arr[i] < minival){
            minival = arr[i];
        }
    }
    return minival;
}

int maxval(int arr[], int n)
{
    int maxival = arr[0];
    #pragma omp parallel for reduction(max : maxival)
    for(int i = 0; i<n;i++){
        if(arr[i] > maxival){
            maxival = arr[i];
        }
    }
    return maxival;
}

int sum(int arr[], int n){
  int sumi = arr[0];
  #pragma omp parallel for reduction(+ : sumi)
    for(int i = 0; i < n; i++){
      sumi += arr[i];
    }
  return sumi;
}

int average(int arr[], int n){
  return (double)sum(arr, n) / n;
}


int main(){
    int n = 50;
    int arr[n];
    for(int i=0;i<n;i++)
      arr[i]=rand()%100;  
     
    cout << "The minimum value is: " << minval(arr, n) << '\n';
    cout << "The maximum value is: " << maxval(arr, n) << '\n';
    cout << "The summation is: " << sum(arr, n) << '\n';
    cout << "The average is: " << average(arr, n) << '\n';
  return 0; 
    
}
