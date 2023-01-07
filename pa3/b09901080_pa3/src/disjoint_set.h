#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <iostream>
using namespace std;

class disjoint_set
{
public:
    disjoint_set(){};

    void make_set(int n)
    {
        num = n;

        rank = new int[n];
        representative = new int[n];

        // make set
        for (int i = 0; i < n; i++)
        {
            representative[i] = i;
            rank[i] = 0;
        }
    }

    int find(int idx)
    {
        if (representative[idx] != idx)
            representative[idx] = find(representative[idx]);
        return representative[idx];
    }

    void Union(int u, int v)
    {
        int s1 = find(u);
        int s2 = find(v);

        if (s1 == s2)
            return;
        if (rank[s1] < rank[s2])
            representative[s1] = s2;
        else if (rank[s1] > rank[s2])
            representative[s2] = s1;
        else // same rank
        {
            representative[s1] = s2;
            rank[s2] += 1;
        }
    }

    bool connected()
    {
        int itr = 0;
        while (itr < num && find(itr) == find(0))
            itr++;
        if (itr == num - 1)
            return true;
        return false;
    }

private:
    int num;
    int *rank;
    int *representative;
};

#endif