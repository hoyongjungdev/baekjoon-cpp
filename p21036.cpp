#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct candidate {
    int score;
    int index;

public:
    candidate(int score, int index) : score(score), index(index) {

    }

    bool operator<(candidate other) const {
        if (score == other.score) {
            return index < other.index;
        }

        return score > other.score;
    }
};

int score_by_distance(int distance) {
    return distance / 2 + 1;
}

int max_score(vector<int> &stores, int n, int k) {
    int size = stores.size();

    if (size == 1) {
        return n;
    }

    vector<int> scores(size);

    int distance = stores[1] - stores[0];
    scores[0] = stores[0] - 1 + score_by_distance(distance);

    for (int i = 1; i < size - 1; i++) {
        int left_distance = stores[i] - stores[i - 1];
        int right_distance = stores[i + 1] - stores[i];

        scores[i] = score_by_distance(left_distance) + score_by_distance(right_distance) - 1;
    }

    distance = stores[size - 1] - stores[size - 2];
    scores[size - 1] = n - stores[size - 1] + score_by_distance(distance);

    set<candidate> s;

    for (int i = 0; i < size; i++) {
        s.insert(candidate(scores[i], i));
    }

    int score_sum = 0;
    int cnt = 0;

    while (!s.empty() && cnt < k) {
        // debug
//        for (auto element: s) {
//            printf("(%d, %d) ", element.index, element.score);
//        }


        candidate c = *s.begin();
        int here = c.index;

        //printf("\nscore: %d, index: %d\n", c.score, c.index);

        s.erase(s.begin());

        score_sum += c.score;
        cnt++;

        if (here > 0 && (stores[here] - stores[here - 1]) % 2 == 0) {
            candidate left(scores[here - 1], here - 1);
            auto il = s.find(left);

            if (il != s.end()) {
                s.erase(il);
                scores[here - 1]--;
                s.insert(candidate(scores[here - 1], here - 1));
            }
        }

        if (here < size && (stores[here] - stores[here + 1]) % 2 == 0) {
            candidate right(scores[here + 1], here + 1);
            auto ir = s.find(right);

            if (ir != s.end()) {
                s.erase(ir);
                scores[here + 1]--;
                s.insert(candidate(scores[here + 1], here + 1));
            }
        }
    }

    return score_sum;
}

int main() {
    int n, m, k;

    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);

    vector<int> stores(m);

    for (int i = 0; i < m; i++) {
        int num;
        scanf("%d", &num);
        stores[i] = num;
    }


    set<int> s( stores.begin(), stores.end() );
    stores.assign( s.begin(), s.end() );

    printf("%d\n", max_score(stores, n, k));

    return 0;
}

