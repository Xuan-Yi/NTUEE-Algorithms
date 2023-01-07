#ifndef CYCLEBREAKER_H
#define CYCLEBREAKER_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include "sort_tool.h"
#include "disjoint_set.h"

using namespace std;

class CycleBreaker
{
public:
    CycleBreaker(string, string);
    ~CycleBreaker();
    void break_cycle();
    void print_graph();

    friend void QuickSort(vector<tuple<int, int, int>> &);
    friend void QuickSortSubVector(vector<tuple<int, int, int>> &, int, int);
    friend int Partition(vector<tuple<int, int, int>> &, int, int);

private:
    char graph_type = 'f'; // u: undirected, d: directed
    int n = 0;             // number of vertices
    int m = 0;             // number of edges

    string fout_path;
    vector<tuple<int, int, int>> edges;
    // int **graph; // also weight table (from, to)
    // vector<vector<int>> graph;
    int **graph;

    vector<tuple<int, int, int>> break_graph();
    vector<tuple<int, int, int>> break_directed_graph();
    // bool isCycle(vector<vector<int>> &, int); // return tru if cycle exists
    bool isCycle(int **, int); // return tru if cycle exists
    // void dfs(int, int, int[], vector<vector<int>> &, bool &);
    void dfs(int, int, int[], int **, bool &);
};

CycleBreaker::CycleBreaker(string in_filename, string out_filename)
{
    fout_path = out_filename;

    ifstream fin(in_filename.c_str());
    if (!fin.is_open())
    {
        printf("Error opening input file \"%s\".\n", in_filename.c_str());
        exit(EXIT_FAILURE);
    }

    // read file - params
    string line;
    getline(fin, line);
    graph_type = line[0]; // graph type
    getline(fin, line);
    n = stoi(line); // number of vertices
    getline(fin, line);
    m = stoi(line); // number of edges

    // graph.reserve(n);
    // for (int i = 0; i < n; i++)
    //     graph[i].reserve(n);
    if (graph_type == 'd')
    {
        graph = new int *[n];
        for (int i = 0; i < n; i++)
            graph[i] = new int[n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = 101; // unconnected edge with weight 101
    }

    // read file - weight table
    for (int t = 0; t < m; t++)
    {
        getline(fin, line);

        istringstream iss(line);
        int i, j, w;
        if (!(iss >> i >> j >> w))
        {
            if (i != 0) // end of file
                printf("Cannot read line %s\n", line.c_str());
            break;
        }
        tuple<int, int, int> e(i, j, w);
        edges.push_back(e);
        if (graph_type == 'd')
            graph[i][j] = w;
    }
    fin.close();
}

CycleBreaker::~CycleBreaker()
{
    if (graph_type == 'd')
    {
        for (int i = 0; i < n; i++)
            delete[] graph[i];
        delete[] graph;
    }
}

void CycleBreaker::print_graph()
{

    if (graph_type == 'u')
        printf("\nUndirected Graph: \n");
    else if (graph_type == 'd')
        printf("\nDirected Graph \n");
    else
        printf("\nGraph type is not read: %c\n", graph_type);

    printf("n (number of vertices): %i\nm (number of edges): %i\n", n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << graph[i][j] << '\t';
        cout << '\n';
    }
}

void CycleBreaker::break_cycle()
{
    vector<tuple<int, int, int>> rm_edges;

    rm_edges = break_graph();

    int total_weight = 0;
    for (int i = 0; i < rm_edges.size(); i++)
        total_weight += get<2>(rm_edges[i]);

    // write output file
    ofstream fout(fout_path.c_str());
    if (!fout.is_open())
    {
        printf("Error opening input file \"%s\".\n", fout_path.c_str());
        exit(EXIT_FAILURE);
    }
    fout << total_weight << '\n';
    for (int i = 0; i < rm_edges.size(); i++)
        fout << get<0>(rm_edges[i]) << " " << get<1>(rm_edges[i]) << " " << get<2>(rm_edges[i]) << '\n';
    if (rm_edges.size() == 0)
        fout << 0 << '\n';
    fout.close();
}

vector<tuple<int, int, int>> CycleBreaker::break_graph()
{
    vector<tuple<int, int, int>> diff_edges, rm_edges;
    if (graph_type == 'd')
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                graph[i][j] = 101;
            graph[i][i] = 0;
        }
    }

    QuickSort(edges);
    // vector<tuple<int, int, int>> new_edges = CountingSort(edges);
    // cout << "4\n";
    // cout.flush();
    // for (int i = 0; i < new_edges.size(); i++)
    //     cout << get<2>(new_edges[i]) << " ";
    // cout << endl;

    disjoint_set dijs; // store the idx
    dijs.make_set(n);

    for (int e = m - 1; e >= 0; e--)
    {

        int u = get<0>(edges[e]);
        int v = get<1>(edges[e]);
        int w = get<2>(edges[e]);

        if (dijs.find(u) == dijs.find(v)) // connected
            diff_edges.push_back(edges[e]);
        else
        {
            dijs.Union(u, v);
            if (graph_type == 'd')
                graph[u][v] = w;
        }
    }

    if (graph_type == 'd')
    {
        for (int e = 0; e < diff_edges.size(); e++)
        {
            int u = get<0>(diff_edges[e]);
            int v = get<1>(diff_edges[e]);
            int w = get<2>(diff_edges[e]);

            if (w <= 0)
            {
                rm_edges.push_back(diff_edges[e]);
                continue;
            }

            graph[u][v] = w;
            if (isCycle(graph, u))
            {
                graph[u][v] = 101;
                rm_edges.push_back(diff_edges[e]);
            }
        }
    }
    else // undirected graph
        return diff_edges;

    return rm_edges;
}

bool CycleBreaker::isCycle(int **G, int s)
{

    bool isCyc = false;
    int color[n];
    for (int i = 0; i < n; i++)
        color[i] = 0; // 0: white

    // int counter = 0;
    // for (int s = 0; s < n; s++)
    // {
    //     if (color[s] == 2 || isCyc)
    //         continue;
    dfs(s, s, color, G, isCyc);
    //     counter++;
    // }

    return isCyc;
}

void CycleBreaker::dfs(int u, int u_p, int color[], int **G, bool &isCyc)
{
    if (color[u] == 2) // 2: black
        return;
    if (color[u] == 1) // 1:gray
    {
        isCyc = true;
        return;
    }
    color[u] = 1;

    for (int v = 0; v < n; v++)
    {
        if (G[u][v] == 101 || u == v)
            continue;
        dfs(v, u, color, G, isCyc);
    }
    color[u] = 2;
}

#endif