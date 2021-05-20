#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

double t_height = sqrt(3) / 2.0;
double t_remain = 1.0 - t_height;
double r_half = M_PI_2;

double side(char c) {
    if (c == 'C') {
        return r_half;
    } else {
        return 1;
    }
}

double height(char c) {
    if (c == 'T') {
        return t_height;
    } else {
        return 1;
    }
}

double top_part(int dist, char c) {
    if (dist == 0) {
        return 0.0;
    }

    if (c == 'S') {
        double dx = dist - 0.5;
        return sqrt(pow(dx, 2) + pow(t_remain, 2));
    }
    double x = sqrt(pow(t_height - 0.5, 2) + pow((double) dist, 2) - 0.25);
    //cout << x << endl;

    double theta1 = atan((t_height - 0.5) / dist);
    double theta2 = atan(2 * x);
    double theta3 = M_PI_2 - theta1 - theta2;

    return theta3 * 0.5 + x;
}

double top_middle(int dist, char left, char right) {
    double result = dist;

    if (left == 'S') {
        result += 0.5;
    }

    if (right == 'S') {
        result += 0.5;
    }

    return result;
}

double area(string inp) {
    // 위의 최대 높이, 양 옆
    int size = inp.size();

    char first = inp[0];
    char last = inp[size - 1];

    double left_side = side(first);
    double right_side = side(last);

    double max_height = -1;
    double min_height = 2;

    for (int i = 0; i < size; i++) {
        max_height = max(max_height, height(inp[i]));
        min_height = min(min_height, height(inp[i]));
    }

    double top = -1;

    if (height(first) > 0.999 && height(last) > 0.999) {
        top = size;

        if (first == 'C') {
            top -= 0.5;
        }
        if (last == 'C') {
            top -= 0.5;
        }
    } else if (max_height < 0.999) {
        top = size - 1;
    } else {
        int lm_one = -1;
        int rm_one = -1;
        double p1, p2, p3;

        for (int i = 0; i < size; i++) {
            if (height(inp[i]) > 0.999) {
                lm_one = i;
                break;
            }
        }

        for (int i = size - 1; i >= 0; i--) {
            if (height(inp[i]) > 0.999) {
                rm_one = i;
                break;
            }
        }

        p1 = top_part(lm_one, inp[lm_one]);

        p2 = top_middle(rm_one - lm_one, inp[lm_one], inp[rm_one]);

        p3 = top_part(size - 1 - rm_one, inp[rm_one]);

        top = p1 + p2 + p3;
    }

    // 아래의 양 옆
    double bottom = size;

    if (first == 'C') {
        bottom -= 0.5;
    }
    if (last == 'C') {
        bottom -= 0.5;
    }

//    cout << "top: " << top << endl;
//    cout << "bottom: " << bottom << endl;
//    cout << "left: " << left_side << endl;
//    cout << "right: " << right_side << endl;

    return top + bottom + left_side + right_side;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(12);

    int n;
    cin >> n;

    string inp;
    cin >> inp;

    cout << area(inp) << endl;

    return 0;
}
