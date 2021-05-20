#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int n;

int pow(int k) {
    int result = 1;
    for (int i = 0; i < k; i++) {
        result *= 2;
    }

    return result;
}

map<int, vector<string>> subseq(string s) {
//    cout << "subseq: " << s << endl;
    int len = s.size();
    int end = pow(len) - 1;

    map<int, vector<string>> m;

    for (int i = 1; i <= end; i++) {
        char now[20];

        int cnt = 0;

        for (int j = 0; j < 15; j++) {
            if ((i & (1 << j)) != 0) {
                now[cnt] = s[j];
                cnt++;
            }
        }
        now[cnt] = 0;

        string sub = string(now);
        int l = cnt - 1;

        if (m.find(l) == m.end()) {
            m[l] = vector<string>();
        }

        m[l].push_back(sub);
    }

    for (auto &p : m) {
        sort(m[p.first].begin(), m[p.first].end());
    }

//    for (auto a : m[2]) {
//        cout << a << endl;
//    }

    return m;
}

int longest(vector<string> &names, vector<string> &before, int index) {
    if (index == n) {
        for (int i = 255; i >= 0; i--) {
            if (before[i] != "*") {
                //cout << before[i] << endl;
                return i;
            }
        }
        return -1;
    }

    string s = names[index];

    auto sub = subseq(s);

    vector<string> possible(256);

    for (int i = 0; i <= 255; i++) {
        possible[i] = "*";
    }

    for (int i = 0; i <= 255; i++) {
        string b = before[i];

        if (b == "*") {
            continue;
        }

        for (auto &subp: sub) {
            auto it = upper_bound(subp.second.begin(), subp.second.end(), b);

            if (it != subp.second.end()) {
                string low = *it;
                int l = i + low.size();

                if (possible[l] == "*") {
                    possible[l] = low;
                } else {
                    possible[l] = min(possible[l], low);
                }
            }
        }
    }

//    for (int i=0; i<=255; i++) {
//        if (possible[i] != "*") {
//            cout << i << " " << possible[i] << endl;
//        }
//    }
    int result = longest(names, possible, index + 1);
//    cout << "index: " << index << endl;
//    cout << "result: " << result << endl;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    vector<string> names;

    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        names.push_back(name);
    }

    vector<string> before(256);
    before[0] = "";
    for (int i = 1; i <= 255; i++) {
        before[i] = "*";
    }

    cout << longest(names, before, 0) << endl;

    return 0;
}
