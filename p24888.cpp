#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

const int MAX_SIZE = 200005;

vector<pi> adj[MAX_SIZE];
vector<int> adj2[MAX_SIZE];
ll dist[MAX_SIZE];
int check[MAX_SIZE];
int dp[MAX_SIZE];
int before[MAX_SIZE];

int num(int start) {
    if (dp[start] != -1) {
        return dp[start];
    }

    int max_num = 0;

    for (auto there: adj2[start]) {
        int num_there = num(there);
        if (max_num <= num_there) {
            before[start] = there;
            max_num = num_there;
        }
    }

    max_num += check[start];

    dp[start] = max_num;

    return max_num;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int notes = 0;

    int a;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        check[i] = a;

        notes += a;
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        dist[i] = 1e16;
    }

    dist[1] = 0;

    priority_queue<pl, vector<pl>, greater<pl>> q;
    q.push({0, 1});

    while (!q.empty()) {
        auto t = q.top();
        q.pop();

        ll cost = t.first;
        ll here = t.second;

        if (dist[here] < cost) {
            continue;
        }

        for (auto np: adj[here]) {
            int there = np.first;
            int d = np.second;

            if (dist[there] > cost + d) {
                dist[there] = cost + d;
                q.push({dist[there], there});
            }
        }
    }

    for (int here = 1; here <= n; here++) {
        ll d = dist[here];

        for (auto np: adj[here]) {
            int there = np.first;
            int d2 = np.second;
            if (d + d2 == dist[there]) {
                adj2[there].push_back(here);
            }
        }
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        dp[i] = -1;
    }

    int max_num = num(n);

    //printf("%d %d\n", notes, max_num);

    if (max_num == notes) {
        vector<int> trj;

        int now = n;
        trj.push_back(now);
        now = before[now];
        while (now > 0) {
            trj.push_back(now);
            now = before[now];
        }

        printf("%d\n", trj.size());

        for (int i=trj.size()-1; i>=0; i--) {
            printf("%d ", trj[i]);
        }

        printf("\n");
    } else {
        printf("-1\n");
    }

    return 0;
}
