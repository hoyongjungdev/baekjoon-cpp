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

int arr[100001];
int mnBin[400];
int mxBin[400];

int n, m;

int sq;

void mm(int a, int b) {
    int mn = 1000000001;
    int mx = 0;

    if (n <= 5) {
        for (int i = a; i <= b; i++) {
            mn = min(mn, arr[i]);
            mx = max(mx, arr[i]);
        }
    } else {
        int start = a;
        int end = b;

        while (start % sq != 0 && start <= end) {
            mn = min(mn, arr[start]);
            mx = max(mx, arr[start]);

            start++;
        }

        while ((end+1) % sq != 0 && start <= end) {
            mn = min(mn, arr[end]);
            mx = max(mx, arr[end]);

            end--;
        }

        //printf("> %d %d\n", start, end);

        if (start % sq == 0) {
            while (start <= end) {
                mn = min(mn, mnBin[start/sq]);
                mx = max(mx, mxBin[start/sq]);

                start += sq;
            }
        }
    }

    printf("%d %d\n", mn, mx);
}

int main() {
    scanf("%d%d", &n, &m);

    sq = sqrt(n);

    for (int i = 0; i < 400; i++) {
        mnBin[i] = 1000000001;
        mxBin[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);

        arr[i] = num;

        mnBin[i / sq] = min(mnBin[i / sq], arr[i]);
        mxBin[i / sq] = max(mxBin[i / sq], arr[i]);
    }

//    for (int i = 0; i < 10; i++) {
//        printf("> %d %d\n", mnBin[i], mxBin[i]);
//    }


    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        a--;
        b--;

        mm(a, b);
    }

    return 0;
}