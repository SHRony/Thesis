#include<bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 5;
vector<int> adj1[MAX], adj2[MAX], values1[MAX], values2[MAX];
int pos1[MAX], pos2[MAX];
long long mask1[MAX];
long long dfs1(int u,int p = 0){
	for(auto v : adj1[u]) if(v != p) mask1[u] |= dfs1(v, u);
	return mask1[u];
}
long long mask2[MAX];
long long dfs2(int u,int p = 0){
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
	for(int i = 0; i < a; i++) cin >> pos1[i];
	for(int i = 0; i < b; i++) cin >> pos2[i];
	int q;
	cin >> q;
	vector<pair<int,int>> queries(q);
	for(auto &[u, v] : queries) cin >> u >> v;
	for(int i = 0; i < min(a, b); i += 60){
		for(int u = 1; u <= n; u++) mask1[u] = 0;
		for(int u = 1; u <= m; u++) mask2[u] = 0;
		for(int j = 0; j < 60 && i + j < min(a, b); j++) mask1[pos1[i + j]] |= (1LL << j), mask2[pos2[i + j]] |= (1LL << j);
		dfs1(1);
		dfs2(1);
		for(int qid = 0; qid < q; qid++){
			auto [u, v] = queries[qid];
			ans[qid] += __builtin_popcountll(mask1[u] & mask2[v]);
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
