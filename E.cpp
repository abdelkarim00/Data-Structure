#include <bits/stdc++.h>

using namespace std;
//+18

typedef long long ll;

const ll inf = 1<<30;

#define rep(i,n)    for(int i=0;i<n;i++)
#define siz(s  )    (int)(s.size())
#define one(n,i)    ((n>>i)&1)

const int MAXN = 200002;
int len;
int up[20][MAXN] ;
int tin [MAXN] ;
int tout[MAXN];
int tme;

void dfs(const vector<vector<int> > & tree, int u, int p) {
	tin[u] = tme++;
	up[0][u] = p;
	for (int i = 1; i < len; i++)
  		up[i][u] = up[i - 1][up[i - 1][u]];
	for (int i=0;i<tree[u].size();i++){
  		int v = tree[u][i];
  		if (v != p)
    		dfs(tree, v, u);
	}
	tout[u] = tme++;
}

void LcaSparseTable(const vector<vector<int> > & tree , int root) {
	int n = tree.size();
	len = 1;
	while ((1 << len) <= n) ++len;
	dfs(tree, root, root);
}

bool isParent(int parent, int child) {
	return tin[parent] <= tin[child] && tout[child] <= tout[parent];
}

int lca(int a, int b) {
	if (isParent(a, b))
  		return a;
	if (isParent(b, a))
  		return b;
	for (int i = len - 1; i >= 0; i--)
  		if (!isParent(up[i][a], b))
    		a = up[i][a];
	return up[0][a];
}
vector<vector<int> > adj;
vector<int> spr;
vector<pair<int,int> > outs,ins;
int dest[MAXN];
void predfs(int node, int p){
	for(int i=0;i<adj[node].size();i++){
		int v = adj[node][i];
		if(v!=p){
			dest[v] =  dest[node] + 1 ;
			predfs(v , node);
		}
	}
}
bool vis[MAXN];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	spr.resize(2*k);
	for(int i=0;i<2*k;i++)
		scanf("%d", &spr[i]);
	int u,v;
	adj.resize(n+1);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	LcaSparseTable(adj,1);
	for(int i=0;i<spr.size();i++){
		outs.push_back(make_pair(tout[spr[i]] , spr[i]));
		ins.push_back(make_pair(tin[spr[i]] , spr[i]));
	}
	sort(outs.begin(), outs.end());
	sort(ins.begin(),ins.end());
	int l = 0 , r = 0 ;
	ll ans = 0;
	
	predfs(1,1);
	while(l  < 2*k && r < 2*k){
		if(vis[outs[l].second]){
			l++;
			continue;
		}
		if(vis[ins[r].second]){
			r++;
			continue;
		}
		if(ins[r].second == outs[l].second){
			r++;
			continue;
		}
		int u = ins[r].second;
		int v = outs[l].second;
		int lc = lca(u,v);
		ans += dest[u] + dest[v] - 2 * dest[lc];
		vis[u] = 1;
		vis[v] = 1;
	}
	cout<<ans<<endl;
}

