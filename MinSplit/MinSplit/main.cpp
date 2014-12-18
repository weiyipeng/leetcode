//
//  main.cpp
//  MinSplit
//
//  Created by 魏弋彭 on 12/13/14.
//  Copyright (c) 2014 魏弋彭. All rights reserved.
//

#include <iostream>
#include <string>
#include <map> 
#include <vector>

using namespace std;

int minSplit(string s) {
    map<int, int> palindrome;
    int len = (int)s.length();
    int i, j;
    int start=0, end=0;
    for(i = 0; i < len; i++) {
        for(j = 0; j <= i; j++){
            if(s[i-j] != s[i+j]){
                start = i-j+1;
                end = i+j-1;
                break;
            }
            else {
                start = i-j;
                end = i+j;
            }
        }
        
        map<int, int>::iterator iter;
        int abandon = 0;
        cout<<"palindrome.size()" << palindrome.size()<<endl;
        for(iter = palindrome.begin(); iter != palindrome.end(); ){
            if(iter->first >= start && iter->second <= end){
                cout <<"aplindrome.erase " << iter->first <<" -> " << iter->second << endl;
                palindrome.erase(iter++);
            }
            else if(iter->first <= start && iter->second >= end) {
                abandon = 1;
                iter++;
            }
            else
                iter++;
        }
        if(abandon == 0){
            cout <<"palindrome.add " << start <<" -> " << end << endl;
            palindrome[start] = end;
        }
    }
    for(map<int,int>::iterator iter = palindrome.begin(); iter != palindrome.end(); iter++){
        std::cout<<"palindrome: " << s <<" : " << iter->first <<" -> " << iter->second << " "<< s.substr(iter->first, iter->second + 1 - iter->first) << std::endl;
    }
    return (int)palindrome.size();
}

int main(int argc, const char * argv[]) {
    minSplit("1abcba1ertytre1dfefd1");
    std::cout << "Hello, World!\n";
    return 0;
}
