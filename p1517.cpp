#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

int n;
int arr[500005];

ll times(int start, int end) {
    if (start == end) {
        return 0;
    }

    int mid = (start + end) / 2;
    ll result = 0;

    result += times(start, mid);
    result += times(mid + 1, end);

    sort(arr + start, arr + (mid + 1));
    sort(arr + (mid + 1), arr + (end + 1));

    for (int i=start; i<=mid; i++) {
        auto it = lower_bound(arr + (mid + 1), arr + (end + 1), arr[i]);
        int cnt = it - (arr + (mid + 1));

        result += cnt;
    }

    return result;
}

int main() {
    scanf("%d", &n);

    int num;
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        arr[i] = num;
    }

    ll result = times(0, n - 1);
    printf("%lld\n", result);

    return 0;
}
