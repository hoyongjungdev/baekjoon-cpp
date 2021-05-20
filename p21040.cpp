#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> scores(vector<int> &nums, long long interval, int n) {
    auto min_score = 1987654321;
    auto last = nums[0];
    auto cnt = 1;

    for (int i = 1; i < n; i++) {
        if (nums[i] - last >= interval) {
            min_score = min(min_score, nums[i] - last);
            last = nums[i];
            cnt++;

            //printf("%d %d %d\n", last, min_score, cnt);
        }
    }


    return make_pair(cnt, min_score);
}

int main() {
    int n, k;

    scanf("%d", &n);
    scanf("%d", &k);

    auto nums = vector<int>(n);

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        nums[i] = num;
    }

    sort(nums.begin(), nums.end());

    long long lo = 1;
    long long hi = nums[n - 1] - nums[0] + 1;

    if (hi == 1) {
        printf("0\n");

        return 0;
    }

    while (lo < hi) {
        auto mid = (lo + hi) / 2;

        auto result = scores(nums, mid, n);

        if (result.first >= k) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    auto result = scores(nums, hi - 1, n);

    printf("%d\n", result.second);

    return 0;
}

