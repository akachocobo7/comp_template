#include "template.cpp"



// 最小費用流(ベルマンフォード)
class min_cost_flow
{
private:
    struct edge{
        long long to, cap, cost, rev;
    };
    long long vertex;   // 頂点数
    long long infinity; // 初期化に使う値
    vector<vector<edge>> graph;     // グラフの隣接リスト
    vector<long long> distance;     // 最短距離
    vector<long long> prev_v, prev_e;   // 直前の頂点と辺
public:
    min_cost_flow(long long v, long long inf = 1e16);     // vは頂点の数, infは初期化に使う値
    void add_edge(long long from, long long to, long long cap, long long cost);     // fromからtoへ向かう容量cap、コストcostの辺を張る
    long long get_min_cost_flow(long long s, long long t, long long f);     // sからtへの流量fの最小費用流を求める。流せない場合は-1を返す。
};

min_cost_flow::min_cost_flow(long long v, long long inf){
    vertex = v;
    infinity = inf;
    graph.resize(vertex);
    distance.resize(vertex);
    prev_v.resize(vertex);
    prev_e.resize(vertex);
}

void min_cost_flow::add_edge(long long from, long long to, long long cap, long long cost){
    graph[from].push_back((edge){to, cap, cost, (long long)graph[to].size()});
    graph[to].push_back((edge){from, 0, -cost, (long long)graph[from].size() - 1});
}

long long min_cost_flow::get_min_cost_flow(long long s, long long t, long long f){
    long long res = 0;
    
    while(f > 0){
        distance.assign(vertex, infinity);
        distance[s] = 0;
        bool update = true;
        while(update){
            update = false;
            for(long long v = 0; v < vertex; v++){
                if(distance[v] == infinity) continue;
                for(long long i = 0; i < graph[v].size(); i++){
                    edge &e = graph[v][i];
                    if(e.cap > 0 && distance[e.to] > distance[v] + e.cost){
                        distance[e.to] = distance[v] + e.cost;
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        update = true;
                    }
                }
            }
        }
    
        if(distance[t] == infinity) return -1;
        
        long long d = f;
        for(long long v = t; v != s; v = prev_v[v]){
            d = min(d, graph[prev_v[v]][prev_e[v]].cap);
        }
        f -= d;
        res += d * distance[t];
        for(long long v = t; v != s; v = prev_v[v]){
            edge &e = graph[prev_v[v]][prev_e[v]];
            e.cap -= d;
            graph[v][e.rev].cap += d;
        }
    }
    
    return res;
}