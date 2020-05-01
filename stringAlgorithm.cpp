using ll = long long;

class RollingHash {
private:
    using ull = unsigned long long;
    const ull base1;
    const ull base2;
    const ull mod1;
    const ull mod2;
    vector<ull> hash1;
    vector<ull> hash2;
    vector<ull> pow1;
    vector<ull> pow2;
    
    string s;
    
public:
    RollingHash(string &s) : s(s), base1(1009), base2(2009), mod1(1000000007), mod2(1000000009),
                             hash1(s.size() + 1), hash2(s.size() + 1), pow1(s.size() + 1, 1), pow2(s.size() + 1, 1) {
        for(int i = 0; i < s.size(); i++){
            hash1[i + 1] = (hash1[i] * base1 + s[i]) % mod1;
            hash2[i + 1] = (hash2[i] * base2 + s[i]) % mod2;
            pow1[i + 1] = (pow1[i] * base1) % mod1;
            pow2[i + 1] = (pow2[i] * base2) % mod2;
        }
    }
    
    // s の [l, r) のハッシュ値を返す
    ull get(int l, int r){
        return (hash1[r] - ((hash1[l] * pow1[r - l]) % mod1) + mod1) % mod1;
    }
    
    ull get(){
        return get(0, s.size());
    }
    
    ull operator () (){
        return get(0, s.size());
    }
    
    ull operator () (int l, int r){
        return get(l, r);
    }
};


class SuffixArray {
private:
    int n, k;
    vector<int> first_i, rank;
    string S;
    
public:
    SuffixArray(string &s) : S(s), n(s.size()), first_i(n + 1), rank(n + 1) {
        for(int i = 0; i <= n; i++){
            first_i[i] = i;
            rank[i] = i < n? S[i] : -1;
        }
        
        vector<int> tmp(n + 1);
        for(k = 1; k <= n; k *= 2){
            auto compare = [&](int i, int j){
                if(rank[i] != rank[j]) return rank[i] < rank[j];
                else{
                    int ri = i + k <= n ? rank[i + k] : -1;
                    int rj = j + k <= n ? rank[j + k] : -1;
                    return ri < rj;
                }
            };
            sort(first_i.begin(), first_i.end(), compare);
            tmp[first_i[0]] = 0;
            for(int i = 1; i <= n; i++){
                tmp[first_i[i]] = tmp[first_i[i - 1]] + (compare(first_i[i - 1], first_i[i]) ? 1 : 0);
            }
            for(int i = 0; i <= n; i++){
                rank[i] = tmp[i];
            }
        }
    }
    
    bool contain(string &t){
        int a = 0, b = S.size();
        while(b - a > 1){
            int c = (a + b) / 2;
            if(S.compare(first_i[c], t.size(), t) < 0) a = c;
            else b = c;
        }
        return S.compare(first_i[b], t.size(), t) == 0;
    }
};


/* Z algorithm */
/* 文字列が与えられた時、各 i について
  「S と S[i:|S|-1] の最長共通接頭辞の長さ」
   を記録した配列 A を 構築する */
vector<ll> Z_algorithm(string &s){
    ll n = s.size();
    vector<ll> a(n);
    a[0] = n;
    ll i = 1, j = 0;
    while(i < n){
        while(i + j < n && s[j] == s[i + j]) j++;
        a[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        ll k = 1;
        while(i + k < n && k + a[k] < j){
            a[i + k] = a[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return a;
}


/* Manacher */
/* 文字列が与えられた時、各 i について
  「文字 i を中心とする最長の回文の半径」
   を記録した配列 R を構築する */
vector<ll> manacher(string &s){
    ll n = s.size();
    vector<ll> r(n);
    ll i = 0, j = 0;
    while(i < n){
        while(i - j >= 0 && i + j < n && s[i - j] == s[i + j]){
            j++;
        }
        r[i] = j;
        ll k = 1;
        while(i - k >= 0 && i + k < n && k + r[i - k] < j){
            r[i + k] = r[i - k];
            k++;
        }
        i += k;
        j -= k;
    }
    return r;
}