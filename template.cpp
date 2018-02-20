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
	vector<ll> par;
	vector<ll> rank;
public:
	void init(ll n);
	ll find(ll x);
	void unite(ll x, ll y);
	bool same(ll x, ll y);
};

// 初期化
void unionfind::init(ll n) {
	for (ll i = 0; i < n; i++) {
		par.push_back(i);
		rank.push_back(0);
	}
}

// 木の根を求める
ll unionfind::find(ll x) {
	if (par[x] == x) {
		return x;
	}
	else {
		return par[x] = find(par[x]);
	}
}

// xとyの属する集合を併合
void unionfind::unite(ll x, ll y) {
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
bool unionfind::same(ll x, ll y) {
	return find(x) == find(y);
}
/* unionfind end*/

int main()
{
    
}