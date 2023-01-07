#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "cyclebreaker.h"

using namespace std;

int main(int argc, char *argv[])
{
    string in_filename = argv[1];
    string out_filename = argv[2];

    CycleBreaker cb(in_filename, out_filename);
    // printf("input filename: %s\noutput filename: %s\n", argv[1], argv[2]);
    // cb.print_graph();
    cb.break_cycle();

    return EXIT_SUCCESS;
}