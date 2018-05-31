#include "template.cpp"



class unionfind
{
private:
    vector<long long> par;
    vector<long long> rank;
    vector<long long> counter;
public:
    unionfind(long long n);
    long long find(long long x);
    void unite(long long x, long long y);
    bool same(long long x, long long y);
    long long count(long long x);
};

// 初期化
unionfind::unionfind(long long n){
    for (long long i = 0; i < n; i++) {
        par.push_back(i);
        rank.push_back(0);
        counter.push_back(1);
    }
}

// 木の根を求める
long long unionfind::find(long long x) {
    if (par[x] == x) {
        return x;
    }
    else {
        return par[x] = find(par[x]);
    }
}

// xとyの属する集合を併合
void unionfind::unite(long long x, long long y) {
    x = find(x);
    y = find(y);
    if (x == y)return;
    
    if (rank[x] < rank[y]) {
        counter[y] += counter[x];
        counter[x] = counter[y];
        par[x] = y;
    }
    else {
        counter[y] += counter[x];
        counter[x] = counter[y];
        par[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

// xとyが同じ集合に属していたらtrue
bool unionfind::same(long long x, long long y) {
    return find(x) == find(y);
}

// xと同じ集合に属している要素数を返す
long long unionfind::count(long long x){
    return counter[find(x)];
}