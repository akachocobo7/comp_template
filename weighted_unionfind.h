using ll = long long;

class weighted_unionfind
{
private:
    vector<ll> par;
    vector<ll> rank;
    vector<ll> diff_weight;
public:
    weighted_unionfind(ll n);
    ll find(ll x);
    void unite(ll x, ll y, ll w);
    bool same(ll x, ll y);
    void swap(ll *x, ll *y);
    ll weight(ll x);
    ll diff(ll x, ll y);
};

// 初期化
weighted_unionfind::weighted_unionfind(ll n){
    for (ll i = 0; i < n; i++) {
        par.push_back(i);
        rank.push_back(0);
    }
    diff_weight.resize(n, 0);
}

// 木の根を求める
ll weighted_unionfind::find(ll x) {
    if (par[x] == x) {
        return x;
    }
    else {
        ll t = find(par[x]);
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = t;
    }
}

void weighted_unionfind::swap(ll *x, ll *y){
    ll tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

// xとyの属する集合を併合
void weighted_unionfind::unite(ll x, ll y, ll w) {
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
bool weighted_unionfind::same(ll x, ll y) {
    return find(x) == find(y);
}

ll weighted_unionfind::weight(ll x){
    find(x);
    return diff_weight[x];
}

ll weighted_unionfind::diff(ll x, ll y){
    return weight(y) - weight(x);
}
