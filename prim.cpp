using ll = long long;

class prim
{
private:
    vector<vector<ll>> list; // 隣接リスト
    vector<ll> mincost;   // 集合Xからの辺の最小コスト
    vector<bool> used;  // 頂点iが集合Xに含まれているか
    ll vertex;   // 頂点数
public:
    prim(ll n, ll infinity = 1e16); // nは頂点の数、infinityは初期化に使う値
    void add_edge(ll u, ll v, ll cost);    // 頂点uから頂点vにコストcostの辺を張る
    ll run();    // 最小全域木を求める
};

prim::prim(ll n, ll infinity){
    vertex = n;
    list.resize(n);
    mincost.resize(vertex);
    used.resize(vertex);
    
    for(ll i = 0; i < vertex; i++){
        list[i].resize(n);
        for(ll j = 0; j < vertex; j++){
            list[i][j] = infinity;
            mincost[i] = infinity;
            used[i] = false;
        }
    }
    
    mincost[0] = 0;
}

void prim::add_edge(ll u, ll v, ll cost){
    list[u][v] = cost;
    list[v][u] = cost;
}

ll prim::run(){
    ll res = 0;  // 最小全域木のコスト
    
    for(;;){
        ll v = -1;
        for(ll u = 0; u < vertex; u++){
            if(!used[u] && (v == -1 || mincost[u] < mincost[v])){
                v = u;
            }
        }
        
        if(v == -1) break;
        
        used[v] = true;
        res += mincost[v];
        
        for(ll u = 0; u < vertex; u++){
            mincost[u] = min(mincost[u], list[v][u]);
        }
    }
    
    return res;
}
