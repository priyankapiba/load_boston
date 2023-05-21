/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int low, int mid, int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    int left[n1];
    int right[n2];
    
    for(int i = 0; i <n1; i++){
        left[i] = arr[low + i];
    }
    
    for(int i = 0; i <n2; i++){
        right[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = low;
    
    while(i<n1 && j<n2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i < n1){
        arr[k] = left[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = right[i];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high){
    if(low < high){
        int mid = (low + high) /2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid +1, high);
        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}

int main(){
    int n = 10;
    int arr[n], brr[n];
    
    for(int i = 0, j = n; i<n; i++,j--){
        arr[i] = j;
        brr[i] = j;
    }
    
    mergeSort(arr, 0, n - 1);
    for(int i = 0; i<n; i++){
        cout<< arr[i] << " ";
    }
    parallelMergeSort(brr, 0, n - 1);
    for(int i = 0; i<n; i++){
        cout<< arr[i] << " ";
    }
    return 0;
}
