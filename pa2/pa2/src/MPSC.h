#ifndef MPSC_H
#define MPSC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

typedef struct
{
    int i; // first pivot
    int j; // second pivot
} chord;

const int MAX_CHORD_NUM = 90000; // max n

class MPSC
{
private:
    int n;         // 1 <= n <= 90000
    int chord_num; // number of chords
    chord *chords; // array of chords use first pivot as index
    int **M;       // M array of MPSC problem
    char **Cases;  // Memorize cases in iterations to trace back for chords (1,2,3)
    chord *varychords;

    chord split_line(const string &line);
    chord make_twin(chord &crd); // create a copy with inverse index order

    void wrt2M(int i, int j, int val); // write to M in self- defined way
    int rd4M(int i, int j);            // read from M in self- defined way

    void wrt2Cases(int i, int j, char _case); // write to Cases in self- defined way
    char rd4Cases(int i, int j);              // read from Cases in self- defined way

    int MIS(int i, int j); // return max. num. of chords in [i, j]
    void traceBack(int i, int j);

public:
    MPSC(char *filename);
    ~MPSC();

    void showM();
    void showCases();

    int getMaxChordNum();
    vector<chord> getVaryChords();
};

#endif