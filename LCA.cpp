using ll = long long;

class LCA {
    ll n, log_n;
    vector<vector<pair<ll, ll>>> parent;
    vector<ll> depth;
    vector<bool> used;
    
private:
    void dfs(const vector<vector<pair<ll, ll>>> &g, ll now, ll par, ll d, ll cost){
        parent[0][now].first = par;
        parent[0][now].second = cost;
        depth[now] = d;
        used[now] = true;
        
        for(auto &edge : g[now]){
            ll child = edge.first, c = edge.second;
            if(child != par){
                dfs(g, child, now, d + 1, c);
            }
        }
    }
    
public:
    LCA(const vector<vector<pair<ll, ll>>> &g) : n(g.size()), log_n(0), depth(n), used(n) {
        for(ll v = n; v > 0; v /= 2){
            log_n++;
        }
        parent.resize(log_n, vector<pair<ll, ll>>(n));
        for(ll i = 0; i < n; i++){
            if(!used[i]){
                dfs(g, i, -1, 0, 0);
            }
        }
        for(ll k = 0; k < log_n - 1; k++){
            for(ll v = 0; v < n; v++){
                if(parent[k][v].first < 0){
                    parent[k + 1][v] = parent[k][v];
                }
                else{
                    parent[k + 1][v].first = parent[k][parent[k][v].first].first;
                    parent[k + 1][v].second = max(parent[k][v].second, parent[k][parent[k][v].first].second);
                }
            }
        }
    }
    
    ll query(ll u, ll v){
        if(depth[u] > depth[v]){
            swap(u, v);
        }
        ll res = 0;
        for(ll k = 0; k < log_n; k++){
            if(((depth[v] - depth[u]) >> k) & 1){
                res = max(res, parent[k][v].second);
                v = parent[k][v].first;
            }
        }
        if(u == v){
            return res;
        }
        for(ll k = log_n - 1; k >= 0; k--){
            if(parent[k][u] != parent[k][v]){
                res = max(res, parent[k][u].second);
                res = max(res, parent[k][v].second);
                u = parent[k][u].first;
                v = parent[k][v].first;
            }
        }
        return res;
    }
};