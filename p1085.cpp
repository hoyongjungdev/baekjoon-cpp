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

int main() {
    int x, y, w, h;
    scanf("%d%d%d%d", &x, &y, &w, &h);

    int dist = 10000;

    dist = min(dist, x);
    dist = min(dist, y);
    dist = min(dist, w-x);
    dist = min(dist, h-y);

    printf("%d\n", dist);

    return 0;
}