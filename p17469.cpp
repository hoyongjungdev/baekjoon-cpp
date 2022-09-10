#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int parent[100005];
pair<int,int> input[1100005];
int uf[100005];

set<int> color[100005];
int answer[1000005];

int find(int node) {
    if (uf[node] == node) {
        return node;
    } else {
        uf[node] = find(uf[node]);
        return uf[node];
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    for (int i=1; i<=n; i++) {
        uf[i] = i;
    }

    int num;
    for (int i=2; i<=n; i++) {
        scanf("%d", &num);
        parent[i] = num;
    }

    for (int i=1; i<=n; i++) {
        scanf("%d", &num);
        color[i].insert(num);
    }

    int one, two;
    for (int i=0; i<n-1+q; i++) {
        scanf("%d%d", &one, &two);

        input[i] = {one, two};
    }

    int cnt = 0;

    for (int i=n+q-2; i>=0; i--) {
        tie(one, two) = input[i];

        if (one == 1) {
            int p = parent[two];
            int before = uf[two];
            int now = find(p);
            uf[two] = now;

            if (color[before].size() < color[now].size()) {
                for (int e: color[before]) {
                    color[now].insert(e);
                }
            } else {
                for (int e: color[now]) {
                    color[before].insert(e);
                }

                swap(color[now], color[before]);
            }

            color[before].clear();
        } else {
            answer[cnt] = color[find(two)].size();
            cnt++;
        }
    }

    for (int i=q-1; i>=0; i--) {
        printf("%d\n", answer[i]);
    }

    return 0;
}