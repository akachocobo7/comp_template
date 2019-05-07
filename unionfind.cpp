using ll = long long;

class unionfind
{
private:
    vector<ll> par;
    vector<ll> rank;
    vector<ll> counter;
public:
    unionfind(ll n);
    ll find(ll x);
    void unite(ll x, ll y);
    bool same(ll x, ll y);
    ll count(ll x);
};

// 初期化
unionfind::unionfind(ll n){
    for (ll i = 0; i < n; i++) {
        par.push_back(i);
        rank.push_back(0);
        counter.push_back(1);
    }
}

// 木の根を求める
ll unionfind::find(ll x) {
    if (par[x] == x) {
        return x;
    }
    else {
        return par[x] = find(par[x]);
    }
}

// xとyの属する集合を併合
void unionfind::unite(ll x, ll y) {
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
bool unionfind::same(ll x, ll y) {
    return find(x) == find(y);
}

// xと同じ集合に属している要素数を返す
ll unionfind::count(ll x){
    return counter[find(x)];
}
