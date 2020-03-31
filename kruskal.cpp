/* unionfindを使います */

template <typename T>
class Kruskal {
private:
    struct edge{
        T cost;
        int u, v;
        
        bool operator<(const edge& e1) const {
            return cost < e1.cost;
        }
    };
    vector<edge> es;
    int n;

public:
    Kruskal(int n) : n(n){}
    
    void add_edge(int u, int v, T cost){
        es.push_back({cost, u, v});
        es.push_back({cost, v, u});
    }
    
    T run(){
        sort(es.begin(), es.end());
    
        Unionfind uni(n);
        T res = 0;
        
        for(auto& e : es){
            if(!uni.same(e.u, e.v)){
                uni.unite(e.u, e.v);
                res += e.cost;
            }
        }
        
        return res;
    }
};