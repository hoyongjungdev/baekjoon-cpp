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

vector<int> adj[20005];

int cnt = 0;

int visit[20005];
int finished[20005];
int rev[20005];
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

//        printf(" > %d: ", sccNum);

        while (!s.empty()) {
            int t = s.top();
            s.pop();

//            printf("%d\n", t);

            v.push_back(t);
            finished[t] = 1;
            rev[t] = sccNum;

            if (t == here) {
                break;
            }
        }

        scc.push_back(v);
    }

//    printf("%d %d %d\n", here, visit[here], mn);

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
    scanf("%d%d", &n, &m);

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

        adj[x].push_back(neg(y));
        adj[y].push_back((neg(x)));
    }

    for (int i = 2; i <= 2 * n + 1; i++) {
        if (visit[i] == 0) {
            dfs(i);
        }
    }

//    for (int i=0; i<6; i++) {
//        for (int k: adj[i]) {
//            printf("%d ", k);
//        }
//        printf("\n");
//    }

    for (int i = 1; i <= n; i++) {
//        printf("%d %d\n", rev[2 * i], rev[2 * i + 1]);
        if (rev[2 * i] == rev[2 * i + 1]) {
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");

    return 0;
}