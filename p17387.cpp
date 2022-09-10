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
typedef pair<ll, ll> pll;

int ccw(pll one, pll two, pll three) {
    ll value = (one.first * two.second + two.first * three.second + three.first * one.second)
               - (one.second * two.first + two.second * three.first + three.second * one.first);

    if (value > 0) {
        return 1;
    } else if (value == 0) {
        return 0;
    } else {
        return -1;
    }
}

int main() {
    pll a, b, c, d;
    scanf("%lld%lld", &a.first, &a.second);
    scanf("%lld%lld", &b.first, &b.second);
    scanf("%lld%lld", &c.first, &c.second);
    scanf("%lld%lld", &d.first, &d.second);

    int abc = ccw(a, b, c);
    int abd = ccw(a, b, d);
    int cda = ccw(c, d, a);
    int cdb = ccw(c, d, b);

    if (abc * abd == 0 && cda * cdb == 0) {
        if (a > b) {
            swap(a, b);
        }

        if (c > d) {
            swap(c, d);
        }

        if (a <= d && c <= b) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    } else if (abc * abd <= 0 && cda * cdb <= 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}