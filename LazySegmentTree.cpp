using ll = long long;



template <typename T>
class LazySegmentTree {
private:
    int n;      // 配列の要素数
    T init;     // 遅延伝搬用の配列の初期の値
    vector<T> node, lazy;   // セグメントツリーを持つ配列
    
    // 二項演算
    T f(T a, T b){
        return min(a, b); // RMQ;
        // return a + b; // RSQ;
    };
    
    // 区間に対しての操作
    void g(T &a, T b, ll r = 1){
        a = b; // range update
        // a += b * r; // range add
    }
    
    // 子ノードへ伝搬するときの演算
    void h(T &a, T b){
        a = b; // range update
        // a += b / 2; // range add
    }
    
    void eval(int k, int l, int r){
        if(lazy[k] != init){            
            g(node[k], lazy[k]);
            
            if(r - l > 1){
                h(lazy[k * 2 + 1], lazy[k]);
                h(lazy[k * 2 + 2], lazy[k]);
            }
            
            lazy[k] = init;
        }
    }
    
public:
    LazySegmentTree(vector<T> v, T init = 0) : n(1), init(init) {
        int sz = v.size();
        while(n < sz) n *= 2;
        node.resize(2 * n - 1);
        lazy.assign(2 * n - 1, init);
        
        for(int i = 0; i < sz; i++) node[i + n - 1] = v[i];
        for(int i = n - 2; i >= 0; i--) node[i] = f(node[i * 2 + 1], node[i * 2 + 2]);
    }
    
    LazySegmentTree(ll n, T init = 0) : LazySegmentTree(vector<T>(n, init), init) {}
    
    // [a, b) を x で更新
    void update(int a, int b, T x, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        
        eval(k, l, r);
        
        if(b <= l || r <= a) return;
        
        if(a <= l && r <= b){
            g(lazy[k], x, (r - l));
            eval(k, l, r);
        }
        else{
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = f(node[2 * k + 1], node[2 * k + 2]);
        }
    }
    
    // [a, b) の値を求める
    T query(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0) r = n;
        
        eval(k, l, r);
        
        if(b <= l || r <= a) return init;
        if(a <= l && r <= b) return node[k];
        T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
};