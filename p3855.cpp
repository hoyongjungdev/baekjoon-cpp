#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef pair<double, double> pd;

double distanceSquare(double x, double y, double c) {
    return (x - c) * (x - c) + y * y;
}

pd solve(vector<pd> dots) {
    int n = dots.size();

    for (int i=0; i<n; i++) {
        pd dot = dots[i];
        dot.second = abs(dot.second);
        dots[i] = dot;
    }

    sort(dots.begin(), dots.end());

    if (n <= 1) {
        return make_pair(dots[0].first, dots[0].second);
    }

    double lo = dots[0].first;
    double hi = dots[n-1].first;

    while (hi - lo > 1e-10) {
        double mid = (hi + lo) / 2;

        double leftMax = -1;
        double rightMax = -1;

        for (int i=0; i<n; i++) {
            pd dot = dots[i];
            double dSquare = distanceSquare(dot.first, dot.second, mid);
            if (dot.first < mid) {
                leftMax = max(leftMax, dSquare);
            }
            else {
                rightMax = max(rightMax, dSquare);
            }
        }

        double score = rightMax - leftMax;

        if (score >= 0) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    double ans = -1;

    for (int i=0; i<n; i++) {
        pd dot = dots[i];
        double dSquare = distanceSquare(dot.first, dot.second, hi);
        ans = max(ans, dSquare);
    }

    return make_pair(hi, sqrt(ans));

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int n;
        cin >> n;

        if (n == 0) {
            break;
        }

        vector<pd> dots;

        for (int i=0; i<n; i++) {
            double x, y;
            cin >> x >> y;

            dots.push_back(make_pair(x, y));
        }

        auto ans = solve(dots);
        printf("%.9lf %.9lf\n", ans.first, ans.second);
    }

    return 0;
}

