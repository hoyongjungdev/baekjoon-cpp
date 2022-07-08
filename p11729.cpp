#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int n;

void hanoi(int size, int a, int b, int c) {
    if (size == 1) {
        printf("%d %d\n", a, c);
        return;
    }

    hanoi(size - 1, a, c, b);
    hanoi(1, a, b, c);
    hanoi(size - 1, b, a, c);
}

int main() {
    scanf("%d", &n);

    int result = (1 << n) - 1;
    printf("%d\n", result);

    hanoi(n, 1, 2, 3);
    return 0;
}
