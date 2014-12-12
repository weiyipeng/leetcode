//
//  main.cpp
//  leetcode
//
//  Created by 魏弋彭 on 12/13/14.
//  Copyright (c) 2014 魏弋彭. All rights reserved.
//

#include <iostream>
#include <map>
#include <list> 
#include <vector>

using namespace std;

//  Definition for singly-linked list with a random pointer.
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

void printList(RandomListNode * head){
    RandomListNode * trav_ptr = head;
    while(trav_ptr != NULL) {
        std::cout <<" Node: " << trav_ptr->label <<"  -> next:" << (trav_ptr->next == NULL ? -1 : trav_ptr->next->label) << " -> random: " << (trav_ptr->random == NULL ? -1 : trav_ptr->random->label) << std::endl;
        trav_ptr = trav_ptr->next;
    }
}

#include <iostream>

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode *ptr = head;
        RandomListNode *cp_prev_ptr=NULL, *cp_head = NULL;
        int length = 0; //length of list
        map<RandomListNode *, list<int>> randomMap;
        vector<RandomListNode*> cp_ptr_vec;
        vector<RandomListNode*> ptr_vec;
        while(ptr != NULL) {
            RandomListNode *cp_ptr = new RandomListNode(ptr->label); // new copied pointer. assign label.
            if(cp_head == NULL){
                cp_head = cp_ptr;
            }
            if(cp_prev_ptr != NULL)
                cp_prev_ptr->next = cp_ptr; //connect the new pointer with prev.
            cp_prev_ptr = cp_ptr; //store the new pointer as prev for next new pointer
            randomMap[ptr->random].push_back(length);
            std::cout<<"create map " << (ptr->random != NULL ? ptr->random->label : -1 )<<" -> " << length << endl;
            ptr_vec.push_back(ptr);
            ptr = ptr->next; //traverse the list with next
            length++;
            cp_ptr_vec.push_back(cp_ptr);
        }
        map<RandomListNode*, list<int>>::iterator iter;
        for(iter = randomMap.begin(); iter != randomMap.end(); iter++){
            std::cout<<"Map, " << (iter->first == NULL ? -1 : iter->first->label) << " <- " ;
            list<int>::iterator iter2;
            for(iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++){
                std::cout<< *iter2 <<"  ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"copy the list with next finish\n";
        printList(cp_head);
        ptr = head;
        int i = 0;
        while(ptr != NULL){
            while(randomMap[ptr].size() > 0){
                int j = randomMap[ptr].front();
                randomMap[ptr].pop_front();
                cp_ptr_vec[j]->random = cp_ptr_vec[i];
            }
            ptr = ptr -> next;
            i++;
        }
        ptr = NULL;
        while(randomMap[ptr].size() > 0){
            int j = randomMap[ptr].front();
            randomMap[ptr].pop_front();
            cp_ptr_vec[j]->random = NULL;
        }
        
        return cp_head;
    }
};

int main(int argc, const char * argv[]) {
    RandomListNode * head = new RandomListNode(0);
    RandomListNode * trav_ptr = head;
    for(int i = 0; i < 10; i++){
        RandomListNode * new_node = new RandomListNode(i+1);
        trav_ptr -> next = new_node;
        trav_ptr = new_node;
    }
    std::cout<<"initial List finish\n";
    trav_ptr = head;
    int i = 0;
    while(trav_ptr != NULL) {
        trav_ptr->random = i < 5 ? trav_ptr->next->next->next : i % 4 ? head : NULL;
        trav_ptr = trav_ptr->next;
        i++;
    }
    printList(head);
    Solution solution;
    printList(solution.copyRandomList(head));
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
