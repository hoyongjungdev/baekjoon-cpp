#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef pair<double, double> pd;

const double INF = 1e12;
const double EP = 1e-12;

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

vector<pd> current;

double distance(pd p1, pd p2) {
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
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

double through(pd p1, pd p2, gate g) {
    if (abs(p1.first - p2.first) < EP) {
        return p1.first;
    }

    double dx = -(p1.second - g.y) * (p1.first - p2.first) / (p1.second - p2.second);

    return p1.first + dx;
}

pd makeEndPoint(gate e, double x) {
    pd endPoint;
    int d = dir(e.x1, e.x2, x);

    if (d == 1) {
        endPoint = make_pair(e.x2, e.y);
    } else if (d == -1) {
        endPoint = make_pair(e.x1, e.y);
    } else {
        endPoint = make_pair(x, e.y);
    }

    return endPoint;
}

double solve(pd start, vector<gate> gates) {
    int n = gates.size();

    gate e = gates[n - 1];
    pd endPoint = makeEndPoint(e, start.first);

    current.clear();

    for (int i = 0; i < n - 1; i++) {
        gate g = gates[i];
        int c = cross(start, endPoint, g);

        pd here;
        here.second = g.y;

        if (c == 1) {
            here.first = g.x1;
        } else if (c == -1) {
            here.first = g.x2;
        } else {
            here.first = through(start, endPoint, g);
        }

        current.push_back(here);
    }

    current.push_back(endPoint);

    int count = 0;

    while (count < 1000) {
        for (int i = -1; i < n - 2; i++) {
            pd one;

            if (i == -1) {
                one = start;
            } else {
                one = current[i];
            }

            pd three = current[i + 2];

            gate g = gates[i + 1];

            int c = cross(one, three, g);

            if (c == 1) {
                current[i + 1].first = g.x1;
            } else if (c == -1) {
                current[i + 1].first = g.x2;
            } else {
                double t = through(one, three, g);
                current[i + 1].first = t;
            }
        }

        if (n >= 2) {
            current[n - 1] = makeEndPoint(gates[n - 1], current[n - 2].first);
        }

        count++;
    }

    double ans = 0;

    for (int i = -1; i < n - 1; i++) {
        pd one;
        if (i == -1) {
            one = start;
        } else {
            one = current[i];
        }

        pd two = current[i + 1];

        ans += distance(one, two);
    }

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

        double xs, ys;
        cin >> xs >> ys;

        pd start = make_pair(xs, ys);
        vector<gate> gates;

        for (int i = 0; i < n; i++) {
            double y, x1, x2;
            cin >> y >> x1 >> x2;

            gates.push_back({y, x1, x2});
        }

        printf("%.12lf\n", solve(start, gates));
    }

    return 0;
}
