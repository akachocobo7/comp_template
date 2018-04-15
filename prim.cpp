#include "template.cpp"



class prim
{
private:
    vector<vector<long long>> list; // 隣接リスト
    vector<long long> mincost;   // 集合Xからの辺の最小コスト
    vector<bool> used;  // 頂点iが集合Xに含まれているか
    long long vertex;   // 頂点数
    long long res = 0;  // 最小全域木のコスト
public:
    prim(long long n); // nは頂点の数
    void add_edge(long long u, long long v, long long cost);    // 頂点uから頂点vにコストcostの辺を張る
    long long run();    // 最小全域木を求める
};

prim::prim(long long n){
    vertex = n;
    list.resize(n);
    mincost.resize(vertex);
    used.resize(vertex);
    
    for(long long i = 0; i < vertex; i++){
        list[i].resize(n);
        for(long long j = 0; j < vertex; j++){
            list[i][j] = INF;
        }
        mincost[i] = INF;
        used[i] = false;
    }
    
    mincost[0] = 0;
}

void prim::add_edge(long long u, long long v, long long cost){
    list[u][v] = cost;
    list[v][u] = cost;
}

long long prim::run(){
    for(;;){
        long long v = -1;
        for(long long u = 0; u < vertex; u++){
            if(!used[u] && (v == -1 || mincost[u] < mincost[v])){
                v = u;
            }
        }
        
        if(v == -1) break;
        
        used[v] = true;
        res += mincost[v];
        
        for(long long u = 0; u < vertex; u++){
            mincost[u] = min(mincost[u], list[v][u]);
        }
    }
    
    return res;
}