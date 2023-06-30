/* Code By [ junah ]
GitHub : [ junah201 ] */
#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define all(v) v.begin(), v.end()
#define INF LONG_LONG_MAX

int N, M;
vector<vector<int>> sort_tree;
vector<int> seg_tree;
vector<pair<int, int>> card, opers, new_opers;

// merge sort tree 초기 설정
void sort_tree_init(int node, int start, int end)
{
    if (start == end)
    {
        sort_tree[node].emplace_back(opers[start].first);
        return;
    }

    int mid = (start + end) / 2;
    sort_tree_init(node * 2, start, mid);
    sort_tree_init(node * 2 + 1, mid + 1, end);

    sort_tree[node].resize(sort_tree[node * 2].size() + sort_tree[node * 2 + 1].size());

    merge(all(sort_tree[node * 2]), all(sort_tree[node * 2 + 1]), sort_tree[node].begin());
}

// left ~ right 범위에 target 보다 크거나 같은 값의 개수를 리턴
int sort_tree_query(int node, int start, int end, int left, int right, int target)
{
    if (end < left || right < start)
        return 0;

    if (left <= start && end <= right)
    {
        // 이분탐색을 통해서 전체 개수에서 target 이상인 값이 처음으로 나오는 index를 구함
        // 이 index를 통해서 target보다 크거나 같은 값의 개수를 리턴
        return sort_tree[node].end() - lower_bound(all(sort_tree[node]), target);
    }

    int mid = (start + end) / 2;
    int lsum = sort_tree_query(node * 2, start, mid, left, right, target);
    int rsum = sort_tree_query(node * 2 + 1, mid + 1, end, left, right, target);

    return lsum + rsum;
}

// seg tree 초기 설정
void seg_tree_init(int node, int start, int end)
{
    if (start == end)
    {
        seg_tree[node] = new_opers[start].second;
        return;
    }

    int mid = (start + end) / 2;
    seg_tree_init(node * 2, start, mid);
    seg_tree_init(node * 2 + 1, mid + 1, end);

    seg_tree[node] = max(seg_tree[node * 2], seg_tree[node * 2 + 1]);
}

// left ~ right 범위에서 max index를 리턴
int seg_tree_query(int node, int start, int end, int left, int right)
{
    if (end < left || right < start)
        return -1;

    if (left <= start && end <= right)
    {
        return seg_tree[node];
    }

    int mid = (start + end) / 2;
    int lsum = seg_tree_query(node * 2, start, mid, left, right);
    int rsum = seg_tree_query(node * 2 + 1, mid + 1, end, left, right);

    return max(lsum, rsum);
}

// a <= k < b인 값이 나타나는 마지막 idx를 리턴
int get_last_idx(int a, int b)
{
    int left = lower_bound(all(new_opers), make_pair(a, (int)0)) - new_opers.begin();

    // a보다 크거나 같은 첫번째 값이 b보다 크거나 같을 경우
    // a <= k < b 인 값이 없는 것이므로 -1 리턴
    if (new_opers[left].first >= b)
        return -1;

    int right = lower_bound(all(new_opers), make_pair(b, (int)0)) - new_opers.begin() - 1;

    // b보다 크거나 같지 않는 마지막 값이 a보다 작을 경우
    // a <= K < b 인 값이 없는 것이므로 -1 리턴
    if (new_opers[right].first < a)
        return -1;

    int idx = seg_tree_query(1, 0, new_opers.size() - 1, left, right);

    return idx;
}

signed main()
{
    scanf("%lld %lld", &N, &M);
    int h = (int)ceil(log2(M + 1));
    int sort_tree_size = (1 << (h + 1));
    sort_tree.resize(sort_tree_size);
    card.resize(N);
    opers.resize(M);

    for (int i = 0; i < N; i++)
        scanf("%lld %lld", &card[i].first, &card[i].second);

    for (int i = 0; i < M; i++)
    {
        scanf("%lld", &opers[i].first);
        opers[i].second = -i;
    }

    sort_tree_init(1, 0, M - 1);

    // 좌표 압축 및 중복 제거
    sort(opers.begin(), opers.end());

    new_opers.emplace_back(opers[0]);

    for (size_t i = 1; i < opers.size(); i++)
        if (opers[i - 1].first != opers[i].first)
            new_opers.emplace_back(opers[i]);

    for (auto &[value, index] : new_opers)
        index = -index;

    h = (int)ceil(log2(new_opers.size() + 1));
    int seg_tree_size = (1 << (h + 1));
    seg_tree.resize(seg_tree_size);

    // seg tree에는 좌표압축한 명령들이 들어가는데
    // start ~ end 범위의 세그의 노드는 start ~ end 범위의 값들 중 idx가 가장 큰 값을 저장하고 있음
    // 이를 통해서 start ~ end 범위의 값 중 idx가 가장 큰 값을 logN으로 찾을 수 있음
    seg_tree_init(1, 0, new_opers.size() - 1);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        auto [a, b] = card[i];

        if (a == b)
        {
            ans += a;
            continue;
        }

        int idx = get_last_idx(min(a, b), max(a, b));

        // a <= k < b 인 카드가 없으면 앞면으로 시작
        if (idx == -1)
        {
            // 전체 범위에서 b <= k 인 카드의 개수를 구함
            // 구한 카드의 개수를 홀짝을 이용해서 최종적으로 앞면인지 뒷면인지 계산함
            int cnt = sort_tree_query(1, 0, M - 1, 0, M - 1, max(a, b));
            if (cnt % 2 == 0)
                ans += a;
            else
                ans += b;
        }
        // a <= k < b 인 카드가 있으면 뒷면으로 시작
        else
        {
            // a <= k < b 인 명령이 실행되고 나면 항상 결과 값은 b로 고정 됨
            // 따라서 a <= k < b 명령 뒤에 있는 b <= k인 명령의 개수를 구한 후
            // 구한 명령의 개수를 홀짝을 이용해서 최종적으로 앞면인지 뒷면인지 계산함
            int cnt = sort_tree_query(1, 0, M - 1, idx + 1, M - 1, max(a, b));
            if (cnt % 2 == 0)
                ans += max(a, b);
            else
                ans += min(a, b);
        }
    }

    printf("%lld", ans);

    return 0;
}
