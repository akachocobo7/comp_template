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
#include <bitset>
#include <stack>
#include <assert.h>
#include <unordered_set>


using namespace std;
using ll = long long;
using ull = unsigned long long;

const ll INF = 1e16;
const ll MOD = 1e9 + 7;

#define REP(i, n) for(int i = 0; i < n; i++)





template<typename T>
auto make_v(int n){
    return vector<T>(n);
}

template<typename T, typename... Ints>
auto make_v(int n, Ints... m){
    auto v = make_v<T>(m...);
    return vector<decltype(v)>(n, v);
}