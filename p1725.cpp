#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int arr[100005];
int l_small[1000005];
int r_small[1000005];

int main() {
    int n;
    scanf("%d", &n);

    stack<pi> left;
    stack<pi> right;

    int num;

    for (int i = 0; i < n; i++) {
        scanf("%d", &num);

        arr[i] = num;
    }

    for (int i = 0; i < n; i++) {
        pi x = {arr[i], i};

        while (!left.empty() && left.top().first >= x.first) {
            left.pop();
        }

        if (left.empty()) {
            l_small[i] = 0;
        } else {
            l_small[i] = left.top().second + 1;
        }

        left.push(x);
    }

    for (int i = n - 1; i >= 0; i--) {
        pi x = {arr[i], i};

        while (!right.empty() && right.top().first >= x.first) {
            right.pop();
        }

        if (right.empty()) {
            r_small[i] = n - 1;
        } else {
            r_small[i] = right.top().second - 1;
        }

        right.push(x);
    }

    ll result = 0;

    for (int i = 0; i < n; i++) {
        //printf("%d >> %d %d %d\n", i, arr[i], l_small[i], r_small[i]);

        result = max(result, ((ll) r_small[i] - l_small[i] + 1) * arr[i]);
    }

    printf("%lld\n", result);

    return 0;
}
