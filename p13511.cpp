#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

typedef long long int ll;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAX_SIZE = 17;

int parent[100005][MAX_SIZE + 1];
ll sum[100005][MAX_SIZE + 1];
int depth[100005];

vector<pii> adj[100005];

void dfs(int here, int p, int d, int weightBefore) {
    depth[here] = d;
    parent[here][0] = p;
    sum[here][0] = weightBefore;

    for (int i = 1; i <= MAX_SIZE; i++) {
        int before = parent[here][i - 1];
        parent[here][i] = parent[before][i - 1];
        sum[here][i] = sum[here][i - 1] + sum[before][i - 1];
    }

    for (pii node: adj[here]) {
        int there = node.first;
        int weight = node.second;
        if (there == p) {
            continue;
        }

        dfs(there, here, d + 1, weight);
    }
}

pll lca(int a, int b, int k) {
    int u = a;
    int v = b;

//    printf(" > %d %d\n", depth[a], depth[b]);
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    ll s = 0;

    if (depth[a] != depth[b]) {
        for (int i = MAX_SIZE; i >= 0; i--) {
            if (depth[parent[a][i]] >= depth[b]) {
                s += sum[a][i];
                a = parent[a][i];
            }
        }
    }

    int result = a;

//    printf("%d %d\n", a, b);

    if (a != b) {
        for (int i = MAX_SIZE; i >= 0; i--) {
            if (parent[a][i] != parent[b][i]) {
                s += sum[a][i];
                s += sum[b][i];

                a = parent[a][i];
                b = parent[b][i];
            }

            result = parent[a][i];

//            printf("%d %lld\n", i, s);
        }

        s += sum[a][0];
        s += sum[b][0];

//        printf("%lld\n", s);
    }

    int idx = -1;

    if (k != -1) {
        int la = depth[u] - depth[result];

        if (k - 1 == la) {
            idx = result;
        } else if (k - 1 < la) {
            int goal = depth[u] - k + 1;

            for (int i = MAX_SIZE; i >= 0; i--) {
                if (depth[parent[u][i]] >= goal) {
                    u = parent[u][i];
                }
            }

            idx = u;
        } else {
            int goal = (k - 1) - depth[u] + 2 * depth[result];

            for (int i = MAX_SIZE; i >= 0; i--) {
                if (depth[parent[v][i]] >= goal) {
                    v = parent[v][i];
                }
            }

            idx = v;
        }
    }

    return {s, idx};
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    dfs(1, 0, 1, 0);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d", &a);

        int k;

        if (a == 1) {
            scanf("%d%d", &b, &c);
            k = -1;
        } else {
            scanf("%d%d%d", &b, &c, &d);
            k = d;
        }

        pll result = lca(b, c, k);
        if (a == 1) {
            printf("%lld\n", result.first);
        } else {
            printf("%lld\n", result.second);
        }
    }

    return 0;
}