/**

    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value is 5 but its right child's value is 4.         
             
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode * left;
 *     TreeNode * right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
class Solution {
public:
    bool isValidBST(TreeNode * root) {
        if (!root) return true;
        return isBSTUtil(root, nullptr, nullptr);
    }
private:
    bool isBSTUtil(TreeNode * root, int * upperL, int * lowerL) {
        if (!root) return true;       
        if (upperL && root->val >= *upperL) return false;
        if (lowerL && root->val <= *lowerL) return false;        
        if (!isBSTUtil(root->left, &root->val, lowerL)) return false;
        return isBSTUtil(root->right, upperL, &root->val);
    }
};
