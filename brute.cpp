#include<bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 5;
vector<int> adj1[MAX], adj2[MAX], values1[MAX], values2[MAX];
int par1[MAX], par2[MAX], st1[MAX], ed1[MAX], st2[MAX], ed2[MAX], node1[MAX], node2[MAX], T;
 
void dfs1(int u,int p = 0){
	par1[u] = p;
	node1[T] = u;
	st1[u] = T++;
	for(auto v : adj1[u]) if(v != p) dfs1(v, u);
	ed1[u] = T;
}
void dfs2(int u,int p = 0){
	par2[u] = p;
	node2[T] = u;
	st2[u] = T++;
	for(auto v : adj2[u]) if(v != p) dfs2(v, u);
	ed2[u] = T;
}
 
int cnt[MAX];
 
void solve(){
	int n, m;
	cin >> n >> m;
	for(int i = 1, x, y; i < n; i++) cin >> x >> y, adj1[x].push_back(y), adj1[y].push_back(x);
	for(int i = 1, x, y; i < m; i++) cin >> x >> y, adj2[x].push_back(y), adj2[y].push_back(x);
	int a, b;
	cin >> a >> b;
	for(int i = 1, x; i <= a; i++) cin >> x, values1[x].push_back(i);
	for(int i = 1, x; i <= b; i++) cin >> x, values2[x].push_back(i);
	dfs1(1);
	dfs2(1);
	int q;
	cin >> q;
	for(int i = 1; i <= q; i++){
		int u, v, ans = 0;
		cin >> u >> v;
		for(int j = st1[u]; j < ed1[u]; j++) for(auto x : values1[node1[j]]) cnt[x]++;
		for(int j = st2[v]; j < ed2[v]; j++) for(auto x : values2[node2[j]]) cnt[x]++, ans += (cnt[x] == 2);
		for(int j = st1[u]; j < ed1[u]; j++) for(auto x : values1[node1[j]]) cnt[x] = 0;
		for(int j = st2[v]; j < ed2[v]; j++) for(auto x : values2[node2[j]]) cnt[x] = 0;
		cout << ans << '\n';
	}	
}
 
int32_t main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
}
