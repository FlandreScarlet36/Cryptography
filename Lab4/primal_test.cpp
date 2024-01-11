#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;

long long power(ll base, ll exp, ll mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int jacobi(ll a, ll n) {
    if (a == 0)
        return 0;
    if (a == 1)
        return 1;

    int result = 1;
    if (a < 0) {
        a = -a;
        if (n % 4 == 3)
            result = -result;
    }

    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            ll nMod8 = n % 8;
            if (nMod8 == 3 || nMod8 == 5)
                result = -result;
        }
        swap(a, n);
        if (a % 4 == 3 && n % 4 == 3)
            result = -result;
        a = a % n;
    }

    if (n == 1)
        return result;
    return 0;
}

bool solovayStrassenTest(ll n, int k) {
    if (n <= 1)
        return false;

    if (n == 2 || n == 3)
        return true;

    for (int i = 0; i < k; ++i) {
        ll a = 2 + rand() % (n - 3);
        int jacobiSymbol = jacobi(a, n);
        ll modResult = power(a, (n - 1) / 2, n);

        if (jacobiSymbol == 0 || (modResult != 1 && modResult != n - 1))
            return false;
    }

    return true;
}

int main() {
    ll n;
    cin >> n;

    int k = 100;

    if (solovayStrassenTest(n, k))
        cout << "Yes";
    else
        cout << "No";

    return 0;
}
