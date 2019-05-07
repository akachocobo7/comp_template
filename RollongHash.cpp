using ll = long long;

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