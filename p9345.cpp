#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int sz = 400005;

int mx_seg[sz];
int mn_seg[sz];

int mx_update(int start, int end, int node, int idx, int val) {
    if (start > idx || idx > end) {
        return mx_seg[node];
    }

    if (start == end) {
        mx_seg[node] = val;
        return val;
    }

    int mid = (start + end) / 2;

    mx_seg[node] = max(
            mx_update(start, mid, 2 * node, idx, val), mx_update(mid + 1, end, 2 * node + 1, idx, val)
    );

    return mx_seg[node];
}

int mn_update(int start, int end, int node, int idx, int val) {
    if (start > idx || idx > end) {
        return mn_seg[node];
    }

    if (start == end) {
        mn_seg[node] = val;
        return val;
    }

    int mid = (start + end) / 2;

    mn_seg[node] = min(
            mn_update(start, mid, 2 * node, idx, val), mn_update(mid + 1, end, 2 * node + 1, idx, val)
    );

    return mn_seg[node];
}

int mx(int start, int end, int node, int from, int to) {
    if (from <= start && end <= to) {
        return mx_seg[node];
    }

    if (end < from || to < start) {
        return 0;
    }

    int mid = (start + end) / 2;

    int result = max(mx(start, mid, 2 * node, from, to), mx(mid + 1, end, 2 * node + 1, from, to));

    return result;
}

int mn(int start, int end, int node, int from, int to) {
    if (from <= start && end <= to) {
        return mn_seg[node];
    }

    if (end < from || to < start) {
        return sz;
    }

    int mid = (start + end) / 2;

    int result = min(mn(start, mid, 2 * node, from, to), mn(mid + 1, end, 2 * node + 1, from, to));

    return result;
}

void print() {
    for (int i=1; i<=50; i++) {
        printf("%d ", mn_seg[i]);
    }
    printf("\n");

    for (int i=1; i<=50; i++) {
        printf("%d ", mx_seg[i]);
    }
    printf("\n");
}

int main() {
    int testcase;
    scanf("%d", &testcase);

    for (int t = 0; t < testcase; t++) {
        for (int i = 0; i < sz; i++) {
            mx_seg[i] = 0;
            mn_seg[i] = sz;
        }

        int n, k;
        scanf("%d%d", &n, &k);

        for (int i = 1; i <= n; i++) {
            mx_update(1, n, 1, i, i);
            mn_update(1, n, 1, i, i);
        }

        //print();

        int q, a, b;
        for (int i = 0; i < k; i++) {
            scanf("%d%d%d", &q, &a, &b);

            a++;
            b++;

            if (q == 0) {
                int val_a = mx(1, n, 1, a, a);
                int val_b = mx(1, n, 1, b, b);
                mx_update(1, n, 1, a, val_b);
                mn_update(1, n, 1, a, val_b);
                mx_update(1, n, 1, b, val_a);
                mn_update(1, n, 1, b, val_a);
            } else {
                int mx_val = mx(1, n, 1, a, b);
                int mn_val = mn(1, n, 1, a, b);

                //printf(" >> %d %d\n", mn_val, mx_val);

                if (mn_val == a && mx_val == b) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
            }

            //print();
        }
    }

    return 0;
}
