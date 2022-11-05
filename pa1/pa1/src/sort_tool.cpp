// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int j = 1; j < data.size(); j++)
    {
        int key = data[j];
        int i = j - 1;

        while ((i >= 0) && ((data[i] > key)))
        {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data)
{
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low < high)
    {
        int mid = Partition(data, low, high);
        QuickSortSubVector(data, low, mid - 1);
        QuickSortSubVector(data, mid + 1, high);
    }
}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
    // srand(1000000); // fixed random seed = 1000000

    int pivot_idx = rand() % (high - low + 1) + low;
    swap(data[pivot_idx], data[high]); // randomized quick sort

    int pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (data[j] <= pivot)
        {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low < high)
    {
        int q = (low + high) / 2;
        MergeSortSubVector(data, low, q);
        MergeSortSubVector(data, q + 1, high);
        Merge(data, low, q, q + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int len1 = middle1 - low + 1;  // length of vector L
    int len2 = high - middle2 + 1; // length of vector R
    vector<int> L;
    vector<int> R;
    L.reserve(len1 + 1);
    R.reserve(len2 + 1);
    for (int i = 0; i < len1; i++)
        L.push_back(data[low + i]);
    for (int i = 0; i < len2; i++)
        R.push_back(data[middle2 + i]);
    L.push_back(2147483647); // max integer
    R.push_back(2147483647); // max integer

    int i = 0; // iterator of L
    int j = 0; // iterator of R
    for (int k = low; k <= high; k++)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else // L[i] > R[j]
        {
            data[k] = R[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

// Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = root * 2 + 1;
    int r = root * 2 + 2;
    int max_idx;

    if ((l < heapSize) && (data[l] > data[root]))
        max_idx = l;
    else
        max_idx = root;
    if ((r < heapSize) && (data[r] > data[max_idx]))
        max_idx = r;

    if (max_idx != root)
    {
        swap(data[root], data[max_idx]);
        MaxHeapify(data, max_idx);
    }
}

// Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = data.size() / 2 - 1; i >= 0; i--)
        MaxHeapify(data, i);
}
