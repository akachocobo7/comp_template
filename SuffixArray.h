using ll = long long;

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