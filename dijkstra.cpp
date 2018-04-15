#include "template.cpp"



class dijkstra
{
private:
    using P = pair<long long, long long>;
    struct edge{
        long long to, cost;
    };
    long long vertex;   // 頂点数
    vector<vector<edge>> list;  //隣接リスト
    vector<long long> distance;    // 距離
public:
    dijkstra(long long n);  // nは頂点の数
    void add_edge(long long v1, long long v2, long long cost);    // 頂点v1から頂点v2に辺を張る
    void run(long long s);        // sは開始地点。
    long long get_distance(long long v);    // 頂点vへの距離を返す
};

dijkstra::dijkstra(long long n){
    vertex = n;
    list.resize(n);
}

void dijkstra::add_edge(long long v1, long long v2, long long cost){
    list[v1].push_back({ v2, cost });
}

void dijkstra::run(long long s){
    priority_queue<P, vector<P>, greater<P>> que;
    distance = vector<long long>(vertex, INF);
    distance[s] = 0;    // 開始点の距離は0
    que.push(P(0, s));
    
    while(!que.empty()){
        P p = que.top(); que.pop();
        long long v = p.second;
        if(distance[v] < p.first) continue;
        for(auto e : list[v]){
            if(distance[e.to] > distance[v] + e.cost){
                distance[e.to] = distance[v] + e.cost;
                que.push(P(distance[e.to], e.to));
            }
        }
    }
}

long long dijkstra::get_distance(long long v){
    return distance[v];
}