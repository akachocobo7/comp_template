using ll = long long;

class unionfind {
private:
    vector<int> par;
    vector<int> rank;
    vector<int> counter;
public:
    unionfind(int n) : rank(n), counter(n, 1){
        for(int i = 0; i < n; i++){
            par.push_back(i);
        }
    }
    
    int find(int x){
        if (par[x] == x) {
            return x;
        }
        else {
            return par[x] = find(par[x]);
        }
    }
    
    void unite(int x, int y){
        x = find(x);
        y = find(y);
        if (x == y) return;
        
        if (rank[x] < rank[y]) {
            counter[y] += counter[x];
            counter[x] = counter[y];
            par[x] = y;
        }
        else {
            counter[y] += counter[x];
            counter[x] = counter[y];
            par[y] = x;
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        }
    }
    
    bool same(int x, int y){
        return find(x) == find(y);
    }
    
    ll count(int x){
        return counter[find(x)];
    }
};