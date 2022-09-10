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

int parent[100005][18];
int depth[100005];

vector<int> adj[100005];

const int MAX_SIZE = 17;

void dfs(int here, int p, int d) {
    depth[here] = d;
    parent[here][0] = p;

    for (int i = 1; i <= MAX_SIZE; i++) {
        parent[here][i] = parent[parent[here][i - 1]][i - 1];
    }

    for (int there: adj[here]) {
        if (there == p) {
            continue;
        }

        dfs(there, here, d + 1);
    }
}

int lca(int a, int b) {
    if (a == 1 || b == 1) {
        return 1;
    }

//    printf(" > %d %d\n", depth[a], depth[b]);
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    if (depth[a] != depth[b]) {
        for (int i = MAX_SIZE; i >= 0; i--) {
            if (depth[parent[a][i]] >= depth[b]) {
                a = parent[a][i];
            }
        }
    }

    if (a == b) {
        return a;
    }

    int result = a;

    for (int i = MAX_SIZE; i >= 0; i--) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }

        result = parent[a][i];
    }

    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0, 1);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        printf("%d\n", lca(a, b));
    }

    return 0;
}