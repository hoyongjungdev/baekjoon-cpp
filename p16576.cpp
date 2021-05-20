#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int MAX_NUM = 505;

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);

    int r, c;
    scanf("%d", &r);
    scanf("%d", &c);

    int l = max(r, c);
    int s = min(r, c);

    if (l <= 2) {
        printf("0\n");
        return 0;
    }

    char map[MAX_NUM][MAX_NUM];

    getchar();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            map[i][j] = getchar();
        }
        getchar();
    }

    int cnt = 0;

    if (s == 1) {
        if (r == 1) {
            for (int i = 1; i < c - 1; i++) {
                if (map[0][i] == '.') {
                    cnt++;
                }
            }
        } else {
            for (int i = 1; i < r - 1; i++) {
                if (map[i][0] == '.') {
                    cnt++;
                }
            }
        }

        printf("%d\n", cnt);
        return 0;
    }

    if (s == 2) {
        if (r == 2) {
            for (int i = 1; i < c - 1; i++) {
                if (map[0][i] == '.' && map[1][i] == '.') {
                    cnt++;
                }
            }
        } else {
            for (int i = 1; i < r - 1; i++) {
                if (map[i][0] == '.' && map[i][1] == '.') {
                    cnt++;
                }
            }
        }

        printf("%d\n", cnt);
        return 0;
    }


    for (int i = 1; i < r - 1; i++) {
        for (int j = 1; j < c - 1; j++) {
            if (map[i][j] == '.') {
                cnt++;
            }
        }
    }

    bool found = false;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int edge = 0;

            if (i == 0 || i == r - 1) {
                edge++;
            }

            if (j == 0 || j == c - 1) {
                edge++;
            }

            if (edge == 1) {
                if (map[i][j] == '#') {
                    found = true;
                }
            }
        }
    }

    if (!found) {
        cnt++;
    }

    printf("%d\n", cnt);

    return 0;
}
