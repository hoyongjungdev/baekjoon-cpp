#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

int n;
int arr[200005];

int gcd(int start, int end) {
    int num = arr[start];

    for (int i = start + 1; i <= end; i++) {
        int a = num;
        int b = arr[i];

        if (a < b) {
            swap(a, b);
        }

        while (b != 0) {
            int k = a % b;
            a = b;
            b = k;
        }

        num = a;
    }

    return num;
}

int beauty(int start, int end) {
    int size = end - start + 1;

    if (size == 1) {
        return arr[start];
    }

    int mid = (start + end - 1) / 2;

    int gcd_left = gcd(start, mid);
    int gcd_right = gcd(mid + 1, end);

    int result = max(
            gcd_left + beauty(mid + 1, end),
            gcd_right + beauty(start, mid)
    );

    //printf("%d %d %d\n", start, end, result);

    return result;
}

int main() {
    scanf("%d", &n);

    int num;
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        arr[i] = num;
    }

    int result = beauty(0, n - 1);

    printf("%d\n", result);

    return 0;
}
