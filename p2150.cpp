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

vector<int> adj[10005];

int cnt = 0;

int visit[10005];
int finished[10005];
vector<vector<int>> scc;

stack<int> s;

int dfs(int here) {
    cnt++;
    visit[here] = cnt;

    s.push(here);

    int mn = visit[here];

    for (int there: adj[here]) {
        if (visit[there] == 0) {
            mn = min(mn, dfs(there));
        } else if (finished[there] == 0) {
            mn = min(mn, visit[there]);
        }
    }

    if (mn == visit[here]) {
        vector<int> v;

        while (!s.empty()) {
            int t = s.top();
            s.pop();

            v.push_back(t);
            finished[t] = 1;

            if (t == here) {
                break;
            }
        }

        scc.push_back(v);
    }

//    printf("%d %d %d\n", here, visit[here], mn);

    return mn;
}

int main() {
    int v, e;
    scanf("%d%d", &v, &e);

    int a, b;
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
    }

    for (int i = 1; i <= v; i++) {
        if (visit[i] == 0) {
            dfs(i);
        }
    }

    vector<pii> nodes;

    for (int i = 0; i < scc.size(); i++) {
        sort(scc[i].begin(), scc[i].end());

        nodes.push_back({scc[i][0], i});
    }

    sort(nodes.begin(), nodes.end());

    printf("%d\n", scc.size());

    for (pii p: nodes) {
        int i = p.second;

        for (int vertex: scc[i]) {
            printf("%d ", vertex);
        }
        printf("-1\n");
    }

    return 0;
}