#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

int n, m, k;

const int limit = 1000005;
const int sz = limit * 4;

ll num[limit];
ll seg[sz];

ll init(int start, int end, int node) {
    if (start == end) {
        seg[node] = num[start];
        return seg[node];
    }

    int mid = (start + end) / 2;

    seg[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
//    printf("%d %d %d %lld\n", start, end, node, seg[node]);
    return seg[node];
}

ll update(int start, int end, int node, int idx, ll val) {
    if (start > idx || idx > end) {
        return seg[node];
    }

    if (start == end) {
        seg[node] = val;
        return val;
    }

    int mid = (start + end) / 2;

    seg[node] = update(start, mid, 2 * node, idx, val) + update(mid + 1, end, 2 * node + 1, idx, val);

    return seg[node];
}

ll sum(int start, int end, int node, int from, int to) {
    if (from <= start && end <= to) {
        return seg[node];
    }

    if (end < from || to < start) {
        return 0;
    }

    int mid = (start + end) / 2;

    ll result = sum(start, mid, 2 * node, from, to) + sum(mid + 1, end, 2 * node + 1, from, to);

    //printf("%d %d %d %d %d %lld\n", start, end, node, from, to, result);

    return result;
}

void print() {
    printf(" >> ");
    for (int i = 1; i <= 50; i++) {
        printf("%lld ", seg[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    ll a;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a);
        num[i] = a;
    }

    init(1, n, 1);

    ll b, c;

//    print();

    for (int i = 0; i < m + k; i++) {
        scanf("%lld%lld%lld", &a, &b, &c);

        if (a == 1) {
            update(1, n, 1, b, c);
        } else {
            printf("%lld\n", sum(1, n, 1, b, c));
        }

        //print();
    }

    return 0;
}
