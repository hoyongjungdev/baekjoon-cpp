#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <deque>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

int arr[100005];
ll result[100005];

int main() {
    int n, d;

    scanf("%d%d", &n, &d);

    ll num;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &num);
        arr[i] = num;
    }

    deque<pl> deq;

    deq.push_back({arr[0], 0});
    result[0] = arr[0];

    for (int i = 1; i < n; i++) {
        num = max(deq.front().first + arr[i], (ll)arr[i]);
        result[i] = num;
//        printf("%d : %d\n", i, num);
//        printf("%d\n", deq.size());
        while (!deq.empty() && deq.back().first < num) {
            deq.pop_back();
        }

        while (!deq.empty() && i - deq.front().second >= d) {
            deq.pop_front();
        }

        deq.push_back({num, i});
    }

    ll ans = -1000000005;
    for (int i=0; i<n; i++) {
        ans = max(ans, result[i]);
    }

    printf("%lld\n", ans);

    return 0;
}
