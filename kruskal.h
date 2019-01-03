using ll = long long;

/* unionfindを使います */

class kruskal
{
private:
    struct edge{
        ll cost, u, v;
        
        bool operator<(const edge& e1) const {
            return cost < e1.cost;
        }
    };
    vector<edge> es;
    ll vertex;    // vertexは頂点の数
public:
    kruskal(ll n);   // nは頂点数
    void add_edge(ll u, ll v, ll cost);    // 頂点uから頂点vにコストcostの辺を貼る
    ll run();
};

kruskal::kruskal(ll n){
    vertex = n;
}

void kruskal::add_edge(ll u, ll v, ll cost){
    es.push_back({cost, u, v});
    es.push_back({cost, v, u});
}

ll kruskal::run(){
    sort(es.begin(), es.end());
    
    unionfind uni(vertex);
    ll res = 0;
    
    for(auto e : es){
        if(!uni.same(e.u, e.v)){
            uni.unite(e.u, e.v);
            res += e.cost;
        }
    }
    
    return res;
}
