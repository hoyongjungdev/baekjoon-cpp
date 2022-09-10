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

int arr[2005];
int dp[2005][2005];

bool is_palindrome(int start, int end) {
    if (end <= start) {
        return true;
    }

    if (dp[start][end] != -1) {
        return dp[start][end];
    }

    if (arr[start] == arr[end]) {
        dp[start][end] = is_palindrome(start + 1, end - 1);
    } else {
        dp[start][end] = false;
    }

    return dp[start][end];
}

int main() {
    for (int i = 0; i < 2005; i++) {
        for (int j = 0; j < 2005; j++) {
            dp[i][j] = -1;
        }
    }

    int n;
    scanf("%d", &n);

    int num;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num);

        arr[i] = num;
    }

    int m;
    scanf("%d", &m);

    int s, e;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &s, &e);

        printf("%d\n", is_palindrome(s, e));
    }

    return 0;
}
