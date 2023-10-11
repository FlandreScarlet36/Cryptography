#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int S[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
int P[16] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
int key[32] = { 0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1 };

void Substitution(int* a, int* b, int* s);
void Permutation(int* a, int* b, int* p);
void SPN(int* x, int* y, int* s, int* p, int* key);

int main()
{
    ifstream input(".\\data\\pairs.txt");
    ofstream output(".\\data\\output.txt");

    int x1[16] = {}, x2[16] = {};
    int y1[16] = {}, y2[16] = {};

    for (int i = 0; i < 16000; i++)
    {
        string X1, X2;
        input >> X1 >> X2;
        int len = X1.length();
        for (int i = 0; i < len; i++)
        {
            x1[i] = X1[i] - '0';
            x2[i] = X2[i] - '0';
        }

        SPN(x1, y1, S, P, key);
        SPN(x2, y2, S, P, key);

        //y_{<1>}={y_{<1>}}^* && y_{<3>}={y_{<3>}}^*
        if (y1[0] == y2[0] && y1[1] == y2[1] && y1[2] == y2[2] && y1[3] == y2[3] && y1[8] == y2[8] && y1[9] == y2[9] && y1[10] == y2[10] && y1[11] == y2[11])
        {
            for (int j = 0; j < 16; j++) output << x1[j];
            output << endl;
            for (int j = 0; j < 16; j++) output << y1[j];
            output << endl;
            for (int j = 0; j < 16; j++) output << x2[j];
            output << endl;
            for (int j = 0; j < 16; j++) output << y2[j];
            output << endl;
        }
    }
    input.close();
    output.close();
    system("pause");
    return 0;
}

void Substitution(int* a, int* b, int* s)
{
    int T[4] = {};
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        T[i] = a[i * 4] * pow(2, 3) + a[i * 4 + 1] * pow(2, 2) + a[i * 4 + 2] * pow(2, 1) + a[i * 4 + 3];
        int temp = s[T[i]];

        int j = (i * 4) + 3;
        while (temp > 0)
        {
            b[j] = temp % 2;
            temp = temp / 2;
            j--;
        }
        while (j >= (i * 4))
        {
            b[j] = 0;
            j--;
        }
    }
}

void Permutation(int* a, int* b, int* p)
{
    for (int i = 0; i < 16; i++)
    {
        b[p[i]] = a[i];
    }
}

void SPN(int* x, int* y, int* s, int* p, int* key)
{
    int w[16], u[16], v[16], k[16];
    for (int i = 0; i < 16; i++)
    {
        w[i] = x[i];
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            k[j] = key[4 * i + j];
        }

        for (int j = 0; j < 16; j++)
        {
            u[j] = w[j] ^ k[j];
        }

        Substitution(u, v, s);
        Permutation(v, w, p);
    }

    for (int j = 0; j < 16; j++)
    {
        k[j] = key[4 * 3 + j];
    }

    for (int j = 0; j < 16; j++)
    {
        u[j] = w[j] ^ k[j];
    }

    Substitution(u, v, s);

    for (int j = 0; j < 16; j++)
    {
        k[j] = key[4 * 4 + j];
    }

    for (int j = 0; j < 16; j++)
    {
        y[j] = v[j] ^ k[j];
    }
}