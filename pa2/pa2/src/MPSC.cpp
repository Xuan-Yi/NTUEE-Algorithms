#include "MPSC.h"

MPSC::MPSC(char *filename)
{
    // load input file data
    vector<string> lines;
    string line; // temporary data container
    ifstream fin(filename);

    if (!fin.is_open())
    {
        cout << "Failed to open " << filename << "\nProgram aborted.\n";
        exit(0);
    }
    else
    {
        lines.clear();
        while (getline(fin, line))
            lines.push_back(line);
        fin.close();

        // load to array or variable
        n = stoi(lines[0]) / 2;       // get n
        chord_num = lines.size() - 2; // get number of chords

        chords = new chord[2 * n];     // allocate chords array
        varychords = new chord[2 * n]; // allocate chords array

        for (int k = 0; k < 2 * n; k++)
        {
            chord null_chord; // indicate not chord
            null_chord.i = -1;
            null_chord.j = -1;
            chords[k] = null_chord;
            varychords[k] = null_chord;
        }

        for (int i = 0; i < chord_num; i++)
        {
            chord c0 = split_line(lines[i + 1]);
            chord c1 = make_twin(c0);

            chords[c0.i] = c0;
            chords[c1.i] = c1;
        }

        // allocate M, Cases
        M = new int *[2 * n - 1];      // i: 0~2*n-2, j: 0~2*n-1
        Cases = new char *[2 * n - 1]; // i: 0~2*n-2, j: 0~2*n-1

        for (int i = 0; i < 2 * n - 1; i++)
        {
            M[i] = nullptr;     // initial length = 1, j: i~2*n-1 (max. = 2n-i)
            Cases[i] = nullptr; // initial length = 1, j: i~2*n-1 (max. = 2n-i)
        }
    }
}

MPSC::~MPSC()
{
    // deallocate chords
    delete[] chords;
    delete[] varychords;

    // deallocate M 2D array
    for (int i = 0; i < 2 * n - 1; i++)
    {
        if (M[i] != nullptr)
            delete[] M[i];
        if (Cases[i] != nullptr)
            delete[] Cases[i];
    }
    delete[] M;
    delete[] Cases;
}

chord MPSC::split_line(const string &line)
{
    vector<string> result;
    stringstream ss(line);
    string item;
    chord c;

    while (getline(ss, item, ' ')) // delimiter = ' '
        result.push_back(item);

    c.i = stoi(result[0]);
    c.j = stoi(result[1]);

    return c;
}

chord MPSC::make_twin(chord &crd)
{
    chord crd_twin;

    crd_twin.i = crd.j;
    crd_twin.j = crd.i;

    return crd_twin;
}

void MPSC::wrt2M(int i, int j, int val)
{
    // map_i = i
    // map_j = j-i

    if (M[i] == nullptr)
    {
        // allocate array M[i]
        M[i] = new int[2 * n - i]; // j: i~2n-1

        M[i][0] = 0; // i=j
        for (int l = 1; l < 2 * n - i; l++)
            M[i][l] = -1;
    }

    M[i][j - i] = val;
}

int MPSC::rd4M(int i, int j)
{
    if (M[i] == nullptr)
    {
        if (i == j)
            return 0;
        else
            return -1;
    }
    else
        return M[i][j - i];
}

void MPSC::wrt2Cases(int i, int j, char _case)
{
    // map_i = i
    // map_j = j-i

    if (Cases[i] == nullptr)
    {
        // allocate array Cases[i]
        Cases[i] = new char[2 * n - i];

        for (int l = 0; l < 2 * n - i; l++)
            Cases[i][l] = '0';
    }
    Cases[i][j - i] = _case;
}

char MPSC::rd4Cases(int i, int j)
{
    if (Cases[i] == nullptr)
        return '0';
    else
        return Cases[i][j - i];
}

void MPSC::showM()
{
    cout << "\n=== M START ===\n";
    for (int i = 0; i < 2 * n - 1; i++)
    {
        for (int j = 0; j < i; j++)
            cout << setw(5) << '*' << "\t";

        if (M[i] != nullptr)
        {
            for (int j = i; j < 2 * n; j++)
                cout << setw(5) << rd4M(i, j) << "\t";
        }
        else
        {
            for (int j = i; j < 2 * n; j++)
                cout << setw(5) << -1 << "\t";
        }
        cout << "\n";
    }
    cout << "=== M FINISH ===\n\n";
}

void MPSC::showCases()
{
    cout << "\n=== Cases START ===\n";
    for (int i = 0; i < 2 * n - 1; i++)
    {
        for (int j = 0; j < i; j++)
            cout << setw(5) << '*' << "\t";

        if (Cases[i] != nullptr)
        {
            for (int j = i; j < 2 * n; j++)
                cout << setw(5) << rd4Cases(i, j) << "\t";
        }
        else
        {
            for (int j = i; j < 2 * n; j++)
                cout << setw(5) << '0' << "\t";
        }
        cout << "\n";
    }
    cout << "=== Cases FINISH ===\n\n";
}

int MPSC::getMaxChordNum()
{
    return MIS(0, 2 * n - 1);
}

int MPSC::MIS(int i, int j)
{

    if (rd4M(i, j) != -1) // existed in M
        return rd4M(i, j);

    int k = chords[j].j; // j = chords[j].i

    if (k != -1) // kj is chord
    {
        if ((k < i || k > j))
        {
            // M[i][j] = M[i][j - 1];
            int to_write = rd4M(i, j - 1);

            if (to_write == -1)
            {
                to_write = MIS(i, j - 1);
                wrt2M(i, j - 1, to_write);
            }

            wrt2M(i, j, to_write);
            wrt2Cases(i, j, '1');
        }
        else if (k == i)
        {
            // M[i][j] = M[i + 1][j - 1] + 1;
            int to_write = rd4M(i + 1, j - 1);

            if (to_write == -1)
            {
                to_write = MIS(i + 1, j - 1);
                wrt2M(i + 1, j - 1, to_write);
            }
            to_write += 1;

            wrt2M(i, j, to_write);
            wrt2Cases(i, j, '3');
        }
        else
        {
            // M[i][j] = max(M[i][j - 1], M[i][k - 1] + 1 + M[k + 1][j - 1]);
            int to_write1 = rd4M(i, j - 1);
            int to_write2;
            int to_write2_1 = rd4M(i, k - 1);
            int to_write2_2 = rd4M(k + 1, j - 1);

            if (to_write1 == -1)
            {
                to_write1 = MIS(i, j - 1);
                wrt2M(i, j - 1, to_write1);
            }
            if (to_write2_1 == -1)
            {
                to_write2_1 = MIS(i, k - 1);
                wrt2M(i, k - 1, to_write2_1);
            }
            if (to_write2_2 == -1)
            {
                to_write2_2 = MIS(k + 1, j - 1);
                wrt2M(k + 1, j - 1, to_write2_2);
            }
            to_write2 = to_write2_1 + 1 + to_write2_2;

            if (to_write1 > to_write2) // to_write1 is max.
            {
                wrt2M(i, j, to_write1);
                wrt2Cases(i, j, '1');
            }
            else // to_write2 is max.
            {
                wrt2M(i, j, to_write2);
                wrt2Cases(i, j, '2');
            }
        }
    }
    else // kj is not chord
    {
        int to_write = MIS(i, j - 1);

        wrt2M(i, j, to_write);
        wrt2Cases(i, j, '1');
    }

    return rd4M(i, j);
}

void MPSC::traceBack(int i, int j)
{
    int k = chords[j].j;

    switch (rd4Cases(i, j))
    {
    case '1':
        traceBack(i, j - 1);
        break;
    case '2':
        traceBack(i, k - 1);
        traceBack(k + 1, j - 1);

        varychords[j].i = j;
        varychords[j].j = k;

        varychords[k].i = k;
        varychords[k].j = j;

        break;
    case '3':
        traceBack(i + 1, j - 1);

        varychords[j].i = j;
        varychords[j].j = i;

        varychords[i].i = i;
        varychords[i].j = j;

        break;
    default:
        if (i != j) // If i==j, it's base case, no chord to append, just skip
            cout << "traceback (" << i << ", " << j << ") = " << rd4Cases(i, j) << " error \n";
        break;
    }
}

vector<chord> MPSC::getVaryChords()
{
    vector<chord> result;

    traceBack(0, 2 * n - 1);
    // sort and filter
    for (int i = 0; i < 2 * n; i++)
    {
        if (varychords[i].i < varychords[i].j)
        {
            result.push_back(varychords[i]);
        }
    }

    return result;
};