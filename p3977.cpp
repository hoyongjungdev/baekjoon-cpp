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

vector<int> adj[100005];

int cnt = 0;

int visit[100005];
int finished[100005];
int visited[100005];
vector<vector<int>> scc;

stack<int> s;

int visitCnt = 0;

void dfs2(int here) {
    visited[here] = 1;
    visitCnt++;

    for (int there: adj[here]) {
        if (visited[there] == 0) {
            dfs2(there);
        }
    }
}

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
    int t;
    scanf("%d", &t);

    int n, m;
    for (int testcase = 0; testcase < t; testcase++) {
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; i++) {
            adj[i].clear();
            visit[i] = 0;
            visited[i] = 0;
            finished[i] = 0;
        }

        cnt = 0;
        visitCnt = 0;

        scc.clear();

        s = stack<int>();

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);

            adj[a].push_back(b);
        }

        for (int i = 0; i < n; i++) {
            if (visit[i] == 0) {
                dfs(i);
            }
        }

        int lastNum = scc.size() - 1;

        int node = scc[lastNum][0];
        dfs2(node);

        if (visitCnt == n) {
            sort(scc[lastNum].begin(), scc[lastNum].end());
            for (int i: scc[lastNum]) {
                printf("%d\n", i);
            }
            printf("\n");

        } else {
            printf("Confused\n\n");
        }
    }

    return 0;
}