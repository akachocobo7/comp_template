#include "template.cpp"



class weighted_unionfind
{
private:
    vector<long long> par;
    vector<long long> rank;
    vector<long long> diff_weight;
public:
    weighted_unionfind(long long n);
    long long find(long long x);
    void unite(long long x, long long y, long long w);
    bool same(long long x, long long y);
    void swap(long long *x, long long *y);
    long long weight(long long x);
    long long diff(long long x, long long y);
};

// 初期化
weighted_unionfind::weighted_unionfind(long long n){
    for (long long i = 0; i < n; i++) {
        par.push_back(i);
        rank.push_back(0);
    }
    diff_weight.resize(n, 0);
}

// 木の根を求める
long long weighted_unionfind::find(long long x) {
    if (par[x] == x) {
        return x;
    }
    else {
        long long t = find(par[x]);
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = t;
    }
}

void weighted_unionfind::swap(long long *x, long long *y){
    long long tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

// xとyの属する集合を併合
void weighted_unionfind::unite(long long x, long long y, long long w) {
    w += weight(x);
    w -= weight(y);
    x = find(x);
    y = find(y);
    if (x == y)return;
    
    if (rank[x] < rank[y]) {
        swap(&x, &y);
        w = -w;
    }
    if(rank[x] == rank[y]){
        rank[x]++;
    }
    
    par[y] = x;
    diff_weight[y] = w;
}

// xとyが同じ集合に属していたらtrue
bool weighted_unionfind::same(long long x, long long y) {
    return find(x) == find(y);
}

long long weighted_unionfind::weight(long long x){
    find(x);
    return diff_weight[x];
}

long long weighted_unionfind::diff(long long x, long long y){
    return weight(y) - weight(x);
}