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

int in[32001];
vector<int> adj[32001];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    queue<int> q;

    for (int i = 0; i < m; i++) {
        int a, b;

        scanf("%d%d", &a, &b);

        in[b]++;

        adj[a].push_back(b);
    }

    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int here = q.front();
        q.pop();

        ans.push_back(here);

        for (int there: adj[here]) {
            in[there]--;

            if (in[there] == 0) {
                q.push(there);
            }
        }
    }

    for (int a: ans) {
        printf("%d ", a);
    }
    printf("\n");

    return 0;
}