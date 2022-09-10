#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
#include <deque>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int n, g, b, d;

vector<pi> dp;
int next_stop[50005];

ll cost = 0;

bool possible = true;

void go(int cur_idx, int to_idx) {
//    printf(" >> cost: %lld\n", cost);
//    printf(" >> cur_idx, to_idx, b: %d %d %d\n", cur_idx, to_idx, b);

    int to_dist = dp[to_idx].first;
    int cur_dist = dp[cur_idx].first;

    if (to_dist - cur_dist <= b) {
        b -= to_dist - cur_dist;
        return;
    }

    int ns = next_stop[cur_idx];
//    printf(" >> ns: %d\n", ns);

    if (ns == to_idx) {
        int right_next_dist = dp[cur_idx + 1].first;
        if (right_next_dist - cur_dist > b) {
            cost += (ll) dp[cur_idx].second * (right_next_dist - cur_dist - b);
            b = right_next_dist - cur_dist;
        }

        b -= right_next_dist - cur_dist;

        go(cur_idx + 1, to_idx);
        return;
    }

    go(cur_idx, ns);

    int ns_dist = dp[ns].first;

    int fill = min(g - b, d - ns_dist - b);

    cost += (ll) fill * dp[ns].second;
    b += fill;

    go(ns, to_idx);
}

int main() {
    scanf("%d%d%d%d", &n, &g, &b, &d);

    int n1, n2;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &n1, &n2);
        dp.push_back({n1, n2});
    }
    dp.push_back({d, 0});

    sort(dp.begin(), dp.end());

    vector<pi> dp_tmp;

    dp_tmp.push_back(dp[0]);

    int before = dp[0].first;

    for (int i = 1; i <= n; i++) {
        if (dp[i].first != before) {
            dp_tmp.push_back(dp[i]);
            before = dp[i].first;
        }
    }

    dp = dp_tmp;

    dp.insert(dp.begin(), {0, 1000001});

    n = dp.size() - 2;

    for (int i = 0; i <= n; i++) {
        if (dp[i + 1].first - dp[i].first > g) {
            printf("-1\n");
            return 0;
        }
    }

    if (dp[1].first > b) {
        printf("-1\n");
        return 0;
    }

    deque<pi> s;

    for (int i = n; i >= 0; i--) {
        pi x = {dp[i].second, i};

        if (s.empty()) {
            next_stop[i] = -1;
        } else {
            next_stop[i] = s.front().second;
        }

        while (!s.empty() && s.back().first >= x.first) {
            s.pop_back();
        }

        s.push_back(x);
    }

    next_stop[0] = s.front().second;

    go(0, n + 1);

    printf("%lld\n", cost);

    return 0;
}
