using ll = long long;
const ll INF = 1e18;

class Dinic {
private:
    struct edge {
        ll to, cap, rev;
    };
    vector<vector<edge>> list;  // グラフの隣接リスト
    vector<ll> level;    // sからの距離
    vector<ll> iter;     // どこまで調べ終わったか
    
public:
    Dinic(ll n) : list(n), level(n), iter(n){}
    
    void add_edge(ll from, ll to, ll cap){
        list[from].push_back({to, cap, (ll)list[to].size()});
        list[to].push_back({from, 0, (ll)list[from].size() - 1});
    }
    
    void bfs(ll s){
        level.assign(level.size(), -1);
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
    
    ll dfs(ll v, ll t, ll f){
        if(v == t) return f;
    
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
    
    ll max_flow(ll s, ll t){
        ll flow = 0;
    
        for(;;){
            bfs(s);
            if(level[t] < 0) return flow;
            
            iter.assign(iter.size(), 0);
            
            ll f;
            while((f = dfs(s, t, INF)) > 0){
                flow += f;
            }
        }
    }
};