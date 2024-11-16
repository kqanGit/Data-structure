#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Node
{
    int key;
    Node *p_left;
    Node *p_right;
};

struct BST
{
    Node *p_root;
};

BST *initialize()
{
    return new BST{nullptr};
}

void deinitializeHelper(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    deinitializeHelper(root->p_left);
    deinitializeHelper(root->p_right);
    delete root;
}

void deinitialize(BST *tree)
{
    deinitializeHelper(tree->p_root);
}

bool isEmpty(BST *tree)
{
    if (tree->p_root == nullptr)
        return true;
    return false;
}

Node *createNode(int data)
{
    Node *node = new Node{data, nullptr};
    return node;
}

void insertNodeHelper(Node *&root, int data)
{
    if (root == nullptr)
    {
        root = createNode(data);
        return;
    }

    if (root->key > data)
    {
        insertNodeHelper(root->p_left, data);
        return;
    }

    insertNodeHelper(root->p_right, data);
}

void insertNode(BST *tree, int data)
{
    insertNodeHelper(tree->p_root, data);
}

void NLR(Node *root)
{
    if (root == nullptr)
        return;
    cout << root->key << ' ';
    NLR(root->p_left);
    NLR(root->p_right);
}

Node* rotateRight(Node* A)
{
    Node* B = A->p_left;
    A->p_left = B->p_right;
    B->p_right = A;
    return B;
}

Node* rotateLeft(Node* A)
{
    Node* B = A->p_right;
    A->p_right = B->p_left;
    B->p_left = A;
    return B;
}

int createBackBone(Node* root)
{
    int count = 0;
    Node* grand = root;
    Node* p = root->p_right;
    while(p != nullptr)
    {
        if (p->p_left != nullptr)
        {
            p = rotateRight(p);
            grand->p_right = p;
        }
        else
        {
            count++;
            grand = p;
            p = p->p_right;
        }
    }
    return count;
}

void compress(Node* root, int times)
{
    Node* grand = root;
    Node* node = root->p_right;
    for (int i = 1; i <= times; i++)
    {
        node = rotateLeft(node);
        grand->p_right = node;
        grand = node;
        node = node->p_right;
    }
}

void createCompleteTree(Node*& root)
{
    Node* dummyNode = createNode(0);    // dummy node technicl
    dummyNode->p_right = root;
    int n = createBackBone(dummyNode);
    int m = pow(2, (int) log2(n + 1)) - 1;
    compress(dummyNode, n - m);
    while(m > 0)
    {
        m = m / 2;
        compress(dummyNode, m);
    }
    
    root = dummyNode->p_right;
}

int main()
{
    BST *tree = initialize();
    insertNode(tree, 2);
    insertNode(tree, 1);
    insertNode(tree, 3);
    NLR(tree->p_root);
    cout << endl;
    createCompleteTree(tree->p_root);
    NLR(tree->p_root);
}