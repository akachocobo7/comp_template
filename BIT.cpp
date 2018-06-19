#include "template.cpp"



/* BIT */

// 1-indexed
class BIT
{
private:
    long long b;    // bit.size() < 2^n になる最小の2^n
    vector<long long> bit;
public:
    BIT(long long n);   // nは要素数
    long long sum(long long i); // iまでの合計
    void add(long long i, long long x); // i番目にxを加算
    long long lower_bound(long long x); // x番目に小さい値を返す
};

BIT::BIT(long long n){
    bit.resize(n + 1);
    
    b = 1;
    while(b <= n){
        b <<= 1;
    }
}

long long BIT::sum(long long i){
    long long sum = 0;
    
    for(i++; i > 0; i -= i & -i){
        sum += bit[i];
    }
    
    return sum;
}

void BIT::add(long long i, long long x){
    for(i++; i < bit.size(); i += i & -i){
        bit[i] += x;
    }
}

long long BIT::lower_bound(long long x){
    long long res = 0;
    
    for(long long i = b; i > 0; i >>= 1){
        if(res + i < bit.size() && bit[res + i] < x){
            x -= bit[res + i];
            res += i;
        }
    }
    
    return res;
}