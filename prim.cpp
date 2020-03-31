using ll = long long;

class Prim {
private:
    using P = pair<ll, ll>;
    vector<vector<P>> g;
    vector<bool> used;  // 頂点iが集合Xに含まれているか
    ll n;
    
public:
    Prim(ll n) : n(n), g(n){}
    
    void add_edge(ll u, ll v, ll cost){
        g[u].push_back({cost, v});
        g[v].push_back({cost, u});
    }
    
    ll run(){
        ll res = 0;
        priority_queue<P, vector<P>, greater<P>> que;
        used.assign(n, false);
        que.push({0, 0});
        while(!que.empty()){
            auto tmp = que.top(); que.pop();
            ll cost = tmp.first, v = tmp.second;
            if(used[v]) continue;
            used[v] = true;
            res += cost;
            for(auto &e : g[v]){
                que.push(e);
            }
        }
        return res;
    }
};