#include <bits/stdc++.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;
typedef long long ll;
mt19937_64 gen(time(0));
ll L, R;
ll read_num(char *s) {
	int len = strlen(s);
	ll res = 0;
    ll flag = 1;
	for (int i = 0; i < len; ++i) {
        if (s[i] == '-') {flag = -1; continue;}
		res = res * 10ll + s[i] - '0';
	}
	return res * flag;
}

// const int PN = 1e7 + 10;

// int f[PN], op = 0;
// bool np[PN];

// void init() {
//     for (int i = 2; i < PN; ++i) {
//         if (!np[i]) f[op ++] = i;
//         for (int j = 0; j < op && 1ll * f[j] * i < PN; ++j) {
//             np[f[j] * i] = 1;
//             if (i % f[j] == 0) break;
//         }
//     }
// }


ll timestamp()
{
    struct timeval begin;
    gettimeofday(&begin,NULL);
    long long Nowtime = (long long)begin.tv_sec * 1000 + (long long)begin.tv_usec / 1000;
    return Nowtime;
}

ll rd(ll l = L, ll r = R) {
    // mt19937_64 gen(timestamp()%999997);
    ll len = r - l + 1;
    ll x = (gen() % len + len) % len;
    return x + l;
}

void init_gen() {
    ll t = timestamp();
    // cout << t % 99997 << '\n';
    ll p = timestamp();
    p = p % 997 * t % 9997;
    for (int i = 1; i <= p; ++i) {
        gen();
    }
    // cout << gen() << "++==\n";
}
const int N = 1e5+100;
int a[N];

int main(int argc, char *argv[]) {
    // init();
    init_gen();
    int l[20], r[20];
    for (int i = 1; i <= 3; ++i) {
        l[i] = read_num(argv[i * 2 - 1]);
        r[i] = read_num(argv[i * 2]);
        
    }
    int n = rd(l[1], r[1]), m = rd(l[1], r[1]);
    

    
    return 0;
}
