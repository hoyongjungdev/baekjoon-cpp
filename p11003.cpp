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

int arr[5000005];

int main() {
    int n, k;

    scanf("%d%d", &n, &k);

    int num;
    for (int i=0; i<n; i++) {
        scanf("%d", &num);
        arr[i] = num;
    }

    deque<pi> d;

    for (int i=0; i<n; i++) {
        num = arr[i];

        while (!d.empty() && d.back().first > num) {
            d.pop_back();
        }

        while (!d.empty() && i-d.front().second >= k) {
            d.pop_front();
        }

        d.push_back({num, i});

        printf("%d ", d.front().first);
    }

    printf("\n");

    return 0;
}
