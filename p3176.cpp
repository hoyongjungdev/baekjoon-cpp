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

const int MAX_SIZE = 17;

int parent[100005][MAX_SIZE + 1];
int mn[100005][MAX_SIZE + 1];
int mx[100005][MAX_SIZE + 1];
int depth[100005];

vector<pii> adj[100005];

void dfs(int here, int p, int d, int weight) {
    depth[here] = d;
    parent[here][0] = p;
    mn[here][0] = weight;
    mx[here][0] = weight;

    for (int i = 1; i <= MAX_SIZE; i++) {
        int before = parent[here][i - 1];
        parent[here][i] = parent[before][i - 1];
        mn[here][i] = min(mn[before][i - 1], mn[here][i - 1]);
        mx[here][i] = max(mx[before][i - 1], mx[here][i - 1]);
    }

    for (pii node: adj[here]) {
        int there = node.first;
        int thereWeight = node.second;
        if (there == p) {
            continue;
        }

        dfs(there, here, d + 1, thereWeight);
    }
}

pii lca(int a, int b) {
//    printf(" > %d %d\n", depth[a], depth[b]);
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    int minE = 1000001;
    int maxE = -1;

    if (depth[a] != depth[b]) {
        for (int i = MAX_SIZE; i >= 0; i--) {
            if (depth[parent[a][i]] >= depth[b]) {
                minE = min(minE, mn[a][i]);
                maxE = max(maxE, mx[a][i]);
                a = parent[a][i];
            }
        }
    }

    if (a == b) {
        return {minE, maxE};
    }

    for (int i = MAX_SIZE; i >= 0; i--) {
        if (parent[a][i] != parent[b][i]) {
            minE = min(minE, mn[a][i]);
            maxE = max(maxE, mx[a][i]);
            minE = min(minE, mn[b][i]);
            maxE = max(maxE, mx[b][i]);

            a = parent[a][i];
            b = parent[b][i];
        }
    }

    minE = min(minE, mn[a][0]);
    maxE = max(maxE, mx[a][0]);
    minE = min(minE, mn[b][0]);
    maxE = max(maxE, mx[b][0]);

    return {minE, maxE};
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
        int a, b;
        scanf("%d%d", &a, &b);
        pii result = lca(a, b);
        printf("%d %d\n", result.first, result.second);
    }

    return 0;
}