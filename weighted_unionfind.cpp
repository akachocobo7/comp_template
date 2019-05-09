using ll = long long;

class weighted_unionfind {
private:
    vector<int> par;
    vector<int> rank;
    vector<ll> diff_weight;
public:
    weighted_unionfind(int n) : rank(n), diff_weight(n) {
        for (int i = 0; i < n; i++) {
            par.push_back(i);
        }
    }
    
    int find(int x){
        if (par[x] == x) {
            return x;
        }
        else {
            int t = find(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = t;
        }
    }
    
    void unite(int x, int y, ll w){
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        if (x == y)return;
        
        if (rank[x] < rank[y]) {
            swap(x, y);
            w = -w;
        }
        if(rank[x] == rank[y]){
            rank[x]++;
        }
        
        par[y] = x;
        diff_weight[y] = w;
    }
    
    bool same(int x, int y){
        return find(x) == find(y);
    }
    
    ll weight(int x){
        find(x);
        return diff_weight[x];
    }
    
    ll diff(int x, int y){
        return weight(y) - weight(x);
    }
};

