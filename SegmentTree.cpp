using ll = long long;

/* Segment Tree */
class SegmentTree
{
private:
    ll n;    // 配列の要素数
    ll s;    // 配列を初期化するときの値
    vector<ll> data;     // セグメントツリーを持つ配列
public:
    SegmentTree(ll m, ll t);   // mは配列の要素数、tは配列を初期化するときの値
    ll operation(ll t1, ll t2); // 二項演算
    void update(ll k, ll a);  // k番目(0-indexed)の値をaに変更
    ll query(ll a, ll b);   // [a, b) の値を求める。
    ll query(ll a, ll b, ll k, ll l, ll r);   // [a, b) の値を求める。
};

SegmentTree::SegmentTree(ll m, ll t){
    n = 1;
    
    while(n < m) n *= 2;
    
    data.assign(2 * n - 1, t);
    
    s = t;
}

ll SegmentTree::operation(ll t1, ll t2){
    return min(t1, t2);
}

void SegmentTree::update(ll k, ll a){
    k += n - 1;
    data[k] = a;
    
    while(k > 0){
        k = (k - 1) / 2;
        data[k] = operation(data[k * 2 + 1], data[k * 2 + 2]);
    }
}

ll SegmentTree::query(ll a, ll b){
    return query(a, b, 0, 0, n);
}

ll SegmentTree::query(ll a, ll b, ll k, ll l, ll r){
    if(r <= a || b <= l) return s;
    if(a <= l && r <= b){
        return data[k];
    }
    else{
        ll vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        
        return operation(vl, vr);
    }
}