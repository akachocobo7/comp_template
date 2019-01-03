using ll = long long;


/* Rolling Hash */
class RollingHash
{
private:
    using ull = unsigned long long;
    const ull B = 100000007;    // ハッシュの基数
public:
    bool contain(string a, string b);   // aはbに含まれているか？
};

bool RollingHash::contain(string a, string b){
    ll al = a.length(), bl = b.length();
    if(al > bl) return false;
    
    ull t = 1;
    for(ll i = 0; i < al; i++) t *= B;
    
    ull ah = 0, bh = 0;
    for(ll i = 0; i < al; i++) ah = ah * B + a[i];
    for(ll i = 0; i < al; i++) bh = bh * B + b[i];
    
    for(ll i = 0; i + al <= bl; i++){
        if(ah == bh) return true;
        if(i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return false;
}

/* Suffix Array */
class SuffixArray
{
private:
    ll n, k;
    vector<ll> first_i, rank;
    string S;
public:
    SuffixArray(string s);
    bool contain(string t);   // Sの中にtがあるか？
};

SuffixArray::SuffixArray(string s){
    S = s;
    n = S.size();
    first_i.resize(n + 1);
    rank.resize(n + 1);
    
    for(ll i = 0; i <= n; i++){
        first_i[i] = i;
        rank[i] = i < n? S[i] : -1;
    }
    
    vector<ll> tmp(n + 1);
    for(k = 1; k <= n; k *= 2){
        auto compare = [&](ll i, ll j){
            if(rank[i] != rank[j]) return rank[i] < rank[j];
            else{
                ll ri = i + k <= n ? rank[i + k] : -1;
                ll rj = j + k <= n ? rank[j + k] : -1;
                return ri < rj;
            }
        };
        sort(first_i.begin(), first_i.end(), compare);
        tmp[first_i[0]] = 0;
        for(ll i = 1; i <= n; i++){
            tmp[first_i[i]] = tmp[first_i[i - 1]] + (compare(first_i[i - 1], first_i[i]) ? 1 : 0);
        }
        for(ll i = 0; i <= n; i++){
            rank[i] = tmp[i];
        }
    }
}

bool SuffixArray::contain(string t){
    ll a = 0, b = S.size();
    while(b - a > 1){
        ll c = (a + b) / 2;
        if(S.compare(first_i[c], t.size(), t) < 0) a = c;
        else b = c;
    }
    return S.compare(first_i[b], t.size(), t) == 0;
}


/* Z algorithm */
vector<ll> Z_algorithm(string s){
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