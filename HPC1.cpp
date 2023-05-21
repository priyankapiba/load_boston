/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<iostream>
#include<omp.h>
#include<stack>
#include<queue>

using namespace std;

struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x){
      val = x;
      left = NULL;
      right = NULL;
  }
};

void pBFS(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qSize = q.size();
        
        #pragma omp parallel for
        for(int i = 0; i< qSize; i++)
        {
            TreeNode* node;
            
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
                if(node->left) {
                    q.push(node->left);
                }
                if(node->right) {
                    q.push(node->right);
                }
            }
        }
    }
}


void pDFS(TreeNode* root){
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        int sSize = s.size();
        #pragma omp parallel for
        for(int i = 0; i< sSize; i++)
        {
            TreeNode* node;
            
            #pragma omp critical
            {
                node = s.top();
                cout << node->val << " ";
                s.pop();
                if(node->right) {
                    s.push(node->right);
                }
                if(node->left) {
                    s.push(node->left);
                }
            }
        }
        
    }
}


int main(){
    TreeNode* tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3);
    tree->left->left = new TreeNode(4);
    tree->left->right = new TreeNode(5);
    tree->right->left = new TreeNode(6);
    tree->right->left = new TreeNode(7);
    
    cout << "Parallel BFS:";
    pBFS(tree);
    cout << "\n";
    cout << "Parallel DFS:";
    pDFS(tree);
}