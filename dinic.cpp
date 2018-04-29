#include "template.cpp"



class dinic
{
private:
    long long inf;  // 初期化に使う値
    struct edge {
        long long to, cap, rev;
    };
    vector<vector<edge>> list;  // グラフの隣接リスト
    vector<long long> level;    // sからの距離
    vector<long long> iter;     // どこまで調べ終わったか
public:
    dinic(long long n, long long infinity = 1e16);    // nは頂点の数、infinityは初期化に使う値
    void add_edge(long long from, long long to, long long cap); // fromからtoへ容量capの辺をはる
    void bfs(long long s);  // sからの最短距離を求める
    long long dfs(long long v, long long t, long long f);   // 増加パスをdfsで探す
    long long max_flow(long long s, long long t);   // sからtへの最大流を求める
};

dinic::dinic(long long n, long long infinity){
    list.resize(n);
    level.resize(n);
    iter.resize(n);
}

void dinic::add_edge(long long from, long long to, long long cap){
    list[from].push_back((edge){to, cap, (long long)list[to].size()});
    list[to].push_back((edge){from, 0, (long long)list[from].size() - 1});
}

void dinic::bfs(long long s){
    for(long long i = 0; i < level.size(); i++){
        level[i] = -1;
    }
    queue<long long> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()){
        long long v = que.front(); que.pop();
        for(auto &x : list[v]){
            if(x.cap > 0 && level[x.to] < 0){
                level[x.to] = level[v] + 1;
                que.push(x.to);
            }
        }
    }
}

long long dinic::dfs(long long v, long long t, long long f){
    if(v == t)return f;
    
    for(long long &i = iter[v]; i < list[v].size(); i++){
        edge &e = list[v][i];
        if(e.cap > 0 && level[v] < level[e.to]){
            long long d = dfs(e.to, t, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                list[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

long long dinic::max_flow(long long s, long long t){
    long long flow = 0;
    
    for(;;){
        bfs(s);
        if(level[t] < 0)return flow;
        
        for(long long i = 0; i < iter.size(); i++){
            iter[i] = 0;
        }
        
        long long f;
        while((f = dfs(s, t, INF)) > 0){
            flow += f;
        }
    }
}
