using ll = long long;
const ll INF = 1e16;

class bellmanford
{
private:
    struct edge {
        ll to, cost;
    };
    ll vertex;    // 頂点数
    vector<vector<edge>> list;    // 隣接リスト
    vector<ll> distance;    // 距離
public:
    bellmanford(ll n);   // nは頂点数
    void add_edge(ll v1, ll v2, ll cost);    // 頂点v1から頂点v2に辺を張る
    bool run(ll s);        // sは開始地点。返り値がfalseのとき負の閉路あり
    ll get_distance(ll v);    // 頂点vへの距離を返す
};

bellmanford::bellmanford(ll n){
    list.resize(n);
    vertex = n;
}

void bellmanford::add_edge(ll v1, ll v2, ll cost) {
    list[v1].push_back({ v2, cost });
}

bool bellmanford::run(ll s) {
    distance = vector<ll>(vertex, INF);
    distance[s] = 0;    //開始点の距離は0
    
    for (ll i = 0; i < vertex; i++) {
        for (ll v = 0; v < vertex; v++) {
            for (auto edge : list[v]) {
                if (distance[v] != INF && distance[edge.to] > distance[v] + edge.cost) {
                    distance[edge.to] = distance[v] + edge.cost;
                    if (i == vertex - 1) {
                        //return false;
                        distance[edge.to] = -INF;
                    }
                }
            }
        }
    }
    return true;
}

ll bellmanford::get_distance(ll v) {
    return distance[v];
}
