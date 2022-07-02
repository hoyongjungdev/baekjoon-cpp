#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

typedef long long int ll;

map<int,int> m;

int arr[41];

vector<int> sums(vector<int> v) {
    vector<int> result = {};

    int size = v.size();
    int end = 1 << size;

    for (int i=0; i<end; i++) {
        int sum = 0;
        for (int j=0; j<size; j++) {
            if ((1 << j) & i) {
                sum += v[j];
            }
        }

        result.push_back(sum);
    }

    return result;
}

int main() {
    int n, s;

    scanf("%d%d", &n, &s);

    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    vector<int> left(arr, arr+n/2);
    vector<int> right(arr+n/2, arr+n);

    vector<int> ls = sums(left);
    vector<int> rs = sums(right);

    for (int i=0; i<ls.size(); i++) {
        int val = ls[i];

        auto it = m.find(val);
        if (it == m.end()) {
            m[val] = 1;
        } else {
            m[val]++;
        }
    }

    ll result = 0;

    for (int i=0; i<rs.size(); i++) {
        int val = rs[i];
        auto it = m.find(s - val);

        if (it != m.end()) {
            result += it->second;
        }
    }

    if (s == 0) {
        result--;
    }

    printf("%lld\n", result);

    return 0;
}