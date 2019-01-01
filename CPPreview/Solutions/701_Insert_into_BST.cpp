//LeetCode 701
//Given the root node of a binary search tree (BST) and a value to be inserted into the tree, 
//insert the value into the BST. Return the root node of the BST after the insertion

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

    TreeNode * insertIntoBST(TreeNode * root, int val) {
        if (val >= root->val) {
            if (root->right) 
                insertIntoBST(root->right, val);
            else
                root->right = new TreeNode{ val };
        }
        else {
            if (root->left) 
                insertIntoBST(root->left, val);
            else
                root->left = new TreeNode{ val };
        }
        return root;
    }
    
