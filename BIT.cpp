using ll = long long;

/* BIT */

// 1-indexed
class BIT
{
private:
    ll b;    // bit.size() < 2^n になる最小の2^n
    vector<ll> bit;
public:
    BIT(ll n);   // nは要素数
    ll sum(ll i); // iまでの合計
    void add(ll i, ll x); // i番目にxを加算
    ll lower_bound(ll x); // x番目に小さい値を返す
};

BIT::BIT(ll n){
    bit.resize(n + 1);
    
    b = 1;
    while(b <= n){
        b <<= 1;
    }
}

ll BIT::sum(ll i){
    ll sum = 0;
    
    for(i++; i > 0; i -= i & -i){
        sum += bit[i];
    }
    
    return sum;
}

void BIT::add(ll i, ll x){
    for(i++; i < bit.size(); i += i & -i){
        bit[i] += x;
    }
}

ll BIT::lower_bound(ll x){
    ll res = 0;
    
    for(ll i = b; i > 0; i >>= 1){
        if(res + i < bit.size() && bit[res + i] < x){
            x -= bit[res + i];
            res += i;
        }
    }
    
    return res;
}
