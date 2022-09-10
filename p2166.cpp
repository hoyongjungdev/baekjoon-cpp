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

struct vec {
    double x;
    double y;

    double outer(vec other) {
        return this->x * other.y - this->y * other.x;
    }
};

int main() {
    int n;
    scanf("%d", &n);

    vector<vec> points;

    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);

        points.push_back({x, y});
    }

    double area = 0;

    for (int i = 0; i < n; i++) {
        vec here = points[i];
        vec next = points[(i + 1) % n];

        area += here.outer(next);
    }

    if (area < 0) {
        area *= -1;
    }

    printf("%.1lf\n", area / 2);

    return 0;
}