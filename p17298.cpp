#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>

using namespace std;

typedef long long ll;

int n;
int arr[1000005];
int result[1000005];

int main() {
    scanf("%d", &n);

    int num;
    for (int i=0; i<n; i++) {
        scanf("%d", &num);
        arr[i] = num;
    }

    stack<int> s;



    for (int i=n-1; i>=0; i--) {
        num = arr[i];
        while (!s.empty() && s.top() <= num) {
            s.pop();
        }

        if (s.empty()) {
            result[i] = -1;
        } else {
            result[i] = s.top();
        }

        s.push(num);
    }

    for (int i=0; i<n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
