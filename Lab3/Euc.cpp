#include<iostream>
using namespace std;
void exeu(long long a, long long b, long long& t, long long& s, long long& d)
{
    if (!b)
    {
        d = a;
        t = 1;
        s = 0;
        return;//递归出口
    }
    exeu(b, a % b, t, s, d);//递归调用
    long long temp = t;
    t = s;
    s = temp - (a / b) * s;//欧几里得算法公式部分
}
int main()
{
    long long a, p, t, s, d;
    cin >> a >> p;
    long long aa = a, pp = p;
    exeu(aa, pp, t, s, d);
    t = (t % pp + pp) % pp; //防止出现负数
    cout << t;
    return 0;
}
