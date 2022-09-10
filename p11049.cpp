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

pi mat[505];

int dp[505][505];

int solve(int start, int end) {
    if (start == end) {
        return 0;
    }

    if (start + 1 == end) {
        return mat[start].first * mat[start].second * mat[end].second;
    }

    if (dp[start][end] != -1) {
        return dp[start][end];
    }

    int result = 0x7FFFFFFF;

    for (int mid = start; mid < end; mid++) {
        result = min(result,
                     solve(start, mid) + solve(mid + 1, end) + mat[start].first * mat[mid].second * mat[end].second);
    }

    dp[start][end] = result;
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    int r, c;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &r, &c);

        mat[i] = {r, c};
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", solve(0, n - 1));

    return 0;
}
