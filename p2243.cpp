#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int limit = 1000005;
const int sz = limit * 4;

int seg[sz];

void update(int start, int end, int node, int idx, int diff) {
    if (start > idx || idx > end) {
        return;
    }

    seg[node] += diff;

    if (start == end) {
        return;
    }

    int mid = (start + end) / 2;

    update(start, mid, 2 * node, idx, diff);
    update(mid + 1, end, 2 * node + 1, idx, diff);
}

int find(int start, int end, int node, int num) {
    if (start == end) {
        return start;
    }

    int a = seg[2 * node];

    int mid = (start + end) / 2;

    if (num <= a) {
        return find(start, mid, 2 * node, num);
    } else {
        return find(mid + 1, end, 2 * node + 1, num - a);
    }
}

void print() {
    for (int i=1; i<=50; i++) {
        printf("%d ", seg[i]);
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    int a, b, c;

    int len = 1000000;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);

        if (a == 1) {
            scanf("%d", &b);
            int num = find(1, len, 1, b);
            update(1, len, 1, num, -1);
            printf("%d\n", num);
        } else {
            scanf("%d%d", &b, &c);
            update(1, len, 1, b, c);
        }

        //print();
    }

    return 0;
}
