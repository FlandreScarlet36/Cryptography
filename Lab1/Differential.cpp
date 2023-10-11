#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

int S[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
int Count[16][16] = {};//计数器

void DecimalToBinary(int decimal, int* binary, int num);

int main()
{
	int S1[16] = {};//S盒的逆
	for (int i = 0; i < 16; i++)
	{
		S1[S[i]] = i;
	}

	ifstream input(".\\data\\xor_result.txt");

	int L1[4] = {};
	int L2[4] = {};
	int v1[16] = {};
	int v2[16] = {};
	int u1[16] = {};
	int u2[16] = {};
	int u3[16] = {};

	int n = 0;//样本四元组对个数
	cout << "请输入需要分析的四元组对个数：" << endl;
	cin >> n;

	auto start = high_resolution_clock::now(); //开始时间

	for (int i = 0; i < n; i++)
	{
		string X1, X2, Y1, Y2;
		input >> X1 >> Y1 >> X2 >> Y2;
		//cout << X1 << endl << Y1 << endl << X2 << endl << Y2 << endl;
		int x1[16] = {}, x2[16] = {}, y1[16] = {}, y2[16] = {};
		int len = X1.length();
		for (int i = 0; i < len; i++)
		{
			x1[i] = X1[i] - '0';
			x2[i] = X2[i] - '0';
			y1[i] = Y1[i] - '0';
			y2[i] = Y2[i] - '0';
		}
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				DecimalToBinary(j, L1, 3);
				DecimalToBinary(k, L2, 3);

				v1[4] = L1[0] ^ y1[4];
				v1[5] = L1[1] ^ y1[5];
				v1[6] = L1[2] ^ y1[6];
				v1[7] = L1[3] ^ y1[7];
				v1[12] = L2[0] ^ y1[12];
				v1[13] = L2[1] ^ y1[13];
				v1[14] = L2[2] ^ y1[14];
				v1[15] = L2[3] ^ y1[15];

				int temp1 = v1[4] * pow(2, 3) + v1[5] * pow(2, 2) + v1[6] * pow(2, 1) + v1[7] * pow(2, 0);
				int temp2 = S1[temp1];//S盒的逆运算
				DecimalToBinary(temp2, u1, 7);

				temp1 = v1[12] * pow(2, 3) + v1[13] * pow(2, 2) + v1[14] * pow(2, 1) + v1[15] * pow(2, 0);
				temp2 = S1[temp1];//S盒的逆运算
				DecimalToBinary(temp2, u1, 15);

				v2[4] = L1[0] ^ y2[4];
				v2[5] = L1[1] ^ y2[5];
				v2[6] = L1[2] ^ y2[6];
				v2[7] = L1[3] ^ y2[7];
				v2[12] = L2[0] ^ y2[12];
				v2[13] = L2[1] ^ y2[13];
				v2[14] = L2[2] ^ y2[14];
				v2[15] = L2[3] ^ y2[15];

				temp1 = v2[4] * pow(2, 3) + v2[5] * pow(2, 2) + v2[6] * pow(2, 1) + v2[7] * pow(2, 0);
				temp2 = S1[temp1];//S盒的逆运算
				DecimalToBinary(temp2, u2, 7);

				temp1 = v2[12] * pow(2, 3) + v2[13] * pow(2, 2) + v2[14] * pow(2, 1) + v2[15] * pow(2, 0);
				temp2 = S1[temp1];//S盒的逆运算
				DecimalToBinary(temp2, u2, 15);

				u3[4] = u1[4] ^ u2[4];
				u3[5] = u1[5] ^ u2[5];
				u3[6] = u1[6] ^ u2[6];
				u3[7] = u1[7] ^ u2[7];
				u3[12] = u1[12] ^ u2[12];
				u3[13] = u1[13] ^ u2[13];
				u3[14] = u1[14] ^ u2[14];
				u3[15] = u1[15] ^ u2[15];
				if (u3[4] == 0 &&
					u3[5] == 1 &&
					u3[6] == 1 &&
					u3[7] == 0 &&
					u3[12] == 0 &&
					u3[13] == 1 &&
					u3[14] == 1 &&
					u3[15] == 0)
				{
					Count[j][k]++;
				}
			}
		}

	}
	auto stop = high_resolution_clock::now(); //结束时间
	auto duration = duration_cast<microseconds>(stop - start); //执行时间
	input.close();

	int max = -1;
	int LL1 = 0, LL2 = 0;//记录最大的Count[i][j]对应的L1和L2
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (Count[i][j] > max)
			{
				max = Count[i][j];
				LL1 = i;
				LL2 = j;
			}
		}
	}
	cout << "maxkey:" << endl;
	DecimalToBinary(LL1, L1, 3);
	for (int i = 0; i < 4; i++)
	{
		cout << L1[i];
	}
	cout << " ";
	DecimalToBinary(LL2, L2, 3);
	for (int i = 0; i < 4; i++)
	{
		cout << L2[i];
	}

	cout << endl << "time：" << endl << duration.count() << " 微秒" << endl;

	system("pause");
	return 0;
}

void DecimalToBinary(int decimal, int* binary, int num)
{
	int i = num - 3;//最低索引位
	while (decimal > 0)
	{
		binary[num] = decimal % 2;
		decimal /= 2;
		num--;
	}
	while (num >= i)//空位补0
	{
		binary[num] = 0;
		num--;
	}
}