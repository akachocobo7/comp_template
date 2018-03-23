#include <cstdio>
#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include <numeric>
#include <functional>
#include <unordered_map>

using namespace std;
using ll = long long;
using ull = unsigned long long;

const ll INF = 1e9;
const ll MOD = 1e9 + 7;

#define REP(i, n) for(int i = 0; i < n; i++)

/* unionfind begin*/
class unionfind
{
private:
	vector<long long> par;
	vector<long long> rank;
public:
	void init(long long n);
	long long find(long long x);
	void unite(long long x, long long y);
	bool same(long long x, long long y);
};

// 初期化
void unionfind::init(long long n) {
	for (long long i = 0; i < n; i++) {
		par.push_back(i);
		rank.push_back(0);
	}
}

// 木の根を求める
long long unionfind::find(long long x) {
	if (par[x] == x) {
		return x;
	}
	else {
		return par[x] = find(par[x]);
	}
}

// xとyの属する集合を併合
void unionfind::unite(long long x, long long y) {
	x = find(x);
	y = find(y);
	if (x == y)return;

	if (rank[x] < rank[y]) {
		par[x] = y;
	}
	else {
		par[y] = x;
		if (rank[x] == rank[y]) {
			rank[x]++;
		}
	}
}

// xとyが同じ集合に属していたらtrue
bool unionfind::same(long long x, long long y) {
	return find(x) == find(y);
}
/* unionfind end*/

/* bellmanford begin*/
struct edge {
	long long to, cost;
};

class bellmanford
{
private:
	long long vertex;	// 頂点数
	vector<vector<edge>> list;	// 隣接リスト
	vector<long long> distance;	// 距離
public:
	void init(long long n);	// nは頂点数
	void add_edge(long long v1, long long v2, long long cost);	// 頂点v1から頂点v2に辺を張る
	bool run(long long s);		// sは開始地点。返り値がfalseのとき負の閉路あり
	long long get_distance(long long v);	// 頂点vへの距離を返す
};

void bellmanford::init(long long n) {
	list.resize(n);
	vertex = n;
}

void bellmanford::add_edge(long long v1, long long v2, long long cost) {
	list[v1].push_back({ v2, cost });
}

bool bellmanford::run(long long s) {
	distance = vector<long long>(vertex, INF);
	distance[s] = 0;	//開始点の距離は0

	for (long long i = 0; i < vertex; i++) {
		for (long long v = 0; v < vertex; v++) {
			for (auto edge : list[v]) {
				if (distance[v] != INF && distance[edge.to] > distance[v] + edge.cost) {
					distance[edge.to] = distance[v] + edge.cost;
					if (i == vertex - 1) {
						//return false;
						distance[edge.to] = -INF;
					}
				}
			}
		}
	}
	return true;
}

long long bellmanford::get_distance(long long v) {
	return distance[v];
}
/* bellmanford end*/

/* dijkstra begin */
using P = pair<long long, long long>;

struct edge{
    long long to, cost;
};

class dijkstra
{
private:
    long long vertex;   // 頂点数
    vector<vector<edge>> list;  //隣接リスト
    vector<long long> distance;    // 距離
public:
    void init(long long n);  // nは頂点の数
    void add_edge(long long v1, long long v2, long long cost);    // 頂点v1から頂点v2に辺を張る
    void run(long long s);        // sは開始地点。
    long long get_distance(long long v);    // 頂点vへの距離を返す
};

void dijkstra::init(long long n){
    vertex = n;
    list.resize(n);
}

void dijkstra::add_edge(long long v1, long long v2, long long cost){
    list[v1].push_back({ v2, cost });
}

void dijkstra::run(long long s){
    priority_queue<P, vector<P>, greater<P>> que;
    distance = vector<long long>(vertex, INF);
    distance[s] = 0;    // 開始点の距離は0
    que.push(P(0, s));

    while(!que.empty()){
        P p = que.top(); que.pop();
        long long v = p.second;
        if(distance[v] < p.first) continue;
        for(auto e : list[v]){
            if(distance[e.to] > distance[v] + e.cost){
                distance[e.to] = distance[v] + e.cost;
                que.push(P(distance[e.to], e.to));
            }
        }
    }
}

long long dijkstra::get_distance(long long v){
    return distance[v];
}
/* dijkstra end */


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


int main()
{
    
}