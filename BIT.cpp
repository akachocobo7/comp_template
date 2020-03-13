// 1-indexed
template <typename T>
class BIT {
private:
    int b;    // bit.size() < 2^n になる最小の2^n
    vector<T> bit;
    
public:
    BIT(int n) : bit(n + 1){
        b = 1;
        while(b <= n){
            b <<= 1;
        }
    }
    
    // posまでの合計
    T sum(int pos){
        T sum = 0;
    
        for(pos++; pos > 0; pos -= pos & -pos){
            sum += bit[pos];
        }
        
        return sum;
    }
    
    void add(int pos, T x){
        for(pos++; pos < bit.size(); pos += pos & -pos){
            bit[pos] += x;
        }
    }
    
    int lower_bound(T x){
        int res = 0;
    
        for(int i = b; i > 0; i >>= 1){
            if(res + i < bit.size() && bit[res + i] < x){
                x -= bit[res + i];
                res += i;
            }
        }
        
        return res;
    }
};
