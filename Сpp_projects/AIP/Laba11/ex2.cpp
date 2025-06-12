#include <iostream>
#include <unordered_set>
#include <chrono>
#include <stack>
#include <utility>

using namespace std;
using namespace std::chrono;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value >= root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

void findUniqueAncestorsWithOddDescendantsRecursive(TreeNode* node, unordered_set<int>& result) {
    if (node == nullptr) return;
    
    bool hasOddChild = false;
    if (node->left && node->left->value % 2 != 0) hasOddChild = true;
    if (node->right && node->right->value % 2 != 0) hasOddChild = true;
    
    if (hasOddChild) {
        result.insert(node->value);
    }
    
    findUniqueAncestorsWithOddDescendantsRecursive(node->left, result);
    findUniqueAncestorsWithOddDescendantsRecursive(node->right, result);
}

void findUniqueAncestorsWithOddDescendantsIterative(TreeNode* root, unordered_set<int>& result) {
    if (root == nullptr) return;

    stack<TreeNode*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        TreeNode* currentNode = nodeStack.top();
        nodeStack.pop();

        bool hasOddChild = false;
        if (currentNode->left && currentNode->left->value % 2 != 0) hasOddChild = true;
        if (currentNode->right && currentNode->right->value % 2 != 0) hasOddChild = true;
        
        if (hasOddChild) {
            result.insert(currentNode->value);
        }

        if (currentNode->right) nodeStack.push(currentNode->right);
        if (currentNode->left) nodeStack.push(currentNode->left);
    }
}

void printTree(TreeNode* root) {
    if (root != nullptr) {
        printTree(root->left);
        cout << root->value << " ";
        printTree(root->right);
    }
}

int main() {
    TreeNode* root = nullptr;
    int value;
    
    cout << "Enter integers to build a binary tree (enter -1 to stop):\n";
    while (true) {
        cin >> value;
        if (value == -1) break;
        root = insert(root, value);
    }

    cout << "\nOriginal tree (in-order traversal): ";
    printTree(root);
    cout << endl;

    unordered_set<int> recursiveResult;
    auto start_rec = high_resolution_clock::now();
    auto result_rec = findUniqueAncestorsWithOddDescendantsRecursive(root);
    auto end_rec = high_resolution_clock::now();
    auto duration_rec = duration_cast<nanoseconds>(end_rec - start_rec);

cout << "Time (recursive): " << duration_rec.count() << " ns" << endl;
    cout << "\nUnique ancestors with odd direct descendants (recursive): ";
    for (int val : recursiveResult) {
        cout << val << " ";
    }
    cout << "\nExecution time (recursive): " << duration_rec.count() << " microseconds" << endl;

    unordered_set<int> iterativeResult;
    auto start_iter = high_resolution_clock::now();
    findUniqueAncestorsWithOddDescendantsIterative(root, iterativeResult);
    auto end_iter = high_resolution_clock::now();
    auto duration_iter = duration_cast<microseconds>(end_iter - start_iter);

    cout << "Unique ancestors with odd direct descendants (iterative): ";
    for (int val : iterativeResult) {
        cout << val << " ";
    }
    cout << "\nExecution time (iterative): " << duration_iter.count() << " microseconds" << endl;

    return 0;
}