#include<bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 5;
vector<int> adj1[MAX], adj2[MAX], values1[MAX], values2[MAX];
int T = 1;
int node_at[MAX];
 
 
 
 
 
 
struct segtree
{
	int N;
 
	// change vrtx combine and fokka based on problem
	struct vrtx
	{
		int val;
		vrtx(int x){
			val = x;
		}
		vrtx(){
			val = 0;
		}
	};
	vrtx fokka;
	vector<vrtx> tre;
	segtree(int n){
		N = n;
		tre.resize(4 * N);
	}
	vrtx combine(vrtx a,vrtx b){
		return vrtx(a.val + b.val);
	}
	void update(int n,int l,int r,int i,int val){
		if(i > r || i < l) return;
		if(l == r){
			tre[n].val += val;
			return ;
		}
		int mid = (l + r) / 2;
		update(2 * n, l, mid, i, val);
		update(2 * n + 1, mid + 1, r, i, val);
		tre[n] = combine(tre[2 * n], tre[2 * n + 1]);
	}
	vrtx query(int n,int l,int r,int i,int j){
		if(i > r || j < l) return fokka;
		if(i <= l && j >= r) return tre[n];
		int mid = (l + r) / 2;
		return combine(query(2 * n, l, mid, i, j), query(2 * n + 1, mid + 1, r, i, j));
	}
	int query(int l,int r){
		return query(1, 1, N, l, r).val;
	}
	void update(int i,int val){
		update(1, 1, N, i, val);
	}
} ds(MAX);
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
int pos_euler[MAX], st_euler[MAX], ed_euler[MAX];
void dfs_euler(int u,int p = 0){
	for(auto x : values2[u]) pos_euler[x] = T;
	node_at[st_euler[u] = T++] = u;
	for(auto v : adj2[u]) if(v != p) dfs_euler(v, u);
	ed_euler[u] = T;
}
 
 
 
int sz[MAX];
 
 
 
 
 
// calculates subtree size for each node of first tree
//u is the current node and p is its parent
// returns the subtree size of u
int dfs_sz(int u,int p = 0){
	sz[u] = 1;// initialize size with one
	for(auto v : adj1[u]) if(v != p) sz[u] += dfs_sz(v, u); // add size of each child v to the size of u
	return sz[u]; 
}
 
 
 
// returns the bigchild of u where p is the parent of u
int get_bigchild(int u,int p){
	int ret = -1;
	for(auto v : adj1[u]){
		if(v == p) continue;//v is the parent of u
		if(ret == -1 || sz[v] > sz[ret]) ret = v;// v is the first child or bigger than the current big child
	}
	return ret;
}
 
int dsu_T, dsu_node_at[MAX];
// the main dfs for dsu on tree
 
void add_range_to_ds(int st,int ed){
	for(int t = st; t < ed; t++) for(auto x : values1[dsu_node_at[t]]) if(pos_euler[x]) ds.update(pos_euler[x], 1);
}
 
void remove_range_from_ds(int st,int ed){
	for(int t = st; t < ed; t++) for(auto x : values1[dsu_node_at[t]]) if(pos_euler[x]) ds.update(pos_euler[x], -1);
}
 
vector<pair<int,int>> queries[MAX];
int ans[MAX];
void dfs_dsu(int u,int p = 0,bool to_keep = 0){
	int bigchild = get_bigchild(u, p); // calculates the bigchild of u
	int st = dsu_T++;//starting time for this subtree
	dsu_node_at[st] = u;
	for(auto v : adj1[u]) if(v != p && v != bigchild) dfs_dsu(v, u, 0); // calls the function for each child except bigchild and and cleans everything while returning
	int ed = dsu_T; // end time for this subtree excluding the bigchild
	if(~bigchild) dfs_dsu(bigchild, u, 1); //calls the function for the bigchild if exists and doesn't clean
	add_range_to_ds(st, ed); // add whole subtree except the bigchild to the ds
	for(auto [i, v] : queries[u]) ans[i] = ds.query(st_euler[v], ed_euler[v] - 1); // answer the queries
	if(!to_keep) remove_range_from_ds(st, dsu_T);
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
	dfs_euler(1);
	dfs_sz(1);
 
	// dfs1(1);
	// dfs2(1);
	int q;
	cin >> q;
	for(int i = 1; i <= q; i++){
		int u, v;
		cin >> u >> v;
		queries[u].push_back({i, v});
	}
	dfs_dsu(1);
	// return ;
	for(int i = 1; i <= q; i++) cout << ans[i] << "\n";
	// return ;
	
}
 
int32_t main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
}
