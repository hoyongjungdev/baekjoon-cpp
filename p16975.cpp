#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int sz = 100005;

int num[sz];

ll seg[sz * 4];

ll update(int start, int end, int node, int idx, int diff) {
    if (start > idx || idx > end) {
        return seg[node];
    }

    if (start == end) {
        seg[node] += diff;
        return seg[node];
    }

    int mid = (start + end) / 2;

    seg[node] = update(start, mid, 2 * node, idx, diff) + update(mid + 1, end, 2 * node + 1, idx, diff);

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

    return result;
}

void print() {
    for (int i=1; i<=50; i++) {
        printf("%lld ", seg[i]);
    }
    printf("\n");
}

int main() {
    int n;

    scanf("%d", &n);

    int a;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);

        if (i == 1) {
            num[i] = a;
            update(1, n, 1, i, a);
        } else {
            num[i] = a;
            update(1, n, 1, i, a - num[i - 1]);
        }
    }

    //print();

    int m;
    scanf("%d", &m);

    int q, i, j, k;
    for (int y = 0; y < m; y++) {
        scanf("%d", &q);

        if (q == 1) {
            scanf("%d%d%d", &i, &j, &k);

            update(1, n, 1, i, k);

            if (j < n) {
                update(1, n, 1, j + 1, -k);
            }
        } else {
            scanf("%d", &i);

            ll result = sum(1, n, 1, 1, i);

            printf("%lld\n", result);
        }

//        print();
    }

    return 0;
}
