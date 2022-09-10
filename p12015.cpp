#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

vector<pair<int, int>> inp;

int seg[4000005];

int update(int start, int end, int node, int idx, int val) {
    if (start > idx || idx > end) {
        return seg[node];
    }

    if (start == end) {
        seg[node] = val;
        return val;
    }

    int mid = (start + end) / 2;

    seg[node] = max(
            update(start, mid, 2 * node, idx, val), update(mid + 1, end, 2 * node + 1, idx, val)
    );

    //printf("%d %d %d %d\n", start, end, node, seg[node]);

    return seg[node];
}

int mx(int start, int end, int node, int from, int to) {
    if (from <= start && end <= to) {
        return seg[node];
    }

    if (end < from || to < start) {
        return 0;
    }

    int mid = (start + end) / 2;

    int result = max(mx(start, mid, 2 * node, from, to), mx(mid + 1, end, 2 * node + 1, from, to));

    //printf("%d %d %d %d %d %lld\n", start, end, node, from, to, result);

    return result;
}

void print() {
    for (int i=1; i<=20; i++) {
        printf("%d ", seg[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    int num;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num);
        inp.push_back({num, -i});
    }

    sort(inp.begin(), inp.end());

    for (int i = 0; i < n; i++) {
        int idx = -inp[i].second;

        int sz = mx(1, n, 1, 1, idx - 1);
        update(1, n, 1, idx, sz + 1);

        //printf("%d %d\n", idx, sz + 1);
        //print();
    }

    printf("%d\n", mx(1, n, 1, 1, n));

    return 0;
}
