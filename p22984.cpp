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

int main() {
    int n;
    scanf("%d", &n);

    vector<double> arr;

    double num;

    double ex = 0.0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &num);
        arr.push_back(num);

        ex += arr[i];
        if (i > 0) {
            ex += arr[i - 1] * (1 - arr[i]) + (1 - arr[i - 1]) * arr[i];
        }
    }

    printf("%.10lf\n", ex);

    return 0;
}
