#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
int a[4005], b[4005], c[4005], d[4005];

vector<int> one, two;

int main() {
    scanf("%d", &n);

    int ai, bi, ci, di;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &ai, &bi, &ci, &di);
        a[i] = ai;
        b[i] = bi;
        c[i] = ci;
        d[i] = di;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = a[i] + b[j];

            one.push_back(sum);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = c[i] + d[j];

            two.push_back(sum);
        }
    }

    sort(two.begin(), two.end());

    ll result = 0;

    for (int i=0; i<one.size(); i++) {
        auto a = lower_bound(two.begin(), two.end(), -one[i]);
        auto b = upper_bound(two.begin(), two.end(), -one[i]);

        result += b-a;
    }

    printf("%lld\n", result);

    return 0;
}