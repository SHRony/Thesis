#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> adj1, adj2, values1, values2;
vector<int> pos1, pos2;
vector<int> mask1;
int dfs1(int u,int p = 0){
	for(auto v : adj1[u]) if(v != p) mask1[u] |= dfs1(v, u);
	return mask1[u];
}
vector<int> mask2;
int dfs2(int u,int p = 0){
	for(auto v : adj2[u]) if(v != p) mask2[u] |= dfs2(v, u);
	return mask2[u];
}
vector<int> ans;
void solve(){
	int n, m;
	cin >> n >> m;
	adj1.resize(n + 1);
	adj2.resize(m + 1);
	values1.resize(n + 1);
	values2.resize(m + 1);
	mask1.resize(n + 1);
	mask2.resize(m + 1);
	for(int i = 1, x, y; i < n; i++) cin >> x >> y, adj1[x].push_back(y), adj1[y].push_back(x);
	for(int i = 1, x, y; i < m; i++) cin >> x >> y, adj2[x].push_back(y), adj2[y].push_back(x);
	int a, b;
	cin >> a >> b;
	pos1.resize(a + 1);
	pos2.resize(b + 1);
	for(int i = 0; i < a; i++) cin >> pos1[i];
	for(int i = 0; i < b; i++) cin >> pos2[i];
	int q;
	cin >> q;
	ans.resize(q + 1);
	vector<pair<int,int>> queries(q);
	for(auto &[u, v] : queries) cin >> u >> v;
	for(int i = 0; i < min(a, b); i += 31){
		for(int u = 1; u <= n; u++) mask1[u] = 0;
		for(int u = 1; u <= m; u++) mask2[u] = 0;
		for(int j = 0; j < 31 && i + j < min(a, b); j++) mask1[pos1[i + j]] |= (1 << j), mask2[pos2[i + j]] |= (1 << j);
		dfs1(1);
		dfs2(1);
		for(int qid = 0; qid < q; qid++){
			auto [u, v] = queries[qid];
			ans[qid] += __builtin_popcount(mask1[u] & mask2[v]);
		}
	}
	for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}
 
int32_t main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
}
