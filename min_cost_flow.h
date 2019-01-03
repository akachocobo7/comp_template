using ll = long long;

// 最小費用流
class min_cost_flow
{
private:
    struct edge{
        ll to, cap, cost, rev;
    };
    ll vertex;   // 頂点数
    ll infinity; // 初期化に使う値
    vector<vector<edge>> graph;     // グラフの隣接リスト
    vector<ll> distance;     // 最短距離
    vector<ll> prev_v, prev_e;   // 直前の頂点と辺
public:
    min_cost_flow(ll v, ll inf = 1e16);     // vは頂点の数, infは初期化に使う値
    void add_edge(ll from, ll to, ll cap, ll cost);     // fromからtoへ向かう容量cap、コストcostの辺を張る
    ll get_min_cost_flow(ll s, ll t, ll f);     // sからtへの流量fの最小費用流を求める。流せない場合は-1を返す。
};

min_cost_flow::min_cost_flow(ll v, ll inf){
    vertex = v;
    infinity = inf;
    graph.resize(vertex);
    distance.resize(vertex);
    prev_v.resize(vertex);
    prev_e.resize(vertex);
}

void min_cost_flow::add_edge(ll from, ll to, ll cap, ll cost){
    graph[from].push_back((edge){to, cap, cost, (ll)graph[to].size()});
    graph[to].push_back((edge){from, 0, -cost, (ll)graph[from].size() - 1});
}

ll min_cost_flow::get_min_cost_flow(ll s, ll t, ll f){
    ll res = 0;
    
    while(f > 0){
        distance.assign(vertex, infinity);
        distance[s] = 0;
        bool update = true;
        while(update){
            update = false;
            for(ll v = 0; v < vertex; v++){
                if(distance[v] == infinity) continue;
                for(ll i = 0; i < graph[v].size(); i++){
                    edge &e = graph[v][i];
                    if(e.cap > 0 && distance[e.to] > distance[v] + e.cost){
                        distance[e.to] = distance[v] + e.cost;
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        update = true;
                    }
                }
            }
        }
        
        if(distance[t] == infinity) return -1;
        
        ll d = f;
        for(ll v = t; v != s; v = prev_v[v]){
            d = min(d, graph[prev_v[v]][prev_e[v]].cap);
        }
        f -= d;
        res += d * distance[t];
        for(ll v = t; v != s; v = prev_v[v]){
            edge &e = graph[prev_v[v]][prev_e[v]];
            e.cap -= d;
            graph[v][e.rev].cap += d;
        }
    }
    
    return res;
}
