#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

typedef pair<int,int> pii;

vector<int> arr;

int random(int mx) {
    int rand_max = 30000;

    int a = rand_max * (rand()%rand_max) + (rand()%rand_max);
    return a % (mx + 1);
}

void quick_sort(int from, int to) {
    if (from >= to) {
        return;
    }

    int size = to - from + 1;

    if (size <= 5) {
        sort(arr.begin() + from, arr.begin() + (to + 1));
        return;
    }

    int pivot_idx = from + random(size - 1);
    int pivot = arr[pivot_idx];

    swap(arr[from], arr[pivot_idx]);

    int s = from + 1;
    int e = to;

    while (s <= e) {
        while (s <= to && arr[s] <= pivot) {
            s++;
        }

        while (e > from && arr[e] >= pivot) {
            e--;
        }

        if (s > e) {
            swap(arr[from], arr[e]);
        } else if (s < e) {
            swap(arr[s], arr[e]);
        }
    }

    quick_sort(from, e-1);
    quick_sort(e+1, to);
}

int main() {
    srand(500);

    int n;
    scanf("%d", &n);

    int num;
    for (int i=0; i<n; i++) {
        scanf("%d", &num);
        arr.push_back(num);
    }

    quick_sort(0, n-1);

    for (int i=0; i<n; i++) {
        printf("%d\n", arr[i]);
    }
}