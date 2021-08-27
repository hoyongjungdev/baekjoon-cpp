#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>

using namespace std;

// p11623
const int MAX_SIZE = 200005;
int selected[MAX_SIZE];

vector<int> solve(int size, vector<int> &knights) {
    set<int> group;
    int n = size / 2;

    for (int i = 1; i <= size; i++) {
        selected[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        group.insert(i);
        selected[knights[i]]++;
    }

    vector<int> addList;

    for (int i = n + 1; i <= size; i++) {
        if (selected[i] == 0) {
            addList.push_back(i);
        }
    }

    while (!addList.empty()) {
        vector<int> alt;

//        cout << "Group: ";
//        for (auto g: group) {
//            cout << g << " ";
//        }
//        cout << endl;
//
//        cout << "Selected: ";
//        for (int i=1; i<=size; i++) {
//            cout << selected[i] << " ";
//        }
//        cout << endl;

        for (auto a: addList) {
            group.insert(a);
            selected[knights[a]]++;

            auto it = group.find(knights[a]);
            if (it != group.end()) {
                int here = *it;
                int next = knights[here];
                group.erase(it);
                selected[next]--;

                if (selected[next] == 0) {
                    alt.push_back(next);
                }
            }
        }

        addList = alt;
    }

    return vector<int>(group.begin(), group.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(12);

    int n;
    cin >> n;

    vector<int> knights(2 * n + 1);

    for (int i = 1; i <= 2 * n; i++) {
        cin >> knights[i];
    }

    auto result = solve(2 * n, knights);

    for (auto r: result) {
        cout << r << " ";
    }

    cout << endl;

    return 0;
}
