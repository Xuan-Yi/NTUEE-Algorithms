#ifndef SORT_TOOL_H
#define SORT_TOOL_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <tuple>

using namespace std;

vector<tuple<int, int, int>> CountingSort(vector<tuple<int, int, int>> &);

// Counting Sort
vector<tuple<int, int, int>> CountingSort(vector<tuple<int, int, int>> &A)
{
    vector<tuple<int, int, int>> B(A.size());
    unsigned C[201] = {0}; // -100~100
    for (int j = 0; j < A.size(); j++)
        C[get<2>(A[j]) + 100] += 1;
    for (int i = 1; i < 201; i++)
        C[i] += C[i - 1];
    for (int j = A.size() - 1; j >= 0; j--)
    {
        get<0>(B[C[get<2>(A[j]) + 100]]) = get<0>(A[j]);
        get<1>(B[C[get<2>(A[j]) + 100]]) = get<1>(A[j]);
        get<2>(B[C[get<2>(A[j]) + 100]]) = get<2>(A[j]);
        C[get<2>(A[j]) + 100] -= 1;
        // cout << C[get<2>(A[j]) + 100] << " ";
    }

    return B;
}

void QuickSort(vector<tuple<int, int, int>> &);
void QuickSortSubVector(vector<tuple<int, int, int>> &, int, int);
int Partition(vector<tuple<int, int, int>> &, int, int);

// QuickSort
void QuickSort(vector<tuple<int, int, int>> &data)
{
    QuickSortSubVector(data, 0, data.size() - 1);
}

void QuickSortSubVector(vector<tuple<int, int, int>> &data, int low, int high)
{
    if (low < high)
    {
        int mid = Partition(data, low, high);
        QuickSortSubVector(data, low, mid - 1);
        QuickSortSubVector(data, mid + 1, high);
    }
}

int Partition(vector<tuple<int, int, int>> &data, int low, int high)
{
    // srand(time(NULL));
    int pivot_idx = rand() % (high - low + 1) + low;
    swap(data[pivot_idx], data[high]); // randomized quick sort

    int pivot = get<2>(data[high]);
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (get<2>(data[j]) < pivot)
        {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

#endif