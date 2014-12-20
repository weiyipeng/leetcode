//
//  main.cpp
//  WordLadder2
//
//  Created by 魏弋彭 on 12/20/14.
//  Copyright (c) 2014 魏弋彭. All rights reserved.
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include <map>
#include <list>
#include <string> 


using namespace std;

class Solution {
public:
    struct treeNode{
        vector<treeNode*>   child;
        vector<treeNode*>   parent;
        string              word;
        int                 level;
        treeNode(string w, int l) : word(w), level(l) {}
    };
    
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        vector<vector<string>> ret;
        int size = (int)dict.size();
        int start_i;
        int end_i;
        vector<vector<int>> edges;
        vector<string> dict_vs;
        map<string,int> dict_reverse;
        map<int, treeNode*> dict_ptr;
        
        for(int i = 0; i < size; i++){ //initialize 2-dimension vectors to 0
            vector<int> tmp_vec;
            for(int j = 0; j < size; j++)
                tmp_vec.push_back(0);
            edges.push_back(tmp_vec);
        }
        
        unordered_set<string>::iterator iter;
        int i = 0;
        for(iter = dict.begin(); iter != dict.end(); iter++, i++){
            dict_vs.push_back(*iter);
            dict_reverse[*iter] = i;
            if(*iter == start)
                start_i = i;
            if(*iter == end)
                end_i = i;
            unordered_set<string>::iterator iter2;
            int j = 0;
            for(iter2 = dict.begin(); iter2 != dict.end(); iter2++, j++){
                string a, b;
                a = *iter;
                b = *iter2;
                int diff = 0;
                for(int k = 0; k < a.size(); k++){
                    if(a[k] != b[k])
                        diff++;
                }
                if(diff == 1){
                    edges[i][j] = 1;
                }
            }
        }
        
        //for(int i = 0; i < size; i++) {
        //    for(int j = 0; j < size; j++){
        //        cout << edges[i][j] << " ";
        //    }
        //    cout << endl;
        //}
        
        treeNode * root = new treeNode(start, 1);
        //cout <<"new ptr" << hex << (long int) root << endl;
        list<treeNode*>  nodes;
        treeNode * endNode = NULL;
        nodes.push_back(root);
        int cur = dict_reverse[start];
        
        int * level = new int[size];
        for(int i= 0; i < size; i++)
            level[i] = 0;
        level[cur] = 1;
        
        do{
            cur = dict_reverse[nodes.front()->word];
            for(int i = 0; i < size; i++){
                if(edges[cur][i] == 1 && (level[i] == 0 || level[i] == level[cur]+1)){
                    treeNode * new_child;
                    if(level[i] == 0) {
                        new_child = new treeNode(dict_vs[i], nodes.front()->level+1);
                        //cout <<"new ptr" << (long int) new_child << endl;
                        dict_ptr[i] = new_child;
                        level[i] = level[cur] + 1;
                    }
                    else
                        new_child = dict_ptr[i];
                    
                    ((nodes.front())->child).push_back(new_child);
                    new_child->parent.push_back(nodes.front());
                    //cout << nodes.front()->word <<" has child " << new_child->word << endl;
                    //cout << new_child->word <<"  has parent " << nodes.front()->word << endl;
                    nodes.push_back(new_child);
                    if(dict_vs[i] == end) {
                        endNode = new_child;
                    }
                }
            }
            for(int i = 0; i < size; i++){
                edges[cur][i] = 0;
                edges[i][cur] = 0;
            }
            nodes.pop_front();
        }while(nodes.size() > 0);
        
        if(endNode == NULL)
            return ret;
        
        vector<vector<treeNode*>> ret_ptr;
        vector<treeNode*> ladder_ptr;
        ladder_ptr.push_back(endNode);
        ret_ptr.push_back(ladder_ptr);
        int reach_root = 0;
        //cout <<"hi" << endl;
        do{
            for(int i = 0; i < ret_ptr.size(); i++) {
                //cout <<" i = " << i << " size = " << ret_ptr.size() << endl;
                int j = (int)ret_ptr[i].size() - 1;
                if(ret_ptr[i][j]->parent.size() == 0){
                    reach_root = 1;
                    break;
                }
                vector<treeNode*> tmp_ladder_ptr = ret_ptr[i];
                //cout <<i <<"  " << j << "  " << ret_ptr[i][j]->word << "  parent.size " << ret_ptr[i][j]->parent.size() << endl;
                for(int k = 0; k < ret_ptr[i][j]->parent.size(); k++){
                    if(k == 0){
                        ret_ptr[i].push_back(ret_ptr[i][j]->parent[k]);
                    }
                    else{
                        //cout <<"hihi" << endl;
                        ret_ptr.push_back(tmp_ladder_ptr);
                        ret_ptr.back().push_back(ret_ptr[i][j]->parent[k]);
                    }
                }
            }
        }while(reach_root == 0);
        
        for(int i = 0; i < ret_ptr.size(); i++){
            vector<string> ladder;
            for(int j = (int)ret_ptr[i].size(); j > 0; j--){
                ladder.push_back(ret_ptr[i][j-1]->word);
            }
            ret.push_back(ladder);
        }        return ret;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
        unordered_set<string> dict;
        dict.insert("hot");
        dict.insert("dog");
        dict.insert("cog");
        dict.insert("pot");
        dict.insert("dot");
        Solution sol;
        vector<vector<string>> ret = sol.findLadders("hot", "dog", dict);
        unordered_set<string>::iterator iter;
        dict.clear();
        for(int i = 0; i < ret.size(); i++){
            for(int j = 0; j < ret[i].size(); j++) {
                cout <<ret[i][j] <<" ";
            }
            cout << endl;
        }
    return 0;
}
