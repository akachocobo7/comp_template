using ll = long long;

// 高速に n^m (mod p) を求める
ll POW(ll n, ll m, ll p){
    if(m == 0){
        return 1;
    }
    if(m % 2 == 0){
        ll tmp = POW(n, m / 2, p) % p;
        return tmp * tmp % p;
    }
    else{
        return n * POW(n, m - 1, p) % p;
    }
}

/* フェルマーの小定理 : a^p ≡ a (mod p) */
// a^(p - 1 - x) ≡ a^(-x) (mod p)
ll Fermat(ll a, ll x, ll p){
    return POW(a, p - 1 - x, p);
}



/* nCr */
const ll table_size = 100005;
ll fact[table_size], finv[table_size], inv[table_size];

// 前処理
void make_table(ll mod) {
    fact[0] = fact[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (ll i = 2; i < table_size; i++){
        fact[i] = fact[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }
}

// nCr
ll nCr(ll n, ll r, ll mod){
    return fact[n] * (finv[r] * finv[n - r] % mod) % mod;
}



/* 行列累乗 */
using vec = vector<ll>;
using mat = vector<vec>;

mat mul(mat a, mat b){
    mat c(a.size(), vec(b[0].size()));
    
    for(ll i = 0; i < a.size(); i++){
        for(ll k = 0; k < b.size(); k++){
            for(ll j = 0; j < b[0].size(); j++){
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
            }
        }
    }
    
    return c;
}

mat POW(mat a, ll n){
    mat b(a.size(), vec(a.size()));
    
    for(ll i = 0; i < a.size(); i++){
        b[i][i] = 1;
    }
    while(n > 0){
        if(n & 1){
            b = mul(b, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    
    return b;
}
