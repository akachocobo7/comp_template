template<int MOD_>
class ModInt {
private:
public:
    long long val;
    constexpr ModInt(long long v = 0) noexcept : val(v % MOD_) {
        if (val < 0) val += MOD_;
    }
    constexpr int getmod() { return MOD_; }
    constexpr ModInt operator - () const noexcept {
        return val ? MOD_ - val : 0;
    }
    constexpr ModInt operator + (const ModInt& r) const noexcept { return ModInt(*this) += r; }
    constexpr ModInt operator - (const ModInt& r) const noexcept { return ModInt(*this) -= r; }
    constexpr ModInt operator * (const ModInt& r) const noexcept { return ModInt(*this) *= r; }
    constexpr ModInt operator / (const ModInt& r) const noexcept { return ModInt(*this) /= r; }
    constexpr ModInt operator % (const ModInt& r) const noexcept { return ModInt(*this) %= r; }
    constexpr ModInt operator ^ (const ModInt& r) const noexcept { return ModInt(*this) ^= r; }
    constexpr ModInt operator & (const ModInt& r) const noexcept { return ModInt(*this) &= r; }
    constexpr ModInt operator | (const ModInt& r) const noexcept { return ModInt(*this) |= r; }
    constexpr ModInt& operator += (const ModInt& r) noexcept {
        val += r.val;
        if (val >= MOD_) val -= MOD_;
        return *this;
    }
    constexpr ModInt& operator -= (const ModInt& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD_;
        return *this;
    }
    constexpr ModInt& operator *= (const ModInt& r) noexcept {
        val = val * r.val % MOD_;
        return *this;
    }
    constexpr ModInt& operator /= (const ModInt& r) noexcept {
        long long a = r.val, b = MOD_, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        val = val * u % MOD_;
        if (val < 0) val += MOD_;
        return *this;
    }
    constexpr ModInt& operator %= (const ModInt& r) noexcept {
        assert(r != 0);
        val = val % r.val;
        return *this;
    }
    constexpr ModInt& operator ^= (const ModInt& r) noexcept {
        val = (val ^ r.val) % MOD_;
        return *this;
    }
    constexpr ModInt& operator &= (const ModInt& r) noexcept {
        val = val & r.val;
        return *this;
    }
    constexpr ModInt& operator |= (const ModInt& r) noexcept {
        val = (val | r.val) % MOD_;
        return *this;
    }
    constexpr bool operator == (const ModInt& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator != (const ModInt& r) const noexcept {
        return this->val != r.val;
    }
    constexpr bool operator < (const ModInt& r) const noexcept {
        return this->val < r.val;
    }
    constexpr bool operator > (const ModInt& r) const noexcept {
        return this->val > r.val;
    }
    constexpr bool operator <= (const ModInt& r) const noexcept {
        return this->val <= r.val;
    }
    constexpr bool operator >= (const ModInt& r) const noexcept {
        return this->val >= r.val;
    }
    constexpr bool operator && (const ModInt& r) const noexcept {
        return this->val && r.val;
    }
    constexpr bool operator || (const ModInt& r) const noexcept {
        return this->val || r.val;
    }
    constexpr ModInt& operator ++ () noexcept {
        val = (val + 1) % MOD_;
        return *this;
    }
    constexpr ModInt operator ++ (int n) noexcept {
        ModInt<MOD_> t = *this;
        val = (val + 1) % MOD_;
        return t;
    }
    constexpr ModInt& operator -- () noexcept {
        val = (val - 1 + MOD_) % MOD_;
        return *this;
    }
    constexpr ModInt operator -- (int n) noexcept {
        ModInt<MOD_> t = *this;
        val = (val - 1 + MOD_) % MOD_;
        return t;
    }
    constexpr ModInt operator ! () noexcept {
        return val? 1 : 0;
    }
    friend constexpr ostream& operator << (ostream &os, const ModInt<MOD_>& x) noexcept {
        return os << x.val;
    }
    friend constexpr istream& operator >> (istream &is, ModInt<MOD_>& x) noexcept {
        return is >> x.val;
    }
    friend constexpr ModInt<MOD_> modpow(const ModInt<MOD_> &a, long long n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1) t = t * a;
        return t;
    }
};