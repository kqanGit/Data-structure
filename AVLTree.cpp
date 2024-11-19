#include <iostream>
#include <cmath>
using namespace std;

struct Node
{
    int key;
    Node *p_left;
    Node *p_right;
    int height;
};

Node *createNode(int data)
{
    return new Node{data, nullptr, nullptr, 1};
}

int height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int balancedFactor(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->p_left) - height(node->p_right);
}

void inOrderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    inOrderTraversal(root->p_left);
    cout << root->key << ' ';
    inOrderTraversal(root->p_right);
}

void rotateRight(Node *&A)
{
    // rotate tree
    Node *B = A->p_left;
    A->p_left = B->p_right;
    B->p_right = A;

    // update height of A first and the B
    A->height = 1 + max(height(A->p_left), height(A->p_right));
    B->height = 1 + max(height(B->p_left), height(B->p_right));
    A = B;
}

void rotateLeft(Node *&A)
{
    // same as rotateRight
    Node *B = A->p_right;
    A->p_right = B->p_left;
    B->p_left = A;

    A->height = 1 + max(height(A->p_left), height(A->p_right));
    B->height = 1 + max(height(B->p_left), height(B->p_right));
    A = B;
}

void insert(Node *&root, int data)
{
    if (root == nullptr)
    {
        root = createNode(data);
        return;
    }

    if (root->key > data)
    {
        insert(root->p_left, data);
    }
    else if (root->key < data)
    {
        insert(root->p_right, data);
    }
    else
    {
        return;
    }

    root->height = 1 + max(height(root->p_left), height(root->p_right));
    int balance = balancedFactor(root);

    // left left
    if (balance > 1 && root->p_left->key > data)
    {
        rotateRight(root);
        return;
    }

    // left right
    if (balance > 1 && root->p_left->key < data)
    {
        rotateLeft(root->p_left);
        rotateRight(root);
    }

    // right right
    if (balance < -1 && root->p_right->key < data)
    {
        rotateLeft(root);
        return;
    }

    // right left
    if (balance < -1 && root->p_right->key > data)
    {
        rotateRight(root->p_right);
        rotateLeft(root);
    }

    // do not thing if balace = {-1, 0, 1}
}

void remove(Node *&root, int data)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->key > data)
    {
        remove(root->p_left, data);
    }
    else if (root->key < data)
    {
        remove(root->p_right, data);
    }
    else
    {
        if (root->p_left == nullptr || root->p_right == nullptr)
        {
            Node *temp = nullptr;
            if (root->p_left == nullptr)
            {
                temp = root->p_right;
            }
            else
            {
                temp = root->p_left;
            }

            delete root;
            root = temp;
        }
        else
        {
            Node *successor = root->p_right;
            while (successor->p_left != nullptr)
            {
                successor = successor->p_left;
            }
            root->key = successor->key;
            remove(root->p_right, root->key);
        }
    }

    // if node need to be delete is leaf
    if (root == nullptr)
    {
        return;
    }
    root->height = 1 + max(height(root->p_left), height(root->p_right));
    int balance = balancedFactor(root);

    // left left
    if (balance > 1 && balancedFactor(root->p_left) == 1)
    {
        rotateRight(root);
        return;
    }

    // left right
    if (balance > 1 && balancedFactor(root->p_left) == -1)
    {
        rotateLeft(root->p_left);
        rotateRight(root);
    }

    // right right
    if (balance < -1 && balancedFactor(root->p_right) == -1)
    {
        rotateLeft(root);
        return;
    }

    // right left
    if (balance < -1 && balancedFactor(root->p_right) == 1)
    {
        rotateRight(root->p_right);
        rotateLeft(root);
    }
}

int main()
{
    Node *root = nullptr;
    insert(root, 10);
    insert(root, 5);
    insert(root, 2);
    insert(root, 11);
    insert(root, 4);
    inOrderTraversal(root);
    cout << endl;
    remove(root, 2);
    inOrderTraversal(root);
}