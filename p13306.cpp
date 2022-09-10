#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int parent[200005];
tuple<int,int,int> input[400005];
int uf[200005];

bool answer[200005];

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

    int one, two, three;
    for (int i=0; i<n-1+q; i++) {
        scanf("%d%d", &one, &two);
        if (one == 1) {
            scanf("%d", &three);
        }

        input[i] = {one, two, three};
    }

    int cnt = 0;

    for (int i=n+q-1; i>=0; i--) {
        tie(one, two, three) = input[i];
        if (one == 0) {
            int p = parent[two];
            uf[two] = find(p);
        } else {
            if (find(two) == find(three)) {
                answer[cnt] = true;
            } else {
                answer[cnt] = false;
            }

            cnt++;
        }
    }

    for (int i=q-1; i>=0; i--) {
        if (answer[i]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}