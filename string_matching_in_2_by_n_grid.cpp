#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define int long long
const int MAX = 4e5 + 5;
struct AC{
	int N, P;
	const int A = 26;
	vector<vector<int>> next;
	vector<int> link, out_link;
	vector<vector<int>> out;
	AC():N(0), P(0){node();}
	int node(){
		next.emplace_back(A, 0);
		link.emplace_back(0);
		out_link.emplace_back(0);
		out.emplace_back(0);
		return N++;
	}
	inline int get(char c){
		return c - 'a';
	}
	int add_pattern(const string T){
		int u = 0;
		for(auto c : T){
			if(!next[u][get(c)]) next[u][get(c)] = node();
			u = next[u][get(c)];
		}
		out[u].push_back(P);
		return P++;
	}
	void compute(){
		queue<int> q;
		for(q.push(0); !q.empty();){
			int u = q.front();
			q.pop();
			for(int c = 0; c < A; c++){
				int v = next[u][c];
				if(!v) next[u][c] = next[link[u]][c];
				else{
					link[v] = u ? next[link[u]][c] : 0;
					out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
					q.push(v);
				}
			}
		}
	}
	int advance(int u, char c){
		while(
u && !next[u][get(c)]) u = link[u];
		u = next[u][get(c)];
		return u;
	}
};
struct BIT{
	vector<long long> tre;
	long long n;
	BIT(){n = 0;}
	BIT(long long _n){
		n = _n + 1;
		tre.resize(n + 1);
	}
	void update(long long u,long long val){
		while(u <= n) tre[u] += val, u += (u & (-u));
	}
	long long query(long long i){
		long long ret = 0;
		while(i) ret += tre[i], i -= i & (-i);
		return ret;
	}
	long long query(long long l,long long r){
		return query(r) - query(l - 1);
	}
} ds(MAX);
 
 
 
 
 
 
 
vector<int> adj1[MAX], adj2[MAX], indexes_at[MAX];
int pos_of_index[MAX];
vector<pair<int,int>> queries[MAX];
int st_euler[MAX], en_euler[MAX], node_at[MAX], T;
int ans[MAX];
void dfs_euler(int u){
	node_at[st_euler[u] = T++] = u;
	for(auto v : adj2[u]){
		dfs_euler(v);
	}
	en_euler[u] = T;
}
int sub_sz[MAX];
int dfs_sz(int u){
	sub_sz[u] = indexes_at[u].size();
	for(auto v : adj1[u]) sub_sz[u] += dfs_sz(v);
	return sub_sz[u];
}
 
int flattened_indexes[MAX], T_dsu;
 
void dfs_dsu(int u,int baad = 1){
	int st = T_dsu;
	for(auto i : indexes_at[u]) flattened_indexes[T_dsu++] = i;
	int bigchild = -1;
	for(auto v : adj1[u]) if(bigchild == -1 || sub_sz[v] > sub_sz[bigchild]) bigchild = v;
	for(auto v : adj1[u]) if(v != bigchild) dfs_dsu(v, 1);
	int ed = T_dsu;
	if(~bigchild) dfs_dsu(bigchild, 0);
	for(int i = st; i < ed; i++){
		ds.update(st_euler[pos_of_index[flattened_indexes[i]]], 1);
	}
	for(auto [i, x] : queries[u]) ans[i] += ds.query(st_euler[x], en_euler[x] - 1);
	if(baad) for(int i = st; i < T_dsu; i++) ds.update(st_euler[pos_of_index[flattened_indexes[i]]], -1);
}
 
 
void solve(){
	T = T_dsu = 1;
	string s, t;
	cin >> s >> t;
	t = "*" + t;
	s = s + "#";
	int q;
	cin >> q;
	vector<string> q_pats(q);
	AC aho1, aho2;
	for(auto &pat : q_pats){
		cin >> pat;
		aho1.add_pattern(pat);
		reverse(pat.begin(), pat.end());
		aho2.add_pattern(pat);
		reverse(pat.begin(), pat.end());
	}
	aho1.compute();
	aho2.compute();
	for(int i = 1; i < aho1.N; i++) adj1[aho1.link[i]].push_back(i);
	for(int i = 1; i < aho2.N; i++) adj2[aho2.link[i]].push_back(i);
 
 
	indexes_at[0].push_back(0);
	int cur = 0;
	for(int i = 0; i < s.size(); i++){
		cur = aho1.advance(cur, s[i]);
		indexes_at[cur].push_back(i + 1);
	}
	cur = 0;
	pos_of_index[t.size()] = 0;
	for(int i = (int)t.size() - 1; i >= 0; i--){
		cur = aho2.advance(cur, t[i]);
		pos_of_index[i] = cur;
	}
 
	for(int i = 0; i < q; i++){
		ans[i] = 0;
		string pat = q_pats[i];
		vector<int> A, B;
 
 
 
 
		int cur = 0;
		A.push_back(0);
		for(auto c : pat) cur = aho1.advance(cur, c), A.push_back(cur);
		cur = 0;
		B.push_back(0);
		reverse(pat.begin(), pat.end());
		for(auto c : pat) cur = aho2.advance(cur, c), B.push_back(cur);
 
		reverse(B.begin(), B.end());
		reverse(pat.begin(), pat.end());
		for(int j = 1; j + 1 < A.size(); j++) queries[A[j]].push_back({i, B[j]});
 
	}
 
	dfs_euler(0);
	dfs_sz(0);
	dfs_dsu(0);
	for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}
int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	// cin >> t;
	while(t--) solve();
	return 0; 
}
