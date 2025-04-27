#include<iostream>
using namespace std;

void input(int arr[], int size){
    cout<< "Enter "<<size<< " Elements of the Array: ";

    for(int i = 0; i<size; i++){
        cin>> arr[i];
    }
}

void display(int arr[], int size){
    cout<<"Sorted Array: ";
    for(int i = 0; i<size;i++){
        cout<<arr[i]<< " ";
    }
    cout<<endl;
}

void SelectionSort(int arr[], int size){
    for(int i = 0; i<size-1; i++){
        int minIndex = i;

        for(int j = i+1; j<size; j++){
            if(arr[j]<arr[minIndex]){
                minIndex = j;
            }
        }

        if(minIndex != i){
            swap(arr[i], arr[minIndex]);
        }
    }
}

int main(){
    int size;
    cout<<"Enter Number of Elements in array: ";
    cin>>size;

    int arr[size];

    input(arr, size);

    SelectionSort(arr, size);

    display(arr, size);

    return 0;
}