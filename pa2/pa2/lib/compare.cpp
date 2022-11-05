#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    string f1_path = argv[1];
    string f2_path = argv[2];

    // === load files ===
    vector<string> fdata1, fdata2;
    string line1, line2; // temporary data container
    ifstream fin1(f1_path);
    ifstream fin2(f2_path);

    if (!fin1.is_open() || !fin2.is_open())
    {
        if (!fin1.is_open())
            cout << "Failed to open " << f1_path << "\nProgram aborted.\n";
        if (!fin2.is_open())
            cout << "Failed to open " << f2_path << "\nProgram aborted.\n";

        exit(0);
    }
    else
    {
        fdata1.clear();
        fdata2.clear();
        string line;

        // file1
        while (getline(fin1, line1))
            fdata1.push_back(line1);
        fin1.close();
        // file2
        while (getline(fin2, line2))
            fdata2.push_back(line2);
        fin2.close();
    }

    // === compare data ===
    if (fdata1.size() != fdata2.size())
        cout << "Two files are different.\n";
    else
    {
        bool diff = false; // difference label

        for (int i = 0; i < fdata1.size(); i++)
        {
            if (fdata1[i] != fdata2[i])
                diff = true;
        }

        if (diff)
            cout << "Two files are different.\n";
        else
            cout << "They have same content.\n";
    }

    return 0;
}