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

int weight[10005];
vector<int> adj[10005];

int dp[10005][2];
vector<pi> track[10005][2];
vector<int> result;

void solve(int here, int prev) {
    dp[here][1] = weight[here];

    for (auto there: adj[here]) {
        if (there != prev) {
            solve(there, here);
            dp[here][1] += dp[there][0];
            track[here][1].push_back({there, 0});

            dp[here][0] += max(dp[there][0], dp[there][1]);
            track[here][0].push_back({there, dp[there][1] > dp[there][0]});
        }
    }
}

void solve2(int here, int fill) {
    if (fill == 1) {
        result.push_back(here);
    }

    for (pi a: track[here][fill]) {
        solve2(a.first, a.second);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int w;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w);

        weight[i] = w;
    }

    int a, b;

    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    solve(1, -1);

    int zero = dp[1][0];
    int one = dp[1][1];

    if (zero > one) {
        printf("%d\n", zero);
        solve2(1, 0);
    } else {
        printf("%d\n", one);
        solve2(1, 1);
    }

    sort(result.begin(), result.end());

    for (int i = 0; i < result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
