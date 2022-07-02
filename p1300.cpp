#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

ll n, k;

ll cnt(ll num) {
    ll s = 0;

    for (ll i=1; i<=n; i++) {
        s += min((ll)n, num / i);
    }

    return s;
}

int main() {
    scanf("%lld%lld", &n, &k);

    ll low = 1, high = n*n + 1;

    while (low < high) {
        ll mid = (low + high) / 2;

        ll val = cnt(mid);

        //printf("%lld %lld %lld %lld\n", low, high, mid, val);

        if (val >= k) {
            high = mid;
        } else if (val < k) {
            low = mid + 1;
        }
    }

    printf("%lld\n", low);

    return 0;
}