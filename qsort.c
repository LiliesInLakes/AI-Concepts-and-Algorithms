#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int left, int right){
    int temp;
    temp=0;
    temp= arr[left];
    arr[left]= arr[right];
    arr[right]= temp;
}
int sort(int arr[], int low, int high){
    int pivot;
    int pivot_numb;
    pivot = (low+high)/2;
    pivot_numb= arr[pivot];
    swap(arr, pivot, high);
    int i;
    int left, right;
    left=low;
    right= high;
    
    for(i=left; i<right; i++){
        while(left<right){
            while(arr[left]<pivot_numb){
                left++;
            }
            while(arr[right]>pivot_numb){
                right--;
            }
            swap(arr, left, right);
        }
        break;
    }
    swap(arr, pivot, right);
    return right;

}
int quicsort(int arr[], int low, int high){
    if(low>=high){
        return 0;
    }
    int pivot;
    pivot= sort(arr, low, high);
    quicsort(arr, low, pivot);
    quicsort(arr, pivot, high);
    return 0;
}
int main(){
    int arr[6]= {1, 2, 5, 7, 3, 6};
    quicsort(arr, 0, 5);
    int i;
    for(i=0; i<6; i++){
        printf("%d ", arr[i]);
    }
}