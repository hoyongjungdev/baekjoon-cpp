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

int a[200005];
int b[200005];

void calculatePi(vector<int> &pi, vector<int> &str) {
    pi[0] = -1;
    for (int i = 1, j = -1; i < str.size(); i++) {
        while (j >= 0 && str[i] != str[j + 1]) {
            j = pi[j];
        }
        if (str[i] == str[j + 1]) {
            pi[i] = ++j;
        } else {
            pi[i] = -1;
        }
    }
}

vector<int> kmp(vector<int> &text, vector<int> &pattern) {
    vector<int> pi(pattern.size()), ans;
    if (pattern.size() == 0) {
        return ans;
    }
    calculatePi(pi, pattern);
    for (int i = 0, j = -1; i < text.size(); i++) {
        while (j >= 0 && text[i] != pattern[j + 1]) {
            j = pi[j];
        }
        if (text[i] == pattern[j + 1]) {
            j++;
            if (j + 1 == pattern.size()) {
                ans.push_back(i - j);
                j = pi[j];
            }
        }
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);

    int num;

    for (int i = 0; i < n; i++) {
        scanf("%d", &num);

        a[i] = num;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &num);

        b[i] = num;
    }

    sort(a, a + n);
    sort(b, b + n);

    vector<int> text(2 * n);
    vector<int> pattern(n);

    int MAX_NUM = 360000;

    for (int i = 0; i < n - 1; i++) {
        text[i + n] = text[i] = a[i + 1] - a[i];
        pattern[i] = b[i + 1] - b[i];
    }

    text[2 * n - 1] = text[n - 1] = (a[0] - a[n - 1] + MAX_NUM) % MAX_NUM;
    pattern[n - 1] = (b[0] - b[n - 1] + MAX_NUM) % MAX_NUM;

//    printf("> ");
//    for (int t: text) {
//        printf("%d ", t);
//    }
//    printf("\n");
//
//    printf("> ");
//    for (int p: pattern) {
//        printf("%d ", p);
//    }
//    printf("\n");

    vector<int> ans = kmp(text, pattern);

//    printf("> ");
//    for (int a: ans) {
//        printf("%d ", a);
//    }
//    printf("\n");

    if (!ans.empty()) {
        printf("possible\n");
    } else {
        printf("impossible\n");
    }

    return 0;
}