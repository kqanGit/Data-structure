#include <iostream>
using namespace std;

struct TNode
{
    int key;
    TNode* pLeft;
    TNode* pRight;
};

struct BST
{
    TNode* root;
};

BST* initialize()
{
    return new BST{nullptr};
}

void deinitializeHelper(TNode*& root)
{
    if (root == nullptr)
    {
        return;
    }
    deinitializeHelper(root->pLeft);
    deinitializeHelper(root->pRight);
    delete root;
    root = nullptr;
}

void deinitialize(BST* tree)
{
    deinitializeHelper(tree->root);
}

TNode* newNode(int value)
{
    TNode* node = new TNode;
    if (!node)
    {
        cout << "Memory is full" << endl;
        return nullptr;
    }
    node->key = value;
    node->pRight = nullptr;
    node->pLeft = nullptr;
    return node;
}

void insertHelper(TNode*& root, int value)
{
    if (root == nullptr)
    {
        root = newNode(value);
        return;
    }
    
    if (root->key > value)
    {
        insertHelper(root->pLeft, value);
        return;
    }

    if (root->key < value)
    {
        insertHelper(root->pRight, value);
        return;
    }
}

void insert(BST* tree, int value)
{
    insertHelper(tree->root, value);
}

int successor(TNode* root)
{
    TNode* node = root->pRight;
    while(node->pLeft != nullptr)
    {
        node = node->pLeft;
    }
    return node->key;
}

TNode* removeHelper(TNode* root, int value)
{
    if (root == nullptr)
    {
        return root;
    }
    
    if (root->key > value)
    {
        root->pLeft = removeHelper(root->pLeft, value);
        return root;
    }

    if (root->key < value)
    {
        root->pRight = removeHelper(root->pRight, value);
        return root;
    }

    // if root->key = value

    if (root->pLeft == nullptr || root->pRight == nullptr)
    {
        TNode* tmp = nullptr;
        if (root->pLeft == nullptr)
        {
            tmp = root->pRight;            
        }
        else
        {
            tmp = root->pLeft;
        }
        
        delete root;
        root = nullptr;
        return tmp;
    }
    
    root->key = successor(root);
    root->pRight = removeHelper(root->pRight, root->key);
    return root;
}

void remove(BST* tree, int value)
{
    removeHelper(tree->root, value);
}

void inOrderTraverse(TNode* root)
{
    if (root == nullptr)
    {
        return;
    }
    inOrderTraverse(root->pLeft);
    cout << root->key << ' ';
    inOrderTraverse(root->pRight);
}

void printTree(BST* tree)
{
    if (tree->root == nullptr)
    {
        cout << "Tree is empty" << endl;
    }
    inOrderTraverse(tree->root);
    cout << endl;
}

int main()
{
    BST* tree = initialize();
    insert(tree, 6);
    insert(tree, 3);
    insert(tree, 10);
    insert(tree, 2);
    insert(tree, 4);
    insert(tree, 7);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 40);
    printTree(tree);
    cout << endl;
    remove(tree, 6);
    remove(tree, 3);
    printTree(tree);
    deinitialize(tree);
    printTree(tree);
}