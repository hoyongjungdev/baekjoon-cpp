#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#include <map>
#include <unordered_map>

using namespace std;

typedef long long int ll;

vector<string> words;

struct Node {
    Node *m[26];
    bool finish = false;

    ~ Node() {
        for (int i = 0; i < 26; i++) {
            if (m[i] != nullptr) {
                delete m[i];
            }
        }
    }

    Node() {
        for (int i = 0; i < 26; i++) {
            m[i] = nullptr;
        }
    }

    void construct(const char *s) {
        if (s[0] == '\0') {
            finish = true;
            return;
        }

        int c = s[0] - 'a';

        if (m[c] == nullptr) {
            m[c] = new Node;
            m[c]->finish = false;
        }

        m[c]->construct(s + 1);
    }

    int size() {
        int sum = 0;
        for (int i = 0; i < 26; i++) {
            if (m[i] != nullptr) {
                sum++;
            }
        }

        return sum;
    }

    int check(const char *s, bool noSkip) {
        if (s[0] == '\0') {
            return 0;
        }

        int c = s[0] - 'a';

        int ans = 0;

        if (this->size() == 1 && !finish && !noSkip) {
            ans = 1;
        }

        return ans + m[c]->check(s + 1, false);
    }
};

int main() {
    int n;

    while (scanf("%d", &n) != EOF) {
        words.clear();

        for (int i = 0; i < n; i++) {
            string word;
            cin >> word;

            words.push_back(word);
        }

        Node root;

        for (string &word: words) {
//            cout << word << endl;
            root.construct(word.c_str());
        }

        double sizeSum = 0;
        double skippedSum = 0;

        for (string &word: words) {
//            cout << word << endl;

            int size = word.size();
            int skipped = root.check(word.c_str(), true);

//            printf(" > %d %d\n", size, skipped);

            sizeSum += size;
            skippedSum += skipped;
        }

        printf("%.2lf\n", (sizeSum - skippedSum) / words.size());
    }

    return 0;
}