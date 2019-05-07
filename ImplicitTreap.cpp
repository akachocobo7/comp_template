const long long INF = 1e18;

using T = long long;

class xorshift{
private:
    uint64_t x;
public:
    xorshift(){
        random_device rnd;
        mt19937 mt(rnd());
        x = mt();
        for(int i = 0; i < 50; i++){
            random();
        }
    }
    uint64_t random(){
        x = x ^ (x << 7);
        return x = x ^ (x >> 9);
    }
};



struct SumMonoid{
    static constexpr T id(){
        return 0;
    }
    static T op(T a, T b){
        return a + b;
    }
};

struct MinMonoid{
    static constexpr T id(){
        return INF;
    }
    static T op(T a, T b){
        return min(a, b);
    }
};

struct MaxMonoid{
    static constexpr T id(){
        return -INF;
    }
    static T op(T a, T b){
        return max(a, b);
    }
};

struct UpdateMonoid{
    static constexpr T id(){
        return INF;
    }
    static T op(T a, T b){
        return b;
    }
};



/* RSQ
struct Modifier{
    static T op(T a, T b, int sz){
        return b == UpdateMonoid::id() ? a : b * sz;
    }
};
*/

struct Modifier{
    static T op(T a, T b, int sz){
        return b == UpdateMonoid::id() ? a : b;
    }
};



template<class Monoid, class OperatorMonoid>
class ImplicitTreap {
private:
    xorshift rnd;
    
    struct Node{
        T value, acc, lazy;
        int priority, cnt;
        bool rev;
        Node *l, *r;
        Node(T value, int priority) : value(value), acc(Monoid::id()), lazy(OperatorMonoid::id()), priority(priority), cnt(1), rev(false), l(nullptr), r(nullptr) {};
    } *root = nullptr;
    
    using Tree = Node *;
    
    int cnt(Tree t){
        return t ? t->cnt : 0;
    }
    
    T acc(Tree t){
        return t ? t->acc : Monoid::id();
    }
    
    void update_cnt(Tree t){
        if(t){
            t->cnt = 1 + cnt(t->l) + cnt(t->r);
        }
    }
    
    void update_acc(Tree t){
        if(t){
            t->acc = Monoid::op(acc(t->l), Monoid::op(t->value, acc(t->r)));
        }
    }
    
    void pushup(Tree t){
        update_cnt(t);
        update_acc(t);
    }
    
    void pushdown(Tree t){
        if(t && t->rev){
            t->rev = false;
            swap(t->l, t->r);
            if(t->l) t->l->rev ^= 1;
            if(t->r) t->r->rev ^= 1;
        }
        if(t && t->lazy != OperatorMonoid::id()){
            if(t->l){
                t->l->lazy = OperatorMonoid::op(t->l->lazy, t->lazy);
                t->l->acc = Modifier::op(t->l->acc, t->lazy, cnt(t->l));
            }
            if(t->r){
                t->r->lazy = OperatorMonoid::op(t->r->lazy, t->lazy);
                t->r->acc = Modifier::op(t->r->acc, t->lazy, cnt(t->r));
            }
            t->value = Modifier::op(t->value, t->lazy, 1);
            t->lazy = OperatorMonoid::id();
        }
        pushup(t);
    }
    
    void split(Tree t, T key, Tree &l, Tree &r){
        if(!t){
            l = r = nullptr;
            return;
        }
        pushdown(t);
        int implicit_key = cnt(t->l) + 1;
        if(key < implicit_key){
            split(t->l, key, l, t->l);
            r = t;
        }
        else{
            split(t->r, key - implicit_key, t->r, r);
            l = t;
        }
        pushup(t);
    }
    
    void merge(Tree& t, Tree l, Tree r){
        pushdown(l);
        pushdown(r);
        if(!l || !r){
            t = l ? l : r;
        }
        else if(l->priority > r->priority){
            merge(l->r, l->r, r);
            t = l;
        }
        else{
            merge(r->l, l, r->l);
            t = r;
        }
        pushup(t);
    }
    
    void insert(Tree &t, int key, Tree item){
        Tree t1, t2;
        split(t, key, t1, t2);
        merge(t1, t1, item);
        merge(t, t1, t2);
    }
    
    void erase(Tree& t, T key){
        Tree t1, t2, t3;
        split(t, key + 1, t1, t2);
        split(t1, key, t1, t3);
        merge(t, t1, t2);
    }
    
    void update(Tree t, int l, int r, T x){
        Tree t1, t2, t3;
        split(t, l, t1, t2);
        split(t2, r - l, t2, t3);
        t2->lazy = OperatorMonoid::op(t2->lazy, x);
        t2->acc = Modifier::op(t2->acc, x, cnt(t2));
        merge(t2, t2, t3);
        merge(t, t1, t2);
    }
    
    T query(Tree t, int l, int r){
        Tree t1, t2, t3;
        split(t, l, t1, t2);
        split(t2, r - l, t2, t3);
        T ret = t2->acc;
        merge(t2, t2, t3);
        merge(t, t1, t2);
        return ret;
    }
    
    int find(Tree t, T x, int offset, bool left = true){
        if(Monoid::op(t->acc, x) == x) return -1;
        
        if(left){
            if(t->l && Monoid::op(t->l->acc, x) != x){
                return find(t->l, x, offset, left);
            }
            else{
                return Monoid::op(t->value, x) != x ? offset + cnt(t->l) : find(t->r, x, offset + cnt(t->l) + 1, left);
            }
        }
        else{
            if(t->r && Monoid::op(t->r->acc, x) != x){
                return find(t->r, x, offset + cnt(t->l) + 1, left);
            }
            else{
                return Monoid::op(t->value, x) != x ? offset + cnt(t->l) : find(t->l, x, offset, left);
            }
        }
    }
    
    void reverse(Tree t, int l, int r){
        if(l > r) return;
        Tree t1, t2, t3;
        split(t, l, t1, t2);
        split(t2, r - l, t2, t3);
        t2->rev ^= 1;
        merge(t2, t2, t3);
        merge(t, t1, t2);
    }
    
    void rotate(Tree t, int l, int m, int r){
        reverse(t, l, r);
        reverse(t, l, l + r - m);
        reverse(t, l + r - m, r);
    }
    
    void dump(Tree t){
        if(!t) return;
        pushdown(t);
        dump(t->l);
        cerr << t->value << " ";
        dump(t->r);
    }
    
public:
    ImplictTreap(){}
    ImplictTreap(vector<T> as){
        ::reverse(as.begin(), as.end());
        for(T a : as){
            insert(0, a);
        }
    }
    ImplictTreap(initializer_list<T> init){
        for(auto itr = rbegin(init); itr != rend(init); itr++){
            insert(0, *itr);
        }
    }
    
    int size(){
        return cnt(root);
    }
    
    void insert(int pos, T x){
        insert(root, pos, new Node(x, rnd.random()));
    }
    
    void update(int l, int r, T x){
        update(root, l, r, x);
    }
    
    void update(int pos, T x){
        update(root, pos, pos + 1, x);
    }
    
    T query(int l, int r){
        return query(root, l, r);
    }
    
    // 存在しない場合は-1
    int find(int l, int r, T x, bool left = true){
        Tree t1, t2, t3;
        split(root, l, t1, t2);
        split(t2, r - l, t2, t3);
        int ret = find(t2, x, l, left);
        merge(t2, t2, t3);
        merge(root, t1, t2);
        return ret;
    }
    
    void erase(int pos){
        erase(root, pos);
    }
    
    void reverse(int l, int r){
        reverse(root, l, r);
    }
    
    void rotate(int l, int m, int r){
        rotate(root, l, m, r);
    }
    
    void dump(){
        dump(root);
        cerr << endl;
    }
    
    T operator[](int pos){
        if(pos < 0 || pos >= cnt(root)){
            cerr << "Index out of range." << endl;
            return -1;
        }
        Tree t1, t2, t3;
        split(root, pos + 1, t1, t2);
        split(t1, pos, t1, t3);
        T ret = t3->acc;
        merge(t1, t1, t3);
        merge(root, t1, t2);
        return ret;
    }
    
    void operator =(vector<T> as){
        while(cnt(root)){
            erase(0);
        }
        ::reverse(as.begin(), as.end());
        for(T a : as){
            insert(0, a);
        }
    }
};
