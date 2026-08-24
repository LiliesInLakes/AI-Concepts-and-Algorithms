#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int max(int a, int b){
    return a>b? a:b;
}

int main(){
    int n, temp, current_max, glob_max, start, end, flag, i;
    scanf("%d", &n);
    scanf("%d", &temp);
    current_max=glob_max=temp;
    start=end=1;
    for(i=2; i<n+1; i++){
        scanf("%d", &temp);
        if(current_max+temp>= temp){
            current_max= current_max+temp;
        }
        else{
            current_max= temp;
            flag=i;
        }
        if(current_max>glob_max){
            start= flag;
            end= i;
            glob_max= current_max;
        }
    }
    printf("%d %d %d", glob_max, start, end);
}