/* 極大独立集合を求める */

template<typename T>
class maximal_indsets{
    const int n;
    const vector<vector<T>> &g;
    vector<vector<T>> ret;
    vector<int> cur, deg, block;
    vector<bool> exists;
    int max_indsets_size = 0;

private:
    void erase(T v){
        if(exists[v]){
            exists[v] = false;
            for(T nv : g[v]){
                deg[nv]--;
            }
        }
    }
    
    void restore(T v){
        exists[v] = true;
        for(T nv : g[v]){
            deg[nv]++;
        }
    }
    
    void select(T v){
        cur.push_back(v);
        block[v]++;
        erase(v);
        for(T nv : g[v]){
            block[nv]++;
            erase(nv);
        }
    }
    
    void unselect(T v){
        cur.pop_back();
        block[v]--;
        restore(v);
        for(T nv : g[v]){
            block[nv]--;
            if(block[nv] == 0){
                restore(nv);
            }
        }
    }
    
    void dfs(){
        int mn = n, v = -1;
        for(int u = 0; u < n; u++){
            if(exists[u]){
                if(mn > deg[u]){
                    mn = deg[u];
                    v = u;
                }
            }
        }
        if(v == -1){
            ret.push_back(cur);
            return;
        }
        
        select(v);
        dfs();
        unselect(v);
        for(T nv : g[v]){
            if(exists[nv]){
                select(nv);
                dfs();
                unselect(nv);
            }
        }
    }

public:
    maximal_indsets(const vector<vector<T>>& g) : n(g.size()), g(g), exists(n, true), deg(n), block(n) {
        for(int v = 0; v < n; v++){
            deg[v] = g[v].size();
        }
        dfs();
        
        for(int i = 0; i < ret.size(); i++){
            max_indsets_size = max(max_indsets_size, (int)ret[i].size());
        }
    }
    
    const vector<vector<T>>& get() const {
        return ret;
    }
    
    int maximam_indsets_size(){
        return max_indsets_size;
    }
};