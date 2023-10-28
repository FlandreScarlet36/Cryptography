#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int S[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
int P[16] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };

int x[16], y[16], key[32];  // 定义存储数据和密钥的数组

// 将每4位二进制数字替换为S-盒中的值
void Substitution(int* a, int* b, int* s)
{
    int T[4] = {};
    int k = 0;
    for (int i = 0; i < 4; i++){
        // 将每4位二进制数字转换为整数
        T[i] = a[i * 4] * pow(2, 3) + a[i * 4 + 1] * pow(2, 2) + a[i * 4 + 2] * pow(2, 1) + a[i * 4 + 3];
        int temp = s[T[i]];  // 从S-盒中获取替换值

        int j = (i * 4) + 3;
        while (temp > 0){
            b[j] = temp % 2;  // 将替换值转换为二进制
            temp = temp / 2;
            j--;
        }
        while (j >= (i * 4)){
            b[j] = 0;  // 补充前导零
            j--;
        }
    }
}

// 根据P-盒置换顺序重新排列数据
void Permutation(int* a, int* b, int* p){
    for (int i = 0; i < 16; i++)
        b[p[i]] = a[i];
}

// SPN算法
void SPN(int* x, int* y, int* s, int* p, int* key){
    int w[16], u[16], v[16], k[16];
    for (int i = 0; i < 16; i++)
        w[i] = x[i];

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 16; j++)
            k[j] = key[4 * i + j];

        for (int j = 0; j < 16; j++)
            u[j] = w[j] ^ k[j];  // 通过密钥异或数据
        Substitution(u, v, s);  // 使用S-盒替换
        Permutation(v, w, p);  // 使用P-盒置换
    }

    for (int j = 0; j < 16; j++)
        k[j] = key[4 * 3 + j];

    for (int j = 0; j < 16; j++)
        u[j] = w[j] ^ k[j];

    Substitution(u, v, s);

    for (int j = 0; j < 16; j++)
        k[j] = key[4 * 4 + j];

    for (int j = 0; j < 16; j++)
        y[j] = v[j] ^ k[j];  // 通过密钥异或结果
}

int main()
{
    string X, Key;
    cin >> X >> Key;  // 从用户输入读取数据和密钥

    int len = X.length();
    for (int i = 0; i < len; i++)
        x[i] = X[i] - '0';  // 将输入数据从字符转换为整数

    len = Key.length();
    for (int i = 0; i < len; i++)
        key[i] = Key[i] - '0';  // 将密钥从字符转换为整数

    SPN(x, y, S, P, key);  // 调用SPN算法进行加密

    for (int i = 0; i < 16; i++)
        cout << y[i];  // 输出加密后的结果
    system("pause");  // 等待用户按键后关闭程序
    return 0;
}
