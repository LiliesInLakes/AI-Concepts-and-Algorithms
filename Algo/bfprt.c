#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void swap(int arr[], int i, int j){
    int temp;
    temp= arr[i];
    arr[i]= arr[j];
    arr[j]= temp;
    
}

int sort(int arr[], int start, int end){
    int i;
    int j;
    for(i= start; i<end; i++){
        for(j=i; j>0; j--){
            if(arr[j]<arr[j-1]){
                swap(arr, j, j-1);
            }
        }
    }
    // printf("in sort ");
    // for(i=start; i<end; i++){
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");    
    return 0;
}

int med(int arr[], int start, int end){
    sort(arr, start, end);
    int i;
    printf("in median ");
    for(i=start; i<end; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");   
    int median_pos;
    median_pos= (start+end)/2;
    return arr[median_pos];
}

int bfprt(int arr[], int k, int start, int end){
    int i;
    printf("in bfprt, k is %d", k);
    if(end- start <=5){
        sort(arr, start, end);
        printf("in <4 ");
        for(i=start; i<end; i++){
            printf("%d ", arr[i]);
        }
        printf("\n"); 
        return arr[start+k];
    }
    int *med_arr;
    int len_med;
    len_med=0;
    int strtcpy;
    strtcpy= start;
    med_arr= (int *)malloc(sizeof(int)*((start+end+4)/5));
    printf("len_med is %d", (start+end+4)/5);
    for(i=1; i<(start+end+4)/5; i++){
        printf("%d  to  %d\n", arr[strtcpy], arr[strtcpy+5]);
        med_arr[len_med++]=med(arr, strtcpy, strtcpy+5);
        strtcpy+=5;
    }
    printf("%d  to  %d\n", arr[strtcpy], arr[end]);
    med_arr[len_med]= med(arr, strtcpy, end);
    int median;
    printf("median arr is ");
    for(i=0; i<len_med+1; i++){
            printf("%d ", med_arr[i]);
        }
    printf("\n");
    printf("doing bfprt on med_arr, len_med is %d k is %d", len_med, (len_med+1)/2);
    median= bfprt(med_arr, (len_med+1)/2, 0, len_med+1);
    printf("median is %d\n", median);
    sort(arr, start, end);
    for(i=start; i<end; i++){
        if(arr[i]==median){
            printf("median found in arr\n");
            break;
        }
    }
    if(k==i){
        printf("returning median\n");
        return median;
    }
    else if(k<= i){
        printf("bfprt left");
        return bfprt(arr, k, start, i);
    }
    printf("bfprt right");
    return bfprt(arr, k- i-1, i+1, end);
    
}


int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *arr;
    arr= (int  *)malloc(sizeof(int)*n);
    int i;
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("-----------final o: %d -----------", bfprt(arr, k-1, 0, n));
     
    return 0;
}
