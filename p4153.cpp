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

int arr[3];

int sq(int num) {
    return num * num;
}

int main() {
    while (true) {
        scanf("%d%d%d", &arr[0], &arr[1], &arr[2]);

        if (arr[0] == 0) {
            break;
        }

        sort(arr, arr + 3);

        if (sq(arr[0]) + sq(arr[1]) == sq(arr[2])) {
            printf("right\n");
        } else {
            printf("wrong\n");
        }
    }

    return 0;
}