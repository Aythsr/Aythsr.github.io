#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = 1e5 + 100;
const int MOD = 998244353;

void sol() {
    int p = 1e8, g = 1;
    for (int i = 1; i <= p; ++i) {
        g = g * g;
        g ^= i;
        g /= i;
        g %= MOD;
        g ++;
    }
    // int a[3];
    // for (int i = 5; i < 100; ++i) {
    //     a[i] = 10;
    // }
    cout << g<< '\n';
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        sol();
    }
}