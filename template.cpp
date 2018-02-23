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
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
 
const ll INF = 1e9;
const ll MOD = 1e9 + 7;

#define REP(i, n) for(int i = 0; i < n; i++)
#define RREP(i, n) for(int i = n - 1; i >= 0; i--)
#define REP2(i, n, k) for(int i = 0; i < n; i += k)

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
	ll from, to, cost;
};

class bellmanford 
{
private:
	long long vertex;	// 頂点数
	long long inf = 1LL << 60;
	vector<edge> e;	// 辺
	vector<long long> distance;	// 最短距離
public:
	void init(long long n);	// nは頂点の数
	void add_edge(long long from, long long to, long long cost);	// 頂点fromから頂点toに辺を張る
	bool run(long long s);		// sは開始地点。返り値がfalseのとき負の閉路あり
	ll get_distance(long long v);	// 頂点vへの距離を返す
};

void bellmanford::init(long long n) {
	vertex = n;
}

void bellmanford::add_edge(long long from, long long to, long long cost) {
	e.push_back({ from, to, cost });
}

bool bellmanford::run(long long s) {
	distance = vector<long long>(vertex, inf);
	distance[s] = 0;	//開始点の距離は0

	for (long long i = 0; i < vertex; i++) {
		for (auto es : e) {
			if (distance[es.from] != inf && distance[es.to] > distance[es.from] + es.cost) {
				distance[es.to] = distance[es.from] + es.cost;
				if (i == vertex - 1) {
					return false;
					// distance[es.to] = -inf;
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

int main()
{
    
}