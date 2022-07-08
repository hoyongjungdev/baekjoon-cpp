#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int arr[130][130];
int white = 0;
int blue = 0;

void div(int y, int x, int size) {
    int start = arr[y][x];

    if (size == 1) {
        if (start == 0) {
            white++;
        } else {
            blue++;
        }

        return;
    }

    bool diff = false;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[y+i][x+j] != start) {
                diff = true;
            }
        }
    }

    if (diff) {
        int m = size / 2;
        div(y, x, m);
        div(y + m, x, m);
        div(y, x + m, m);
        div(y + m, x + m, m);
    } else {
        if (start == 0) {
            white++;
        } else {
            blue++;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int num;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &num);
            arr[i][j] = num;
        }
    }

    div(0, 0, n);

    printf("%d\n%d\n", white, blue);

    return 0;
}
