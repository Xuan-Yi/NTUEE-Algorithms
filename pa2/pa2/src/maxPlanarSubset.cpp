#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MPSC.h"
#include "tm_usage.h"

using namespace std;

int main(int argc, char **argv)
{
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    string fin_path = argv[1];
    string fout_path = argv[2];

    // === Run Algorithm ===
    tmusg.periodStart();

    MPSC mpsc(fin_path.data());

    int maxChordNum = mpsc.getMaxChordNum();
    vector<chord> maxChords;

    cout << maxChordNum << endl;
    cout.flush();
    maxChords = mpsc.getVaryChords();

    // show M, Cases
    // mpsc.showM();
    // mpsc.showCases();

    tmusg.getPeriodUsage(stat);
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    // === write to file ===
    ofstream fout(fout_path.data());

    fout << maxChordNum << "\n";
    for (int n = 0; n < maxChordNum; n++)
        fout << maxChords[n].i << " " << maxChords[n].j << "\n";
    fout.close();

    return 0;
}