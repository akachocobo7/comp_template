#include "template.cpp"



// 高速に n^m (mod p) を求める
long long POW(long long n, long long m, long long p){
    if(m == 0){
        return 1;
    }
    if(m % 2 == 0){
        long long tmp = POW(n, m / 2, p) % p;
        return tmp * tmp % p;
    }
    else{
        return n * POW(n, m - 1, p) % p;
    }
}


/* フェルマーの小定理 : a^p ≡ a (mod p) */
// a^(p - 1 - x) ≡ a^(-x) (mod p)
long long Fermat(long long a, long long x, long long p){
    return POW(a, p - 1 - x, p);
}


/* nCr (mod.ver) */
long long comb(long long n, long long r, long long mod){
    r = min(r, n - r);  // nCr = nC(n-r)
    
    long long tmp = 1;
    for(long long i = n; i > n - r; i--){
        tmp = tmp * i % mod;
    }
    for(long long i = r; i > 1; i--){
        tmp = tmp * Fermat(i, 1, mod) % mod;
    }
    
    return tmp;
}





/* パスカルの三角形 */
const long long table_size = 50;
long long comb_table[table_size + 1][table_size + 1];   // nCr = comb_table[n][r]

void make_table(){
    for(long long i = 0; i <= table_size; i++){
        for(long long j = 0; j <= i; j++){
            if(i == 0 || j == i){
                comb_table[i][j] = 1;
            }
            else{
                comb_table[i][j] = comb_table[i - 1][j - 1] + comb_table[i - 1][j];
            }
        }
    }
}


/* 行列累乗 */
using vec = vector<long long>;
using mat = vector<vec>;

mat mul(mat a, mat b){
    mat c(a.size(), vec(b[0].size()));
    
    for(long long i = 0; i < a.size(); i++){
        for(long long k = 0; k < b.size(); k++){
            for(long long j = 0; j < b[0].size(); j++){
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
            }
        }
    }
    
    return c;
}

mat POW(mat a, long long n){
    mat b(a.size(), vec(a.size()));
    
    for(long long i = 0; i < a.size(); i++){
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
