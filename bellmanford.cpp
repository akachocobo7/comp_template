#include "template.cpp"



class bellmanford
{
private:
    struct edge {
        long long to, cost;
    };
    long long vertex;    // 頂点数
    vector<vector<edge>> list;    // 隣接リスト
    vector<long long> distance;    // 距離
public:
    bellmanford(long long n);   // nは頂点数
    void add_edge(long long v1, long long v2, long long cost);    // 頂点v1から頂点v2に辺を張る
    bool run(long long s);        // sは開始地点。返り値がfalseのとき負の閉路あり
    long long get_distance(long long v);    // 頂点vへの距離を返す
};

bellmanford::bellmanford(long long n){
    list.resize(n);
    vertex = n;
}

void bellmanford::add_edge(long long v1, long long v2, long long cost) {
    list[v1].push_back({ v2, cost });
}

bool bellmanford::run(long long s) {
    distance = vector<long long>(vertex, INF);
    distance[s] = 0;    //開始点の距離は0
    
    for (long long i = 0; i < vertex; i++) {
        for (long long v = 0; v < vertex; v++) {
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

long long bellmanford::get_distance(long long v) {
    return distance[v];
}