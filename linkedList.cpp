#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node* next;
};

Node* createNode(int data)
{
    return new Node {data, nullptr};
}

void pushBack(Node*& head, int data)
{
    Node* node = createNode(data);
    if (head == nullptr)
    {
        head = node;
        return;
    }
    Node* tail = head;
    while(tail->next != nullptr)
    {
        tail = tail->next;
    }
    tail->next = node;
}

Node* findMid(Node* head)
{
    Node* fast = head;
    Node* slow = head;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* merge(Node* A, Node* B)
{
    Node* head = nullptr;
    Node* node = nullptr;
    while(A && B)
    {
        Node* temp = nullptr;
        if (A->key < B->key)
        {
            temp = A;
            A = A->next;
        }
        else
        {
            temp = B;
            B = B->next;
        }

        if (head == nullptr)
        {
            head = temp;
            node = temp;
        }
        else
        {
            node->next = temp;
            node = temp;
        }
    }

    if (A != nullptr)
    {
        node->next = A;
    }
    
    if (B != nullptr)
    {
        node->next = B;
    }
    
    return head;
}

void mergeSort(Node*& head)
{
    if (!head || !head->next)
    {
        return;
    }

    Node* mid = findMid(head);
    Node* prev_mid = head;
    while(prev_mid->next != mid)
    {
        prev_mid = prev_mid->next;
    }
    prev_mid->next = nullptr;
    mergeSort(head);
    mergeSort(mid);
    head = merge(head, mid);
}

void printList(Node* head)
{
    for (Node* node = head; node != nullptr; node = node->next)
    {
        cout << node->key << ' ';
    }
    cout << endl;
}

int main()
{
    Node* head = nullptr;
    pushBack(head, 1);
    pushBack(head, -1);
    pushBack(head, 4);
    pushBack(head, 3);
    printList(head);
    mergeSort(head);
    printList(head);
}