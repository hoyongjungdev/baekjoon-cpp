#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int n, m;
vector<int> nums;

void perm() {
    int size = nums.size();

    if (size == m) {
        for (int i = 0; i < size; i++) {
            printf("%d ", nums[i]);
        }
        printf("\n");
        return;
    }

    int last = 0;

    if (size > 0) {
        last = nums[size - 1];
    }

    for (int i = last + 1; i <= n; i++) {
        nums.push_back(i);
        perm();
        nums.pop_back();
    }
}

int main() {
    scanf("%d%d", &n, &m);

    nums = vector<int>();

    perm();

    return 0;
}
