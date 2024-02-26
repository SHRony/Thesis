#include<bits/stdc++.h>
using namespace std;
const int MAX = 5e4 + 5;
vector<int> adj1[MAX], adj2[MAX], values1[MAX], values2[MAX];
int pos1[MAX], pos2[MAX];
bitset<MAX> mask1[MAX];
bitset<MAX> dfs1(int u,int p = 0){
	for(auto v : adj1[u]) if(v != p) mask1[u] |= dfs1(v, u);
	return mask1[u];
}
bitset<MAX> mask2[MAX];
bitset<MAX> dfs2(int u,int p = 0){
	for(auto v : adj2[u]) if(v != p) mask2[u] |= dfs2(v, u);
	return mask2[u];
}
int ans[MAX];
void solve(){
	int n, m;
	cin >> n >> m;
	for(int i = 1, x, y; i < n; i++) cin >> x >> y, adj1[x].push_back(y), adj1[y].push_back(x);
	for(int i = 1, x, y; i < m; i++) cin >> x >> y, adj2[x].push_back(y), adj2[y].push_back(x);
	int a, b;
	cin >> a >> b;
	for(int i = 0; i < a; i++) cin >> pos1[i], mask1[pos1[i]].set(i);
	for(int i = 0; i < b; i++) cin >> pos2[i], mask2[pos2[i]].set(i);
	int q;
	cin >> q;
	vector<pair<int,int>> queries(q);
	dfs1(1);
	dfs2(1);
 
	for(auto &[u, v] : queries) cin >> u >> v, cout << ((mask1[u] & mask2[v]).count()) << '\n';
}
 
int32_t main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
}
