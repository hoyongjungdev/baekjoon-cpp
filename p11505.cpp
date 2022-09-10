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

ll arr[1000001];
ll bin[1005];

int n, m, k;

int sq;

const int MOD = 1000000007;

void update(int idx, int value) {
    arr[idx] = value;

    int start = idx / sq * sq;
    int end = min(n-1, start + sq - 1);

    ll result = 1;

    for (int i = start; i <= end; i++) {
        result = (result * arr[i]) % MOD;
//        printf(" > %d %d\n", i, arr[i]);
    }

    bin[idx / sq] = result;
}

ll mult(int a, int b) {
    if (n <= 4) {
        ll result = 1;

        for (int i = a; i <= b; i++) {
            result = (result * arr[i]) % MOD;
        }

        return result;
    } else {
        int start = a;
        int end = b;

        ll result = 1;

        while (start % sq != 0 && start <= end) {
            result = (result * arr[start]) % MOD;

            start++;
        }

        while ((end + 1) % sq != 0 && start <= end) {
            result = (result * arr[end]) % MOD;

            end--;
        }

//        printf("> %d %d\n", start, end);

        if (start % sq == 0) {
            while (start <= end) {
                result = (result * bin[start / sq]) % MOD;

                start += sq;
            }
        }

        return result;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    sq = sqrt(n);

    for (int i = 0; i < 1005; i++) {
        bin[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);

        arr[i] = num;

        bin[i / sq] = (bin[i / sq] * arr[i]) % MOD;
    }

//    for (int j=0; j<5; j++) {
//        printf("%d ", arr[j]);
//    }
//    printf("\n");
//    for (int i=0; i<5; i++) {
//        printf("%d ", bin[i]);
//    }
//    printf("\n");

    for (int i = 0; i < m + k; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        if (a == 1) {
            b--;

            update(b, c);
        } else {
            b--;
            c--;

            printf("%lld\n", mult(b, c));
        }

//        for (int j=0; j<5; j++) {
//            printf("%d ", arr[j]);
//        }
//        printf("\n");
//        for (int j=0; j<5; j++) {
//            printf("%d ", bin[j]);
//        }
//        printf("\n");
    }

    return 0;
}