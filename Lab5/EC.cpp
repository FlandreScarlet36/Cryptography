#include <iostream>

using namespace std;

typedef long long ll;

class Point
{
public:
    ll x, y;
    bool isINF; //是否是无穷远点
    Point(ll x = -1, ll y = -1, bool isINF = false);
    friend ostream& operator<< (ostream& out, const Point& p);
    bool operator ==(const Point& p);
    void Output(ostream& out) const;
};

class Elliptic_Curve
{
private:
    ll p;
    ll a, b;
public:
    Elliptic_Curve(ll p, ll a, ll b);
    bool Is_Inverse(const Point& p1, const Point& p2); //判断两个点是否互逆
    Point Add(const Point& p1, const Point& p2); //进行点加运算
    Point Add_K_Times(Point p, ll k); //对点p进行k倍加

};

ll Get_Inverse(ll a, ll m) //在 (a, m) = 1 的条件下，求a模m的乘法逆元
{
    a = (a + m) % m;
    ll s0 = 1, s1 = 0;
    ll r0 = a, r1 = m;
    while (1)
    {
        ll q = r0 / r1;
        ll tmp = r1;
        r1 = r0 % r1;
        r0 = tmp;
        if (r1 == 0)
        {
            break;
        }
        tmp = s1;
        s1 = s0 - s1 * q;
        s0 = tmp;
    }
    return (s1 + m) % m;
}

Point::Point(ll x, ll y, bool isINF)
{
    this->x = x;
    this->y = y;
    this->isINF = isINF;
}

ostream& operator<< (ostream& out, const Point& p)
{
    p.Output(out);
    return out;
}

bool Point::operator ==(const Point& p)
{
    return x == p.x && y == p.y;
}

void Point::Output(ostream& out) const
{
    if (isINF) cout << "-1 -1";
    else cout << x << ' ' << y;
}

Elliptic_Curve::Elliptic_Curve(ll p, ll a, ll b) //椭圆曲线构造函数
{
    this->p = p;
    this->a = a;
    this->b = b;
}

Point Elliptic_Curve::Add(const Point& p1, const Point& p2)
{
    if (p1.isINF)
    {
        return p2;
    }
    else if (p2.isINF)
    {
        return p1;
    }
    else if (Is_Inverse(p1, p2))
    {
        return { -1, -1, true };
    }
    else
    {
        if ((p1.x - p2.x) % p == 0) //倍加公式
        {
            ll k = ((3 * p1.x * p1.x + a) * Get_Inverse(2 * p1.y, p) % p + p) % p;
            ll x3 = ((k * k - 2 * p1.x) % p + p) % p;
            ll y3 = ((k * (p1.x - x3) - p1.y) % p + p) % p;
            return { x3, y3 };
        }
        else                        //点加公式
        {
            ll k = ((p2.y - p1.y) * Get_Inverse(p2.x - p1.x, p) % p + p) % p;
            ll x3 = ((k * k - p1.x - p2.x) % p + p) % p;
            ll y3 = ((k * (p1.x - x3) - p1.y) % p + p) % p;
            return { x3, y3 };
        }
    }
}

Point Elliptic_Curve::Add_K_Times(Point pt, ll k)
{
    Point ret(0, 0, true);
    while (k)
    {
        if (k & 1)
        {
            ret = Add(ret, pt);
        }
        pt = Add(pt, pt);
        k >>= 1;
    }
    return ret;
}

bool Elliptic_Curve::Is_Inverse(const Point& p1, const Point& p2)
{
    return (p1.x - p2.x) % p == 0 && (p1.y + p2.y) % p == 0;
}

int main()
{
    ll a, b, p;
    cin >> a >> b >> p;
    Elliptic_Curve ec(p, a, b);

    ll x, y, k;
    cin >> x >> y >> k;
    if (x == -1)
        cout << "-1 -1";
    else
        cout << ec.Add_K_Times({ x, y }, k);

    return 0;
}
