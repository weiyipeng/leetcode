//
//  main.cpp
//  path_sum_2
//
//  Created by 魏弋彭 on 12/19/14.
//  Copyright (c) 2014 魏弋彭. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> ret;
        vector<TreeNode*> path;
        TreeNode * trav = root;
        while(trav != NULL) {
            path.push_back(trav);
            if(trav->left != NULL){
                trav = trav->left;
            }
            else if(trav->right != NULL){
                trav = trav->right;
            }
            else{
                int sum_path = 0;
                vector<int> path_val;
                for(int i = 0; i < path.size(); i++){
                    sum_path += path[i]->val;
                    path_val.push_back(path[i]->val);
                    cout <<"sum_path = " << sum_path << endl;
                }
                if(sum_path == sum)
                    ret.push_back(path_val);
                trav = NULL;
                while(trav == NULL && path.size() > 0){
                    TreeNode * child = path.back();
                    path.pop_back();
                    if(path.size() == 0) break;
                    if(child == path.back()->left){
                        if(path.back()->right != NULL)
                            trav = path.back()->right;
                    }
                }
            }
        }
        return ret;
    }
};
int main(int argc, const char * argv[]) {
    TreeNode *root = new TreeNode(1);
    Solution *sol = new Solution();
    vector<vector<int>> ret = sol->pathSum(root, 1);
    for(int i = 0; i < ret.size(); i++){
        for(int j = 0; j < ret[i].size(); j++)
            cout <<"  " << ret[i][j];
        cout << endl;
    }
    std::cout << "Hello, World!\n";
    return 0;
}
