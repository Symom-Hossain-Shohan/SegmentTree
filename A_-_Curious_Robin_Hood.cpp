#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mx = 1e5+1; 

ll ar[mx], tree[4*mx];

void buildTree(ll s, ll e, ll index)
{
    if(s==e) 
    {
        tree[index] = ar[s];
        return; 
    }
    else 
    {
        ll mid = (s+e)/2; 
        buildTree(s, mid, 2*index);
        buildTree(mid+1, e, 2*index+1);

        tree[index] = tree[2*index] + tree[2*index+1];
        return; 
    }
}

ll query(ll s, ll e, ll index, ll l, ll r)
{
    if(r<s or l>e) return 0; 
    else if(s>=l and e<=r) return tree[index];
    else 
    {
        ll mid  = (s+e)/2; 
        return query(s, mid, 2*index, l, r) + query(mid+1, e, 2*index+1, l, r); 
    }
}

void update(ll s, ll e, ll index, ll i, ll inc)
{
    if(i<s or i>e) return; 
    if(s==e)
    {
        tree[index] += inc; 
        return; 
    }
    else 
    {
        ll mid = (s+e)/2; 
        update(s, mid, 2*index, i, inc);
        update(mid+1, e, 2*index+1, i, inc);
        tree[index] = tree[2*index] + tree[2*index+1];
        return; 
    }
}


void solve()
{
    ll n, q; 
    cin >> n >> q; 
    for(int i=0;i<n;i++) cin >> ar[i];
    buildTree(0, n-1, 1);

    while(q--)
    {
        int ch; 
        cin >> ch; 
        if(ch==1)
        {
            ll i; 
            cin >> i; 
            ll x = query(0, n-1, 1, i, i); 
            cout << x << endl; 
            update(0, n-1, 1, i, -x);
        }
        else if(ch == 2)
        {
            ll i, v; 
            cin >> i >> v; 
            update(0, n-1, 1, i, v);
        }
        else 
        {
            ll i, j; 
            cin >> i >> j; 
            cout << query(0, n-1, 1, i, j) << endl; 
        }
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