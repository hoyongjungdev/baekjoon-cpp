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

int arr[8];

int cnt = 0;

struct vec {
    double x;
    double y;

    vec operator-(vec other) {
        return {this->x - other.x, this->y - other.y};
    }
};

vec coor(int num) {
    double degree = M_PI_4 * num;
    return {cos(degree) * arr[num], sin(degree) * arr[num]};
}

bool convex() {
    for (int i = 0; i < 8; i++) {
        vec prev = coor((i + 7) % 8);
        vec here = coor(i);
        vec next = coor((i + 1) % 8);

        vec a = here - prev;
        vec b = next - here;

//        printf("%.1lf %.1lf\n", a.x, a.y);
//        printf("%.1lf %.1lf\n", b.x, b.y);
//        printf("%.1lf\n", a.x * b.y - a.y * b.x);

        if (a.x * b.y - a.y * b.x < 0) {
            return false;
        }
    }

    return true;
}

void perm(int l) {
    if (l == 8) {
//        for (int i=0; i<8; i++) {
//            printf("%d ", arr[i]);
//        }
//        printf("\n");
//
//        for (int i=0; i<8; i++) {
//            vec c = coor(i);
//            printf("%.1lf,%.1lf ", c.x, c.y);
//        }
//        printf("\n");

        if (convex()) {
            cnt++;
//            printf("OK");
        }

//        printf("\n");

        return;
    }

//    if (cnt > 20) {
//        return;
//    }

    for (int i = l; i < 8; i++) {
        swap(arr[i], arr[l]);
        perm(l + 1);
        swap(arr[i], arr[l]);
    }
}

int main() {
    for (int i = 0; i < 8; i++) {
        scanf("%d", &arr[i]);
    }

    perm(0);
    printf("%d\n", cnt);

    return 0;
}