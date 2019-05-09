using ll = long long;
const ll INF = 1e18;

template <typename T>
class bellmanford {
private:
    struct edge {
        int to;
        T cost;
    };
    int n;
    vector<vector<edge>> g;
    vector<T> dist;
    
public:
    bellmanford(int n) : n(n), g(n){}
    
    void add_edge(int v1, int v2, T cost){
        g[v1].push_back({ v2, cost });
    }
    
    // 負の閉路があるときfalseを返す
    bool run(int s){
        dist = vector<T>(n, INF);
        dist[s] = 0;    //開始点の距離は0
        
        for (int i = 0; i < n; i++) {
            for (int v = 0; v < n; v++) {
                for (auto& e : g[v]) {
                    if (dist[v] != INF && dist[e.to] > dist[v] + e.cost) {
                        dist[e.to] = dist[v] + e.cost;
                        if (i == n - 1) {
                            // return false;
                            dist[e.to] = -INF;
                        }
                    }
                }
            }
        }
        return true;
    }
    
    T get_distance(int v){
        return dist[v];
    }
};
