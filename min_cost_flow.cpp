using ll = long long;

// 最小費用流
class min_cost_flow {
private:
    struct edge{
        ll to, cap, cost, rev;
    };
    ll n;
    vector<vector<edge>> g;     // グラフの隣接リスト
    vector<ll> dist;     // 最短距離
    vector<ll> prev_v, prev_e;   // 直前の頂点と辺
public:
    min_cost_flow(ll n) : n(n), g(n), dist(n), prev_v(n), prev_e(n){}
    
    void add_edge(ll from, ll to, ll cap, ll cost){
        g[from].push_back({to, cap, cost, (ll)g[to].size()});
        g[to].push_back({from, 0, -cost, (ll)g[from].size() - 1});
    }
    
    // sからtへの流量fの最小費用流を求める。流せない場合は-1を返す。
    ll get_min_cost_flow(ll s, ll t, ll f){
        ll res = 0;
    
        while(f > 0){
            dist.assign(n, INF);
            dist[s] = 0;
            bool update = true;
            while(update){
                update = false;
                for(ll v = 0; v < n; v++){
                    if(dist[v] == INF) continue;
                    for(ll i = 0; i < g[v].size(); i++){
                        edge &e = g[v][i];
                        if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
                            dist[e.to] = dist[v] + e.cost;
                            prev_v[e.to] = v;
                            prev_e[e.to] = i;
                            update = true;
                        }
                    }
                }
            }
            
            if(dist[t] == INF) return -1;
            
            ll d = f;
            for(ll v = t; v != s; v = prev_v[v]){
                d = min(d, g[prev_v[v]][prev_e[v]].cap);
            }
            f -= d;
            res += d * dist[t];
            for(ll v = t; v != s; v = prev_v[v]){
                edge &e = g[prev_v[v]][prev_e[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        
        return res;
    }
};
