#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <stack>

using namespace std;

typedef long long int ll;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

vector<pii> points;

int cnt[75005];
int sq;
int bin[300];
int n;
int sz;

int sum(int from) {
    int result = 0;
    while (from % sq != 0 && from < sz) {
        result += cnt[from];
        from++;
    }

    while (from / sq < 300 && from < sz) {
        result += bin[from / sq];
        from += sq;
    }

    return result;
}

void update(int idx) {
    cnt[idx]++;
    bin[idx/sq]++;
}

int main() {
    int t;
    scanf("%d", &t);

    for (int testcase = 0; testcase < t; testcase++) {
        scanf("%d", &n);

        sq = sqrt(n);

        points.clear();
        vector<int> xs;

        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);

            points.push_back({-y, x});
            xs.push_back(x);
        }

        sort(xs.begin(), xs.end());

        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sz = xs.size();

        sort(points.begin(), points.end());

        ll result = 0;

        for (int i=0; i<75005; i++) {
            cnt[i] = 0;
        }

        for (int i=0; i<300; i++) {
            bin[i] = 0;
        }

        for (int i = n - 1; i >= 0; i--) {
            pii p = points[i];
            int x = p.second;

            int idx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();

            int s = sum(idx);
            result += s;

            update(idx);
        }

        printf("%lld\n", result);
    }

    return 0;
}