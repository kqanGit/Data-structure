#include <iostream>
using namespace std;

struct Heap
{
    int* tree;
    int capacity;
    int size;
};

Heap initializeHeap(int n)
{
    Heap heap;
    heap.tree = new int [n];
    heap.capacity = n;
    heap.size = 0;
    return heap;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{
    int last_non_leaf = (n / 2) - 1;
    for (int i = last_non_leaf; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

void insert(Heap& heap, int key)
{
    if (heap.capacity == heap.size)
    {
        cout << "heap is full";
        return;
    }

    heap.size++;
    heap.tree[heap.size - 1] = key;
    int node = heap.size - 1;
    while(node != 0 && heap.tree[(node - 1) / 2] < heap.tree[node])
    {
        swap(heap.tree[(node - 1) / 2], heap.tree[node]);
        node = (node - 1) / 2;
    }
}

void print(Heap heap)
{
    for (int i = 0; i < heap.size; i++)
    {
        cout << heap.tree[i] << ' ';
    }
}

int top(Heap heap)
{
    return heap.tree[0];
}

int main()
{
    // int a[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    // int n = sizeof(a) / sizeof(a[0]);
    // buildHeap(a, n);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << a[i] << ' ';
    // }

    Heap heap = initializeHeap(10);
    insert(heap, 4);
    insert(heap, 9);
    insert(heap, 1);
    insert(heap, 11);
    insert(heap, 5);
    insert(heap, 12);
    insert(heap, 12);
    insert(heap, 12);
    print(heap);
}


// MAX HEAP IMPLEMENTATION WITH STRUCT