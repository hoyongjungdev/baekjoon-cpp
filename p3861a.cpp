#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef pair<double, double> pd;

enum status {
    unknown,
    no,
    left_point,
    right_point
};

const double INF = 1e12;
const double EP = 1e-12;

status check[1005];

struct gate {
    double y;
    double x1;
    double x2;

public:
    gate(double y, double x1, double x2) {
        this->y = y;
        this->x1 = x1;
        this->x2 = x2;
    }
};

double distance(pd p1, pd p2) {
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

double angle(pd p1, pd p2, pd p3) {
    pd v1 = make_pair(p2.first - p1.first, p2.second - p1.second);
    pd v2 = make_pair(p3.first - p1.first, p3.second - p1.second);
    double size = sqrt(v2.first * v2.first + v2.second * v2.second);

    v2 = make_pair(v2.first / size, v2.second / size);

    return v1.first * v2.first + v1.second * v2.second;
}

int dir(double x1, double x2, double x) {
    if (x < x1) {
        return -1;
    } else if (x > x2) {
        return 1;
    } else {
        return 0;
    }
}

int cross(pd p1, pd p2, gate g) {
    if (abs(p1.first - p2.first) < EP) {
        return -dir(g.x1, g.x2, p1.first);
    }

    double dx = -(p1.second - g.y) * (p1.first - p2.first) / (p1.second - p2.second);

    double x = p1.first + dx;

    return -dir(g.x1, g.x2, x);
}

double solve(pd start, vector<gate> &gates, int startIndex, int endIndex) {
    int n = gates.size();

    pd startPoint;

    if (startIndex == -1) {
        startPoint = start;
    } else {
        status s = check[startIndex];
        gate g = gates[startIndex];

        if (s == left_point) {
            startPoint = make_pair(g.x1, g.y);
        } else {
            startPoint = make_pair(g.x2, g.y);
        }
    }

    pd endPoint;

    if (endIndex == n - 1) {
        gate e = gates[endIndex];
        int d = dir(e.x1, e.x2, startPoint.first);

        if (d == 1) {
            endPoint = make_pair(e.x2, e.y);
        } else if (d == -1) {
            endPoint = make_pair(e.x1, e.y);
        } else {
            endPoint = make_pair(startPoint.first, e.y);
        }
    } else {
        status s = check[endIndex];
        gate g = gates[endIndex];

        if (s == left_point) {
            endPoint = make_pair(g.x1, g.y);
        } else {
            endPoint = make_pair(g.x2, g.y);
        }
    }

//    cout << "startPoint: " << startPoint.first << " " << startPoint.second << endl;
//    cout << "endPoint: " << endPoint.first << " " << endPoint.second << endl;

    bool allCross = true;

    int l1Index = -100, l2Index = -100, r1Index = -100, r2Index = -100;
    double l1 = INF, l2 = INF, r1 = INF, r2 = INF;

    for (int i = startIndex + 1; i < endIndex; i++) {
        gate g = gates[i];
        int c = cross(startPoint, endPoint, g);

        if (c == 0) {
            continue;
        }

        allCross = false;

        if (c == 1) {
            pd point = {g.x1, g.y};
            double ar1 = angle(startPoint, endPoint, point);
            double ar2 = angle(endPoint, startPoint, point);

            if (ar1 < r1) {
                r1 = ar1;
                r1Index = i;
            }

            if (ar2 < r2) {
                r2 = ar2;
                r2Index = i;
            }
        } else {
            pd point = {g.x2, g.y};
            double al1 = angle(startPoint, endPoint, point);
            double al2 = angle(endPoint, startPoint, point);

            if (al1 < l1) {
                l1 = al1;
                l1Index = i;
            }

            if (al2 < l2) {
                l2 = al2;
                l2Index = i;
            }
        }
    }

    double ans = 0;

    if (allCross) {
        for (int i = startIndex + 1; i < endIndex; i++) {
            check[i] = no;
        }

        ans = distance(startPoint, endPoint);
    } else {
        vector<int> seq;
        seq.push_back(startIndex);

        if (r1Index >= 0) {
            seq.push_back(r1Index);
            if (r1Index != r2Index) {
                seq.push_back(r2Index);
            }

            check[r1Index] = left_point;
            check[r2Index] = left_point;
        }
        if (l1Index >= 0) {
            seq.push_back(l1Index);
            if (l1Index != l2Index) {
                seq.push_back(l2Index);
            }

            check[l1Index] = right_point;
            check[l2Index] = right_point;
        }

        seq.push_back(endIndex);

        sort(seq.begin(), seq.end());

        for (int i = 0; i < seq.size() - 1; i++) {
            ans += solve(start, gates, seq[i], seq[i + 1]);
        }
    }

//    cout << startIndex << " " << endIndex << endl;
//
//    cout << "ans: " << ans << endl;

    return ans;
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

        double x, y;
        cin >> x >> y;

        pd start = make_pair(x, y);
        vector<gate> gates;

        for (int i = 0; i < n; i++) {
            double y, x1, x2;
            cin >> y >> x1 >> x2;

            gates.push_back({y, x1, x2});
        }

        for (int i = 0; i < n - 1; i++) {
            check[i] = unknown;
        }

        printf("%.12lf\n", solve(start, gates, -1, n - 1));
    }

    return 0;
}
