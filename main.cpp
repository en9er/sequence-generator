#include<iostream>
#include<vector>
#include<Seqgen.h>
using namespace std;

using namespace std;

void QuasiOrderedDouble(double* A, int Size, double Min, double Max)
{
    int j = 30;
    double* B = new double[Size + j];
    double min = Min;
    double maxstep = double((Max - Min)) / double(Size);
    double max = min + maxstep;
    double tmp = 0;
    for (int i = 0; i < Size + j; i++)
    {
        B[i] = min + ((double)rand() / (double)RAND_MAX * (max - min));
        min = double(B[i] + maxstep / 100);
        max += maxstep;
        if (int((rand() % 100)) < 10) B[i] = min + ((double)rand() * rand()) / ((double)RAND_MAX * RAND_MAX) * (Max - Min);

        if (i == j)
        {
            for (int ii = j; ii != 0; ii--)
            {
                tmp += B[i - ii];
            }
            A[i - j] = double(tmp / j);
        }

        if (i > j)
        {
            tmp = tmp + B[i] - B[i - j];
            A[i - j] = double(tmp / j);
        }

        if (B[i] > 100)
        {
            int z = 10;
        }
    }
    free(B);
}


int main()
{

    double tmp = 0;
    Seqgen<int> s;
    vector<int> vec;
    s.risingSequence(&vec, 0, 100, 1000);
}

