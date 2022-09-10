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

int main() {
    int n;
    scanf("%d", &n);

    vector<pii> v;

    for (int i=0; i<n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        v.push_back({a, b});
    }

    sort(v.begin(), v.end());

    int start = v[0].first;
    int end = v[0].second;

    int length = 0;

    for (int i=1; i<n; i++) {
        if (end < v[i].first) {
            length += end - start;
            start = v[i].first;
            end = v[i].second;
        } else {
            end = max(end, v[i].second);
        }
    }

    length += end - start;

    printf("%d\n", length);

    return 0;
}