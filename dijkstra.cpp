using ll = long long;
const ll INF = 1e18;


template <typename T>
class dijkstra {
private:
    using P = pair<T, int>;
    struct edge{
        int to;
        T cost;
    };
    int n;
    vector<vector<edge>> g;
    vector<T> dist;
    
public:
    dijkstra(int n) : n(n), g(n), dist(n, INF){}
    
    void add_edge(int v1, int v2, T cost){
        g[v1].push_back({v2, cost});
    }
    
    void run(int s){
        priority_queue<P, vector<P>, greater<P>> que;
    
        dist[s] = 0;
        que.push({0, s});
        
        while(!que.empty()){
            P p = que.top(); que.pop();
            int d = p.first;
            int now = p.second;
            if(dist[now] < d) continue;
            for(auto& e : g[now]){
                if(dist[e.to] > dist[now] + e.cost){
                    dist[e.to] = dist[now] + e.cost;
                    que.push({dist[e.to], e.to});
                }
            }
        }
    }
    
    T get_distance(int v){
        return dist[v];
    }
};
