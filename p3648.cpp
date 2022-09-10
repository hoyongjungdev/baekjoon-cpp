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

vector<int> adj[2005];

int cnt = 0;

int visit[2005];
int finished[2005];
int rev[2005];
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
        int sccNum = scc.size();

        while (!s.empty()) {
            int t = s.top();
            s.pop();

            v.push_back(t);
            finished[t] = 1;
            rev[t] = sccNum;

            if (t == here) {
                break;
            }
        }

        scc.push_back(v);
    }

    return mn;
}

int neg(int num) {
    if (num % 2 == 0) {
        return num + 1;
    } else {
        return num - 1;
    }
}

int main() {
    int n, m;

    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i=0; i<2005; i++) {
            adj[i].clear();
            visit[i] = 0;
            finished[i] = 0;
            rev[i] = 0;
        }

        cnt = 0;
        scc.clear();
        s = stack<int>();

        int a, b;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &a, &b);

            int x = 2 * abs(a);
            int y = 2 * abs(b);

            if (a < 0) {
                x++;
            }

            if (b < 0) {
                y++;
            }

            adj[neg(x)].push_back(y);
            adj[neg(y)].push_back(x);
        }

        adj[3].push_back(2);

        for (int i = 2; i <= 2 * n + 1; i++) {
            if (visit[i] == 0) {
                dfs(i);
            }
        }

//        for (int i=0; i<8; i++) {
//            printf("%d: ", i);
//            for (int e: adj[i]) {
//                printf("%d ", e);
//            }
//            printf("\n");
//        }

//        for (int i=0; i<8; i++) {
//            printf("%d ", rev[i]);
//        }
//        printf("\n");

        bool result = true;

        if (rev[2] > rev[3]) {
            result = false;
        }

        for (int i = 1; i <= n; i++) {
            if (rev[2 * i] == rev[2 * i + 1]) {
                result = false;
                break;
            }
        }

        if (result) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}