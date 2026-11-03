#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector <int> construct_lps(string s){
    int len = 0;
    vector<int> lps(s.size(), 0);
    for(int i = 1; i <s.size(); i++){
        printf("%d %d %c %c\n", i , len, s[i], s[len]);
        if(s[i] == s[len]){
            lps[i] = ++len;
        }
        else{
            if(len){
                i--;
                len = lps[len -1];
            }
            else{
                len = 0;
            }
        }
    }
    for(const auto &c :lps){
        cout << c <<" ";
    }
    
    return lps;
}

int main(){
    string s = "aaaaa";
    string p ="xyz";

    // abbcababb
    vector <int> lps = construct_lps(p);
    int i = 0;
    int len = 0;
    while(i < s.size()){
        if(s[i] == p[len]){
            i++;
            len++;
            if(len == p.size()){
                printf("pattern found at %d ", i- len);
                len = lps[len -1];
            }
        }
        else{
            if(len){
                len = lps[len -1];
            }
            else{
                i ++;
            }
        }

    }
}