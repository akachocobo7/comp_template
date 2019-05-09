using ll = long long;
const ll INF = 1e18;

template <typename T>
class SegmentTree {
private:
    int n;    // 配列の要素数
    T init;    // 配列を初期化するときの値
    vector<T> data;     // セグメントツリーを持つ配列
public:
    SegmentTree(int m, T init = INF) : n(1), init(init){
        while(n < m) n <<= 1;
        data.assign(2 * n - 1, init);
    }
    
    T operation(T t1, T t2){
        return min(t1, t2);
    }
    
    void update(int k, T val){
        k += n - 1;
        data[k] = val;
        
        while(k > 0){
            k = (k - 1) / 2;
            data[k] = operation(data[k * 2 + 1], data[k * 2 + 2]);
        }
    }
    
    // [a, b) の値を求める
    T query(int a, int b){
        return query(a, b, 0, 0, n);
    }
    
    T query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return s;
        if(a <= l && r <= b){
            return data[k];
        }
        else{
            T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return operation(vl, vr);
        }
    }
};
