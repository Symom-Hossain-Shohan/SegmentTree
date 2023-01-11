#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mx = 1e5+1; 

ll ar[mx], tree[4*mx], prop[4*mx];

void update(int s, int e, int index, int l, int r, int inc)
{
    if(prop[index]!=0)
    {
        tree[index] += (e-s+1)*prop[index];
        if(s!=e)
        {
            prop[2*index] += prop[index];
            prop[2*index+1] += prop[index];
        }
        prop[index] = 0; 
        
    }
    if(r<s or l>e) return; 
    else if(s>=l and e<=r)
    {
        tree[index] += (e-s+1)*inc; 
        if(s!=e)
        {
            prop[2*index] += inc; 
            prop[2*index+1] += inc; 
        }
        return; 
    }
    else 
    {
        int mid = (s+e)/2; 
        update(s, mid, 2*index, l, r, inc);
        update(mid+1, e, 2*index+1, l, r, inc);
        tree[index] = tree[2*index] + tree[2*index+1];
        return; 
    }
}

ll query(int s, int e, int index, int l, int r)
{
    if(prop[index]!=0)
    {
        tree[index] += (e-s+1)*prop[index];
        if(s!=e)
        {
            prop[2*index] += prop[index];
            prop[2*index+1] += prop[index];
        }
        prop[index] = 0; 
    }
    if(r<s or l>e) return 0; 
    else if(s>=l and e<=r) return tree[index];
    else 
    {
        int mid = (s+e)/2; 
        return query(s, mid, 2*index, l, r) + query(mid+1, e, 2*index+1, l, r);
    }
}



void solve()
{
    ll n, q; 
    cin >> n >> q; 
    memset(tree, 0, sizeof(0));
    memset(prop, 0, sizeof(prop));
    while(q--)
    {
        int ch; 
        cin >> ch; 
        if(ch==0)
        {
            ll p, q, v; 
            cin >> p >> q >> v; 
            update(0, n-1, 1, p-1, q-1, v);
        }
        else 
        {
            ll p, q; 
            cin >> p >> q; 
            cout << query(0, n-1, 1, p-1, q-1) << endl; 
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
        solve();
    }
    return 0;
}