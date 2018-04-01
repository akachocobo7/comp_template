#include "template.cpp"



class SegmentTree
{
private:
    long long n;    // 配列の要素数
    long long s;    // 配列を初期化するときの値
    vector<long long> data;     // セグメントツリーを持つ配列
public:
    SegmentTree(long long m, long long t);   // mは配列の要素数、tは配列を初期化するときの値
    long long operation(long long t1, long long t2); // 二項演算
    void update(long long k, long long a);  // k番目(0-indexed)の値をaに変更
    long long query(long long a, long long b);   // [a, b) の最小値を求める。外から呼ぶときはこっち
    long long ans(long long a, long long b, long long k, long long l, long long r);   // [a, b) の最小値を求める。
};

SegmentTree::SegmentTree(long long m, long long t){
    n = 1;
    
    while(n < m) n *= 2;
    
    for(long long i = 0; i < 2 * n - 1; i++){
        data.push_back(t);
    }
    
    s = t;
}

long long SegmentTree::operation(long long t1, long long t2){
    return min(t1, t2);
}

void SegmentTree::update(long long k, long long a){
    k += n - 1;
    data[k] = a;
    
    while(k > 0){
        k = (k - 1) / 2;
        data[k] = operation(data[k * 2 + 1], data[k * 2 + 2]);
    }
}

long long SegmentTree::query(long long a, long long b){
    return ans(a, b, 0, 0, n);
}

long long SegmentTree::ans(long long a, long long b, long long k, long long l, long long r){
    if(r <= a || b <= l) return s;
    if(a <= l && r <= b){
        return data[k];
    }
    else{
        long long vl = ans(a, b, k * 2 + 1, l, (l + r) / 2);
        long long vr = ans(a, b, k * 2 + 2, (l + r) / 2, r);
        
        return operation(vl, vr);
    }
}