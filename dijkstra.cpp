#include "template.cpp"



template <typename T>
class dijkstra
{
private:
    using P = pair<T, T>;
    struct edge{
        long long to;
        T cost;
    };
    long long vertex;   // 頂点数
    vector<vector<edge>> list;  //隣接リスト
    vector<T> distance;    // 距離
public:
    dijkstra(long long n, T infinity = 1e16);  // nは頂点の数、infinityは初期化に使う値
    void add_edge(long long v1, long long v2, T cost);    // 頂点v1から頂点v2に辺を張る
    void run(long long s);        // sは開始地点。
    T get_distance(long long v);    // 頂点vへの距離を返す
};

template <typename T>
dijkstra<T>::dijkstra(long long n, T infinity){
    vertex = n;
    list.resize(n);
    distance = vector<T>(vertex, infinity);
}

template <typename T>
void dijkstra<T>::add_edge(long long v1, long long v2, T cost){
    list[v1].push_back({ v2, cost });
}

template <typename T>
void dijkstra<T>::run(long long s){
    priority_queue<P, vector<P>, greater<P>> que;
 
    distance[s] = 0;    // 開始点の距離は0
    que.push(P(0, s));
    
    while(!que.empty()){
        P p = que.top(); que.pop();
        T v = p.second;
        if(distance[v] < p.first) continue;
        for(auto e : list[v]){
            if(distance[e.to] > distance[v] + e.cost){
                distance[e.to] = distance[v] + e.cost;
                que.push(P(distance[e.to], e.to));
            }
        }
    }
}

template <typename T>
T dijkstra<T>::get_distance(long long v){
    return distance[v];
}