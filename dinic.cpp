using ll = long long;

class dinic
{
private:
    ll inf;  // 初期化に使う値
    struct edge {
        ll to, cap, rev;
    };
    vector<vector<edge>> list;  // グラフの隣接リスト
    vector<ll> level;    // sからの距離
    vector<ll> iter;     // どこまで調べ終わったか
public:
    dinic(ll n, ll infinity = 1e16);    // nは頂点の数、infinityは初期化に使う値
    void add_edge(ll from, ll to, ll cap); // fromからtoへ容量capの辺をはる
    void bfs(ll s);  // sからの最短距離を求める
    ll dfs(ll v, ll t, ll f);   // 増加パスをdfsで探す
    ll max_flow(ll s, ll t);   // sからtへの最大流を求める
};

dinic::dinic(ll n, ll infinity){
    list.resize(n);
    level.resize(n);
    iter.resize(n);
    inf = infinity;
}

void dinic::add_edge(ll from, ll to, ll cap){
    list[from].push_back((edge){to, cap, (ll)list[to].size()});
    list[to].push_back((edge){from, 0, (ll)list[from].size() - 1});
}

void dinic::bfs(ll s){
    for(ll i = 0; i < level.size(); i++){
        level[i] = -1;
    }
    queue<ll> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()){
        ll v = que.front(); que.pop();
        for(auto &x : list[v]){
            if(x.cap > 0 && level[x.to] < 0){
                level[x.to] = level[v] + 1;
                que.push(x.to);
            }
        }
    }
}

ll dinic::dfs(ll v, ll t, ll f){
    if(v == t)return f;
    
    for(ll &i = iter[v]; i < list[v].size(); i++){
        edge &e = list[v][i];
        if(e.cap > 0 && level[v] < level[e.to]){
            ll d = dfs(e.to, t, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                list[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

ll dinic::max_flow(ll s, ll t){
    ll flow = 0;
    
    for(;;){
        bfs(s);
        if(level[t] < 0)return flow;
        
        for(ll i = 0; i < iter.size(); i++){
            iter[i] = 0;
        }
        
        ll f;
        while((f = dfs(s, t, inf)) > 0){
            flow += f;
        }
    }
}
