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

double sq(double num) {
    return num * num;
}

int main() {
    double x, y, d, t;
    scanf("%lf%lf%lf%lf", &x, &y, &d, &t);

    double dist = sqrt(sq(x) + sq(y));

    if (d / t < 1.0) {
        printf("%.12lf\n", dist);
        return 0;
    }

    double time = 0;

    double jump = dist / d;

    if (jump >= 1) {
        time = min(ceil(jump) * t, floor(jump) * t + dist - floor(jump) * d);
    } else {
        time = min(dist, t + d - dist);
        time = min(time, 2 * t);
    }

    printf("%.12lf\n", time);

    return 0;
}