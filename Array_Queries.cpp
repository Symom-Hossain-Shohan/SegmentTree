#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mx = 1e5+1; 
ll ar[mx], tree[4*mx];

void buildTree(int s, int e, int index)
{
    if(s==e)
    {
        tree[index] = ar[s];
        return; 
    }
    else 
    {
        int mid = (s+e)/2; 
        buildTree(s, mid, 2*index);
        buildTree(mid+1, e, 2*index+1);

        tree[index] = min(tree[2*index], tree[2*index+1]);
        return; 
    }
}


ll query(ll s, ll e, ll index, ll l, ll r)
{
    if(r<s or l>e) return 1e18; 
    else if(s>=l and e<=r) return tree[index];
    else 
    {
        ll mid = (s+e)/2; 
        return min(query(s, mid, 2*index, l, r), query(mid+1, e, 2*index+1, l, r)); 
    }
}


void solve()
{
    ll n, q; 
    cin >> n >> q; 
    for(int i = 0;i<n;i++) cin >> ar[i];

    buildTree(0, n-1, 1);
    while(q--)
    {
        ll i, j; 
        cin >> i >> j; 
        cout << query(0, n-1, 1, i-1, j-1) << endl; 
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll tc = 1;
    cin >> tc;
    for (ll t = 1; t <= tc; t++)
    {
        cout << "Case " << t << ":\n";
        solve();
    }
    return 0;
}