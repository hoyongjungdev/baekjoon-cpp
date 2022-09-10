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
typedef pair<ll, ll> pl;

int arr[1000005];

int main() {
    int n, k;

    scanf("%d%d", &n, &k);

    int select = n - k;

    int num;
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        arr[i] = num;
    }

    sort(arr, arr + n);

    deque<pi> d;

    int result = 20000005;

    for (int i = 1; i < n; i++) {
        int diff = abs(arr[i] - arr[i - 1]);

        while (!d.empty() && d.back().first > diff) {
            d.pop_back();
        }

        while (!d.empty() && i - d.front().second >= select - 1) {
            d.pop_front();
        }

        d.push_back({diff, i});

        if (i >= select - 1) {
            int large = abs(arr[i] - arr[i - select + 1]);
            int small = d.front().first;

            result = min(result, large + small);
        }
    }

    printf("%d\n", result);

    return 0;
}
